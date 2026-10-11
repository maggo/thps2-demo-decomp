// MEDALS.cpp -- Medal pickup ownership, physics, and camera-relative creation.
// Original: MEDALS.CPP
// Functions: 5
// Address range: 0x80074DC4 - 0x800750CC
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#define CCLASS_POLY_ITEM_FAMILY
#include "CCLASS_POLY.h"
#include "CFRICTION.h"
#include "OB.h"
#include <STDDEF.H>
#include <LIBGTE.H>
#include <INLINE_C.H>
#include "gte_extensions.h"

/** Return caller-provided storage for an owner constructor. */
inline void *operator new(unsigned int, void *address)
{
    return address;
}

struct CMedal;
struct CPowerUp;
struct SLight;

enum MedalPowerUpType {
    MedalPowerUpGold = 0x664,
    MedalPowerUpSilver = 0x665,
    MedalPowerUpBronze = 0x666
};

enum MedalCreationConstant {
    MedalItemVisible = 0x200,
    MedalInfiniteLifetime = 0xFFFF,
    MedalWobbleSpeed = 80
};

#include "SCAMERA.h"

/** Power-up fields initialized after the shared CPowerUp constructor returns. */
struct CPowerUp : CBody {
    void *mpGlow;
    unsigned short mGlowRadiusOrg;
    unsigned short mGlowRadiusAmp;
    unsigned char mHasNode;
    unsigned char mIs3d;
    unsigned char mDropping;
    unsigned char mDropForever;
    unsigned char mHoverHeight;
    unsigned short mNodeIndex;
    int mGroundY;
    struct CVector mOrgPos;
    unsigned short mT;
    unsigned short mMaxWobbleAmplitude;
    unsigned short mWobbleAmplitude;
    unsigned short mWobbleSpeed;
    unsigned short mLifetime;
    unsigned int mTimer;

    /** Initialize a power-up in caller-provided CItem storage. */
    CPowerUp(unsigned short powerUpType, const CVector &position,
             const CVector &velocity, unsigned int flags, int lifetime);
    virtual ~CPowerUp();
};

/** Medal-specific state following the 264-byte CBody base. */
struct CMedal : CBody {
    unsigned char mHasNode;
    unsigned char mIs3d;
    unsigned char mDropping;
    unsigned char mDropForever;
    unsigned char mHoverHeight;
    unsigned short mNodeIndex;
    int mGroundY;
    struct CVector mOrgPos;
    unsigned short mT;
    unsigned short mMaxWobbleAmplitude;
    unsigned short mWobbleAmplitude;
    unsigned short mWobbleSpeed;
    unsigned short mLifetime;

    virtual ~CMedal();
    void DeleteStuff();
    void DoPhysics();
    void AI();
};

typedef char CMedal_size_must_be_300[(sizeof(CMedal) == 300) ? 1 : -1];
typedef char CPowerUp_size_must_be_312[(sizeof(CPowerUp) == 312) ? 1 : -1];

#include "POWERUP.h"
#include "CAREER.h"
#include "SLIGHT.h"

CPowerUp *Medal_Create(EMedalType t, int x, int y, int z, int Size, int yvel);

// === External globals ===
#include "RCOSSIN.h"
#include "CURRENTCAMERA.h"
#include "ZEROVECTOR.h"

/** Read one packed word for the scalar GTE transfer macros. */
#define MEDAL_PACKED_WORD(value, index) \
    (reinterpret_cast<int *>(&(value))[index])

/**
 * Cool white light used by the medal pickup model.
 */
SLight Medal_DefaultLight __attribute__((section(".data"))) = {
    {
        {0, 4096, 0},
        {0, -4096, 0},
        {0, 0, 4096},
    },
    0,
    {
        {2944, 0, 0},
        {0, 2944, 0},
        {0, 0, 2944},
    },
    0,
    {64, 64, 64},
};

/**
 * Releases medal-owned state before destroying the CBody base.
 */
CMedal::~CMedal()
{
    DeleteStuff();
}

/**
 * Releases resources owned exclusively by a medal.
 * Medals currently own no resources beyond their CBody storage.
 */
void CMedal::DeleteStuff()
{
}

/**
 * Restores the pickup's orbit origin and applies its vertical sine wobble.
 */
