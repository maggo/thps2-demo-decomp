/*
 * MAIN physically owns the CClass allocation counter in initialized small
 * data. INIT retains its target-proven absolute-address import view.
 */
#include "PSX.h"
#ifdef TOTALCCLASSUSAGE_ABSOLUTE_DECLARATION
#define TOTALCCLASSUSAGE_DECL_ATTR PSX_SECTION(".data")
#else
#define TOTALCCLASSUSAGE_DECL_ATTR
#endif

/** Bytes currently consumed by CClass allocations. */
extern int TotalCClassUsage TOTALCCLASSUSAGE_DECL_ATTR;

#undef TOTALCCLASSUSAGE_DECL_ATTR
#undef TOTALCCLASSUSAGE_ABSOLUTE_DECLARATION
