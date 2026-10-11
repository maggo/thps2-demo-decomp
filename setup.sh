#!/bin/bash
# One-time setup for verify.py: checks host tools, validates your Psy-Q 4.6 headers,
# installs the pinned egcs 1.1.1 (GCC 2.91.60) compiler from decompals/old-gcc, and installs maspsx
# at a pinned commit plus tools/maspsx.patch. Safe to re-run.
set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
TOOLCHAIN_DIR="$ROOT/toolchain"
COMPILER_DIR="$TOOLCHAIN_DIR/gcc-2.91.60-psx"
MASPSX_DIR="$TOOLCHAIN_DIR/maspsx"
MASPSX_COMMIT=e85ecb373828aabea96d7e6400974d4f91ce8c74
MASPSX_PATCH="$ROOT/tools/maspsx.patch"
PSYQ_SDK_DIR="$TOOLCHAIN_DIR/psyq-4.6-sdk"
PSYQ_SDK_HEADER_HELPER="$ROOT/tools/psyq_sdk_headers.py"
EGCS_COMPILER_VERIFIER="$TOOLCHAIN_DIR/verify_egcs_1_1_1.py"

fail() { echo "setup: $*" >&2; exit 1; }

# 1. Host tools
echo "[1/4] Checking host tools..."
for tool in python3 git cpp mips-linux-gnu-as; do
    command -v "$tool" >/dev/null 2>&1 \
        || fail "missing host tool: $tool (MIPS binutils: apt install binutils-mips-linux-gnu)"
done
python3 -c 'import elftools' 2>/dev/null \
    || fail "missing Python module pyelftools (python3 -m pip install pyelftools)"

# 2. Psy-Q 4.6 headers: user-supplied, never downloaded or redistributed here.
echo "[2/4] Validating Psy-Q 4.6 SDK headers..."
[ -d "$PSYQ_SDK_DIR/INCLUDE" ] \
    || fail "put the unmodified Psy-Q 4.6 (DTL-S2360) SDK at $PSYQ_SDK_DIR (INCLUDE/ inside it)"
python3 "$PSYQ_SDK_HEADER_HELPER" --prepare

# 3. Compiler: egcs 1.1.1 (GCC 2.91.60-psx) from decompals/old-gcc, either its release
# archive or a local Docker build of its recipe; installed only if it matches the hashes
# pinned in toolchain/verify_egcs_1_1_1.py, so a partial or modified install is replaced.
echo "[3/4] Installing GCC 2.91.60-psx (egcs 1.1.1)..."
if python3 "$EGCS_COMPILER_VERIFIER" --check "$COMPILER_DIR" >/dev/null 2>&1; then
    echo "  Already installed."
else
    bash "$ROOT/tools/get_compiler.sh" "$COMPILER_DIR"
fi
python3 "$EGCS_COMPILER_VERIFIER" --check "$COMPILER_DIR"

# 4. maspsx (ASPSX 2.86 emulation) at the pinned commit, plus the checked-in patch.
echo "[4/4] Setting up maspsx..."
if [ ! -d "$MASPSX_DIR/.git" ]; then
    [ ! -e "$MASPSX_DIR" ] || fail "$MASPSX_DIR exists but is not a git checkout"
    git clone -q https://github.com/mkst/maspsx.git "$MASPSX_DIR"
fi
if [ "$(git -C "$MASPSX_DIR" rev-parse HEAD)" != "$MASPSX_COMMIT" ]; then
    [ -z "$(git -C "$MASPSX_DIR" status --porcelain)" ] \
        || fail "preserve your local maspsx changes before selecting $MASPSX_COMMIT"
    git -C "$MASPSX_DIR" checkout -q --detach "$MASPSX_COMMIT"
fi
if git -C "$MASPSX_DIR" apply --check "$MASPSX_PATCH" 2>/dev/null; then
    git -C "$MASPSX_DIR" apply "$MASPSX_PATCH"
fi
git -C "$MASPSX_DIR" diff --cached --quiet \
    && git -C "$MASPSX_DIR" diff --no-ext-diff --binary | cmp -s - "$MASPSX_PATCH" \
    || fail "maspsx must be exactly $MASPSX_COMMIT + tools/maspsx.patch"
echo "  maspsx: $MASPSX_COMMIT + tools/maspsx.patch"

echo
echo "Setup complete. Next:"
echo "  python3 verify.py --exe original/SLUS_900.86 --sym original/MAIN.SYM"
