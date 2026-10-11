#!/bin/bash
# Install egcs 1.1.1 (GCC 2.91.60-psx) cc1/cc1plus into DEST from decompals/old-gcc:
# the prebuilt release archive if one exists, otherwise a local Docker build of
# old-gcc's gcc-2.91.60-psx.Dockerfile. Either way the binaries must match the
# hashes pinned in toolchain/verify_egcs_1_1_1.py before they are installed.
#
#   tools/get_compiler.sh DEST
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
DEST="$1"
VERIFIER="$ROOT/toolchain/verify_egcs_1_1_1.py"
RELEASE_URL=https://github.com/decompals/old-gcc/releases/latest/download/gcc-2.91.60-psx.tar.gz
# decompals/old-gcc#37 (adds gcc-2.91.60 and gcc-2.91.60-psx); used until it is released upstream.
RECIPE_REPO=https://github.com/maggo/old-gcc.git
RECIPE_COMMIT=721536527a459e45de0a0b9bff09fcae665bceaf

fail() { echo "get_compiler: $*" >&2; exit 1; }

STAGE="$(mktemp -d "${TMPDIR:-/tmp}/egcs-1.1.1.XXXXXXXX")"
trap 'rm -rf -- "$STAGE"' EXIT
mkdir "$STAGE/bin"

if curl -fsSL -o "$STAGE/gcc.tar.gz" "$RELEASE_URL" 2>/dev/null; then
    echo "  downloaded $RELEASE_URL"
    tar -xzf "$STAGE/gcc.tar.gz" -C "$STAGE/bin"
else
    echo "  no decompals/old-gcc release with gcc-2.91.60-psx yet; building it with Docker"
    command -v docker >/dev/null 2>&1 || fail "install Docker to build the compiler"
    git init -q "$STAGE/old-gcc"
    git -C "$STAGE/old-gcc" fetch -q --depth 1 "$RECIPE_REPO" "$RECIPE_COMMIT"
    git -C "$STAGE/old-gcc" checkout -q FETCH_HEAD
    docker build --platform linux/amd64 -f "$STAGE/old-gcc/gcc-2.91.60-psx.Dockerfile" \
        --output "type=local,dest=$STAGE/bin" "$STAGE/old-gcc"
fi

chmod +x "$STAGE/bin"/*
python3 "$VERIFIER" --check "$STAGE/bin" >/dev/null \
    || fail "the compiler does not match the pinned egcs 1.1.1 hashes"
rm -rf -- "$DEST"
mkdir -p "$(dirname "$DEST")"
mv "$STAGE/bin" "$DEST"
echo "  installed: $(ls "$DEST" | tr '\n' ' ')"
