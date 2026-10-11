/*
 * M3D physically owns the 1024-entry depth-scaled sine table. M3DINIT retains
 * its target-proven incomplete-array view while initializing that storage.
 */
#ifdef WIBBLETABLES_CONSUMER_DECLARATION
#define WIBBLETABLES_DECL_EXTENT
#else
#define WIBBLETABLES_DECL_EXTENT 1024
#endif

/** Per-depth texture-wibble lookup rows initialized at runtime. */
extern s16 WibbleTables[WIBBLETABLES_DECL_EXTENT];

#undef WIBBLETABLES_DECL_EXTENT
#undef WIBBLETABLES_CONSUMER_DECLARATION
