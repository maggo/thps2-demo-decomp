#!/usr/bin/env python3
"""Compile every translation unit and compare each function with the original.

    python3 verify.py --exe SLUS_900.86 --sym MAIN.SYM [--include PSYQ_INCLUDE_DIR]

Pipeline per TU (flags from tools/tu_flags.json):
    cpp -nostdinc -> egcs 1.1.1 cc1plus/cc1 -> DMPSX GTE rewrite
    -> maspsx (ASPSX 2.86) -> mips-linux-gnu-as

A function matches when its instructions equal the original's, ignoring the
bits a linker would fill in (relocated fields). Function boundaries come from
MAIN.SYM. Neither disc file is part of this repository.
"""
import argparse, bisect, functools, json, os, re, struct, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT / 'tools'))
import sym
from dmpsx_table import DMPSX_TBL
from psyq_lifecycle import LifecycleRecordError, lower_psyq_lifecycle_records
try:
    from elftools.elf.elffile import ELFFile
except ImportError:
    sys.exit('pyelftools is required: python3 -m pip install pyelftools')

sys.path.insert(0, str(ROOT / 'toolchain'))
from verify_egcs_1_1_1 import VerificationError, verify_directory


# ---------------------------------------------------------------- per-TU flags
class Settings:
    """Per-TU compiler settings from tools/tu_flags.json."""
    def __init__(self):
        t = json.loads((ROOT / 'tools' / 'tu_flags.json').read_text())
        self.default, self.units = t['default'], t['units']

    def get(self, tu):
        unit = self.units.get(tu, {})
        flags = unit.get('flags', self.default['flags'])
        gp = unit.get('gp', self.default['gp'])
        cc_gp = unit.get('cc_gp', gp)
        return flags, str(gp), str(cc_gp)


# ------------------------------------------------------------------- DMPSX GTE
def dmpsx_word(w):
    """Sony DMPSX rewrote INLINE_C.H placeholder words into COP2 commands."""
    base = DMPSX_TBL.get((w & 0x3ffc0) >> 6)
    if base is None:
        raise RuntimeError(f'unknown DMPSX placeholder {w:#x}')
    return (((w & 0x40000) >> 18 << 10) | ((w & 0x180000) >> 19 << 13) | ((w & 0x600000) >> 21 << 15)
            | ((w & 0x1800000) >> 23 << 17) | ((w & 0x2000000) >> 25 << 19) | base)


def dmpsx(asm):
    out, in_text = [], True
    for line in asm.split('\n'):
        st = line.strip()
        if st.startswith(('.text', '.section .text', '.section\t.text')):
            in_text = True
        elif st.startswith(('.data', '.rdata', '.sdata', '.bss', '.sbss', '.section')):
            in_text = False
        if in_text:
            def sub(m):
                w = int(m[2], 0)
                return f'{m[1]}0x{dmpsx_word(w):08x}' if (w & 0xfc00003f) == 0x3f else m[0]
            line = re.sub(r'(\.word\s+)(0x[0-9a-fA-F]+|\d+)\b', sub, line)
        out.append(line)
    return '\n'.join(out)


