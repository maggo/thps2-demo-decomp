#ifndef TOTALVABUSAGE_INC_H
#define TOTALVABUSAGE_INC_H

/*
 * SFX physically owns the sound-RAM allocation counter in initialized small
 * data. INIT retains its target-proven absolute-address import view.
 */
#ifdef TOTALVABUSAGE_ABSOLUTE_DECLARATION
#define TOTALVABUSAGE_DECL_ATTR __attribute__((section(".data")))
#else
#define TOTALVABUSAGE_DECL_ATTR
#endif

/** Bytes of SPU sound RAM occupied by loaded VAB data. */
extern int TotalVabUsage TOTALVABUSAGE_DECL_ATTR;

#undef TOTALVABUSAGE_DECL_ATTR
#undef TOTALVABUSAGE_ABSOLUTE_DECLARATION

#endif // TOTALVABUSAGE_INC_H
