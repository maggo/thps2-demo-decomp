/*
 * TRIG physically owns the trigger-file pointer, node-offset table, and node
 * count in small data.  This header is intentionally re-entrant so each
 * translation unit retains its original declaration order and import view.
 */
#include "PSX.h"
#ifdef TRIGSTATE_ABSOLUTE_DECLARATION
#define TRIGSTATE_DECL_ATTR PSX_SECTION(".data")
#else
#define TRIGSTATE_DECL_ATTR
#endif

#ifdef TRIGSTATE_DECLARE_NUM_NODES
/** Number of nodes in the active trigger file. */
extern int NumNodes TRIGSTATE_DECL_ATTR;
#endif

#ifdef TRIGSTATE_DECLARE_OFFSET_LIST
/** Indexed table of node-record pointers in the active trigger file. */
extern short **OffsetList TRIGSTATE_DECL_ATTR;
#endif

#ifdef TRIGSTATE_DECLARE_TRIG_FILE
/** Storage containing the active trigger-file image. */
extern unsigned short *TrigFile TRIGSTATE_DECL_ATTR;
#endif

#ifdef TRIGSTATE_DECLARE_FILE_SIZE
/** Compacted byte size of the active trigger-file image. */
extern int TrigFileSize TRIGSTATE_DECL_ATTR;
#endif

#undef TRIGSTATE_DECL_ATTR
#undef TRIGSTATE_ABSOLUTE_DECLARATION
#undef TRIGSTATE_DECLARE_NUM_NODES
#undef TRIGSTATE_DECLARE_OFFSET_LIST
#undef TRIGSTATE_DECLARE_TRIG_FILE
#undef TRIGSTATE_DECLARE_FILE_SIZE
