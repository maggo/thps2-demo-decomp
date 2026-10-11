// BIT2.cpp -- Reconstructed translation unit
// Original: BIT2.CPP
// Functions: 13 reconstructed entries
// Address range: 0x80036848 - 0x80036FD8
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#include "PSX.h"
#define CCLASS_POLY_BIT_FAMILY
#include "CCLASS_POLY.h"
#define BIT2_OWNER_DECLARATIONS
#include "BIT2.h"
#undef BIT2_OWNER_DECLARATIONS
#include "MEM.h"
#include "UTILS.h"
#include "globals.h"

struct SAnimFrame;

/** Base state shared by the line effects owned by BIT2. */
#include "CNONRENDEREDBIT.h"

/** Textured particle state shared with the motion-blur effect. */
struct CFT4Bit : CBit
{
    short mTransDecay;
    short mScaleDecay;
    unsigned int mCodeBGR;
    SAnimFrame *mpPSXAnim;
    SAnimFrame *mpPSXFrame;
    unsigned char mBitFlags;
    unsigned char mNumFrames;
    char mFrame;
    unsigned char mFrameFrac;
    short mAnimSpeed;
    short mScale;

    /** Assign the particle's RGB tint. */
    void SetTint(unsigned char r, unsigned char g, unsigned char b);
};

/** Rotation and render-priority state of a flat textured particle. */
struct CFlatBit : CFT4Bit
{
    short mAngle;
    short mAngVel;
    short mAngAcc;
    unsigned short mAngFric;
    unsigned int mPostScale;
    unsigned char mForcedPriority;
    unsigned char mSemiTransparencyRate;
    unsigned short mCLUT;

    virtual ~CFlatBit();
};

#include "CMOTIONBLUR.h"

#include "SLINESEG.h"

#include "CPOLYLINE.h"

#include "CGPOLYLINE.h"

struct CSmokeGenerator : CNonRenderedBit
{
    int mPuffs;
    unsigned char mR;
    unsigned char mG;
    unsigned char mB;
    int mVBase;
    int mVRandom;
    int mScaleBase;
    int mScaleRandom;

    virtual ~CSmokeGenerator();
    /** Releases bit-owned storage through the CBit allocator. */
    static void operator delete(void *p) { CBit::operator delete(p); }
    void Move();
};

#include "CGLINE.h"

/** Proven prefix of CItem needed to read a body's position. */
struct CItemPositionPrefix
{
    unsigned short mFlags;
    unsigned short mInquiry;
    CVector mPos;
};

/** Proven prefix of CBody containing its embedded item state. */
struct CBodyPositionPrefix
{
    CItemPositionPrefix CItem;
};

PSX_LAYOUT_CHECK(Bit2_CBit_size_must_be_72, sizeof(CBit) == 72);
PSX_LAYOUT_CHECK(Bit2_CNonRenderedBit_size_must_be_72, sizeof(CNonRenderedBit) == 72);
PSX_LAYOUT_CHECK(Bit2_CFT4Bit_size_must_be_96, sizeof(CFT4Bit) == 96);
PSX_LAYOUT_CHECK(Bit2_CFlatBit_size_must_be_112, sizeof(CFlatBit) == 112);
PSX_LAYOUT_CHECK(Bit2_CMotionBlur_size_must_be_112, sizeof(CMotionBlur) == 112);
PSX_LAYOUT_CHECK(Bit2_SLineSeg_size_must_be_16, sizeof(SLineSeg) == 16);
PSX_LAYOUT_CHECK(Bit2_CPolyLine_size_must_be_96, sizeof(CPolyLine) == 96);
PSX_LAYOUT_CHECK(Bit2_CGPolyLine_size_must_be_100, sizeof(CGPolyLine) == 100);
PSX_LAYOUT_CHECK(Bit2_CGLine_size_must_be_104, sizeof(CGLine) == 104);
typedef char
    Bit2_CItem_position_prefix_size_must_be_16[(sizeof(CItemPositionPrefix) == 16) ? 1 : -1];
typedef char
    Bit2_CBody_position_prefix_size_must_be_16[(sizeof(CBodyPositionPrefix) == 16) ? 1 : -1];

/** Absolute-addressed list heads and the shared zero vector used by BIT2. */
#define BITSTATE_DECLARE_POLY_LINE_LIST
#include "BITSTATE.h"
#define BITSTATE_DECLARE_G_LINE_LIST
#include "BITSTATE.h"
#define BITSTATE_DECLARE_G_POLY_LINE_LIST
#include "BITSTATE.h"
#define ZEROVECTOR_SCALAR_DECLARATION
#include "ZEROVECTOR.h"
#undef ZEROVECTOR_SCALAR_DECLARATION

