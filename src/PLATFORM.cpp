// PLATFORM.cpp -- Scripted and physics-driven environmental platforms.
// Original: PLATFORM.CPP
// Functions: 13
// Address range: 0x8003E690 - 0x8004080C
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#define CCLASS_POLY_ITEM_FAMILY
#define CCLASS_POLY_BADDY_FAMILY
#include "CCLASS_POLY.h"
#include "PLATFORM.h"
#include "MAIN.h"
#include "MECH.h"
#include "PHYSICSSTATE.h"
#include "SFX.h"
#include "OB.h"
#include "SPOOL.h"
#include "globals.h"
#include "M3DZONE.h"
#include "MIPS.h"
#define BADDY_LAYOUT_DECLARATIONS
#include "BADDY.h"
#undef BADDY_LAYOUT_DECLARATIONS
#include <STDDEF.H>
#include <LIBGTE.H>
#include "SMODEL.h"
#include "PSXREGION.h"
#define M3DCOLIJ_LINE_INFO_LAYOUT
#include "M3DCOLIJ.h"
#undef M3DCOLIJ_LINE_INFO_LAYOUT

struct SLight;

/** Composition-only item view used while scanning environmental objects. */
struct PlatformCItemOwner {
    u16 mFlags;
    u16 mInquiry;
    struct CVector mPos;
    struct CSVector mAngles;
    u16 mModel;
    char mDummyFrame;
    u8 mTintIndex;
    u8 mDummyAnim;
    u8 mRegion;
    struct PlatformCItemOwner *mNextItem;
    u32 mRGB;
    struct CSVector mScale;
    u16 _padScale;
    u32 mTRN;
    struct PlatformCItemOwner *mPreviousItem;
    u32 mStoredRGB;
    u8 mPredatorEffectType;
    u8 mPredatorEffectFade;
    u16 mType;
    SLight *mpLight;
    u16 mFlashTimer;
    s16 mFlash_dR;
    s16 mFlash_dG;
    s16 mFlash_dB;
    void *vtable;
};

/** Packed six-halfword interpretation used by platform collision helpers. */
struct PlatformModelBounds {
    short Half[6];
};

/** Scripted bouncing-platform object layout. */
struct CPlatform : CBaddy {
    /** Initialize a scripted platform from one trigger record. */
    CPlatform(short *pInfo, int nodeIndex);
    virtual ~CPlatform();
    u16 mScaleXTimer;
    u16 mScaleYTimer;
    u16 mScaleZTimer;
    s16 mScaleXAdjust;
    s16 mScaleYAdjust;
    s16 mScaleZAdjust;
    s16 mBruceHealthAdjust;
    u16 mNumBounces;
    u16 mType;
    u16 mWidth;
    u16 mHeight;
    u16 mDepth;
    u16 mDeathTimer;
    struct CSVector mTargetAngles;
    u32 mTrodUpon;
    union {
        u32 mNotTrodUponTimer;
        s16 mNotTrodUponScriptValue;
    };
    u32 mLoopingSound;
    int mLoopingSoundUpdate;
    struct CVector mBoundingBox;
    /** Apply this platform's configured bounce response to a skater. */
    void Bounce(CBruce *pSkater, const CVector &direction);
    void BouncyAI();
    /** Run one platform AI update. */
    virtual void AI();
    /** Apply one platform hit and report whether it was accepted. */
    virtual int Hit(int damage, const CVector &knock, int whatHit);
    /** Advance this platform's translation and rotation. */
    void DoPhysics();
    /** Update this platform's movement target. */
    void MoveTo(CVector &pos);
    /** No-op pattern hook used when script processing is disabled. */
    void ProcessPattern();
    /** Execute one scripted platform command. */
    virtual int ExecuteCommand(unsigned short command);
    /** Store one script-visible platform variable. */
    virtual void SetVariable(unsigned short variable);
    /** Read one script-visible platform variable. */
    virtual short GetVariable(unsigned short variable);
};

/**
 * Skater layout slice exposing the inherited CSuper prefix.
 * The known complete size prevents accidental by-value stride changes.
 */
struct CBruce : CSuper {
    u8 _opaqueTail[5228 - 400];

    /** Drive one controller vibration actuator for this skater. */
    void Vibrate(int time, int motor, int value);
};

typedef char CItem_platform_size_check[
    (sizeof(struct PlatformCItemOwner) == 76) ? 1 : -1];
typedef char Platform_SDK_SVECTOR_size_must_be_8[
    (sizeof(SVECTOR) == 8) ? 1 : -1];
typedef char CPlatform_size_check[(sizeof(struct CPlatform) == 592) ? 1 : -1];
typedef char CPlatform_public_size_check[
    (sizeof(struct CPlatform) == PLATFORM_OBJECT_SIZE) ? 1 : -1];
typedef char CBruce_platform_size_check[
    (sizeof(struct CBruce) == 5228) ? 1 : -1];

#include "SHATTER.h"
#include "TRIG.h"
#include "UTILS.h"

/** Assign all three components (the model vectors carry no Set method). */
static inline void PlatformSet(CVector &v, int x, int y, int z)
{
    v.vx = x;
    v.vy = y;
    v.vz = z;
}

static inline void PlatformSet(CSVector &v, int x, int y, int z)
{
    v.vx = x;
    v.vy = y;
    v.vz = z;
}

/** Return the unsigned magnitude of a signed fixed-angle component. */
static inline int AngleMagnitude(short angle)
{
    int value = angle;
    int sign = value >> 31;
    return (value ^ sign) - sign;
}

/** Return the unsigned magnitude of a signed fixed-point component. */
static inline int VectorMagnitude(int value)
{
    int sign = value >> 31;
    return (value ^ sign) - sign;
}

/** View an owner-local vector layout through its canonical public type. */
static inline CVector &PlatformVector(CVector &vector)
{
    return reinterpret_cast<CVector &>(vector);
}

/** View an owner-local vector layout through its canonical public type. */
static inline const CVector &PlatformVector(const CVector &vector)
{
    return reinterpret_cast<const CVector &>(vector);
}

/** View a canonical vector through the identical owner-local layout. */
static inline CVector &PlatformOwnerVector(CVector &vector)
{
    return reinterpret_cast<CVector &>(vector);
}

/** View the owner-local item prefix through SHATTER's opaque public type. */
static inline Item *PlatformShatterItem(CItem &item)
{
    return reinterpret_cast<Item *>(&item);
}

/*
 * GCC 2.91 does not inline the equivalent typed helpers inside AI and
 * ExecuteCommand. These owner-view macros keep those zero-code ABI boundaries
 * named without introducing calls in either large function.
 */
#define PLATFORM_VECTOR_VIEW(vector) reinterpret_cast<CVector &>(vector)
#define PLATFORM_CONST_VECTOR_VIEW(vector)                                  \
    reinterpret_cast<const CVector &>(vector)
