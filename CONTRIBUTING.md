# Contributing

All 1,646 functions match. Every change must keep it that way.

## Before you open a pull request

```bash
python3 verify.py --exe original/SLUS_900.86 --sym original/MAIN.SYM   # must print 1646/1646
python3 tools/check_source.py                                          # also runs in CI
clang-format -i src/*.cpp src/*.h                                      # clang-format 23.1.3 (pip install clang-format==23.1.3)
```

`verify.py` needs your own disc files and Psy-Q 4.6 headers (see the README). CI
cannot run it, so say in the pull request that you did. Changes to data
definitions, statics or section attributes can move data even when every
function still matches; mention them so the maintainer can check the full
executable rebuild.

## Source conventions

- **Formatting** is `.clang-format` (whitespace only; CI checks it). Never
  hand-format around it, and keep formatting changes in their own commits.
- **Behaviour first.** The source must do what the original does. A rewrite that
  only matches by accident (wrong types, wrong control flow that happens to
  compile the same) is a bug.
- **Names and types come from `MAIN.SYM`** where it has them. Use plain C++ for
  what the original wrote: no decompiler placeholders (`FUN_`, `DAT_`,
  `param_N`, `iVarN`).
- **File banners.** Every `.cpp` starts with
  `// NAME.cpp -- description`, the original object name, its function count
  and address range, and the compiler line. Headers start with
  `// NAME.h -- interface of NAME.cpp`.
- **PSX specifics go through `src/PSX.h`:** `PSX_SECTION(".sdata")`,
  `PSX_SECTION_ALIGNED(".rdata", 4)` and `PSX_LAYOUT_CHECK(name, sizeof(T) == N)`
  instead of raw `__attribute__` or `typedef char` tricks.
- **Generated files.** `src/SQRTTAB.inc` comes from
  `tools/generate_sqrttab.py`; regenerate it instead of editing it.
- **Compiler settings** per translation unit live in `tools/tu_flags.json`.
  Change them only with evidence that the original used different flags.

## Matching workarounds

The source still contains a few constructs that exist only to make egcs 1.1.1
produce the original code: register pins (`register T x asm("$n")`), empty
`asm("")` barriers and asm-name aliases. Each one is marked:

```c
// FIXME(match): <register pin|asm barrier|asm alias> — <what it forces>; tried: <rewrites>.
```

- Do not add new workarounds. If one is truly unavoidable, mark it the same way
  and update the counts in the README (`tools/check_source.py` enforces both).
- Removing one is the most useful contribution. List them with
  `grep -rn 'FIXME(match)' src`. Each comment says what was already tried.
  Levers that worked in this and other GCC 2.x projects: local types (MAIN.SYM
  has them), declaration order, dropping alias/copy variables, reusing one
  local for related values (`$v0`/`$v1` choice), statement order and
  comma-expression call arguments (delay slots), and
  [decomp-permuter](https://github.com/simonlindholm/decomp-permuter). The
  [Brave Fencer Musashi cookbook](https://github.com/Druthulu/BFM-decomp/blob/main/cookbook/INDEX.md)
  collects many more for the same compiler family.
- Delete the marker together with the workaround, and update the README counts.

## Commits

One logical change per commit, with a message that says what changed and why.
Keep formatting-only changes in their own commits.
