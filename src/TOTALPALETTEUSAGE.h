/*
 * PAL physically owns the palette-allocation counter as a four-byte common.
 * Cross-owner consumers address that word absolutely.
 */
#include "PSX.h"
#ifdef TOTALPALETTEUSAGE_ABSOLUTE_DECLARATION
#define TOTALPALETTEUSAGE_DECL_ATTR PSX_SECTION(".data")
#else
#define TOTALPALETTEUSAGE_DECL_ATTR
#endif

/** Bytes currently consumed by palette records and their allocations. */
extern int TotalPaletteUsage TOTALPALETTEUSAGE_DECL_ATTR;

#undef TOTALPALETTEUSAGE_DECL_ATTR
#undef TOTALPALETTEUSAGE_ABSOLUTE_DECLARATION
