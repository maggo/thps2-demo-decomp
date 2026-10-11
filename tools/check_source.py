#!/usr/bin/env python3
"""Source checks that need no disc files (run in CI and before committing):

- src/SQRTTAB.inc is what tools/generate_sqrttab.py produces;
- every matching workaround (register pin, empty asm barrier, asm-name alias)
  carries a FIXME(match) comment on its line or just above it;
- the counts stated in README.md equal the counts in the source.

    python3 tools/check_source.py
"""
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
PIN = re.compile(r'register [^;]*asm\("\$[0-9a-z]+"\)')
BARRIER = re.compile(r'(?:__)?asm(?:__)?(?:\s+(?:volatile|__volatile__))?\s*\(\s*""')
ALIAS = re.compile(r'asm\("[A-Za-z_][A-Za-z0-9_.$]*"\)')
MARKER_WINDOW = 6   # lines above a workaround that may hold its FIXME(match)


def workarounds():
    counts = {'pins': 0, 'barriers': 0, 'aliases': 0}
    unmarked = []
    for path in sorted((ROOT / 'src').glob('*.*')):
        lines = path.read_text(errors='ignore').split('\n')
        for i, line in enumerate(lines):
            kinds = [k for k, rx in (('pins', PIN), ('barriers', BARRIER), ('aliases', ALIAS))
                     if rx.search(line)]
            for k in kinds:
                counts[k] += len({'pins': PIN, 'barriers': BARRIER, 'aliases': ALIAS}[k].findall(line))
            if kinds and not any('FIXME(match)' in x for x in lines[max(0, i - MARKER_WINDOW):i + 1]):
                unmarked.append(f'src/{path.name}:{i + 1}')
    return counts, unmarked


def readme_counts():
    text = ' '.join((ROOT / 'README.md').read_text().split())
    m = re.search(r'contain (\d+) register pins.*?(\d+) empty `asm\(""\)` scheduling constraints'
                  r' and (\d+) asm-name aliases', text)
    return dict(zip(('pins', 'barriers', 'aliases'), map(int, m.groups()))) if m else None


def main():
    failures = []
    r = subprocess.run([sys.executable, str(ROOT / 'tools' / 'generate_sqrttab.py'), '--check'],
                       capture_output=True, text=True)
    if r.returncode:
        failures.append(r.stderr.strip() or r.stdout.strip())
    counts, unmarked = workarounds()
    if unmarked:
        failures.append('workarounds without a FIXME(match) comment: ' + ', '.join(unmarked))
    stated = readme_counts()
    if stated != counts:
        failures.append(f'README.md states {stated}, source has {counts}')
    print(f"workarounds: {counts['pins']} pins, {counts['barriers']} barriers, {counts['aliases']} aliases")
    for f in failures:
        print('FAIL:', f)
    sys.exit(1 if failures else 0)


if __name__ == '__main__':
    main()
