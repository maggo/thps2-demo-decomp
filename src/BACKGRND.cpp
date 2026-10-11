// BACKGRND.cpp -- Reconstructed translation unit
// Original: BACKGRND.CPP
// Functions: 5
// Address range: 0x800790B0 - 0x8007924C
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#define CCLASS_POLY_ITEM_FAMILY
#include "CCLASS_POLY.h"
#include "BACKGRND.h"
#include "CFRICTION.h"

/** Background body plus the monotonically assigned background-list index. */
struct CBackground : public CBody
{
    unsigned short mIndex;

    CBackground(unsigned int checksum, const CSVector &ang_vel);
    virtual ~CBackground();
    void AI();
};

typedef char CBackground_size_check[(sizeof(CBackground) == 268) ? 1 : -1];

#include "OB.h"
#include "SPOOL.h"

// Linked list node for background objects -- gp-relative head pointer
CBody *BackgroundList = 0; // gp+0x3D88
static u16 CurrentIndex = 0; // gp+0x3D8C

enum
{
    BACKGROUND_DISABLED_FLAG = 1,
    BACKGROUND_ITEM_FLAGS_CLEARED_ON_INIT = 2,
    BACKGROUND_BODY_FLAGS_CLEARED_ON_INIT = 6
};

// === Function implementations (address order) ===

/**
 * Backgrnd_On__FUs
 *
 * Address:   0x800790B0
 * Mangled:   Backgrnd_On__FUs
 * Demangled: Backgrnd_On(unsigned short)
 *            Traverses the background list and clears the disabled bit on the
 *            object whose index matches.
 *
 * @param index  Background-object index.
 */
void Backgrnd_On(unsigned short index)
{
    CBackground *p_back = static_cast<CBackground *>(BackgroundList);
    while (p_back != 0)
    {
        if (p_back->mIndex == index)
        {
            p_back->mFlags &= ~BACKGROUND_DISABLED_FLAG;
            return;
        }
        p_back = static_cast<CBackground *>(p_back->mNextItem);
    }
}


/**
 * Backgrnd_Off__FUs
 *
 * Address:   0x800790FC
 * Mangled:   Backgrnd_Off__FUs
 * Demangled: Backgrnd_Off(unsigned short)
 *
 * @param index  Background-object index.
 */
void Backgrnd_Off(unsigned short index)
{
    CBackground *p_back = static_cast<CBackground *>(BackgroundList);
    while (p_back != 0)
    {
        if (p_back->mIndex == index)
        {
            p_back->mFlags |= BACKGROUND_DISABLED_FLAG;
            return;
        }
        p_back = static_cast<CBackground *>(p_back->mNextItem);
    }
}


/**
 * __11CBackgroundUiRC8CSVector
 *
 * Address:   0x80079148
 * Mangled:   __11CBackgroundUiRC8CSVector
 * Demangled: CBackground::CBackground(unsigned int, const CSVector &)
 *            Initialize the object and link it into the background list.
 *
 * @param checksum  Asset hash for content lookup.
 * @param ang_vel  Reserved angular-velocity argument; not read here.
 */
CBackground::CBackground(unsigned int checksum, const CSVector &ang_vel)
{
    char *pName = pCurrentObjFile;
    InitItem(pName);
    mModel = Spool_GetModel(checksum, mRegion);
    mFlags &= ~BACKGROUND_ITEM_FLAGS_CLEARED_ON_INIT;
    mCBodyFlags &= ~BACKGROUND_BODY_FLAGS_CLEARED_ON_INIT;
    AttachTo(&BackgroundList);
    mIndex = CurrentIndex++;
}


/**
 * _._11CBackground
 *
 * Address:   0x800791DC
 * Mangled:   _._11CBackground
 * Demangled: CBackground::~CBackground()
 *
 * GCC 2.x supplies the hidden in-charge flag and invokes the class allocator
 * when destruction also owns the object's storage.
 */
CBackground::~CBackground()
{
    DeleteFrom(&BackgroundList);
    CurrentIndex--;
}


/**
 * AI__11CBackground
 *
 * Address:   0x8007924C
 * Mangled:   AI__11CBackground
 * Demangled: CBackground::AI(void)
 *            Advances the object's angles by its angular velocity.
 */
void CBackground::AI()
{
    mAngles += mAngVel;
}
