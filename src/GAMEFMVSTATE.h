/*
 * GAMEFMV physically owns these playback-state words in zero-initialized
 * small data. Cross-owner consumers retain their target-proven absolute
 * addressing views. This header is intentionally re-entrant so each owner
 * declaration stays at its original symbol-order position.
 */
#include "PSX.h"
#ifdef GAMEFMVSTATE_OWNER_DECLARATION
#define GAMEFMVSTATE_DECL_ATTR
#else
#define GAMEFMVSTATE_DECL_ATTR PSX_SECTION(".data")
#endif

#ifdef GAMEFMVSTATE_DECLARE_ACTIVE
/** Whether asynchronous movie playback currently owns the decoder. */
extern int GameFMV_Active GAMEFMVSTATE_DECL_ATTR;
#endif

#ifdef GAMEFMVSTATE_DECLARE_CURRENT_FRAME
/** Frame number most recently consumed from the active movie stream. */
#ifdef GAMEFMVSTATE_OWNER_DECLARATION
extern int GameFMV_CurrentFrame GAMEFMVSTATE_DECL_ATTR;
#else
extern int GameFMV_CurrentFrame[] GAMEFMVSTATE_DECL_ATTR;
#endif
#endif

#ifdef GAMEFMVSTATE_DECLARE_END_X
/** Exclusive horizontal end of the active movie decode region. */
extern u16 GameFMV_EndX GAMEFMVSTATE_DECL_ATTR;
#endif

#ifdef GAMEFMVSTATE_DECLARE_START_X
/** Horizontal origin of the active movie decode region. */
extern s16 GameFMV_StartX GAMEFMVSTATE_DECL_ATTR;
#endif

#ifdef GAMEFMVSTATE_DECLARE_START_Y
/** Vertical origin of the active movie decode region. */
extern s16 GameFMV_StartY GAMEFMVSTATE_DECL_ATTR;
#endif

#undef GAMEFMVSTATE_DECL_ATTR
#undef GAMEFMVSTATE_DECLARE_ACTIVE
#undef GAMEFMVSTATE_DECLARE_CURRENT_FRAME
#undef GAMEFMVSTATE_DECLARE_END_X
#undef GAMEFMVSTATE_DECLARE_START_X
#undef GAMEFMVSTATE_DECLARE_START_Y
#undef GAMEFMVSTATE_OWNER_DECLARATION