/** Typed dependencies owned by BIT and VECTOR. */
#define BIT_DECLARE_MOTION_BLUR_CONSTRUCTOR
#include "BIT.h"
#define Bit2_ConstructMotionBlur \
    BitMotionBlurConstructorABI::__11CMotionBlurRC7CVectorR7CVectorPciii
#include "CVECTOROPS.h"

/**
 * A short-lived generated line attached to a moving body while grinding.
 *
 * The owner-local base layout supplies the recovered field types without
 * importing unrelated generated aggregate declarations.
 */
struct CGrindSpark : CGLine
{
    CVector mOldPos;
    CBody *mpParent;

    CGrindSpark(CBody *pParent, CVector &pos, int vel, int gravity, int life);
    virtual ~CGrindSpark();
    /** Releases bit-owned storage through the CBit allocator. */
    static void operator delete(void *p) { CBit::operator delete(p); }
    void Move();
};


/** Emits a configurable group of short-lived motion-blur particles. */

PSX_LAYOUT_CHECK(Bit2_CGrindSpark_class_size_must_be_120, sizeof(CGrindSpark) == 120);
PSX_LAYOUT_CHECK(Bit2_CSmokeGenerator_size_must_be_96, sizeof(CSmokeGenerator) == 96);
// === Extern vtable symbols ===

/** Returns the full vector stored at the linker-visible `ZeroVector` base. */
static inline const CVector &Bit2_ZeroVector()
{
    return *reinterpret_cast<const CVector *>(&ZeroVector);
}

/** Returns the proven CItem-position prefix of a body. */
static inline const CVector &Bit2_BodyPosition(const CBody *body)
{
    return reinterpret_cast<const CBodyPositionPrefix *>(body)->CItem.mPos;
}
#define BIT2_DECLARE_MOTION_BLUR_ANIMATION_VIEW
#include "BIT2.h"

/** Animation name used by the motion-blur bit effect. */
namespace Bit2AddressViewOwners
{
extern "C"
{
static char s_Smoke[8] PSX_SECTION(".sdata") = "Smoke";
}
}

/*
 * This owner's five CBit subclass vtables, which directly follow the animation
 * name in the original small-data contribution.  C++ forbids taking a
 * destructor's address, so each dispatch slot goes through an addressable
 * declaration of the symbol this TU already defines; `Move__4CBit` is BIT's.
 *
 * Each table is four consecutive eight-byte-aligned small-data words rather
 * than an array, so -G8 keeps emitting the target's `addiu $vX, $gp, off`
 * instead of an absolute lui/addiu pair.
 */
/** Addressable destructor entries used by this owner's five manual vtables. */
static inline void Bit2_SetSegmentSemiTransparent(int index, SLineSeg *segments)
{
    segments[index].code |= 2;
}

// === Function implementations (address order) ===

/**
 *
 * Address:   0x80036848
 * Mangled:   __9CPolyLinei
 * Demangled: CPolyLine::CPolyLine(int)
 *            Purpose: allocate the segment buffer, initialize segments, and attach to the polyline list.
 *
 * @param numsegs  Number of line segments to allocate and initialize.
 * @return `this` pointer (GCC 2.x ctor convention).
 */
CPolyLine::CPolyLine(int numsegs)
{
    int blockSize;
    int i;
    mSegs = static_cast<SLineSeg *>(Mem_New(numsegs << 4, 0, 1));
    blockSize = Mem_GetBlockSize(mSegs);
    TotalBitUsage += 4 + blockSize;
    for (i = 0; i < numsegs; i++)
    {
        *(unsigned int *)&mSegs[i].r = 0x40FFFFFFu;
        mSegs[i].End = Bit2_ZeroVector();
    }
    mNumSegs = numsegs;
    AttachTo(&PolyLineList);
}


/**
 *
 * Address:   0x80036928
 * Mangled:   _._9CPolyLine
 * Demangled: CPolyLine::~CPolyLine()
 *            Purpose: release the segment buffer, detach from the polyline list, and chain to the base destructor.
 *
 */
CPolyLine::~CPolyLine()
{
    SLineSeg *segments;
    CPolyLine **listHead;
    int blockSize;
    int remainingUsage;
    SLineSeg *segmentsToFree;
    segments = mSegs;
    blockSize = Mem_GetBlockSize(segments);
    remainingUsage = TotalBitUsage;
    segmentsToFree = mSegs;
    remainingUsage = remainingUsage - 4;
    remainingUsage = remainingUsage - blockSize;
    TotalBitUsage = remainingUsage;
    Mem_Delete(segmentsToFree);
    listHead = &PolyLineList;
    DeleteFrom(listHead);
}


