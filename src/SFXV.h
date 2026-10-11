#ifndef SFXV_INC_H
#define SFXV_INC_H
#include "PSX.h"

/*
 * SFX physically owns the baddy-playback scratch volume in initialized small
 * data. BADDY retains its target-proven absolute-address import view.
 */
#ifdef SFXV_ABSOLUTE_DECLARATION
#define SFXV_DECL_ATTR PSX_SECTION(".data")
#else
#define SFXV_DECL_ATTR
#endif

/** Scratch volume used while projecting baddy sound effects. */
extern int SFX_v SFXV_DECL_ATTR;

#undef SFXV_DECL_ATTR
#undef SFXV_ABSOLUTE_DECLARATION

#endif // SFXV_INC_H
