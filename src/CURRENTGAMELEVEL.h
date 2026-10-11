#ifndef CURRENTGAMELEVEL_INC_H
#define CURRENTGAMELEVEL_INC_H
#include "PSX.h"

/**
 * Gameplay level currently loaded by MAIN. The owner stores this word in
 * small data; consumers retain their target-recorded absolute address view.
 */
extern int CurrentGameLevel PSX_SECTION(".data");

#endif // CURRENTGAMELEVEL_INC_H
