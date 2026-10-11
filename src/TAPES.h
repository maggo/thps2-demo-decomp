// TAPES.h -- interface of TAPES.cpp
#ifndef TAPES_INC_H
#define TAPES_INC_H

struct CTape;

/** Create the tape trail between two endpoints. */
CTape *Tape_Create(
    int x, int y, int z, int Size,
    int x2, int y2, int z2, int Size2);

#endif // TAPES_INC_H
