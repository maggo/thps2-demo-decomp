#ifndef LOWMEMORY_INC_H
#define LOWMEMORY_INC_H
#include "PSX.h"

/*
 * MEM physically owns the allocator pressure flag in initialized small data.
 * SHATTER retains its target-proven absolute-address import view.
 */
#ifdef LOWMEMORY_ABSOLUTE_DECLARATION
#define LOWMEMORY_DECL_ATTR PSX_SECTION(".data")
#else
#define LOWMEMORY_DECL_ATTR
#endif

/** Nonzero while allocator pressure requires reduced-memory effects. */
extern int LowMemory LOWMEMORY_DECL_ATTR;

#undef LOWMEMORY_DECL_ATTR
#undef LOWMEMORY_ABSOLUTE_DECLARATION

#endif // LOWMEMORY_INC_H
