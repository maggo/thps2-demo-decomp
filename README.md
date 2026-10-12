# THPS2 Demo Decompilation

Matching C/C++ reconstruction of the PlayStation THPS2 demo. This is an
unofficial research project, unaffiliated with the original rights holders.

## Status

**All 1,646 tracked functions match the original instructions after relocation
normalization (100%).** The committed progress report covers every function
range recorded in `MAIN.SYM`, including distinct copies of inline functions.

A fresh local full executable rebuild also reproduces all **882,688 bytes** of
`SLUS_900.86` and places **2,329/2,329 global symbols** at the original addresses.
That rebuild retains original handwritten assembly, SDK objects and 76,154 bytes
of original blobs. It does not mean all SDK and assembly code has been
reconstructed as C/C++.

Known matching workarounds remain. The sources still contain 12 register pins
(`register T x asm("$n")`), 24 empty `asm("")` scheduling constraints and 2
asm-name aliases, in 21 of the 1,646 functions. Each is marked with a
`FIXME(match)` comment that says what it forces and which natural rewrites were
tried; `grep -rn 'FIXME(match)' src` lists them. No hand-written instruction
sequences remain outside the Sony-style GTE macros. Cleanup changes preserve
both the tracked function matches and the executable rebuild.
All 88 bytes of constructor/destructor registration tables are now generated
from source. `verify.py` translates the stock compiler's Sony lifecycle records
into the relocated ELF table words that GNU as needs.
The native/WebAssembly port is a separate effort.

### Progress reporting

`build/report.json` uses objdiff's progress-report schema. The
`.github/workflows/progress.yml` workflow checks its totals and publishes the
`SLUS_900.86_report` artifact. CI validates the committed report; it cannot
repeat binary matching without the user-supplied executable, symbols and SDK.

Refresh the report only from a complete successful canonical verification:

```bash
python3 verify.py --exe original/SLUS_900.86 --sym original/MAIN.SYM \
  --report build/report.json
```

The verifier rebuilds every translation unit, requires the pinned compiler,
checks every function, and derives unique addresses and sizes from `MAIN.SYM`.
A build failure, missing function or mismatch returns a failing exit status;
partial and unchecked-compiler runs cannot overwrite the report.

## Not included

This repository intentionally excludes:

- the original executable, game assets, `MAIN.SYM`, and `MAIN_STRUCTS.h`;
- Psy-Q SDK files, ASPSX, PSYLINK, and other Sony software;
- downloaded compiler or assembler binaries;
- target disassembly, generated objects, link products, and matcher caches;
- recovered or leaked original source and development-project files; and
- private work logs, experiments, IDE state, and local paths.

Use only external inputs that you are legally authorized to possess.

## Build and verify

Use Linux (or WSL) with Bash, Python 3, `pyelftools`, Git, GNU `cpp` and MIPS
GNU binutils, plus Docker while old-gcc has no release of the compiler yet. The
compiler runs as a Linux i386 executable; use an x86 Linux environment or
suitable emulation.

Supply your Psy-Q 4.6 headers at `toolchain/psyq-4.6-sdk/INCLUDE/`, and put your
own executable and debug symbols in `original/SLUS_900.86` and
`original/MAIN.SYM`. These inputs are ignored by Git.

```bash
python3 -m pip install pyelftools
bash setup.sh
python3 verify.py --exe original/SLUS_900.86 --sym original/MAIN.SYM
```

`setup.sh` validates the SDK header set, installs the pinned egcs 1.1.1 compiler,
and installs a pinned maspsx revision plus the checked-in ASPSX compatibility
patch. `verify.py` compiles every translation unit with the recovered
per-translation-unit flags (`tools/tu_flags.json`) and compares every
function.

Existing tool installations can be selected explicitly:

```bash
python3 verify.py --exe /path/to/SLUS_900.86 --sym /path/to/MAIN.SYM \
  --cc-dir /path/to/egcs-1.1.1 --maspsx /path/to/maspsx \
  --include /path/to/psyq/include --out /path/to/scratch
```

The reported 1,646-function result was reproduced with this explicit-input
command and the pinned compiler. Six headers in the measured local include set
(`KERNEL.H`, `LIBCD.H`, `LIBDS.H`, `LIBGTE.H`, `LIBSPU.H`, `MCGUI.H`) differ from
the Psy-Q 4.6 manifest (`tools/psyq_4_6_headers.sha256`); setup reports such
differences as warnings, and `verify.py` reaching 1646/1646 is what proves a
header set. Matching with a manifest-identical SDK has not been verified.
`--include` selects a user-supplied header set directly.

`--tu DB` builds and checks only that translation unit (repeatable), and
`--func Bit_Display__Fv` prints one function's instruction comparison; both
rebuild only the sources involved, in a second or two.
`src/SQRTTAB.inc` is generated: `python3 tools/generate_sqrttab.py --check`
confirms it matches the documented formula.
`--skip-cc-hash` permits diagnostic compiler experiments, clearly marks them
noncanonical and disables report generation.

### Pinned compiler

Canonical verification uses egcs **1.1.1 (GCC 2.91.60)** from
[decompals/old-gcc](https://github.com/decompals/old-gcc) (`gcc-2.91.60-psx`,
the stock GNU release with old-gcc's PSX target and build patches; no
code-generation patches). `tools/get_compiler.sh` downloads old-gcc's release
archive, or builds old-gcc's recipe with Docker until that compiler is
released ([decompals/old-gcc#37](https://github.com/decompals/old-gcc/pull/37)).

`toolchain/verify_egcs_1_1_1.py` checks both compiler binaries against pinned
SHA-256 identities. Setup and canonical verification reject modified or
unknown compiler binaries.

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for the matching rules, source
conventions and how to help remove the remaining `FIXME(match)` workarounds.

## Evidence and rights

The reconstruction is based on permitted binary/debug evidence and
reproducible compiler experiments. Unlicensed original source, editor/tag
databases, and development-project files are not accepted as evidence.

This repository has no blanket open-source license. See
[`LICENSE_SCOPE.md`](LICENSE_SCOPE.md) for the copyright and third-party-rights
scope.