#define PLATFORM_SHORT_VECTOR_VIEW(vector)                                  \
    reinterpret_cast<CSVector &>(vector)
#define PLATFORM_CONST_SHORT_VECTOR_VIEW(vector)                            \
    reinterpret_cast<const CSVector &>(vector)
#define PLATFORM_SHATTER_ITEM_POINTER(item) reinterpret_cast<Item *>(item)

/** Align serialized script data to its next 32-bit word boundary. */
#define PLATFORM_ALIGNED_SCRIPT(type, script)                                \
    reinterpret_cast<type *>(                                                \
        (reinterpret_cast<int>(script) + 3) & ~3)

/** Script opcodes handled directly by CPlatform. */
enum PlatformCommand {
    PlatformCommandDie = 0x4205,
    PlatformCommandMoveTo = 0x4220,
    PlatformCommandMoveToNode = 0x4221,
    PlatformCommandMoveRelative = 0x4222,
    PlatformCommandWaitUntilTrodUpon = 0x4300,
    PlatformCommandShatter = 0x4301,
    PlatformCommandSetBoundingBox = 0x4302,
    PlatformCommandSetBruceHealthAdjust = 0x4303,
    PlatformCommandScale = 0x4304,
    PlatformCommandSetCollision = 0x4305,
    PlatformCommandScaleX = 0x4306,
    PlatformCommandScaleY = 0x4307,
    PlatformCommandScaleZ = 0x4308,
    PlatformCommandSetBounceType = 0x4309,
    PlatformCommandPlayLoopingSound = 0x4507,
    PlatformCommandPlayPositionalLoopingSound = 0x4508,
    PlatformCommandStopLoopingSound = 0x4509,
};

/** Script variables owned by CPlatform rather than its CBaddy base. */
enum PlatformVariable {
    PlatformVariableAngularVelocity = 0x2127,
    PlatformVariableAngularAcceleration = 0x2128,
    PlatformVariableApplyGravity = 0x2123,
    PlatformVariableModelIndex = 0x2124,
    PlatformVariableModelChecksum = 0x212F,
    PlatformVariableVelocity = 0x2134,
    PlatformVariableAngles = 0x2137,
    PlatformVariableNotTrodUponTimer = 0x2200,
};

/** Platform-owned state bits stored in CBaddy::mSpecificFlags. */
enum PlatformStateFlag {
    PlatformMovingToTarget = 1 << 0,
    PlatformHasBoundingBox = 1 << 2,
    PlatformBounceEnabled = 1 << 4,
    PlatformBouncing = 1 << 5,
};

/** CItem flags manipulated by platform construction and script commands. */
enum PlatformItemFlag {
    PlatformItemShattered = 1 << 0,
    PlatformItemCollision = 1 << 3,
    PlatformItemBounceContact = 1 << 5,
    PlatformItemEnvironmental = 1 << 8,
    PlatformItemScaleEnabled = 1 << 9,
};

/** Fixed platform dimensions and initial gameplay values. */
enum PlatformConstant {
    PlatformFixedOne = 1 << 12,
    PlatformHalfTurn = PlatformFixedOne / 2,
    PlatformQuarterTurn = PlatformFixedOne / 4,
    PlatformEighthTurn = PlatformFixedOne / 8,
    PlatformAngleMask = PlatformFixedOne - 1,
    PlatformOrthogonalAngleMask = 3 * PlatformQuarterTurn,
    PlatformGravityPerFrame = 8 * PlatformFixedOne,
    PlatformSoundVolume = 2 * PlatformFixedOne,
    PlatformVelocityRounding = PlatformFixedOne / 2,
    PlatformVelocityDeadZone = PlatformFixedOne + 1,
    PlatformTurnNumerator = 2 * PlatformFixedOne - 32,
    PlatformMaxAngularAcceleration = PlatformFixedOne / 16,
    PlatformLowVerticalSpeed = 12 * PlatformFixedOne,
    PlatformSoftBounceVelocity = -32 * PlatformFixedOne,
    PlatformStandardBounceVelocity = -64 * PlatformFixedOne,
    PlatformStrongBounceVelocity = -80 * PlatformFixedOne,
    PlatformCollisionMargin = 20 * PlatformFixedOne,
    PlatformScriptVariableFlag = 1 << 13,
    PlatformScriptWordMask = (1 << 16) - 1,
    PlatformInitialItemFlags = 0x111,
    PlatformObjectType = 0x192,
    PlatformDefaultMoveSpeed = 0x20,
};

// === Extern vtable/list declarations ===
#define BODYLISTS_DECLARE_ENVIRONMENTAL_OBJECT_LIST
#include "BODYLISTS.h"
#include "MECHLIST.h"
#include "GLEVEL.h"
#include "CURRENTOBJFILE.h"

// === ABI address views and typed dependencies ===
#define M3DMATHS_TYPED_API
#include "M3DMATHS.h"
#undef M3DMATHS_TYPED_API
#include "CVECTOROPS.h"

// === Function implementations (address order) ===

/**
 * Build and initialize a platform from its serialized trigger-node data.
 *
 * @param p_info Cursor into the platform's initialization record.
 * @param node_index Trigger node that owns the platform.
 */
CPlatform::CPlatform(short *p_info, int node_index)
{
    mpCreatedByPlayer = pCurrentPlayer;
    InitItem(pCurrentObjFile);
    AttachTo(&EnvironmentalObjectList);
    unsigned short flags = mFlags;
    mType = PlatformObjectType;
    flags |= PlatformInitialItemFlags;
    flags &= 0xFFFD;
    mFlags = flags;
    short *pos = SquirtPos(p_info);
    short *angles = SquirtAngles(pos);
    mpScript = reinterpret_cast<u16 *>(angles);
    mNode = static_cast<unsigned short>(node_index);
    mLoopingSoundUpdate = -1;
    mBaddyAttributes[0] = PlatformDefaultMoveSpeed;
    mDoScript = 1;
}

/**
 * Detach a platform, stop its looping sound, and destroy its baddy state.
 */
CPlatform::~CPlatform()
{
    DeleteFrom(&EnvironmentalObjectList);
    if (mLoopingSound)
    {
        SFX_Stop(mLoopingSound);
        mLoopingSound = 0;
    }
}

/**
 * Apply the platform's configured bounce response to a skater.
 *
 * @param pSkater Skater receiving the bounce response.
 * @param Direction Incoming horizontal velocity direction.
 */
