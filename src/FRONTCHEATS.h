#ifndef FRONTCHEATS_INC_H
#define FRONTCHEATS_INC_H

/*
 * MAIN physically owns these front-end cheat toggles in small data.  FRONT
 * retains the target-proven absolute-address import view.
 */
#ifdef FRONTCHEATS_ABSOLUTE_DECLARATION
#define FRONTCHEATS_DECL_ATTR __attribute__((section(".data")))
#else
#define FRONTCHEATS_DECL_ATTR
#endif

#ifdef FRONTCHEATS_WITHIN_C_LINKAGE
#define FRONTCHEATS_DECL_LINKAGE extern
#else
#define FRONTCHEATS_DECL_LINKAGE extern "C"
#endif

/** Whether the pause menu permits selecting an arbitrary restart point. */
FRONTCHEATS_DECL_LINKAGE int Cheat_RestartSkip FRONTCHEATS_DECL_ATTR;

/** Whether the front end displays the in-game diagnostic information. */
FRONTCHEATS_DECL_LINKAGE int Cheat_GameInfo FRONTCHEATS_DECL_ATTR;

#undef FRONTCHEATS_DECL_LINKAGE
#undef FRONTCHEATS_DECL_ATTR
#undef FRONTCHEATS_ABSOLUTE_DECLARATION

#endif // FRONTCHEATS_INC_H