/**
 * CPolyLine::SetSemiTransparent()
 *
 * Address:   0x800369B4
 * Mangled:   SetSemiTransparent__9CPolyLine
 * Demangled: CPolyLine::SetSemiTransparent(void)
 *            Marks every packed segment command as semitransparent.
 *
 */
void CPolyLine::SetSemiTransparent()
{
    for (int i = 0; i < mNumSegs; i++)
    {
        Bit2_SetSegmentSemiTransparent(i, mSegs);
    }
}


/**
 *
 * Address:   0x80036A00
 * Mangled:   __10CGPolyLinei
 * Demangled: CGPolyLine::CGPolyLine(int)
 *            Purpose: allocate the segment buffer, initialize segments, and attach to the generated polyline list.
 *
 * @param numsegs  Number of generated line segments to allocate and initialize.
 * @return `this` pointer (GCC 2.x ctor convention).
 */
CGPolyLine::CGPolyLine(int numsegs)
{
    int blockSize;
    int i;
    mSegs = static_cast<SLineSeg *>(Mem_New(numsegs << 4, 0, 1));
    blockSize = Mem_GetBlockSize(mSegs);
    TotalBitUsage += 4 + blockSize;
    for (i = 0; i < numsegs; i++)
    {
        *(unsigned int *)&mSegs[i].r = 0x50FFFFFFu;
        mSegs[i].End = Bit2_ZeroVector();
    }
    mNumSegs = numsegs;
    AttachTo(&GPolyLineList);
    mStartR = 0xff;
    mStartG = 0xff;
    mStartB = 0xff;
    mCode = 0x50;
}


/**
 *
 * Address:   0x80036AF8
 * Mangled:   _._10CGPolyLine
 * Demangled: CGPolyLine::~CGPolyLine()
 *            Purpose: release the segment buffer, detach from the generated polyline list, and chain to the base destructor.
 *
 */
CGPolyLine::~CGPolyLine()
{
    SLineSeg *segments;
    CGPolyLine **listHead;
    int blockSize;
    int remainingUsage;
    SLineSeg *segmentsToFree;
    segments = mSegs;
    blockSize = Mem_GetBlockSize(segments);
    remainingUsage = TotalBitUsage;
    segmentsToFree = mSegs;
    remainingUsage = remainingUsage - 4;
    remainingUsage = remainingUsage - blockSize;
    TotalBitUsage = remainingUsage;
    Mem_Delete(segmentsToFree);
    listHead = &GPolyLineList;
    DeleteFrom(listHead);
}


/**
 * CGPolyLine::SetSemiTransparent()
 *
 * Address:   0x80036B84
 * Mangled:   SetSemiTransparent__10CGPolyLine
 * Demangled: CGPolyLine::SetSemiTransparent(void)
 *            Marks every segment and the line's own draw command as
 *            semitransparent.
 *
 */
void CGPolyLine::SetSemiTransparent()
{
    for (int i = 0; i < mNumSegs; i++)
    {
        Bit2_SetSegmentSemiTransparent(i, mSegs);
    }
    mCode = mCode | 2;
}


/**
 * CSmokeGenerator::~CSmokeGenerator()
 *
 * Address:   0x80036BDC
 * Mangled:   _._15CSmokeGenerator
 * Demangled: CSmokeGenerator::~CSmokeGenerator()
 *
 */
CSmokeGenerator::~CSmokeGenerator()
{
}


/**
 *
 * Address:   0x80036C2C
 * Mangled:   Move__15CSmokeGenerator
 * Demangled: CSmokeGenerator::Move(void)
 *            Purpose: spawn and tint smoke motion-blur particles, age the generator, and kill it when its lifetime expires.
 *
 */
void CSmokeGenerator::Move()
{
    int i = 0;
    CVector upvel;
    upvel.vx = 0;
    int count = mPuffs;
    CVector *upvelPtr = &upvel;
    upvelPtr->vy = 0;
    upvelPtr->vz = 0;
    if (count > 0)
    {
        int defaultAge = 100;
        int loopCount;
        do
        {
            int r = Rnd(mVRandom);
            int yoff = mVBase + r;
            yoff = -yoff;
            upvel.vy = yoff << 12;
            CMotionBlur *foo = static_cast<CMotionBlur *>(CBit::operator new(sizeof(CMotionBlur)));
            if (foo != 0)
            {
                int r2 = Rnd(mScaleRandom);
                int animLen = mScaleBase + r2;
                foo = Bit2_ConstructMotionBlur(foo, &mPos, &upvel, s_Smoke, animLen, 0, 10);
            }
            foo->mFrigDeltaZ = defaultAge;
            int randFrame = Rnd(0x1000);
            foo->mAngle = static_cast<short>(randFrame);
            unsigned int cr = mR;
            unsigned int cg = mG;
            unsigned int cb = mB;
            foo->SetTint(cr, cg, cb);
            loopCount = mPuffs;
            i++;
        } while (i < loopCount);
    }
    int age = static_cast<unsigned short>(mAge);
    int maxAge = mLifetime;
    age = age + 1;
    mAge = static_cast<short>(age);
    short sAge = static_cast<short>(age);
    if (sAge == maxAge)
    {
        if (static_cast<unsigned short>(sAge) != 0xffff)
        {
            Die();
        }
    }
}


