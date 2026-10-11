#!/usr/bin/env python3
"""Prepare the Psy-Q 4.6 headers for a case-sensitive file system.

The SDK ships DOS-style upper-case names (LIBGTE.H) but its headers include each
other in lower case (<sys/types.h>). --prepare mirrors SDK/INCLUDE into
SDK/.casefold-include with symlinks under both spellings; --check (the default)
confirms the mirror is current and, with --print-include-root, prints its path.

Headers are compared with tools/psyq_4_6_headers.sha256 (the DTL-S2360 release)
and differences are reported as warnings: verify.py reaching 1646/1646 is what
proves a header set, and the set used for the published result differs from the
manifest in six files (see the README).

    python3 tools/psyq_sdk_headers.py --prepare [--sdk-root DIR]
    python3 tools/psyq_sdk_headers.py --check --print-include-root
"""
import argparse
import hashlib
import shutil
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
MANIFEST = ROOT / 'tools' / 'psyq_4_6_headers.sha256'
VIEW = '.casefold-include'


def headers(include):
    return sorted(p.relative_to(include) for p in include.rglob('*') if p.is_file())


def view_entries(include):
    """{view path: source path} for the original and the lower-case spelling of every file."""
    out = {}
    for rel in headers(include):
        for name in (rel, Path(str(rel).lower())):
            out[name] = include / rel
    return out


def manifest_warnings(include):
    warnings = []
    for line in MANIFEST.read_text().splitlines():
        if not line or line.startswith('#'):
            continue
        digest, rel = line.split(None, 1)
        path = include / rel
        if not path.is_file():
            warnings.append(f'missing {rel}')
        elif hashlib.sha256(path.read_bytes()).hexdigest() != digest.lower():
            warnings.append(f'differs from Psy-Q 4.6: {rel}')
    return warnings


def view_is_current(view, include):
    return view.is_dir() and all((view / name).resolve() == src.resolve()
                                 for name, src in view_entries(include).items())


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    mode = ap.add_mutually_exclusive_group()
    mode.add_argument('--check', action='store_true', help='confirm the include view (default)')
    mode.add_argument('--prepare', action='store_true', help='(re)create the include view')
    ap.add_argument('--sdk-root', type=Path, default=ROOT / 'toolchain' / 'psyq-4.6-sdk')
    ap.add_argument('--print-include-root', action='store_true', help='print only the include path')
    a = ap.parse_args()

    include, view = a.sdk_root / 'INCLUDE', a.sdk_root / VIEW
    if not include.is_dir():
        sys.exit(f'Psy-Q headers not found: put the SDK INCLUDE directory at {include}')
    if a.prepare:
        if view.exists():
            shutil.rmtree(view)
        for name, src in view_entries(include).items():
            (view / name).parent.mkdir(parents=True, exist_ok=True)
            if not (view / name).exists():
                (view / name).symlink_to(src.resolve())
    elif not view_is_current(view, include):
        sys.exit('Psy-Q include view missing or stale: run setup.sh '
                 '(or tools/psyq_sdk_headers.py --prepare)')

    for w in manifest_warnings(include):
        print('warning:', w, file=sys.stderr)
    print(view if a.print_include_root else f'Psy-Q include view ready: {view}')


if __name__ == '__main__':
    main()
