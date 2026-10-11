#ifndef PHYSICSSTATE_INC_H
#define PHYSICSSTATE_INC_H
#include "PSX.h"

/* PHYSICS physically owns these runtime values in small data. */

struct CVector;

/** Optional stat value applied in place of the active skater statistics. */
extern int Cheat_StatsOverride PSX_SECTION(".data");

/** Terrain type recorded for the most recently resolved collision face. */
extern int Face_Terrain PSX_SECTION(".data");

/** Downward acceleration applied to gravity-driven gameplay objects. */
extern CVector WorldGravity;

#endif // PHYSICSSTATE_INC_H
