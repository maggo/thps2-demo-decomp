/*
 * M3DCOLIJ physically owns the collision-face masks in initialized small
 * data. M3DZONE retains its target-proven absolute-address import view.
 * This header is intentionally re-entrant so both declarations stay at their
 * original owner-local encounter points.
 */
#include "PSX.h"
#ifdef M3DCOLIJMASKS_ABSOLUTE_DECLARATION
#define M3DCOLIJMASKS_DECL_ATTR PSX_SECTION(".data")
#else
#define M3DCOLIJMASKS_DECL_ATTR
#endif

#ifdef M3DCOLIJMASKS_WITHIN_C_LINKAGE
#define M3DCOLIJMASKS_DECL_LINKAGE extern
#else
#define M3DCOLIJMASKS_DECL_LINKAGE extern "C"
#endif

/** Collision-face bits accepted by the active environment zone. */
M3DCOLIJMASKS_DECL_LINKAGE unsigned int M3dColij_OneMask M3DCOLIJMASKS_DECL_ATTR;

/** Collision-face bits rejected by the active environment zone. */
M3DCOLIJMASKS_DECL_LINKAGE unsigned int M3dColij_ZeroMask M3DCOLIJMASKS_DECL_ATTR;

#undef M3DCOLIJMASKS_DECL_LINKAGE
#undef M3DCOLIJMASKS_DECL_ATTR
#undef M3DCOLIJMASKS_ABSOLUTE_DECLARATION
#undef M3DCOLIJMASKS_WITHIN_C_LINKAGE