# ----------------------------------------------------------------------- build
class Toolchain:
    def __init__(self, a):
        self.cc_dir, self.maspsx, self.include = a.cc_dir, a.maspsx, a.include
        self.out, self.settings = a.out, Settings()

    def build(self, tu):
        """Compile one source file -> object path. Raises RuntimeError on failure."""
        n, is_c = tu.stem, tu.suffix == '.c'
        flags, gp, cc_gp = self.settings.get(n)
        i, s, ms, o = (self.out / f'{n}{e}' for e in ('.i', '.s', '.ms', '.o'))

        def run(cmd, what):
            r = subprocess.run(cmd, capture_output=True, text=True)
            if r.returncode:
                err = [l for l in (r.stderr + r.stdout).splitlines() if 'warning' not in l]
                raise RuntimeError(f'{n}: {what} failed: ' + ' | '.join(err[:5]))
            return r

        run(['cpp', '-E', '-nostdinc', f'-I{tu.parent}', f'-I{self.include}'] + (['-lang-c'] if is_c else [])
            + [str(tu), '-o', str(i)], 'cpp')
        cc = str(self.cc_dir / ('cc1' if is_c else 'cc1plus'))
        run([cc, '-quiet'] + flags.split() + [f'-G{cc_gp}', '-msoft-float', '-mno-abicalls',
                                              str(i), '-o', str(s)], 'cc1')
        s.write_text(dmpsx(s.read_text()))
        m = run(['python3', str(self.maspsx / 'maspsx.py'), '--aspsx-version=2.86', f'-G{gp}', str(s)], 'maspsx')
        try:
            translated = lower_psyq_lifecycle_records(m.stdout)
        except LifecycleRecordError as error:
            raise RuntimeError(f'{n}: lifecycle registration failed: {error}') from error
        # ASPSX ignores section flags; GNU as rejects conflicting ones
        ms.write_text(re.sub(r'^(\s*\.section\s+\.rdata)\s*,.*$', r'\1,"a"', translated, flags=re.M))
        run(['mips-linux-gnu-as', '-EL', '-march=r3000', '-mtune=r3000', '-no-pad-sections', '-O1',
             f'-G{gp}', str(ms), '-o', str(o)], 'as')
        return o


# ------------------------------------------------------------- object / compare
RELOC_MASK = {4: 0xfc000000, 5: 0xffff0000, 6: 0xffff0000, 7: 0xffff0000}  # J26, HI16, LO16, GPREL16


@functools.lru_cache(maxsize=None)
def obj_index(path):
    """Parse one object once -> {symbol name: (words, {byte offset: mask of compared bits})}
    for every function-like symbol in an executable section (first definition wins)."""
    out = {}
    with open(path, 'rb') as fh:
        e = ELFFile(fh)
        secs = list(e.iter_sections())
        syms = [x for x in e.get_section_by_name('.symtab').iter_symbols()
                if x['st_info']['type'] in ('STT_FUNC', 'STT_NOTYPE') and isinstance(x['st_shndx'], int)
                and x['st_shndx'] < len(secs) and secs[x['st_shndx']]['sh_flags'] & 4]
        by_sec = {}
        for x in syms:
            if x.name:
                by_sec.setdefault(x['st_shndx'], []).append(x['st_value'])
        for idx in by_sec:
            by_sec[idx].sort()
        sec_data, sec_relocs = {}, {}
        for me in syms:
            if not me.name or me.name in out:
                continue
            idx, start = me['st_shndx'], me['st_value']
            text = secs[idx]
            if idx not in sec_data:
                sec_data[idx] = text.data()
                rel = e.get_section_by_name('.rel' + text.name)
                sec_relocs[idx] = [(r['r_offset'], r['r_info_type']) for r in rel.iter_relocations()] if rel else []
            starts = by_sec[idx]
            later = starts[bisect.bisect_right(starts, start):]
            end = start + me['st_size'] if me['st_size'] else (later[0] if later else text['sh_size'])
            masks = {off - start: RELOC_MASK.get(typ, 0xffffffff)
                     for off, typ in sec_relocs[idx] if start <= off < end}
            out[me.name] = (words(sec_data[idx][start:end]), masks)
    return out


def obj_func(path, name):
    """-> (words, {byte offset: mask of bits that are compared}) or None"""
    return obj_index(path).get(name)


