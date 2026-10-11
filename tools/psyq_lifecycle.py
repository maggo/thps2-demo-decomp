"""Lower the stock PSX GCC constructor/destructor stabs records for GNU as.

ASPSX consumes these N_SETT (22) records as runtime registrations. GNU as keeps
ordinary .stabs in debug sections, so its ELF path needs allocatable table words
with relocations to the compiler-generated functions instead.
"""

import re


class LifecycleRecordError(ValueError):
    """A lifecycle registration cannot be translated without ambiguity."""


_RECORD = re.compile(
    r'^\s*\.stabs\s+"___(CTOR|DTOR)_LIST__"\s*,\s*22\s*,\s*0\s*,\s*0\s*,'
    r'\s*([A-Za-z_$][A-Za-z0-9_.$]*)\s*(?:#.*)?$'
)
_MAGIC = re.compile(r'^\s*\.stabs\s+"___(?:CTOR|DTOR)_LIST__"')
_SECTION = re.compile(r'^\s*\.(section|pushsection)\s+([^\s,]+)')
_WORD = re.compile(r'^\s*\.word\s+([^#]+?)(?:\s*#.*)?$')


def lower_psyq_lifecycle_records(assembly: str) -> str:
    """Replace only valid Sony lifecycle records with relocated runtime words.

    Existing explicit registrations are accepted only when their complete word
    lists equal the emitted records for that section. Mismatches and repeated
    records fail visibly instead of silently duplicating startup/shutdown calls.
    Ordinary stabs records and inputs without lifecycle records are untouched.
    """
    lines = assembly.splitlines(keepends=True)
    if not any(_MAGIC.match(line) for line in lines):
        return assembly
    registrations = {'.ctors': [], '.dtors': []}
    explicit = {'.ctors': [], '.dtors': []}
    kept = []
    section = '.text'
    stack = []
    for line_number, line in enumerate(lines, 1):
        record = _RECORD.fullmatch(line.rstrip('\r\n'))
        if record:
            target = '.ctors' if record[1] == 'CTOR' else '.dtors'
            if record[2] in registrations[target]:
                raise LifecycleRecordError(
                    f'line {line_number}: duplicate {target} record for {record[2]}'
                )
            registrations[target].append(record[2])
            continue
        if _MAGIC.match(line):
            raise LifecycleRecordError(
                f'line {line_number}: malformed PSX lifecycle record: {line.strip()}'
            )
        directive = _SECTION.match(line)
        if directive:
            if directive[1] == 'pushsection':
                stack.append(section)
            section = directive[2]
        elif line.strip() == '.popsection':
            if not stack:
                raise LifecycleRecordError(f'line {line_number}: unmatched .popsection')
            section = stack.pop()
        elif line.strip() in ('.text', '.data', '.sdata', '.bss', '.sbss', '.rdata'):
            section = line.strip()
        if section in explicit:
            word = _WORD.match(line)
            if word:
                explicit[section].extend(value.strip() for value in word[1].split(','))
        kept.append(line)
    if not any(registrations.values()):
        return assembly
    result = ''.join(kept)
    for section, symbols in registrations.items():
        if not symbols:
            continue
        if explicit[section]:
            if explicit[section] != symbols:
                raise LifecycleRecordError(
                    f'{section}: explicit registrations {explicit[section]!r} '
                    f'differ from compiler records {symbols!r}'
                )
            continue
        result += f'\n.pushsection {section},"aw",@progbits\n.align 2\n'
        result += ''.join(f'.word {symbol}\n' for symbol in symbols)
        result += '.popsection\n'
    return result
