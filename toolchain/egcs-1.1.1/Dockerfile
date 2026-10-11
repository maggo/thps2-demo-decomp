# Stock egcs 1.1.1 (gcc 2.91.60) PSX cross-compiler, cc1 / cc1plus only.
#
# Derived from decompals/old-gcc, gcc-2.91.66-psx.Dockerfile
# (https://github.com/decompals/old-gcc, master @ b74211c). The recipe, the
# PSX patches in ./patches and the smoke tests in ./tests are theirs and are
# used unmodified; the source tarball is egcs-1.1.1 instead
# of egcs-1.1.2 (SHA-256 pinned below). The source tree directory keeps the
# 2.91.66 name only so the unchanged decompals patches and paths apply.
#
# Build (x86_64 / i386 Linux binaries, like decompals ships):
#   docker build --platform linux/amd64 --output type=local,dest=out .
# setup_toolchain.sh runs this build and verifies the result with
# toolchain/verify_egcs_1_1_1.py.
FROM ubuntu:focal@sha256:8feb4d8ca5354def3d8fce243717141ce31e2c428701f6682bd2fafe15388214 AS build
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt-get install -y build-essential gcc gcc-multilib wget

ENV VERSION=2.91.66
ENV EGCS=1.1.1
ENV EGCS_SHA256=9279ea878ec3b57b5dc3a51c2b0ddcfaedf0aaaa88750a526fa1a6f63ab419e0

WORKDIR /work
RUN wget https://gcc.gnu.org/pub/gcc/old-releases/egcs/egcs-${EGCS}.tar.bz2
RUN echo "${EGCS_SHA256}  egcs-${EGCS}.tar.bz2" | sha256sum -c -
RUN mkdir -p /work/gcc-${VERSION}/
RUN tar xjf egcs-${EGCS}.tar.bz2 --strip-components=1 -C gcc-${VERSION}

WORKDIR /work/gcc-${VERSION}/

COPY patches /work/patches

RUN sed -i -- 's/include <varargs.h>/include <stdarg.h>/g' **/*.c
RUN patch -u -p1 gcc/obstack.h -i ../patches/obstack-${VERSION}.h.patch
RUN patch -u -p1 gcc/config/mips/mips.h -i ../patches/mips.patch
RUN patch -su -p1 < ../patches/psx-2.91.patch

RUN for dir in libiberty gcc; do \
    cd /work/gcc-${VERSION}/${dir}; \
    ./configure \
        --target=mips-sony-psx \
        --prefix=/opt/cross \
        --with-endian-little \
        --with-gnu-as \
        --disable-gprof \
        --disable-gdb \
        --disable-werror \
        --host=i386-pc-linux \
        --build=i386-pc-linux; \
    done

RUN make -C libiberty/ CFLAGS="-std=gnu89 -m32 -static"
RUN make -C gcc/ --jobs 4 cpp cc1 xgcc cc1plus g++ CFLAGS="-std=gnu89 -m32 -static"

COPY tests /work/tests
RUN ./gcc/cc1 -quiet -O2 /work/tests/little_endian.c && grep -E 'lbu\s\$2,0\(\$4\)' /work/tests/little_endian.s
RUN ./gcc/cc1 -quiet -O2 /work/tests/section_attribute.c
RUN ./gcc/cc1 -version </dev/null 2>&1 | grep -- -msoft-float
RUN ./gcc/cc1 -version </dev/null 2>&1 | grep -- -msplit-addresses
RUN ./gcc/cc1 -version </dev/null 2>&1 | grep -- -mgpopt
# Not in the decompals recipe: confirm this really is the 1.1.1 source.
RUN ./gcc/cc1 -version </dev/null 2>&1 | grep -F 2.91.60

RUN mv ./gcc/xgcc ./gcc/gcc
RUN mkdir /build && cp ./gcc/cpp ./gcc/cc1 ./gcc/gcc ./gcc/cc1plus ./gcc/g++ /build/

FROM scratch AS export
COPY --from=build /build/* .
