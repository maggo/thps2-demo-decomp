#ifndef TOTALTEXTUREUSAGE_INC_H
#define TOTALTEXTUREUSAGE_INC_H

/*
 * SPOOL physically owns the texture-allocation counter in small data. Every
 * cross-owner consumer addresses that word absolutely.
 */
#ifdef TOTALTEXTUREUSAGE_ABSOLUTE_DECLARATION
#define TOTALTEXTUREUSAGE_DECL_ATTR __attribute__((section(".data")))
#else
#define TOTALTEXTUREUSAGE_DECL_ATTR
#endif

/** Bytes currently consumed by loaded texture records and their allocations. */
extern int TotalTextureUsage TOTALTEXTUREUSAGE_DECL_ATTR;

#undef TOTALTEXTUREUSAGE_DECL_ATTR
#undef TOTALTEXTUREUSAGE_ABSOLUTE_DECLARATION

#endif // TOTALTEXTUREUSAGE_INC_H
