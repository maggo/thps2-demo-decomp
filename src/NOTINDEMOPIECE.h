#ifndef NOTINDEMOPIECE_INC_H
#define NOTINDEMOPIECE_INC_H

/*
 * EDITORPIECES physically owns the active unavailable-piece replacement in
 * initialized small data. Consumers retain the target's absolute view.
 */
#ifdef NOTINDEMOPIECE_ABSOLUTE_DECLARATION
#define NOTINDEMOPIECE_DECL_ATTR __attribute__((section(".data")))
#else
#define NOTINDEMOPIECE_DECL_ATTR
#endif

/** Theme-specific replacement used for pieces unavailable in the demo. */
extern int NotInDemoPiece NOTINDEMOPIECE_DECL_ATTR;

#undef NOTINDEMOPIECE_DECL_ATTR
#undef NOTINDEMOPIECE_ABSOLUTE_DECLARATION

#endif // NOTINDEMOPIECE_INC_H
