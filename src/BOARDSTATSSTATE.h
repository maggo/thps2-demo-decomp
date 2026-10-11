#ifndef BOARDSTATSSTATE_INC_H
#define BOARDSTATSSTATE_INC_H
#include "PSX.h"

#include "MECH.h"

/* MECH owns the two-entry array; MAIN uses its target-proven scalar view. */
/** Per-player board-stat bonuses selected during skater construction. */
extern BoardStats GBoardStats PSX_SECTION(".data");

#endif // BOARDSTATSSTATE_INC_H
