#ifndef POLYBUFFERSIZE_INC_H
#define POLYBUFFERSIZE_INC_H
#include "PSX.h"

/*
 * DB physically owns the polygon-buffer byte count as a small-BSS common.
 * Cross-owner consumers retain their target-proven absolute-address import
 * view of that word.
 */
#ifdef POLYBUFFERSIZE_ABSOLUTE_DECLARATION
#define POLYBUFFERSIZE_DECL_ATTR PSX_SECTION(".data")
#else
#define POLYBUFFERSIZE_DECL_ATTR
#endif

/** Number of bytes reserved for each display polygon buffer. */
extern int POLYBUFFERSIZE POLYBUFFERSIZE_DECL_ATTR;

#undef POLYBUFFERSIZE_DECL_ATTR
#undef POLYBUFFERSIZE_ABSOLUTE_DECLARATION

#endif // POLYBUFFERSIZE_INC_H