void CPlatform::Bounce(CBruce *pSkater, const CVector &Direction)
{
    CPlatform *platform = this;
    int Height;
    if (!(platform->mSpecificFlags & PlatformBounceEnabled))
        return;
    if (platform->mSpecificFlags & PlatformBouncing)
        return;

    CVector Dir = Direction;
    Dir.vy = 0;
    int Speed = Dir.Length();

    platform->mNumBounces = 0;
    platform->mSpecificFlags |= PlatformBouncing;
    platform->mFlags |= PlatformItemBounceContact;
    platform->mTargetAngles.vy = Rnd(PlatformFixedOne);
    int randomAngleX = (Rnd(2) << 11) - PlatformQuarterTurn;
    platform->mTargetAngles.vx =
        platform->mAngles.vx + randomAngleX;
    int randomAngleZ = (Rnd(2) << 11) - PlatformQuarterTurn;
    platform->mTargetAngles.vz =
        platform->mAngles.vz + randomAngleZ;

    switch (platform->mType)
    {
    case 1:
        SFX_PlayX(0x68, PlatformSoundVolume, 0);
        goto standard_bounce;
    case 3:
        SFX_PlayX(0x3C, PlatformSoundVolume, 0);
    standard_bounce:
        SFX_Grunt(pSkater);
        pSkater->Vibrate(6, 1, 0x78);

        Height = Speed < 40
            ? PlatformSoftBounceVelocity
            : PlatformStandardBounceVelocity;
        if (Speed < 18)
        {
            platform->mTargetAngles.vy =
                platform->mAngles.vy +
                Rnd(PlatformQuarterTurn) - PlatformEighthTurn;
            platform->mTargetAngles.vx =
                (platform->mAngles.vx +
                 PlatformEighthTurn) & PlatformOrthogonalAngleMask;
            platform->mTargetAngles.vz =
                (platform->mAngles.vz +
                 PlatformEighthTurn) & PlatformOrthogonalAngleMask;
        }

        PlatformSet(platform->mVel, Direction.vx, Height, Direction.vz);
        return;

    case 2:
    case 4:
    case 5:
    {
        if (platform->mType == 2)
        {
            int sound = GLevel == 0 ? Rnd(2) + 0x53 : 0x6A;
            SFX_PlayX(sound, PlatformSoundVolume, 0);
        }
        else if (platform->mType == 4)
        {
            SFX_Grunt(pSkater);
            SFX_PlayX(0x52, PlatformSoundVolume, 0);
        }

        pSkater->Vibrate(2, 1, 0xB4);
        PlatformSet(platform->mVel, Direction.vx + (Direction.vx >> 1),
                                               PlatformStrongBounceVelocity,
                                               Direction.vz + (Direction.vz >> 1));

        if (AngleMagnitude(platform->mTargetAngles.vx) == PlatformHalfTurn &&
            platform->mTargetAngles.vz == 0)
        {
            platform->mTargetAngles.vz =
                platform->mAngles.vz;
        }
        if (platform->mTargetAngles.vx == 0)
        {
            if (AngleMagnitude(platform->mTargetAngles.vz) == PlatformHalfTurn)
            {
                platform->mTargetAngles.vx =
                    platform->mAngles.vx;
            }
        }
        return;
    }

    default:
        PlatformSet(platform->mVel, Direction.vx, PlatformStandardBounceVelocity, Direction.vz);
        return;
    }
}

/**
 * Advance a loose platform through angular motion and collision bounces.
 *
 * The active object advances its angle target, integrates gravity and
 * friction, and resolves up to three collision bounces per frame.
 */
