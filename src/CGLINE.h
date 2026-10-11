// Shared declaration for the generated line effect.
#ifndef CGLINE_INC_H
#define CGLINE_INC_H
// CBIT_VIRTUAL is already defined by whichever TU-wide header came first
// (CCLASS_POLY.h in BIT2/SMOKE, CNONRENDEREDBIT.h/CSPECIALDISPLAY.h/CPOLYLINE.h elsewhere).

/** Two-colour world-space line state. */
struct CGLine : CBit {
    unsigned int mCodeBGR0;
    unsigned int mPadBGR1;
    CVector mStart;
    CVector mEnd;

    /** Construct and attach a generated line. */
    CGLine();
    /** Detach and destroy a generated line. */
    CBIT_VIRTUAL ~CGLine();
    /** Release generated-line storage through the CBit allocator. */
    static void operator delete(void *p) { CBit::operator delete(p); }
};

#endif // CGLINE_INC_H
