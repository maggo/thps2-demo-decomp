#ifndef HIRESMODE_INC_H
#define HIRESMODE_INC_H

/*
 * SHELLUTILS physically owns the high-resolution shell flag in initialized
 * small data. FRONTEND2 retains its target-proven absolute-address view.
 */
#ifdef HIRESMODE_ABSOLUTE_DECLARATION
#define HIRESMODE_DECL_ATTR __attribute__((section(".data")))
#else
#define HIRESMODE_DECL_ATTR
#endif

/** Nonzero while the shell renders through its high-resolution path. */
extern int HiresMode HIRESMODE_DECL_ATTR;

#undef HIRESMODE_DECL_ATTR
#undef HIRESMODE_ABSOLUTE_DECLARATION

#endif // HIRESMODE_INC_H
