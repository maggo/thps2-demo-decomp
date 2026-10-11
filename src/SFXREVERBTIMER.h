#ifndef SFXREVERBTIMER_INC_H
#define SFXREVERBTIMER_INC_H
#include "PSX.h"

/*
 * SFX physically owns the reverb-depth timer in initialized small data.
 * UTILS retains its target-proven absolute-address import view.
 */
#ifdef SFXREVERBTIMER_ABSOLUTE_DECLARATION
#define SFXREVERBTIMER_DECL_ATTR PSX_SECTION(".data")
#else
#define SFXREVERBTIMER_DECL_ATTR
#endif

/** Frames remaining before the pending reverb-depth change is applied. */
extern unsigned int SFX_ReverbDepthSetTimer SFXREVERBTIMER_DECL_ATTR;

#undef SFXREVERBTIMER_DECL_ATTR
#undef SFXREVERBTIMER_ABSOLUTE_DECLARATION

#endif // SFXREVERBTIMER_INC_H
