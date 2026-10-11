/*
 * TRIG physically owns the current object-file cursor in small data. This
 * header is intentionally re-entrant because TRIG first needs its owner view
 * and later encounters BACKGRND's target-recorded absolute-address view.
 */
#include "PSX.h"
#ifdef CURRENTOBJFILE_OWNER_DECLARATION
#define CURRENTOBJFILE_DECL_ATTR
#else
#define CURRENTOBJFILE_DECL_ATTR PSX_SECTION(".data")
#endif

/** Start of the object file currently being interpreted. */
extern char *pCurrentObjFile CURRENTOBJFILE_DECL_ATTR;

#undef CURRENTOBJFILE_DECL_ATTR
#undef CURRENTOBJFILE_OWNER_DECLARATION