void CPlatform::BouncyAI()
{
    MATRIX m;
    SLineInfo LInfo;
    CVector NewPos;
    CVector NewVel;
    CFriction Fric;
    int ObjectExtent;

    if (this->mDeathTimer != 0)
    {
        this->mDeathTimer--;
        if (this->mDeathTimer == 0)
        {
            Die();
            return;
        }
    }

    if ((this->mSpecificFlags & PlatformBouncing) == 0)
        return;

    this->mTargetAngles.Mask();

    this->mAngVel.vx =
        static_cast<short>((this->mTargetAngles.vx -
        this->mAngles.vx) >> 5);
    this->mAngVel.vy =
        static_cast<short>((this->mTargetAngles.vy -
        this->mAngles.vy) >> 5);
    this->mAngVel.vz =
        static_cast<short>((this->mTargetAngles.vz -
        this->mAngles.vz) >> 5);
    PLATFORM_SHORT_VECTOR_VIEW(
        this->mAngVel).KillSmall();

    if (AngleMagnitude(this->mAngVel.vx) < 40 &&
        VectorMagnitude(this->mTargetAngles.vx -
            this->mAngles.vx) > 40)
    {
        this->mAngVel.vx =
            this->mAngVel.vx < 0 ? -40 : 40;
    }
    if (AngleMagnitude(this->mAngVel.vy) < 40 &&
        VectorMagnitude(this->mTargetAngles.vy -
            this->mAngles.vy) > 40)
    {
        this->mAngVel.vy =
            this->mAngVel.vy < 0 ? -40 : 40;
    }
    if (AngleMagnitude(this->mAngVel.vz) < 40 &&
        VectorMagnitude(this->mTargetAngles.vz -
            this->mAngles.vz) > 40)
    {
        this->mAngVel.vz =
            this->mAngVel.vz < 0 ? -40 : 40;
    }

    PLATFORM_SHORT_VECTOR_VIEW(this->mAngles) +=
        PLATFORM_CONST_SHORT_VECTOR_VIEW(this->mAngVel);
    PLATFORM_SHORT_VECTOR_VIEW(
        this->mAngles).Mask();
    M3dMaths_RotMatrixYXZ(
        reinterpret_cast<SVECTOR *>(
            &this->mAngles),
        &m);

    ObjectExtent =
        (this->mWidth * AngleMagnitude(m.m[1][0]) +
         this->mHeight * AngleMagnitude(m.m[1][1]) +
         this->mDepth * AngleMagnitude(m.m[1][2])) >> 1;

    NewVel = PlatformVector(this->mVel);
    NewVel.vy += PlatformGravityPerFrame;
    Fric = CFriction(6, 6, 6);

    NewVel %= Fric;
    NewVel.KillSmall();
    NewPos = operator+(
        PlatformVector(this->mPos), NewVel);

    CVector Dir = NewVel;
    Dir.vy = 0;
    int Speed = Dir.Length();

    for (int NumChecks = 0; NumChecks < 3; NumChecks++)
    {
        LInfo.StartCoords.vx =
            this->mPos.vx;
        LInfo.StartCoords.vy =
            this->mPos.vy;
        LInfo.StartCoords.vz =
            this->mPos.vz;
        LInfo.EndCoords.vx = NewPos.vx;
        LInfo.EndCoords.vy = NewPos.vy;
        LInfo.EndCoords.vz = NewPos.vz;
        M3dColij_InitLineInfo(&LInfo);
        M3dZone_LineToItem(&LInfo, 1);

        if (LInfo.pItem == 0)
        {
            if (NewVel.vy > 0)
            {
                LInfo.StartCoords.vx = NewPos.vx;
                LInfo.StartCoords.vy = NewPos.vy;
                LInfo.StartCoords.vz = NewPos.vz;
                LInfo.EndCoords = LInfo.StartCoords;
                LInfo.StartCoords.vy -= ObjectExtent;
                LInfo.EndCoords.vy += ObjectExtent;
                M3dColij_InitLineInfo(&LInfo);
                M3dZone_LineToItem(&LInfo, 1);
            }

            if (LInfo.pItem == 0)
            {
                this->mPos =
                    PlatformOwnerVector(NewPos);
                this->mVel =
                    PlatformOwnerVector(NewVel);
                break;
            }
        }

        unsigned short NumBounces = this->mNumBounces;
        if (NumBounces < 5)
        {
            switch (this->mType)
            {
            case 1:
                if (Rnd(2) == 0)
                    SFX_PlayX(0x67, PlatformSoundVolume, 0);
                else
                    SFX_PlayX(0x66, PlatformSoundVolume, 0);
                NumBounces = this->mNumBounces;
                break;
            case 3:
                SFX_PlayX(0x45, PlatformSoundVolume, 0);
                NumBounces = this->mNumBounces;
                break;
            case 2:
                if (GLevel != 0)
                {
                    if (Rnd(2) == 0)
                        SFX_PlayX(0x6B, PlatformSoundVolume, 0);
                    else
                        SFX_PlayX(0x6A, PlatformSoundVolume, 0);
                    NumBounces = this->mNumBounces;
                    break;
                }
                SFX_PlayX(Rnd(2) + 0x53, PlatformSoundVolume, 0);
                NumBounces = this->mNumBounces;
                break;
            case 4:
                if (Rnd(2) == 0)
                    SFX_PlayX(0x51, PlatformSoundVolume, 0);
                else
                    SFX_PlayX(0x50, PlatformSoundVolume, 0);
                NumBounces = this->mNumBounces;
                break;
            case 5:
                SFX_PlayX(Rnd(2) + 0x53, PlatformSoundVolume, 0);
                NumBounces = this->mNumBounces;
                break;
            }
        }

        CVector Normal;
        Normal.vx = LInfo.Normal.vx;
        Normal.vy = LInfo.Normal.vy;
        Normal.vz = LInfo.Normal.vz;
        this->mNumBounces = NumBounces + 1;

        int dot = Mips_CVecDotProd(&NewVel, &Normal);
        NewVel.vx -= Mips_FixMul(Normal.vx, dot) << 1;
        NewVel.vy -= Mips_FixMul(Normal.vy, dot) << 1;
        NewVel.vz -= Mips_FixMul(Normal.vz, dot) << 1;

        Fric = CFriction(3, 2, 3);
        if (VectorMagnitude(NewVel.vy) < PlatformLowVerticalSpeed)
        {
            Fric.vy = 0;
            Fric.vx = Fric.vz = 2;
        }
        else
        {
            this->mTargetAngles.vy = Rnd(PlatformFixedOne);

            if (this->mNumBounces == 1)
            {
                this->mTargetAngles.vx +=
                    static_cast<short>(
                        (Rnd(2) << 11) - PlatformQuarterTurn);
                if ((this->mType == 2 || this->mType == 4) &&
                    ((this->mTargetAngles.vx == PlatformHalfTurn &&
                      this->mTargetAngles.vz == 0) ||
                     (this->mTargetAngles.vx == 0 &&
                      this->mTargetAngles.vz == PlatformHalfTurn)))
                {
                    this->mTargetAngles.vx =
                        (Rnd(2) << 11) - PlatformQuarterTurn;
                }
            }

            if (this->mNumBounces == 1)
            {
                this->mTargetAngles.vz += (Rnd(3) - 1) << 10;
                if ((this->mType == 2 || this->mType == 4) &&
                    ((this->mTargetAngles.vx == PlatformHalfTurn &&
                      this->mTargetAngles.vz == 0) ||
                     (this->mTargetAngles.vx == 0 &&
                      this->mTargetAngles.vz == PlatformHalfTurn)))
                {
                    this->mTargetAngles.vz =
                        (Rnd(2) << 11) - PlatformQuarterTurn;
                }
            }

            if (this->mNumBounces == 1 && Speed < 18)
            {
                this->mTargetAngles.vy =
                    this->mAngles.vy +
                    Rnd(PlatformQuarterTurn) - PlatformEighthTurn;
                this->mTargetAngles.vx =
                    (this->mAngles.vx +
                     PlatformEighthTurn) & PlatformOrthogonalAngleMask;
                this->mTargetAngles.vz =
                    (this->mAngles.vz +
                     PlatformEighthTurn) & PlatformOrthogonalAngleMask;
            }
        }

        NewVel %= Fric;
        NewVel.KillSmall();

        if (this->mNumBounces > 18)
        {
            this->mAngles.vx =
                this->mTargetAngles.vx;
            this->mAngles.vz =
                this->mTargetAngles.vz;
            M3dMaths_RotMatrixYXZ(
                reinterpret_cast<SVECTOR *>(
                    &this->mAngles),
                &m);
            NewVel.vx = NewVel.vy = NewVel.vz = 0;
            this->mDeathTimer = 10;
            this->mSpecificFlags &= ~PlatformBouncing;
            return;
        }

        NewPos.vx = LInfo.Position.vx +
            Mips_FixMul(LInfo.Normal.vx, ObjectExtent);
        NewPos.vy = LInfo.Position.vy +
            Mips_FixMul(LInfo.Normal.vy, ObjectExtent);
        NewPos.vz = LInfo.Position.vz +
            Mips_FixMul(LInfo.Normal.vz, ObjectExtent);
    }

    if (this->mNumBounces > 18)
    {
        NewVel.vx = NewVel.vy = NewVel.vz = 0;
        this->mAngles.vx =
            this->mTargetAngles.vx;
        this->mAngles.vz =
            this->mTargetAngles.vz;
        this->mDeathTimer = 10;
        this->mSpecificFlags &= ~PlatformBouncing;
    }
}

/**
 * Advances scripted platform scale, movement, steering, physics, and sound.
 *
 */
