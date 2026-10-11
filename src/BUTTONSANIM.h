#ifndef BUTTONSANIM_INC_H
#define BUTTONSANIM_INC_H
#include "PSX.h"

struct SAnimFrame;

/* FRONT owns this small-data pointer; BIT addresses it absolutely. */
/** Animation frames used for front-end confirm and back button prompts. */
extern SAnimFrame *ButtonsAnim PSX_SECTION(".data");

#endif // BUTTONSANIM_INC_H
