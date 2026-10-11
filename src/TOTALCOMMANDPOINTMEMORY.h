/*
 * TRIG physically owns the command-point allocation counter in initialized
 * small data. Cross-owner consumers address that word absolutely.
 */
#ifdef TOTALCOMMANDPOINTMEMORY_ABSOLUTE_DECLARATION
#define TOTALCOMMANDPOINTMEMORY_DECL_ATTR __attribute__((section(".data")))
#else
#define TOTALCOMMANDPOINTMEMORY_DECL_ATTR
#endif

/** Bytes currently consumed by allocated trigger command points. */
extern int TotalCommandPointMemory TOTALCOMMANDPOINTMEMORY_DECL_ATTR;

#undef TOTALCOMMANDPOINTMEMORY_DECL_ATTR
#undef TOTALCOMMANDPOINTMEMORY_ABSOLUTE_DECLARATION
