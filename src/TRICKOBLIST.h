#ifndef TRICKOBLIST_INC_H
#define TRICKOBLIST_INC_H
#include "PSX.h"

struct CTrickOb;

/*
 * TRICKOB physically owns the active trick-object head in small data. Replay
 * code addresses that pointer absolutely, so each inclusion selects its
 * target-proven declaration view without exposing the object layout.
 */
#ifdef TRICKOBLIST_ABSOLUTE_DECLARATION
#define TRICKOBLIST_DECL_ATTR PSX_SECTION(".data")
#else
#define TRICKOBLIST_DECL_ATTR
#endif

#ifdef TRICKOBLIST_WITHIN_C_LINKAGE
#define TRICKOBLIST_DECL_LINKAGE extern
#else
#define TRICKOBLIST_DECL_LINKAGE extern "C"
#endif

/** Head of the active trick-trigger object list. */
TRICKOBLIST_DECL_LINKAGE CTrickOb *TrickObList TRICKOBLIST_DECL_ATTR;

#undef TRICKOBLIST_DECL_ATTR
#undef TRICKOBLIST_DECL_LINKAGE
#undef TRICKOBLIST_ABSOLUTE_DECLARATION

#endif // TRICKOBLIST_INC_H