void CPlatform::AI()
{
    CPlatform *platform = this;
    if (platform->mScaleXTimer != 0)
    {
        platform->mScaleXTimer--;
        platform->mScale.vx +=
            platform->mScaleXAdjust;
    }
    if (platform->mScaleYTimer != 0)
    {
        platform->mScaleYTimer--;
        platform->mScale.vy +=
            platform->mScaleYAdjust;
    }
    if (platform->mScaleZTimer != 0)
    {
        platform->mScaleZTimer--;
        platform->mScale.vz +=
            platform->mScaleZAdjust;
    }

    platform->mAcc.vx =
        platform->mAcc.vy =
        platform->mAcc.vz = 0;
    if (platform->mTrodUpon == 0)
        platform->mNotTrodUponTimer++;

    unsigned short inputFlags = platform->mInputFlags;
    platform->mInputFlagsCopy = inputFlags;
    if ((inputFlags & 1) != 0)
    {
        platform->mInputFlags = inputFlags & 0xFFFE;
        platform->mInputSignal++;
    }

    if ((platform->mSpecificFlags & PlatformBounceEnabled) != 0)
    {
        platform->BouncyAI();
        return;
    }

    if (platform->mDoScript != 0)
    {
        if (platform->mWaitTimer != 0)
            platform->mWaitTimer--;
        else
            platform->ParseScript(platform->mpScript);
    }
    else
    {
        platform->ProcessPattern();
    }

    if ((platform->mSpecificFlags & PlatformMovingToTarget) != 0)
    {
        CVector distance =
            PLATFORM_CONST_VECTOR_VIEW(
                platform->mPos) -
            PLATFORM_CONST_VECTOR_VIEW(platform->mTargetPos);
        int distanceToTarget = distance.Length();
        int reachedTarget = !(
            static_cast<int>(platform->mBaddyAttributes[0]) <
            distanceToTarget);
        if (reachedTarget != 0)
        {
            platform->mPos =
                platform->mTargetPos;
            if (platform->mBaddyAttributes[2] < 2)
            {
                CVector *velocity =
                    &platform->mVel;
                velocity->vx = velocity->vy = velocity->vz = 0;
            }
            platform->mSpecificFlags &= ~PlatformMovingToTarget;
        }
        else
        {
            unsigned short movementMode =
                platform->mBaddyAttributes[2];
            if (movementMode == 0)
            {
                CSVector ideal_angles;
                Utils_CalcAim(
                    PLATFORM_SHORT_VECTOR_VIEW(ideal_angles),
                    PLATFORM_CONST_VECTOR_VIEW(
                        platform->mPos),
                    PLATFORM_CONST_VECTOR_VIEW(
                        platform->mTargetPos));
                Utils_GetVecFromMagDir(
                    PLATFORM_VECTOR_VIEW(
                        platform->mVel),
                    platform->mBaddyAttributes[0],
                    PLATFORM_CONST_SHORT_VECTOR_VIEW(ideal_angles));
            }
            else if (movementMode == 1)
            {
                CSVector ideal_angles;
                Utils_CalcAim(
                    PLATFORM_SHORT_VECTOR_VIEW(ideal_angles),
                    PLATFORM_CONST_VECTOR_VIEW(
                        platform->mPos),
                    PLATFORM_CONST_VECTOR_VIEW(
                        platform->mTargetPos));
                int ang_acc;
                {
                    CVector remaining =
                        PLATFORM_CONST_VECTOR_VIEW(
                            platform->mTargetPos) -
                        PLATFORM_CONST_VECTOR_VIEW(
                            platform->mPos);
                    ang_acc = PlatformTurnNumerator /
                        remaining.Length();
                }
                if (ang_acc < -PlatformMaxAngularAcceleration)
                    ang_acc = -PlatformMaxAngularAcceleration;
                else if (ang_acc > PlatformMaxAngularAcceleration)
                    ang_acc = PlatformMaxAngularAcceleration;
                else if (ang_acc > 0 && ang_acc < 4)
                    ang_acc = 4;
                else if (ang_acc < 0 && ang_acc > -4)
                    ang_acc = -4;

                Utils_TurnTowards(
                    PLATFORM_CONST_SHORT_VECTOR_VIEW(
                        platform->mAngles),
                    PLATFORM_SHORT_VECTOR_VIEW(
                        platform->mAngVel),
                    PLATFORM_SHORT_VECTOR_VIEW(
                        platform->mAngAcc),
                    PLATFORM_CONST_SHORT_VECTOR_VIEW(ideal_angles),
                    ang_acc);
                platform->mAngles.vx = 0;
                Utils_GetVecFromMagDir(
                    PLATFORM_VECTOR_VIEW(
                        platform->mAcc),
                    platform->mBaddyAttributes[0],
                    PLATFORM_CONST_SHORT_VECTOR_VIEW(ideal_angles));

                short roll = 0;
                if ((platform->mSpecificFlags & PlatformBouncing) != 0)
                {
                    roll = static_cast<short>((ideal_angles.vy -
                        platform->mAngles.vy) &
                        PlatformAngleMask);
                }
                if (roll > PlatformHalfTurn)
                    roll = static_cast<short>(roll - PlatformFixedOne);
                if (roll > PlatformQuarterTurn)
                    roll = PlatformQuarterTurn;
                else if (roll < -PlatformQuarterTurn)
                    roll = -PlatformQuarterTurn;

                roll = static_cast<short>((-roll >> 1) & PlatformAngleMask);
                short rolldiff = static_cast<short>(roll -
                    platform->mAngles.vz);
                if (rolldiff < -PlatformHalfTurn)
                    rolldiff = static_cast<short>(
                        rolldiff + PlatformFixedOne);
                if (rolldiff > PlatformHalfTurn)
                    rolldiff = static_cast<short>(
                        rolldiff - PlatformFixedOne);
                if (rolldiff != 0)
                    platform->mAngAcc.vz =
                        static_cast<short>(rolldiff >> 3);
                else
                    platform->mAngVel.vz = 0;
            }
            else if (movementMode == 2)
            {
                CSVector ideal_angles;
                Utils_CalcAim(
                    PLATFORM_SHORT_VECTOR_VIEW(ideal_angles),
                    PLATFORM_CONST_VECTOR_VIEW(
                        platform->mPos),
                    PLATFORM_CONST_VECTOR_VIEW(
                        platform->mTargetPos));
                int ang_acc;
                {
                    CVector remaining =
                        PLATFORM_CONST_VECTOR_VIEW(
                            platform->mTargetPos) -
                        PLATFORM_CONST_VECTOR_VIEW(
                            platform->mPos);
                    ang_acc = PlatformTurnNumerator /
                        remaining.Length();
                }
                if (ang_acc < -PlatformMaxAngularAcceleration)
                    ang_acc = -PlatformMaxAngularAcceleration;
                else if (ang_acc > PlatformMaxAngularAcceleration)
                    ang_acc = PlatformMaxAngularAcceleration;
                else if (ang_acc > 0 && ang_acc < 4)
                    ang_acc = 4;
                else if (ang_acc < 0 && ang_acc > -4)
                    ang_acc = -4;

                Utils_TurnTowards(
                    PLATFORM_CONST_SHORT_VECTOR_VIEW(
                        platform->mAngles),
                    PLATFORM_SHORT_VECTOR_VIEW(
                        platform->mAngVel),
                    PLATFORM_SHORT_VECTOR_VIEW(
                        platform->mAngAcc),
                    PLATFORM_CONST_SHORT_VECTOR_VIEW(ideal_angles),
                    ang_acc);
                platform->mAngles.vx = 0;
                Utils_GetVecFromMagDir(
                    PLATFORM_VECTOR_VIEW(
                        platform->mAcc),
                    platform->mBaddyAttributes[0],
                    PLATFORM_CONST_SHORT_VECTOR_VIEW(ideal_angles));
            }
        }
    }
    else if (platform->mBaddyAttributes[2] == 1)
    {
        short rolldiff = static_cast<short>(
            -platform->mAngles.vz);
        if (rolldiff < -PlatformHalfTurn)
            rolldiff = static_cast<short>(rolldiff + PlatformFixedOne);
        if (rolldiff > PlatformHalfTurn)
            rolldiff = static_cast<short>(rolldiff - PlatformFixedOne);
        if (rolldiff == 0)
            platform->mAngVel.vz = 0;
        else
            platform->mAngAcc.vz =
                static_cast<short>(rolldiff >> 3);
    }

    if (platform->mApplyGravity != 0)
    {
        // FIXME(match): asm barrier (x2) — keeps the `lui/addiu $a1` WorldGravity setup ahead of `addiu $a0` so reorg does not hoist $a0 into the beqz delay slot (score 5 without); tried: `+= WorldGravity`, pointer/reference locals, `.operator+=`, goto-style zero arm, else arm.
        asm("");
        CVector *gravity = &WorldGravity;
        asm volatile("" : "+r"(gravity));
        PLATFORM_VECTOR_VIEW(platform->mAcc) += *gravity;
    }

    platform->DoPhysics();
    if (platform->mLoopingSoundUpdate != -1 &&
        TTime % platform->mLoopingSoundUpdate == 0)
    {
        SFX_ModifyPos(
            platform->mLoopingSound,
            PlatformVector(platform->mPos),
            0);
    }
    platform->mTrodUpon = 0;

}

