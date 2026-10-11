// BMR.cpp -- Reconstructed data-only bmr.obj translation unit.
// Original: bmr.obj
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#include "PSX.h"
#include "BMR.h"

/** Compressed background image retained while its decoded form is built. */
unsigned short *pCompressedBMR PSX_SECTION(".sdata") = 0;

/** Decoded background image uploaded by the display-buffer code. */
char *pBMR PSX_SECTION(".sdata") = 0;
