#ifndef SOFTRESETSTATE_INC_H
#define SOFTRESETSTATE_INC_H
#include "PSX.h"

/* FRONT owns this small-data word; RFRONT addresses it absolutely. */
/** Whether the front end accepts the start/select soft-reset chord. */
extern int GSoftResetEnabled PSX_SECTION(".data");

#endif // SOFTRESETSTATE_INC_H