void CMedal::DoPhysics()
{
    struct CSVector *angles = &mAngles;
    *angles += mAngVel;
    angles->Mask();
    // Keeping the table base live here preserves seven target instructions.
    short *trigTable = &rcossin_tbl[0];
    mPos = mOrgPos;
    u16 angle = mT;
    u16 speed = mWobbleAmplitude;
    int sinIdx = (angle & 0xFFF) << 1;
    short sinVal = trigTable[sinIdx];
    int product = static_cast<int>(speed) * static_cast<int>(sinVal);
    if (product < 0)
        product += 0xFFF;
    int yDelta = (product >> 12) << 12;
    int curY = mPos.vy;
    u16 angleStep = mWobbleSpeed;
    mPos.vy = curY + yDelta;
    mT = angle + angleStep;
}

/**
 * Advances the medal's per-frame hover motion.
 */
void CMedal::AI()
{
    DoPhysics();
}

/**
 * Creates a medal power-up at a camera-relative position.
 *
 * @param t Medal color/model to create.
 * @param x Camera-relative X coordinate.
 * @param y Camera-relative Y coordinate.
 * @param z Camera-relative Z coordinate.
 * @param Size Uniform pickup scale.
 * @param yvel Initial and maximum wobble amplitude.
 * @return The initialized power-up.
 */
CPowerUp *Medal_Create(EMedalType t, int x, int y, int z, int Size, int yvel)
{
    SVECTOR vec;
    VECTOR vec2;
    CVector MedalPos;
    CPowerUp *Medal;

    vec.vy = static_cast<short>(y);
    vec.vx = static_cast<short>(x);
    vec.vz = static_cast<short>(z);

    {
        SCamera *camera = pCurrentCamera;
        gte_ldrot0(MEDAL_PACKED_WORD(camera->Transform, 0));
        gte_ldrot1(MEDAL_PACKED_WORD(camera->Transform, 1));
        gte_ldrot2(MEDAL_PACKED_WORD(camera->Transform, 2));
        gte_ldrot3(MEDAL_PACKED_WORD(camera->Transform, 3));
        gte_ldrot4(MEDAL_PACKED_WORD(camera->Transform, 4));
    }
    gte_ldvxy0(MEDAL_PACKED_WORD(vec, 0));
    gte_ldvz0(MEDAL_PACKED_WORD(vec, 1));
    gte_mvmva(0, 0, 0, 3, 0);
    gte_stlvnl(&vec2);

    {
        SCamera *camera = pCurrentCamera;
        MedalPos.vx = vec2.vx + (camera->Position.vx << 12);
        MedalPos.vy = vec2.vy + (camera->Position.vy << 12);
        MedalPos.vz = vec2.vz + (camera->Position.vz << 12);
    }

    if (t == MEDAL_SILVER)
    {
        goto make_silver;
    }
    if (static_cast<int>(t) < 7)
    {
        if (t == MEDAL_GOLD)
        {
            goto make_gold;
        }
        goto init_medal;
    }
    if (t == MEDAL_BRONZE)
    {
        goto make_bronze;
    }
    goto init_medal;

make_gold:
    Medal = static_cast<CPowerUp *>(CItem::operator new(sizeof(CPowerUp)));
    if (Medal != 0)
    {
        Medal = ::new (Medal) CPowerUp(
            MedalPowerUpGold, MedalPos, ZeroVector, 0,
            MedalInfiniteLifetime);
    }
    goto init_medal;

make_silver:
    Medal = static_cast<CPowerUp *>(CItem::operator new(sizeof(CPowerUp)));
    if (Medal != 0)
    {
        Medal = ::new (Medal) CPowerUp(
            MedalPowerUpSilver, MedalPos, ZeroVector, 0,
            MedalInfiniteLifetime);
    }
    goto init_medal;

make_bronze:
    Medal = static_cast<CPowerUp *>(CItem::operator new(sizeof(CPowerUp)));
    if (Medal != 0)
    {
        Medal = ::new (Medal) CPowerUp(
            MedalPowerUpBronze, MedalPos, ZeroVector, 0,
            MedalInfiniteLifetime);
    }

init_medal:
    Medal->mWobbleSpeed = MedalWobbleSpeed;
    short scale = static_cast<short>(Size);
    u16 flags = Medal->mFlags;
    Medal->mScale.vx = scale;
    flags |= MedalItemVisible;
    Medal->mFlags = flags;
    CSVector *MedalScale = &Medal->mScale;
    MedalScale->vy = scale;
    MedalScale->vz = scale;
    Medal->mWobbleAmplitude = static_cast<short>(yvel);
    Medal->mMaxWobbleAmplitude = static_cast<short>(yvel);

    return Medal;
}