/**
 * Damage a platform, flashing it while alive or shattering it on death.
 *
 * @param damage Health removed by the hit.
 * @param knock Knockback vector retained by the virtual ABI.
 * @param whathit Hit-category value retained by the virtual ABI.
 * @return One after processing the hit.
 */
int CPlatform::Hit(int damage, const CVector &knock, int whathit)
{
    u8 hitCount = mHit;
    u16 health = mBaddyAttributes[1];
    hitCount++;
    mHit = hitCount;
    if (health != 0)
    {
        s16 hp = mHealth;
        u16 hpu = static_cast<u16>(mHealth);
        if (hp > 0)
        {
            mHealth = hpu - damage;
            if (mHealth <= 0)
            {
                Die();
                Shatter_Item(
                    PlatformShatterItem(*this),
                    0, 1);
            }
            else
            {
                Flash(3, 0xFF, 0xFF, 0xFF);
            }
        }
    }
    return 1;
}

/**
 * Advance platform translation and rotation in the current physics mode.
 *
 */
void CPlatform::DoPhysics()
{
    int mode = mBaddyAttributes[2];

    mNormal.vz = 0;
    mNormal.vy = 0;
    mNormal.vx = 0;

    if (mode == 0)
    {
        int vx = mVel.vx + mAcc.vx;
        int vy = mVel.vy + mAcc.vy;
        int vz = mVel.vz + mAcc.vz;
        short sz;
        if (static_cast<u32>(vx + PlatformVelocityRounding) <
            PlatformVelocityDeadZone)
            vx = 0;
        if (static_cast<u32>(vy + PlatformVelocityRounding) <
            PlatformVelocityDeadZone)
            vy = 0;
        if (static_cast<u32>(vz + PlatformVelocityRounding) <
            PlatformVelocityDeadZone)
            vz = 0;
        mVel.vx = vx;
        mVel.vy = vy;
        mVel.vz = vz;
        mPos.vx += vx;
        mPos.vy += vy;
        mPos.vz += vz;

        short sx = mAngVel.vx;
        short sy = mAngVel.vy;
        int ax = (sx + static_cast<u16>(mAngles.vx)) &
            PlatformAngleMask;
        mAngles.vx = ax;
        u16 ay = mAngles.vy;
        sx += mAngAcc.vx;
        sz = mAngVel.vz;
        int by = (sy + ay) & PlatformAngleMask;
        mAngles.vy = by;
        u16 az = mAngles.vz;
        int bz = (sz + az) & PlatformAngleMask;
        mAngles.vz = bz;
        sy += mAngAcc.vy;
        sz += mAngAcc.vz;
        if (static_cast<u16>(sx + 1) < 3)
            sx = 0;
        if (static_cast<u16>(sy + 1) < 3)
            sy = 0;
        if (static_cast<u16>(sz + 1) < 3)
            sz = 0;
        mAngVel.vx = sx;
        mAngVel.vy = sy;
        mAngVel.vz = sz;
    }
    else
    {
        mode -= 1;
        if (static_cast<u16>(mode) >= 2)
        {
            return;
        }

        CVector *velocity = &mVel;
        PLATFORM_VECTOR_VIEW(*velocity) +=
            PLATFORM_CONST_VECTOR_VIEW(mAcc);
        PLATFORM_VECTOR_VIEW(*velocity) %=
            mFric;
        PLATFORM_VECTOR_VIEW(*velocity).KillSmall();
        PLATFORM_VECTOR_VIEW(mPos) +=
            PLATFORM_CONST_VECTOR_VIEW(*velocity);

        CSVector *angVel = &mAngVel;
        CSVector *angles =
            &mAngles;
        PLATFORM_SHORT_VECTOR_VIEW(*angles) +=
            PLATFORM_CONST_SHORT_VECTOR_VIEW(*angVel);
        PLATFORM_SHORT_VECTOR_VIEW(*angles).Mask();
        PLATFORM_SHORT_VECTOR_VIEW(*angVel) +=
            PLATFORM_CONST_SHORT_VECTOR_VIEW(
                mAngAcc);
        PLATFORM_SHORT_VECTOR_VIEW(*angVel) %=
            mAngFric;
        PLATFORM_SHORT_VECTOR_VIEW(*angVel).KillSmall();
    }
}

/**
 * Update the cached target and mark the platform as moving when it changes.
 *
 * @param pos New target position.
 */
void CPlatform::MoveTo(CVector &pos)
{
    if (PLATFORM_VECTOR_VIEW(mTargetPos) != pos)
    {
        mTargetPos =
            PlatformOwnerVector(pos);
        mSpecificFlags |= PlatformMovingToTarget;
    }
}

/** No-op pattern hook used by platforms whose script processing is disabled. */
void CPlatform::ProcessPattern()
{
}

/**
 * Execute a platform-specific script opcode.
 *
 * @param command  Script opcode to consume.
 * @return One while script execution may continue, or zero after a blocking
 *         wait or destructive command.
 */
