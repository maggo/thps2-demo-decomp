#ifndef OTENTRY_INC_H
#define OTENTRY_INC_H
#include "PSX.h"

/* SHELLUTILS physically owns the ordering-table cursor in small data. */
/** Ordering-table slot currently selected by the shell renderer. */
extern int OT_entry PSX_SECTION(".data");

#endif // OTENTRY_INC_H
