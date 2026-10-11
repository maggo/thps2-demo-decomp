#ifndef CHEATPANELON_INC_H
#define CHEATPANELON_INC_H
#include "PSX.h"

/*
 * MAIN physically owns the panel-visibility cheat in initialized small data.
 * PANEL retains its target-proven absolute-address import view.
 */
#ifdef CHEATPANELON_ABSOLUTE_DECLARATION
#define CHEATPANELON_DECL_ATTR PSX_SECTION(".data")
#else
#define CHEATPANELON_DECL_ATTR
#endif

/** Whether the in-game score panel is enabled. */
extern int Cheat_PanelOn CHEATPANELON_DECL_ATTR;

#undef CHEATPANELON_DECL_ATTR
#undef CHEATPANELON_ABSOLUTE_DECLARATION

#endif // CHEATPANELON_INC_H
