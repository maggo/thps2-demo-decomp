// Shared declaration of the textured-ribbon transient-bit type.
#ifndef CTEXTUREDRIBBON_INC_H
#define CTEXTUREDRIBBON_INC_H
// CBIT_VIRTUAL is already defined by whichever TU-wide header came first
// (CCLASS_POLY.h in BIT2/SMOKE, CNONRENDEREDBIT.h/CSPECIALDISPLAY.h/CPOLYLINE.h elsewhere).

struct Texture;
struct SRibbonPoint;

/** A special-display bit rendered as a chain of textured ribbon points. */
struct CTexturedRibbon : CSpecialDisplay
{
    unsigned char mTrail;
    Texture *mpTex;
    unsigned char mDontDisplay;
    int mU;
    int mV;
    int mDv;
    int mWibble;
    int mNumPoints;
    SRibbonPoint *mpPoints;

    /** Construct a textured ribbon with the requested point count. */
    CTexturedRibbon(int NumPoints, int LeaveTrail);
    CBIT_VIRTUAL ~CTexturedRibbon();
    /** Bind the texture identified by the asset checksum. */
    void SetTexture(unsigned int Checksum);
    /** Render the ribbon into the current viewport ordering table. */
    CBIT_VIRTUAL void Display();
    /** Release textured-ribbon storage through the CBit allocator. */
};

#endif // CTEXTUREDRIBBON_INC_H