int CPlatform::ExecuteCommand(unsigned short command)
{
    struct CPlatform *plat = this;
    CItem *item = plat;

    /* Scale commands only take effect once the per-item scale is enabled. */
#define PLATFORM_ENABLE_SCALE()                                                \
    do {                                                                       \
        int flags = item->mFlags;                                              \
        if ((flags & PlatformItemScaleEnabled) == 0) {                         \
            flags |= PlatformItemScaleEnabled;                                \
            item->mFlags = flags;                                              \
            item->mScale.vz = PlatformFixedOne;                                \
            item->mScale.vy = PlatformFixedOne;                                \
            item->mScale.vx = PlatformFixedOne;                                \
        }                                                                      \
    } while (0)

    switch (command)
    {
    case PlatformCommandSetBounceType:
    {
        unsigned short *pc = plat->mpScript;
        unsigned short type = pc[0];
        plat->mpScript = pc + 1;
        plat->mType = type;
        if (type != 0)
            plat->mSpecificFlags |= PlatformBounceEnabled;
        else
            plat->mSpecificFlags &= ~PlatformBounceEnabled;
        struct SModel *m =
            PSXRegion[item->mRegion].ppModels[item->mModel];
        short *pBox = ((PlatformModelBounds *)&m->Box)->Half;
        plat->mWidth = pBox[0] - pBox[1];
        plat->mHeight = pBox[2] - pBox[3];
        plat->mDepth = pBox[4] - pBox[5];
        break;
    }

    case PlatformCommandSetCollision:
    {
        unsigned short *pc = plat->mpScript;
        unsigned short on = pc[0];
        plat->mpScript = pc + 1;
        if (on != 0)
            item->mFlags |= PlatformItemCollision;
        else
            item->mFlags &= ~PlatformItemCollision;
        break;
    }

    case PlatformCommandPlayLoopingSound:
    {
        if (plat->mLoopingSound != 0)
            SFX_Stop(plat->mLoopingSound);
        unsigned short *pc = plat->mpScript;
        unsigned short sound = pc[0];
        plat->mpScript = pc + 1;
        plat->mLoopingSound = SFX_PlayX(sound, PlatformSoundVolume, 0);
        plat->mLoopingSoundUpdate = -1;
        break;
    }

    case PlatformCommandPlayPositionalLoopingSound:
    {
        if (plat->mLoopingSound != 0)
            SFX_Stop(plat->mLoopingSound);
        unsigned short *pc = plat->mpScript;
        unsigned short sound = *pc++;
        plat->mpScript = pc;
        unsigned short update = *pc++;
        plat->mpScript = pc;
        plat->mLoopingSoundUpdate = update;
        plat->mLoopingSound = SFX_PlayPos(
            sound, PLATFORM_CONST_VECTOR_VIEW(item->mPos), 0);
        break;
    }

    case PlatformCommandStopLoopingSound:
        if (plat->mLoopingSound != 0)
            SFX_Stop(plat->mLoopingSound);
        plat->mLoopingSound = 0;
        break;

    case PlatformCommandScale:
    {
        PLATFORM_ENABLE_SCALE();
        unsigned short *pc = plat->mpScript;
        short p = *pc++;
        plat->mpScript = pc;
        plat->mScaleXTimer = plat->mScaleYTimer =
            plat->mScaleZTimer = *pc++;
        plat->mpScript = pc;
        if (plat->mScaleXTimer != 0)
        {
            plat->mScaleYAdjust = plat->mScaleZAdjust =
                plat->mScaleXAdjust = (static_cast<int>(p) << 12) /
                    static_cast<int>(
                        static_cast<unsigned int>(plat->mScaleXTimer) * 100);
        }
        else
        {
            plat->mScaleYAdjust = plat->mScaleZAdjust =
                plat->mScaleXAdjust = (static_cast<int>(p) << 12) / 100;
        }
        item->mScale.vx += plat->mScaleXAdjust;
        item->mScale.vy += plat->mScaleYAdjust;
        item->mScale.vz += plat->mScaleZAdjust;
        break;
    }

    case PlatformCommandScaleX:
    {
        PLATFORM_ENABLE_SCALE();
        unsigned short *pc = plat->mpScript;
        short p = *pc++;
        plat->mpScript = pc;
        plat->mScaleXTimer = *pc++;
        plat->mpScript = pc;
        if (plat->mScaleXTimer != 0)
            plat->mScaleXAdjust = (static_cast<int>(p) << 12) /
                static_cast<int>(
                    static_cast<unsigned int>(plat->mScaleXTimer) * 100);
        else
            plat->mScaleXAdjust = (static_cast<int>(p) << 12) / 100;
        item->mScale.vx += plat->mScaleXAdjust;
        break;
    }

    case PlatformCommandScaleY:
    {
        PLATFORM_ENABLE_SCALE();
        unsigned short *pc = plat->mpScript;
        short p = *pc++;
        plat->mpScript = pc;
        plat->mScaleYTimer = *pc++;
        plat->mpScript = pc;
        if (plat->mScaleYTimer != 0)
            plat->mScaleYAdjust = (static_cast<int>(p) << 12) /
                static_cast<int>(
                    static_cast<unsigned int>(plat->mScaleYTimer) * 100);
        else
            plat->mScaleYAdjust = (static_cast<int>(p) << 12) / 100;
        item->mScale.vy += plat->mScaleYAdjust;
        break;
    }

    case PlatformCommandScaleZ:
    {
        PLATFORM_ENABLE_SCALE();
        unsigned short *pc = plat->mpScript;
        short p = *pc++;
        plat->mpScript = pc;
        plat->mScaleZTimer = *pc++;
        plat->mpScript = pc;
        if (plat->mScaleZTimer != 0)
            plat->mScaleZAdjust = (static_cast<int>(p) << 12) /
                static_cast<int>(
                    static_cast<unsigned int>(plat->mScaleZTimer) * 100);
        else
            plat->mScaleZAdjust = (static_cast<int>(p) << 12) / 100;
        item->mScale.vz += plat->mScaleZAdjust;
        break;
    }

    case PlatformCommandSetBruceHealthAdjust:
    {
        unsigned short *pc = plat->mpScript;
        plat->mBruceHealthAdjust = pc[0];
        plat->mpScript = pc + 1;
        break;
    }

    case PlatformCommandSetBoundingBox:
    {
        unsigned int flags = plat->mSpecificFlags;
        unsigned short x = *plat->mpScript++;
        unsigned short y = *plat->mpScript++;
        unsigned short z = *plat->mpScript++;
        plat->mSpecificFlags = flags | PlatformHasBoundingBox;
        plat->mBoundingBox.vx = static_cast<unsigned int>(x) << 11;
        plat->mBoundingBox.vy = static_cast<unsigned int>(y) << 11;
        plat->mBoundingBox.vz = static_cast<unsigned int>(z) << 11;
        break;
    }

    case PlatformCommandWaitUntilTrodUpon:
        if (plat->mTrodUpon == 0)
        {
            plat->mpScript = plat->mpScript - 1;
            return 0;
        }
        break;

    case PlatformCommandMoveTo:
    {
        int *p_pos = PLATFORM_ALIGNED_SCRIPT(
            int, plat->mpScript);
        CVector pos;
        pos.vx = *p_pos++;
        pos.vy = *p_pos++;
        pos.vz = *p_pos++;
        int shift = 12;
        pos <<= shift;
        plat->mpScript = reinterpret_cast<unsigned short *>(p_pos);
        MoveTo(pos);
        break;
    }

    case PlatformCommandMoveToNode:
    {
        unsigned short *pc = plat->mpScript;
        unsigned short node = pc[0];
        plat->mpScript = pc + 1;
        if ((node & PlatformScriptVariableFlag) != 0)
        {
            node = GetVariable(node) & PlatformScriptWordMask;
        }
        CVector pos;
        Trig_GetPosition(pos, node);
        MoveTo(pos);
        break;
    }

    case PlatformCommandMoveRelative:
    {
        int *p_pos = PLATFORM_ALIGNED_SCRIPT(
            int, plat->mpScript);
        CVector pos;
        pos.vx = *p_pos++;
        pos.vy = *p_pos++;
        pos.vz = *p_pos++;
        int shift = 12;
        pos <<= shift;
        pos += PLATFORM_CONST_VECTOR_VIEW(item->mPos);
        plat->mpScript = reinterpret_cast<unsigned short *>(p_pos);
        MoveTo(pos);
        break;
    }

    case PlatformCommandDie:
    {
        Die();
        return 0;
    }

    case PlatformCommandShatter:
    {
        item->mFlags |= PlatformItemShattered;
        Die();
        Shatter_Item(
            PLATFORM_SHATTER_ITEM_POINTER(
                this),
            0, 0);
        return 0;
    }

    default:
        return plat->CBaddy::ExecuteCommand(command);
    }
#undef PLATFORM_ENABLE_SCALE
    return 1;
}

