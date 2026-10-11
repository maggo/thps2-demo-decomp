#ifndef MUSICSTOPPED_INC_H
#define MUSICSTOPPED_INC_H
#include "PSX.h"

/* MAIN physically owns the playback-pause word in small data. */
/** Whether replay or movie playback has paused the music stream. */
extern int MusicStopped PSX_SECTION(".data");

#endif // MUSICSTOPPED_INC_H
