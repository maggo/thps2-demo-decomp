// SQRTTAB.cpp -- Reconstructed data-only translation unit
// Original: sqrttab.obj
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#include "PSX.h"
enum
{
    SQRT_TABLE_ENTRY_COUNT = 3072,
};

/**
 * Ten-bit fixed-point square-root samples for inputs from 1024.5 through
 * 4095.5.  The checked-in initializer is reproducibly generated from the
 * integer formula documented in tools/generate_sqrttab.py.
 */
unsigned short SqrtTable[SQRT_TABLE_ENTRY_COUNT] PSX_SECTION(".data") = {
#include "SQRTTAB.inc"
};