/**
 * Consume platform-specific script variables, updating movement/orientation
 * fields directly and delegating unknown variables to 
 *
 * @param variable Script variable identifier to consume.
 */
void CPlatform::SetVariable(unsigned short variable)
{
    variable &= PlatformScriptWordMask;

    switch (variable)
    {
    case PlatformVariableApplyGravity:
    {
        u16 *script = mpScript;
        u8 value = *reinterpret_cast<u8 *>(script);
        mpScript = script + 1;
        mApplyGravity = value;
        break;
    }
    case PlatformVariableModelIndex:
    {
        u16 *script = mpScript;
        u16 value = *script;
        mpScript = script + 1;
        mModel = value;
        break;
    }
    case PlatformVariableModelChecksum:
    {
        unsigned int *p_checksum = PLATFORM_ALIGNED_SCRIPT(
            unsigned int, mpScript);
        unsigned int model = Spool_GetModel(
            *p_checksum,
            mRegion);
        u16 flags = mFlags;
        mModel = model;
        mpScript = reinterpret_cast<u16 *>(p_checksum + 1);
        flags &= 0xFFFE;
        mFlags = flags;
        break;
    }
    case PlatformVariableVelocity:
    {
        s16 x = GetScriptValue();
        s16 y = GetScriptValue();
        s16 z = GetScriptValue();
        PlatformSet(mVel, 
            static_cast<int>(x) << 12,
            static_cast<int>(y) << 12,
            static_cast<int>(z) << 12);
        break;
    }
    case PlatformVariableAngles:
    {
        s16 x = GetScriptValue();
        s16 y = GetScriptValue();
        s16 z = GetScriptValue();
        PlatformSet(mAngles, x, y, z);
        break;
    }
    case PlatformVariableAngularVelocity:
    {
        s16 x = GetScriptValue();
        s16 y = GetScriptValue();
        s16 z = GetScriptValue();
        PlatformSet(mAngVel, x, y, z);
        break;
    }
    case PlatformVariableAngularAcceleration:
    {
        s16 x = GetScriptValue();
        s16 y = GetScriptValue();
        s16 z = GetScriptValue();
        PlatformSet(mAngAcc, x, y, z);
        break;
    }
    default:
        CBaddy::SetVariable(variable);
        break;
    }
}

/**
 * Read a platform-specific script variable or delegate it to 
 *
 * @param variable Script variable identifier.
 * @return The signed script value.
 */
short CPlatform::GetVariable(unsigned short variable)
{
    variable &= PlatformScriptWordMask;
    if (variable == PlatformVariableNotTrodUponTimer)
    {
        return mNotTrodUponScriptValue;
    }
    return CBaddy::GetVariable(variable);
}

/**
 * Test the skater's swept bounds against every active bouncing platform.
 *
 * @param pSkater Active skater being processed.
 */
void Platform_HandleBounce(CBruce *pSkater)
{
    int LP1 = pSkater->mOldPos.vx;
    int RP1 = pSkater->mPos.vx;
    if (RP1 < LP1)
    {
        int tmp = LP1;
        LP1 = RP1;
        RP1 = tmp;
    }
    LP1 -= PlatformCollisionMargin;
    RP1 += PlatformCollisionMargin;

    int UP1 = pSkater->mOldPos.vy;
    int DP1 = pSkater->mPos.vy;
    if (DP1 < UP1)
    {
        int tmp = UP1;
        UP1 = DP1;
        DP1 = tmp;
    }
    UP1 -= PlatformCollisionMargin;
    DP1 += PlatformCollisionMargin;

    int FP1 = pSkater->mOldPos.vz;
    int BP1 = pSkater->mPos.vz;
    if (BP1 < FP1)
    {
        int tmp = FP1;
        FP1 = BP1;
        BP1 = tmp;
    }
    FP1 -= PlatformCollisionMargin;
    BP1 += PlatformCollisionMargin;

    PlatformCItemOwner *pItem =
        reinterpret_cast<PlatformCItemOwner *>(EnvironmentalObjectList);
    while (pItem != 0)
    {
        if (pItem->mFlags & PlatformItemEnvironmental)
        {
            CPlatform *platform = reinterpret_cast<CPlatform *>(pItem);
            int tmp = platform->mSpecificFlags;
            if (tmp & PlatformBounceEnabled)
            {
                pItem->mFlags |= PlatformItemBounceContact;
                if (!(tmp & PlatformBouncing))
                {
                    SModel *m = PSXRegion[pItem->mRegion].ppModels[pItem->mModel];
                    short *pBox = ((PlatformModelBounds *)&m->Box)->Half;
                    int x = pItem->mPos.vx;
                    if (RP1 >= x + (static_cast<int>(pBox[1]) << 12) &&
                        x + (static_cast<int>(pBox[0]) << 12) >= LP1)
                    {
                        int z = pItem->mPos.vz;
                        if (BP1 >= z + (static_cast<int>(pBox[5]) << 12) &&
                            z + (static_cast<int>(pBox[4]) << 12) >= FP1)
                        {
                            int y = pItem->mPos.vy;
                            if (DP1 >= y + (static_cast<int>(pBox[3]) << 12) &&
                                y + (static_cast<int>(pBox[2]) << 12) >= UP1)
                            {
                                platform->Bounce(
                                    reinterpret_cast<CBruce *>(MechList),
                                    PLATFORM_CONST_VECTOR_VIEW(
                                        pSkater->mVel));
                            }
                        }
                    }
                }
            }
        }
        pItem = pItem->mNextItem;
    }
}