def words(b):
    w = list(struct.unpack(f'<{len(b) // 4}I', b[:len(b) // 4 * 4]))
    while w and w[-1] == 0:      # trailing alignment padding
        w.pop()
    return w


def align_key(w):
    """Coarse instruction identity for alignment: ignore I/J-type immediates."""
    op = w >> 26
    if op in (2, 3):
        return w & 0xfc000000
    return w >> 16 if op not in (0, 0x12) else w


def compare(target, mine, masks):
    """objdiff-style alignment -> (rows, score). rows: (tag, target idx, mine idx) with tag
    ' ' equal, '!' changed, '<' only in target, '>' only in ours; score = non-equal rows."""
    import difflib
    sm = difflib.SequenceMatcher(None, [align_key(w) for w in target], [align_key(w) for w in mine],
                                 autojunk=False)
    rows = []
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        for k in range(max(i2 - i1, j2 - j1)):
            ti = i1 + k if i1 + k < i2 else None
            mi = j1 + k if j1 + k < j2 else None
            if ti is not None and mi is not None:
                m = masks.get(mi * 4, 0xffffffff)
                rows.append((' ' if (target[ti] & m) == (mine[mi] & m) else '!', ti, mi))
            else:
                rows.append(('<' if ti is not None else '>', ti, mi))
    return rows, sum(r[0] != ' ' for r in rows)


# ------------------------------------------------------------------------ main
def tu_candidates(funcs, f, src):
    """Source files that may define f: its own TU, then neighbouring owners
    (header-inline functions are emitted into whichever TU includes the header)."""
    i = funcs.index(f)
    order = [f]
    for d in (-1, 1):
        k = i + d
        while 0 <= k < len(funcs) and not funcs[k]['file'].upper().endswith(('.CPP', '.C')):
            order.append(funcs[k])
            k += d
        if 0 <= k < len(funcs):
            order.append(funcs[k])
    out = []
    for g in order:
        b = os.path.splitext(g['file'].split('\\')[-1])[0]
        for p in (src / f'{b}.cpp', src / f'{b}.c', src / f'{b}_H.cpp'):
            if p.exists() and p not in out:
                out.append(p)
    return out


def aliases(name, addr):
    """Names the sources may use for a SYM function (private copies, unmangled statics)."""
    out = [name]
    if name.startswith('_._'):
        out += [f'__DOT__{name[3:]}_{addr:08X}', f'__DOT__{name[3:]}']
    if '__F' in name and not name.startswith('__'):
        out.append(name.split('__F')[0])
    return out


def resolve_include(a):
    if a.include:
        return Path(a.include)
    r = subprocess.run([sys.executable, str(ROOT / 'tools' / 'psyq_sdk_headers.py'), '--check',
                        '--print-include-root'], capture_output=True, text=True)
    if r.returncode:
        sys.exit('Psy-Q headers not found or not verified (run setup.sh, or pass --include):\n' + r.stderr)
    return Path(r.stdout.strip())


def main():
    env = os.environ.get
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--exe', default=env('THPS_EXE', 'original/SLUS_900.86'), help='original PS-EXE [$THPS_EXE]')
    ap.add_argument('--sym', default=env('THPS_SYM', 'original/MAIN.SYM'), help='original MAIN.SYM [$THPS_SYM]')
    ap.add_argument('--src', type=Path, default=ROOT / 'src')
    ap.add_argument('--include', default=env('PSYQ_INCLUDE'), help='Psy-Q 4.6 INCLUDE dir [$PSYQ_INCLUDE]')
    ap.add_argument('--cc-dir', type=Path, default=Path(env('CC_DIR', ROOT / 'toolchain/gcc-2.91.60-psx')),
                    help='dir with cc1 and cc1plus [$CC_DIR]')
    ap.add_argument('--skip-cc-hash', action='store_true',
                    help='do not require the stock compiler hashes (e.g. a native rebuild)')
    ap.add_argument('--maspsx', type=Path, default=Path(env('MASPSX_DIR', ROOT / 'toolchain/maspsx')))
    ap.add_argument('--out', type=Path, default=ROOT / 'out', help='scratch dir for build products')
    ap.add_argument('-j', '--jobs', type=int, default=os.cpu_count() or 1)
    ap.add_argument('--func', help='show the aligned instruction diff of one function (mangled name)')
    ap.add_argument('--tu', action='append', metavar='NAME',
                    help='only build and check this translation unit (e.g. DB; repeatable)')
    ap.add_argument('--report', type=Path,
                    help='refresh an existing objdiff report after a complete canonical match')
    a = ap.parse_args()

    if a.jobs < 1:
        ap.error('--jobs must be a positive integer')
    if a.report and (a.func or a.tu or a.skip_cc_hash):
        ap.error('--report requires a complete run with the pinned compiler')
    if a.report and not a.report.is_file():
        ap.error(f'report template not found: {a.report}')

    for p, what in ((a.exe, '--exe'), (a.sym, '--sym')):
        if not Path(p).is_file():
            sys.exit(f'{what}: {p} not found (supply your own disc files)')
    for name in ('cc1', 'cc1plus'):
        if not (a.cc_dir / name).is_file():
            sys.exit(f'{a.cc_dir / name} missing: run setup.sh')
    if not a.skip_cc_hash:
        try:
            compiler_identity = verify_directory(a.cc_dir)
        except VerificationError as error:
            sys.exit(str(error))
    else:
        print('NONCANONICAL: compiler identity check skipped; report publication disabled.', file=sys.stderr)
    a.include = resolve_include(a)
    a.out.mkdir(parents=True, exist_ok=True)

    funcs = sym.functions(a.sym)
    if not funcs:
        sys.exit('MAIN.SYM contains no function ranges')
    if a.func and not any(f['name'] == a.func for f in funcs):
        sys.exit(f'unknown function: {a.func}')
    exe = Path(a.exe).read_bytes()
    t_addr, t_size = struct.unpack_from('<II', exe, 0x18)
    text = exe[0x800:0x800 + t_size]

    tc = Toolchain(a)
    tus = sorted(set(a.src.glob('*.cpp')) | set(a.src.glob('*.c')))
    if a.tu:
        wanted = {t.upper() for t in a.tu}
        unknown = wanted - {t.stem.upper() for t in tus}
        if unknown:
            sys.exit(f'unknown translation unit(s): {", ".join(sorted(unknown))}')
        tus = [t for t in tus if t.stem.upper() in wanted]
    if a.func:   # only the sources that can define this function
        f = next(f for f in funcs if f['name'] == a.func)
        tus = [t for t in tus if t in set(tu_candidates(funcs, f, a.src))]
    objs, failed = {}, {}

    def one(tu):
        try:
            objs[tu] = tc.build(tu)
        except RuntimeError as e:
            failed[tu] = str(e)
    with ThreadPoolExecutor(a.jobs) as ex:
        list(ex.map(one, tus))
    for tu, msg in sorted(failed.items()):
        print('BUILD FAIL', msg, file=sys.stderr)
    print(f'compiled {len(objs)}/{len(tus)} translation units')

    per_tu, bad, matched = {}, [], set()
    for f in funcs:
        if a.func and f['name'] != a.func:
            continue
        if a.tu and os.path.splitext(f['file'].split('\\')[-1])[0].upper() not in wanted:
            continue
        got = None
        for tu in tu_candidates(funcs, f, a.src):
            if tu in objs:
                for n in aliases(f['name'], f['start']):
                    got = obj_func(objs[tu], n)
                    if got:
                        break
            if got:
                break
        tu_name = os.path.splitext(f['file'].split('\\')[-1])[0]
        ok_tot = per_tu.setdefault(tu_name, [0, 0])
        ok_tot[1] += 1
        off = f['start'] - t_addr
        target = words(text[off:off + f['size']])
        if got is None:
            bad.append((f['name'], tu_name, 'missing', None))
            continue
        mine, masks = got
        rows, score = compare(target, mine, masks)
        if score == 0:
            ok_tot[0] += 1
            matched.add((f['name'], f['start']))
        else:
            bad.append((f['name'], tu_name, f'score {score}', (target, mine, rows)))
        if a.func:
            for tag, ti, mi in rows:
                t = f'{target[ti]:08x}' if ti is not None else '        '
                m = f'{mine[mi]:08x}' if mi is not None else '        '
                print(f'{tag} {t} | {m}')

    if not a.func:
        for tu_name, (ok, tot) in sorted(per_tu.items()):
            print(f'{tu_name:<16}{ok:>5}/{tot:<5}{"" if ok == tot else "  <-- " + str(tot - ok) + " differ"}')
    for name, tu_name, why, _ in bad:
        print(f'MISMATCH {name} ({tu_name}): {why}')
    ok = sum(v[0] for v in per_tu.values())
    tot = sum(v[1] for v in per_tu.values())
    print(f'{ok}/{tot} functions match exactly')
    if failed or bad:
        sys.exit(1)
    if not a.skip_cc_hash:
        try:
            if verify_directory(a.cc_dir) != compiler_identity:
                sys.exit('compiler identity changed during verification')
        except VerificationError as error:
            sys.exit(str(error))
    if a.report:
        refresh_report(a.report, funcs, matched)


def refresh_report(path, funcs, matched):
    """Publish only a fully rebuilt, fully matching set with the template's exact coverage."""
    from collections import Counter, defaultdict
    report = json.loads(path.read_text())
    expected = {(f['name'], f['start']) for f in funcs}
    if matched != expected:
        sys.exit('report requires every tracked function to match; report unchanged')
    grouped = defaultdict(list)
    for f in funcs:
        stem, extension = os.path.splitext(f['file'].split('\\')[-1])
        grouped[stem + ('_H' if extension.upper() not in ('.CPP', '.C') else '')].append(f)
    if report.get('version') != 2 or {u['name'] for u in report['units']} != set(grouped):
        sys.exit('report template units disagree with MAIN.SYM; report unchanged')
    corrected = 0
    for unit in report['units']:
        functions = unit.get('functions', [])
        originals = grouped[unit['name']]
        if Counter(f['name'] for f in functions) != Counter(f['name'] for f in originals):
            sys.exit(f'report function coverage disagrees in {unit["name"]}; report unchanged')
        by_name = defaultdict(list)
        for f in originals:
            by_name[f['name']].append(f)
        for f in functions:
            original = by_name[f['name']].pop(0)
            corrected += int(f['address']) != original['start']
            f.update(address=str(original['start']), size=str(original['size']))
    entries = [f for u in report['units'] for f in u.get('functions', [])]
    if len(entries) != len(expected) or {(f['name'], int(f['address'])) for f in entries} != expected:
        sys.exit('report does not uniquely cover MAIN.SYM; report unchanged')
    total_code = 0
    for unit in report['units']:
        functions = unit.get('functions', [])
        size = sum(int(f['size']) for f in functions)
        for f in functions:
            f['fuzzy_match_percent'] = 100.0
        unit.setdefault('metadata', {})['complete'] = True
        unit['measures'].update(total_code=str(size), matched_code=str(size),
            complete_code=str(size), total_functions=len(functions), matched_functions=len(functions),
            fuzzy_match_percent=100.0, matched_code_percent=100.0,
            complete_code_percent=100.0, matched_functions_percent=100.0)
        total_code += size
    report['measures'].update(total_code=str(total_code), matched_code=str(total_code),
        complete_code=str(total_code), total_functions=len(entries), matched_functions=len(entries),
        total_units=len(report['units']), fuzzy_match_percent=100.0, matched_code_percent=100.0,
        complete_code_percent=100.0, matched_functions_percent=100.0)
    temporary = path.with_suffix(path.suffix + '.tmp')
    temporary.write_text(json.dumps(report, indent=1) + '\n')
    temporary.replace(path)
    print(f'Report refreshed: {len(entries)}/{len(entries)} across {len(report["units"])} units')
    if corrected:
        print(f'Corrected {corrected} inline-copy addresses from MAIN.SYM')


if __name__ == '__main__':
    main()