/**
 * CGLine::CGLine()
 *
 * Address:   0x80036D6C
 * Mangled:   __6CGLine
 * Demangled: CGLine::CGLine(void)
 *            Constructor: calls CBit parent, sets colors, vtable, attaches to GLineList (absolute address)
 *
 */
CGLine::CGLine()
{
    mCodeBGR0 = 0x50808080;
    mPadBGR1 = 0x55808080;
    AttachTo(&GLineList);
}

/**
 * CGLine::~CGLine()
 *
 * Address:   0x80036DC4
 * Mangled:   _._6CGLine
 * Demangled: CGLine::~CGLine()
 *            Destructor: sets vtable, calls DeleteFrom, calls parent ~CBit(flag=0), conditionally deletes
 *
 */
CGLine::~CGLine()
{
    DeleteFrom(&GLineList);
}


/**
 *
 * Address:   0x80036E24
 * Mangled:   __11CGrindSparkP5CBodyR7CVectoriii
 * Demangled: CGrindSpark::CGrindSpark(CBody *, CVector &, int, int, int)
 *            Builds a grind spark line in body-relative coordinates.
 *
 * @param pParent  Body whose position offsets the generated line.
 * @param pos  Spark position relative to the parent body.
 * @param vel  Signed random velocity range.
 * @param gravity  Vertical acceleration applied to the spark.
 * @param life  Exclusive upper bound used to randomize the lifetime.
 * @return `this` pointer (GCC 2.x ctor convention).
 */
CGrindSpark::CGrindSpark(CBody *pParent, CVector &pos, int vel, int gravity, int life)
{

    int vel2;
    if (vel < 0)
    {
        int magnitude = -vel;
        vel2 = -((magnitude >> 1) + Rnd(magnitude));
    }
    else
    {
        vel2 = (vel >> 1) + Rnd(vel);
    }
    Bit_CalculateSparkVelocity(mVel, vel2);

    mAcc.vy = gravity;
    mFric.Set(3, 3, 3);
    mLifetime = static_cast<unsigned short>(Rnd(life) + 1);
    mpParent = pParent;
    mOldPos = pos;
    mPos = pos;

    CVector end = pos + Bit2_BodyPosition(mpParent);
    mEnd = end;
    mStart = mEnd;
    mCodeBGR0 = 0x52000080;
    int color = Rnd(0x9f);
    mPadBGR1 = 0x55000000;
    mCodeBGR0 |= ((color >> 5) + 2) << 12;
}


/**
 * CGrindSpark::~CGrindSpark()
 *
 * Address:   0x80036F88
 * Mangled:   _._11CGrindSpark
 * Demangled: CGrindSpark::~CGrindSpark()
 *
 */
CGrindSpark::~CGrindSpark()
{
}


/**
 *
 * Address:   0x80036FD8
 * Mangled:   Move__11CGrindSpark
 * Demangled: CGrindSpark::Move(void)
 *
 */
void CGrindSpark::Move()
{
    int px = mPos.vx;
    int py = mPos.vy;
    int pz = mPos.vz;

    int nx = px + mVel.vx;
    int ny = py + mVel.vy;
    int nz = pz + mVel.vz;

    int sx = reinterpret_cast<const CBodyPositionPrefix *>(mpParent)->CItem.mPos.vx;
    int sy = reinterpret_cast<const CBodyPositionPrefix *>(mpParent)->CItem.mPos.vy;
    int sz = reinterpret_cast<const CBodyPositionPrefix *>(mpParent)->CItem.mPos.vz;

    mOldPos.vx = px;
    mOldPos.vy = py;
    mOldPos.vz = pz;

    mEnd.vx = px + sx;
    mEnd.vy = py + sy;
    mEnd.vz = pz + sz;

    mPos.vx = nx;
    mPos.vy = ny;
    mPos.vz = nz;

    mStart.vx = nx + sx;
    mStart.vy = ny + sy;
    mStart.vz = nz + sz;

    nx = mVel.vx + mAcc.vx;
    ny = mVel.vy + mAcc.vy;
    nz = mVel.vz + mAcc.vz;

    nx -= nx >> 3;
    ny -= ny >> 3;
    nz -= nz >> 3;

    mVel.vx = nx;
    mVel.vy = ny;
    mVel.vz = nz;

    if (++mAge >= mLifetime)
    {
        Die();
    }
}
