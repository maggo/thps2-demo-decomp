#ifndef SUSPENDDISTANCE_INC_H
#define SUSPENDDISTANCE_INC_H
#include "PSX.h"

/* OB owns this small-data word; TRIG addresses it absolutely. */
/** Distance beyond which environmental objects may be suspended. */
extern unsigned int SuspendDistance PSX_SECTION(".data");

#endif // SUSPENDDISTANCE_INC_H
