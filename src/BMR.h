#ifndef BMR_INC_H
#define BMR_INC_H
#include "PSX.h"

extern "C"
{

// Consumers use absolute relocations for these imported pointers.  The
// extern-only section attributes preserve that addressing contract; BMR.cpp
// still owns both objects in its target-proven small-data contribution.
/** Compressed background image retained while its decoded form is built. */
extern unsigned short *pCompressedBMR PSX_SECTION(".data");

/** Decoded background image uploaded by the display-buffer code. */
extern char *pBMR PSX_SECTION(".data");
}

#endif // BMR_INC_H
