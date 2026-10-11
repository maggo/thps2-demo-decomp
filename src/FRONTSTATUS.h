/*
 * FRONT physically owns the paused-state word in small data. This header is
 * intentionally re-entrant so each consumer retains its original declaration
 * point and absolute-address import view.
 */
#include "PSX.h"
#ifdef FRONTSTATUS_OWNER_DECLARATION
#define FRONTSTATUS_DECL_ATTR
#else
#define FRONTSTATUS_DECL_ATTR PSX_SECTION(".data")
#endif

/** Current paused-game/front-end state, physically allocated by FRONT.cpp. */
extern EPausedStatus Status FRONTSTATUS_DECL_ATTR;

#undef FRONTSTATUS_DECL_ATTR
#undef FRONTSTATUS_OWNER_DECLARATION
