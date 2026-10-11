// Shared declaration for the motion-blur particle.
#ifndef CMOTIONBLUR_INC_H
#define CMOTIONBLUR_INC_H
// CBIT_VIRTUAL is already defined by whichever TU-wide header came first
// (CCLASS_POLY.h in BIT2/SMOKE, CNONRENDEREDBIT.h/CSPECIALDISPLAY.h/CPOLYLINE.h elsewhere).

/** Flat textured particle used for motion-blur effects. */
struct CMotionBlur : CFlatBit
{
    CMotionBlur(const CVector &pos, CVector &vel, char *pAnimName, int initialscale, int scaledecay,
                int transdecay);
    /** Destroy a motion-blur particle. */
    CBIT_VIRTUAL ~CMotionBlur();
    /** Advance the blur and apply its shrink/fade lifecycle. */
    CBIT_VIRTUAL void Move();
    /** Releases motion-blur storage through the CBit allocator. */
};

#endif // CMOTIONBLUR_INC_H
