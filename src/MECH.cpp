// MECH.cpp -- Reconstructed translation unit
// Original: MECH.CPP
// Functions: 26 (all strict-exact)
// Address range: 0x800428F4 - 0x800440E8
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

// Owner-local declarations attributed to MECH.cpp by MAIN.SYM.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char byte;
typedef int undefined;
typedef char undefined1;
typedef short undefined2;
typedef int undefined4;
typedef unsigned long ulong;
typedef unsigned char undefined3[3];

/** Return caller-provided storage for an in-place construction. */
inline void *operator new(unsigned int, void *address)
{
    return address;
}

#define CCLASS_POLY_ITEM_FAMILY
#include "CCLASS_POLY.h"
#define FONTTOOLS_POLYMORPHIC_LAYOUT
#define TEXTEFFECT_POLYMORPHIC_LAYOUT

struct CBody;
struct CBodyOwner;
struct CSuper;
struct EditorOutModel;
struct EditorInModel;
struct LevelGenerator;
struct CBaddy;
struct SModel;
struct SHook;

#define MECHLIST_OWNER_DECLARATIONS
#include "MECHLIST.h"
#undef MECHLIST_OWNER_DECLARATIONS

#define BITSTATE_DECLARE_BIT_COUNT
#include "BITSTATE.h"
#include "CAMERALIST.h"
#include "PHYSICSSTATE.h"
#include "GLEVEL.h"
#include "GENERATELEVEL.h"
#define BITSTATE_DECLARE_SPARK_SEMI_TRANS
#include "BITSTATE.h"
#define BITSTATE_DECLARE_USE_CACHE_FOR_BITS
#include "BITSTATE.h"

#include "EXP.h"
#include "SFX.h"
#define MECH_OWNER_DECLARATIONS
#include "MECH.h"
#undef MECH_OWNER_DECLARATIONS
#include "MAIN.h"
#define STATSTABLE_UNSIZED_STATS_DECLARATION
#include "STATS.h"
#include "BADDY.h"
#include "FRONT.h"
#include "MEM.h"
#include "MIPS.h"
#include "M3DUTILS.h"
#include "M3DZONE.h"
#include "globals.h"
#include "PAD.h"
#include "FONTTOOLS.h"
#include "TEXTEFFECTS.h"
#include "PSXREGION.h"
#define M3DCOLIJ_LINE_INFO_LAYOUT
#include "M3DCOLIJ.h"
#undef M3DCOLIJ_LINE_INFO_LAYOUT

/** Face-packet prefix consumed by dynamic-lighting colour sampling. */
struct SFaceLightingMech {
    u16 Flags;
    u8 _padToColour[6];
    union {
        u32 RGB;
        u8 ColourIndices[4];
    } Colour;
};

/**
 * Panel-data slice exposing only the embedded font and text-effect
 * sub-objects destroyed by CBruce::~CBruce (layout from MAIN_STRUCTS.h;
 * the falling-text sub-objects use their shared target-proven layout).
 */
#define BIT_DUST_MANAGER_LAYOUT
#define BIT_BLOOD_MANAGER_LAYOUT
#include "BIT.h"
#undef BIT_BLOOD_MANAGER_LAYOUT
#undef BIT_DUST_MANAGER_LAYOUT

struct CBruce;
struct CPanelData {
    /** Construct the panel state (owned by PANEL.cpp). */
    CPanelData(CBruce *player);

    u8 _padToTimerFont[356];
    Font mTimerFont;                                  // 0x164
    Font mTrickFont;                                  // 0x1b4
    Font mScoreFont;                                  // 0x204
    FallingTextEffect mFallingTextEffect;             // 0x254
    TrickTextEffect mTrickTextEffect;                 // 0x374 (TrickTextEffect)
    TextEffect *mpTextEffect;                         // 0x38c
    FallingTextEffect mOutOfBoundsText;               // 0x390
    u8 _opaqueTail[2276 - 1200];
};

/** Constructor-local form of the inline three-component game vector. */
struct CVectorMechCtor {
    int vx;
    int vy;
    int vz;

    /** Assign all three game-space components. */
    void Set(int x, int y, int z) {
        vx = x;
        vy = y;
        vz = z;
    }
};

#include "SLIGHT.h"
#include "CPOWERUP.h"
#include "POWERUP.h"

/**
 * The skater: a CSuper with the complete 5228-byte gameplay state.  Slot
 * overrides follow the CBody table: Die, AI, DoLightingSetup, Hit and
 * DeleteStuff; EveryFrame is inherited.
 */
struct CBruce : CSuper {
    CPanelData mPanelData;  // 0x190
    void *mpCamera;  // 0xa74
    struct BoardStats *mpBoardStats;  // 0xa78
    u8 _pada7c[40];
    s16 mTrickGravity;  // 0xaa4
    u8 _padaa6[522];
    Dust mDust;  // 0xcb0
    Blood mBlood;  // 0xcf0
    s16 mFrozen;  // 0xd4c
    u8 _padd4e[2];
    int mDoingATrick;  // 0xd50
    int mCanStartNextTrick;  // 0xd54
    u8 _padd58[80];
    int mSkaterType;  // 0xda8
    int mIndex;  // 0xdac
    int mPlayTime;  // 0xdb0
    struct SControl *mPad;  // 0xdb4
    u8 _paddb8[56];
    int mIsOnTaggedPoly;  // 0xdf0
    int mStickToInvisible;  // 0xdf4
    CVector mLastVel;  // 0xdf8
    int mMaxKickSpeed;  // 0xe04
    int mSpeedBoost;  // 0xe08
    int mCess;  // 0xe0c
    int mManual;  // 0xe10
    int mManIsCrouched;  // 0xe14
    int mManIsJumping;  // 0xe18
    int mJumpPending;  // 0xe1c
    int mAirTime;  // 0xe20
    int mJumpStrength;  // 0xe24
    int mLastJumpStrength;  // 0xe28
    int mApplyJumpForce;  // 0xe2c
    u8 _pade30[56];
    int mRecentEvent1;  // 0xe68
    int mRecentEvent2;  // 0xe6c
    MATRIX mOldRotationMatrix;  // 0xe70
    MATRIX mRotationMatrix;  // 0xe90
    int mDoingSharpTurn;  // 0xeb0
    int mTurning;  // 0xeb4
    int mTapTurn;  // 0xeb8
    int mPitchAngle;  // 0xebc
    int mNumGrinds;  // 0xec0
    int mRailType;  // 0xec4
    int mOnRail;  // 0xec8
    int mStickToRail;  // 0xecc
    u8 _paded0[12];
    int mResponseTimer;  // 0xedc
    u8 _padee0[24];
    int mDontStickTimer;  // 0xef8
    int mSameRailTimer;  // 0xefc
    int mDontStickRail;  // 0xf00
    u8 _padf04[92];
    int mKickLockout;  // 0xf60
    int mJumpSpeed;  // 0xf64
    int mJumpFrame;  // 0xf68
    int mWallrideTime;  // 0xf6c
    int mHandPlantTweaked;  // 0xf70
    int mBailState;  // 0xf74
    int mLimitBailVel;  // 0xf78
    int mInBail;  // 0xf7c
    int mHeadHit;  // 0xf80
    int mMagicPoints;  // 0xf84
    int mMagicTime;  // 0xf88
    u8 _padf8c[136];
    u8 mInputDelay;  // 0x1014
    u8 _pad1015[19];
    int mComboCounter;  // 0x1028
    u8 _pad102c[8];
    int mShadowY;  // 0x1034
    u8 _pad1038[12];
    u32 mSFXGrind;  // 0x1044
    u32 mSFXGround;  // 0x1048
    u32 mSFXAir;  // 0x104c
    u32 mSFXPitch;  // 0x1050
    u32 mSFXVol;  // 0x1054
    int mTruckSqueak;  // 0x1058
    int mFootSound;  // 0x105c
    int mFootSFX;  // 0x1060
    int mTerrain;  // 0x1064
    int mTerrainSFX;  // 0x1068
    int mPhysicsState;  // 0x106c
    int mOldPhysicsState;  // 0x1070
    MATRIX mTempRotationMatrix;  // 0x1074
    CVector mTempPos;  // 0x1094
    CVector mFront;  // 0x10a0
    CVector mRight;  // 0x10ac
    CVector mUp;  // 0x10b8
    CVectorMechCtor mLastFallLine;  // 0x10c4
    int mFallLineAdjustment;  // 0x10d0
    SVECTOR mLastPolyNormal;  // 0x10d4
    int mSameNormal;  // 0x10dc
    VECTOR mOldNormal;  // 0x10e0
    int mLeanAngle;  // 0x10f0
    int mAnimLeanAngle;  // 0x10f4
    u8 _pad10f8[36];
    u8 mGlowR;  // 0x111c
    u8 mGlowG;  // 0x111d
    u8 mGlowB;  // 0x111e
    u8 mTargetGlowR;  // 0x111f
    u8 mTargetGlowG;  // 0x1120
    u8 mTargetGlowB;  // 0x1121
    u8 mGlowSpeed;  // 0x1122
    u8 mGlowDownSpeed;  // 0x1123
    int mBrightness;  // 0x1124
    u8 _pad1128[12];
    u8 mAnalogue;  // 0x1134
    char mAX;  // 0x1135
    char mAY;  // 0x1136
    u8 _pad1137[13];
    u16 mGroundCounter;  // 0x1144
    u8 _pad1146[2];
    int mHistoryPos;  // 0x1148
    struct SHistory mHistory[100];  // 0x114c

    CBruce();
    virtual ~CBruce();
    void Die();
    void AI();
    void DoLightingSetup();
    int Hit(int Damage, const CVector &knock, int whathit);
    void DeleteStuff();

    /** Refresh the orientation basis vectors from the skater matrix. */
    void FRUVectorsFromRotMatrix();
    int History_Add(char *name, int spinAndStance);
    void History_Reset();
    int History_Find(char *name, int spinAndStance);
    void InitItem(char *name);
    void GetStats(int skaterSlot);
    void CalculateDynamicLighting(unsigned int *face, Item *item);
    int FlipToVelocity();
    void BloodSplat(int bodyPart, int maxBloodBits);
    void BoardOff();
    void BoardOn();
    void DoPhysics();
    void DoShadowCheck();
    void CollideWithObject(CBody *body);
    void ReadAnalogueInput();
    void GetHookPosition(CVector &position, u8 hook);
    void HandleWater();
    void GlowUpdate();
};

/**
 * CSpark overlay: velocity inherited from CBit plus the spark's floor
 * plane.  sizeof(CSpark) == 0x5C is the allocation size passed to
 * CBit's operator new by BloodSplat.
 */
struct CSpark {
    /** Construct one transient spark. */
    CSpark(CVector &position, int velocity, int gravity, int life);

    u8 _padToVel[36];
    CVector mVel;                                     // 0x24 (CBit.mVel)
    u8 _padToFloorY[88 - 48];
    int mFloorY;                                      // 0x58
};

#include "SCHARACTERPROGRESS.h"

/** SCareer prefix through the character-progress table used by MECH (MAIN.h only forward-declares it). */
struct SCareer {
    int Version;
    int MaxTapes;
    SCharacterProgress CharacterProgress[14];
};

/** Video recorder state needed to choose live, record, or playback input. */
struct SVideoInfo {
    int VideoMode;
    u8 _opaque[188];
};

/** Camera field selected for the player camera during skater construction. */
struct CCamera {
    u8 _padToCameraMode[1368];
    int mCameraMode;
    u8 _opaqueTail[1668 - 1372];

    /** Select the active gameplay camera mode. */
    void SetMode(int mode) {
        mCameraMode = mode;
    }

    /** Return whether the competition-intro camera mode is active. */
    int InCompetitionIntro();
};

typedef char SFaceLightingMech_size_check[(sizeof(struct SFaceLightingMech) == 12) ? 1 : -1];
typedef char CPanelData_size_check[(sizeof(struct CPanelData) == 2276) ? 1 : -1];
typedef CCamera CCameraMechCtor;
typedef char CCameraMech_size_check[(sizeof(CCamera) == 1668) ? 1 : -1];
typedef char CBruce_mech_size_check[(sizeof(struct CBruce) == 5228) ? 1 : -1];
typedef char CSpark_size_check[(sizeof(struct CSpark) == 0x5C) ? 1 : -1];
typedef char Mech_SCharacterProgress_size_check[(sizeof(struct SCharacterProgress) == 32) ? 1 : -1];
typedef char SVideoInfo_size_check[(sizeof(struct SVideoInfo) == 192) ? 1 : -1];
typedef char CBruce_rotation_matrix_offset_check[((unsigned long)&(((CBruce *)0)->mRotationMatrix) == 0xE90) ? 1 : -1];
typedef char CBruce_old_rotation_matrix_offset_check[((unsigned long)&(((CBruce *)0)->mOldRotationMatrix) == 0xE70) ? 1 : -1];
typedef char CBruce_temp_rotation_matrix_offset_check[((unsigned long)&(((CBruce *)0)->mTempRotationMatrix) == 0x1074) ? 1 : -1];
typedef char CBruce_history_pos_offset_check[((unsigned long)&(((CBruce *)0)->mHistoryPos) == 0x1148) ? 1 : -1];
typedef char CBruce_history_offset_check[((unsigned long)&(((CBruce *)0)->mHistory) == 0x114C) ? 1 : -1];
typedef char SDK_MATRIX_mech_size_check[(sizeof(MATRIX) == 32) ? 1 : -1];
typedef char SDK_VECTOR_mech_size_check[(sizeof(VECTOR) == 16) ? 1 : -1];
typedef char CVectorMechCtor_size_check[(sizeof(struct CVectorMechCtor) == 12) ? 1 : -1];
typedef char SDK_SVECTOR_mech_size_check[(sizeof(SVECTOR) == 8) ? 1 : -1];
typedef char SDK_CVECTOR_mech_size_check[(sizeof(CVECTOR) == 4) ? 1 : -1];
typedef char Mech_CFriction_size_check[(sizeof(struct CFriction) == 3) ? 1 : -1];
typedef char Mech_SLight_size_check[(sizeof(SLight) == 52) ? 1 : -1];

#include "FONT.h"
#include "UTILS.h"
#include "CFLATRIPPLE.h"
typedef char CFlatRipple_size_check[
    (sizeof(CFlatRipple) == 0x74) ? 1 : -1];

// === External function declarations ===
#include "VIDEO.h"
#include "BIT.h"
#include <STDIO.H>

#include "GSKATER_STATE.h"
#define VIDEOINFO_DECLARE_GVINFO1
#define VIDEOINFO_DECLARE_GVINFO2
#include "VIDEOINFO.h"

/**
 * Compact diagnostic format retained in the original small-data section.
 */
static char Mech_StatsFormat[12]
    __attribute__((section(".sdata"), aligned(4))) = "%d %d %d %d";

/** Active skater used by script and collision systems. */
CBruce *pCurrentPlayer __attribute__((section(".sbss")));

/** Default skater light used by ordinary levels. */
SLight Skater_DefaultLight __attribute__((section(".data"))) = {
    {
        {0, 0x1000, 0},
        {0, -0x1000, 0},
        {-3857, 0, 1380},
    },
    0,
    {
        {640, 2944, 320},
        {640, 2944, 320},
        {640, 2944, 320},
    },
    0,
    {2176, 2176, 2176},
};

/** Warmer skater light selected by the generated Mars level. */
SLight Skater_MarsLight __attribute__((section(".data"))) = {
    {
        {0, 0x1000, 0},
        {0, -0x1000, 0},
        {-3857, 0, 1380},
    },
    0,
    {
        {192, 786, 3072},
        {192, 705, 2628},
        {192, 1088, 1992},
    },
    0,
    {1664, 1664, 1664},
};

/** Per-skater hook indices loaded after the skater model is initialized. */
s16 SkaterHooks[14][10] __attribute__((section(".data"))) = {
    {0, 1, 0, 0, 0, 18, 0, 0, 0, 3},
    {0, 1, 0, 0, 0, 12, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 12, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 12, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 12, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 12, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 12, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 12, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 12, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 12, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 12, 0, 0, 0, 0},
    {},
    {},
    {},
};

#define HEADBLOODATFRAME_OWNER_DECLARATION
#include "HEADBLOODATFRAME.h"

/** Animation frame that emits head blood for each skater model. */
s16 HeadBloodAtFrame[14] __attribute__((section(".data"))) = {
    19, -1, 17, 17, 17, 17, 17, 17, 17, 17, 17, 0, 0, 0,
};

/** Board-stat bonuses filled for the active skaters at run setup. */
BoardStats GBoardStats[2] __attribute__((section(".sdata"))) = {};

/** Assign all three components of a short game-space vector. */
static inline void MechSetSVector(CSVector *v, int x, int y, int z)
{
    v->vx = x;
    v->vy = y;
    v->vz = z;
}

/** Branch-free signed magnitude used by the original fixed-point helpers. */
static inline int MechAbs(int value)
{
    int sign = value >> 31;
    return (value ^ sign) - sign;
}

// === Extern "C" forward declarations ===
#include "RCOSSIN.h"

// === Function implementations (address order) ===

/**
 * BoardOff__6CBruce
 *
 * Address:   0x800428F4
 * Mangled:   BoardOff__6CBruce
 * Demangled: CBruce::BoardOff(void)
 *
 */
void CBruce::BoardOff()
{
    mSubObjectDisplayMask |= (1 << Stats[mSkaterType].Board) | (1 << Stats[mSkaterType].Wheel1) | (1 << Stats[mSkaterType].Wheel2);
}

/**
 * BoardOn__6CBruce
 *
 * Address:   0x80042954
 * Mangled:   BoardOn__6CBruce
 * Demangled: CBruce::BoardOn(void)
 *
 */
void CBruce::BoardOn()
{
    mSubObjectDisplayMask &= ~((1 << Stats[mSkaterType].Board) | (1 << Stats[mSkaterType].Wheel1) | (1 << Stats[mSkaterType].Wheel2));
}

/**
 * GetStats__6CBrucei - Fill one player's board-stat bonuses.
 * In single-player career it picks the highest deck the skater has unlocked
 * (by tapes collected in GCareer) and copies that deck's four stat bonuses
 * into GBoardStats[Skater]. In multiplayer the bonuses are cleared instead.
 *
 * Address:   0x800429B4
 * Mangled:   GetStats__6CBrucei
 * Demangled: CBruce::GetStats(int)
 *
 * @param Skater  Player slot (0 or 1) whose GBoardStats entry is filled.
 */
void CBruce::GetStats(int Skater)
{
    if (GNumberOfPlayers == 1)
    {
        int highest_board = 0;

        // Highest deck this skater has unlocked with the tapes collected so far.
        while (highest_board < 7)
        {
            if (GCareer.CharacterProgress[mSkaterType].NumTapes <
                Stats[mSkaterType].Boards[highest_board + 1].TapesToUnlock)
                break;
            highest_board++;
        }

        GBoardStats[Skater].ollie = Stats[mSkaterType].Boards[highest_board].ollie;
        GBoardStats[Skater].speed = Stats[mSkaterType].Boards[highest_board].speed;
        GBoardStats[Skater].air = Stats[mSkaterType].Boards[highest_board].air;
        GBoardStats[Skater].balance = Stats[mSkaterType].Boards[highest_board].balance;
    }
    else
    {
        GBoardStats[Skater].ollie = 0;
        GBoardStats[Skater].speed = 0;
        GBoardStats[Skater].air = 0;
        GBoardStats[Skater].balance = 0;
    }
}

/**
 * Construct a skater and establish its gameplay, orientation, shadow, and
 * controller defaults before attaching it to the live mech list.
 *
 * Address:   0x80042B44
 * Mangled:   __6CBruce
 * Demangled: CBruce::CBruce(void)
 *
 * @param bruce Storage supplied for the new skater.
 * @return `bruce` (the GCC 2.x constructor return convention).
 */
CBruce::CBruce() : mPanelData(this)
{
    int maxKickSpeed;


    mTrickGravity = 100;
    mAnimSpeed = 0x10000;
    mpBoardStats = (BoardStats *)-1;

    if (Levels[GLevel].isCompetition && GGame == 1)
        mPlayTime = 3630;
    else if (GGame == 7)
        mPlayTime = 630;
    else
        mPlayTime = 7230;

    mFlags |= 0x200;
    int statsOverride = Cheat_StatsOverride;
    MechSetSVector(&mScale, 0x1000, 0x1000, 0x1000);

    if (!statsOverride)
    {
        int statsSpeed = Stats[mSkaterType].Speed;
        int boardSpeed = mpBoardStats->speed;
        if (mMagicTime || Cheat_Fire)
        {
            maxKickSpeed =
                ((boardSpeed + statsSpeed + 20) << 12) * 45 / 28;
        }
        else
        {
            maxKickSpeed =
                ((statsSpeed + boardSpeed + 17) << 12) * 45 / 28;
        }
    }
    else
    {
        maxKickSpeed =
            ((statsOverride + 17) << 12) * 45 / 28;
    }
    mMaxKickSpeed = maxKickSpeed;

    mOnRail = 0;
    mStickToRail = 0;
    mSameRailTimer = 0;
    mDontStickTimer = 0;
    mDontStickRail = -1;
    mSFXGrind = 0;
    mSFXGround = 0;
    mTruckSqueak = 0;
    mPhysicsState = 0;
    mOldPhysicsState = 0;
    mManIsCrouched = 0;
    mManIsJumping = 0;
    mJumpPending = 0;
    mDoingATrick = 0;
    mApplyJumpForce = 0;
    mComboCounter = 0;
    mExtraFlags |= 1;

    History_Reset();

    mStickToInvisible = 0;
    mIsOnTaggedPoly = 0;
    mLastFallLine.Set(0, 0, 0);
    mFallLineAdjustment = 0;
    mLastPolyNormal.vx = 0;
    mLastPolyNormal.vy = -0x1000;
    mLastPolyNormal.vz = 0;
    mPitchAngle = 0;
    mLeanAngle = 0;
    mAnimLeanAngle = 0;
    mKickLockout = 0;

    mRotationMatrix.m[0][0] = -0x1000;
    mRotationMatrix.m[1][0] = 0;
    mRotationMatrix.m[2][0] = 0;
    mRotationMatrix.m[0][1] = 0;
    mRotationMatrix.m[1][1] = -0x1000;
    mRotationMatrix.m[2][1] = 0;
    mRotationMatrix.m[0][2] = 0;
    mRotationMatrix.m[1][2] = 0;
    mRotationMatrix.m[2][2] = -0x1000;

    FRUVectorsFromRotMatrix();
    mOldRotationMatrix = mRotationMatrix;

    {
        int normX = mRotationMatrix.m[0][1];
        int normY = mRotationMatrix.m[1][1];
        int normZ = mRotationMatrix.m[2][1];

        mSameNormal = 0;
        mOldNormal.vx = normX;
        mOldNormal.vy = normY;
        mOldNormal.vz = normZ;
        mNormal.vx = normX;
        mNormal.vy = normY;
        mNormal.vz = normZ;
    }

    AttachTo(reinterpret_cast<CBody **>(&MechList));
    u16 bodyFlags =
        mCBodyFlags & (u16)~2;
    int numMechs = ++NumMechs;
    mCBodyFlags = bodyFlags;
    if (numMechs == 1)
        mPad = &Pad[0];
    else
        mPad = &Pad[1];
    mAngFric.Set(5, 1, 5);

    if (GNumberOfPlayers == 1)
    {
        mShadowLights = 1;
        mpShadowSource =
            static_cast<SVECTOR *>(Mem_New(32, 0, 1));
        mpShadowRGB =
            static_cast<CVECTOR *>(Mem_New(16, 0, 1));

        mpShadowSource->vx = 0;
        mpShadowSource->vy = -0x1000;
        mpShadowSource->vz = 0;
        mpShadowRGB->r = 0x80;
        mpShadowRGB->g = 0x80;
        mpShadowRGB->b = 0x80;
    }
    else
    {
        ShadowOn();
        UpdateShadow();
    }

    SLight *defaultLight = &Skater_DefaultLight;
    CCameraMechCtor *camera =
        reinterpret_cast<CCameraMechCtor *>(CameraList);
    void *generateLevel = GenerateLevel;
    camera->SetMode(1);
    mpLight = defaultLight;
    if (!generateLevel)
        mpLight =
            &Skater_MarsLight;

}

/**
 * _._6CBruce
 *
 * Address:   0x80042F44
 * Mangled:   _._6CBruce
 * Demangled: CBruce::~CBruce()
 *
 */
CBruce::~CBruce()
{
    if (mSFXGrind != 0)
    {
        SFX_Stop(mSFXGrind);
        mSFXGrind = 0;
    }

    if (mSFXGround != 0)
    {
        SFX_Stop(mSFXGround);
        mSFXGround = 0;
    }

    if (mpShadowSource != 0)
    {
        Mem_Delete(mpShadowSource);
    }

    if (mpShadowRGB != 0)
    {
        Mem_Delete(mpShadowRGB);
    }

    DeleteFrom(reinterpret_cast<CBody **>(&MechList));
    NumMechs = NumMechs - 1;
    DeleteStuff();


}

/**
 * History_Checksum(char *str, int seed) — rotate-left-1 + xor string hash
 *
 * Address: 0x80043080
 * Mangled: History_Checksum__FPci
 *
 * @param pName  Asset / object name string.
 * @param Spins  Initial low-bit seed mixed into the checksum.
 * @return hash
 */
int History_Checksum(char *pName, int Spins)
{
    int c = Spins & 1;
    if (*pName != '\0')
    {
        do
        {
            int top_bit = ((u32)c & 0x80000000) >> 31;
            c = (c << 1) + top_bit;
            c ^= *(u8 *)pName++;
        } while (*pName != '\0');
    }
    return c;
}

/**
 * History_Find__6CBrucePci
 *
 * Address:   0x800430C8
 * Mangled:   History_Find__6CBrucePci
 * Demangled: CBruce::History_Find(char *, int)
 *
 * @param pName  Asset / object name string.
 * @param Spins  Initial low-bit seed mixed into the checksum.
 * @return Matching history index, or -1 when absent.
 */
int CBruce::History_Find(char *pName, int Spins)
{
    int c = History_Checksum(pName, Spins);

    for (int i = 0; i < mHistoryPos; i++)
    {
        if (mHistory[i].Checksum == c)
        {
            return i;
        }
    }

    return -1;
}

/**
 * CBruce::History_Reset(void) — clear history count
 *
 * Address: 0x80043134
 *          Target: jr $ra; sw $zero, 0x1148($a0)
 * Mangled: History_Reset__6CBruce
 *
 */
void CBruce::History_Reset()
{
    mHistoryPos = 0;
}

/**
 * History_Add__6CBrucePci
 *
 * Address:   0x8004313C
 * Mangled:   History_Add__6CBrucePci
 * Demangled: CBruce::History_Add(char *, int)
 *
 * @param bruce  Skater whose recent-event history is updated.
 * @param pName  Asset / object name string.
 * @param Spins  Initial low-bit seed mixed into the checksum.
 * @return Updated occurrence count for the history entry.
 */
int CBruce::History_Add(char *pName, int Spins)
{
    int i = History_Find(pName, Spins);
    if (i != -1)
        goto done;
    {
        int count = mHistoryPos;
        if (count < 100)
        {
            i = count;
            mHistoryPos = i + 1;
        }
        else
        {
            i = 0;
        }
        {
            int checksum = History_Checksum(pName, Spins);
            mHistory[i].Checksum = checksum;
            mHistory[i].Count = 0;
        }
    }
done:
{
    int hitCount = mHistory[i].Count;
    hitCount++;
    mHistory[i].Count = hitCount;
    return mHistory[i].Count;
}
}

/**
 * GlowTowards(int current, int target, int step) — move current toward target by step
 *
 * Address: 0x800431EC
 *          PERFECT
 * Mangled: GlowTowards__Fiii
 *
 * @param A  Current glow component.
 * @param B  Target glow component.
 * @param Speed  Maximum change for this update.
 * @return Component value moved toward the target.
 */
int GlowTowards(int A, int B, int Speed)
{
    if (A < B)
    {
        if (B < A + Speed)
            return B;
        return A + Speed;
    }
    else
    {
        A = A - Speed;
        if (A < B)
            return B;
        return A;
    }
}

/**
 * GlowUpdate__6CBruce
 *
 * Address:   0x8004322C
 * Mangled:   GlowUpdate__6CBruce
 * Demangled: CBruce::GlowUpdate(void)
 *            Drive the skater glow toward its target color and clear the cycle when settled.
 *
 */
void CBruce::GlowUpdate()
{
    int glow = GlowTowards(mGlowR, mTargetGlowR, mGlowSpeed);
    mGlowR = glow;
    glow = GlowTowards(mGlowG, mTargetGlowG, mGlowSpeed);
    mGlowG = glow;
    glow = GlowTowards(mGlowB, mTargetGlowB, mGlowSpeed);
    mGlowB = glow;
    if (mGlowR == mTargetGlowR)
    {
        if ((((*(const u32 *)&mGlowR) >> 8) & 0xFFFF) ==
            (*(const u16 *)&mTargetGlowG))
        {
            u8 cycle = mGlowDownSpeed;
            if (cycle != 0)
            {
                mTargetGlowR = 0;
                mTargetGlowG = 0;
                mTargetGlowB = 0;
                mGlowSpeed = cycle;
                mGlowDownSpeed = 0;
            }
        }
    }
    if ((mGlowR | mGlowG | mGlowB) != 0)
    {
        mEllipsoidScale = 0x2000;
        u32 green = mGlowG;
        mEllipsoidOTPushback = 0xA;
        u32 red = mGlowR;
        u8 blue = mGlowB;
        u32 color = (green << 8) | 0x02000000;
        u32 packed = red | color;
        packed |= (u32)blue << 16;
        mEllipsoidRGB = packed;
    }
    else
    {
        mEllipsoidRGB = 0;
    }
}

/**
 * CBruce::DoLightingSetup(void) — empty virtual method override
 *
 * Address: 0x80043330
 *          Target: jr $ra; nop
 * Mangled: DoLightingSetup__6CBruce
 */
void CBruce::DoLightingSetup()
{
}

/**
 * CalculateDynamicLighting__6CBrucePUiP4Item
 *
 * Address:   0x80043338
 * Mangled:   CalculateDynamicLighting__6CBrucePUiP4Item
 * Demangled: CBruce::CalculateDynamicLighting(unsigned int *, Item *)
 *
 * For indexed-colour faces, samples the region colour table for each vertex
 * and averages the RGB components. Otherwise averages the face's packed RGB.
 * The resulting brightness is scaled by three before the lighting callback.
 */
void CBruce::CalculateDynamicLighting(
    unsigned int *p_face, Item *p_item)
{
    SFaceLightingMech *pFace =
        (SFaceLightingMech *)p_face;
    unsigned int flags = pFace->Flags;

    if ((flags & 0x800) != 0)
    {
        unsigned int *pColourTable = PSXRegion[p_item->Region].pColourTable;
        int vertices = 4;
        mBrightness = 0;
        if ((flags & 0x10) != 0)
        {
            vertices = 3;
        }
        if (vertices != 0)
        {
            int i = 0;
            unsigned int mask = 0xffffff;
            unsigned char *bytePtr =
                pFace->Colour.ColourIndices;
            do
            {
                unsigned int idx = *bytePtr;
                bytePtr++;
                i++;
                unsigned int c = pColourTable[idx];
                unsigned int rgb = c & mask;
                mBrightness = mBrightness + (c & 0xff) + ((rgb >> 8) & 0xff) + (rgb >> 16);
            } while (i < vertices);
        }
        mBrightness = mBrightness / (vertices * 3);
    }
    else
    {
        unsigned int rgb = pFace->Colour.RGB;
        unsigned int masked = rgb & 0xffffff;
        int sum = (rgb & 0xff) + ((masked >> 8) & 0xff) + (masked >> 16);
        mBrightness = sum / 3;
    }
    int b = mBrightness;
    mBrightness = b * 3;
    DoLightingSetup();
}

/**
 * CBruce::ReadAnalogueInput(void) — read analog stick from pad, optionally flip Y
 *
 * Address: 0x80043474
 *          PERFECT
 * Mangled: ReadAnalogueInput__6CBruce
 *
 */
void CBruce::ReadAnalogueInput()
{
    mAY =
        *(u8 *)&mPad->AnalogueMoveForwardsBackwards;
    mAX = *(u8 *)&mPad->AnalogueMoveLeftRight;
    if (Cheat_FlipScreen != 0)
        mAX = -mAX;
}

/**
 * CBruce::GetHookPosition(CVector &, unsigned char) — wrapper for M3dUtils
 *
 * Address: 0x800434B4
 *          Calls M3dUtils_GetHookPosition(vec, this, hookIndex & 0xFF)
 * Mangled: GetHookPosition__6CBruceR7CVectorUc
 *
 * @param pos  Position vector.
 * @param hook  Model hook index.
 */
void CBruce::GetHookPosition(CVector &pos, u8 hook)
{
    M3dUtils_GetHookPosition(
        reinterpret_cast<VECTOR *>(&pos),
        this, hook);
}

/**
 * CBruce::Die(void) — mark as dead if not already
 *
 * Address: 0x800434E0
 * Mangled: Die__6CBruce
 */
void CBruce::Die()
{
    if (!IsDead())
    {
        mCBodyFlags = mCBodyFlags | 0x40;
        mFlags = mFlags | 0x41;
    }
}

/**
 * CBruce::DeleteStuff(void) — empty virtual method override
 *
 * Address: 0x80043524
 *          Target: jr $ra; nop
 * Mangled: DeleteStuff__6CBruce
 */
void CBruce::DeleteStuff()
{
}

/**
 * CBruce::Hit(int, const CVector &, int) — always returns 1
 *
 * Address: 0x8004352C
 *          Target: jr $ra; addiu $v0, $zero, 1
 * Mangled: Hit__6CBruceiRC7CVectori
 * @param Damage  Damage applied by the hit.
 * @param knock  Knockback vector supplied by the caller.
 * @param whathit  Hit-kind identifier.
 * @return 1
 */
int CBruce::Hit(int Damage, const CVector &knock, int whathit)
{
    (void)Damage;
    (void)knock;
    (void)whathit;
    return 1;
}

/**
 * CBruce::CollideWithObject(CBody *) — empty virtual method override
 *
 * Address: 0x80043534
 *          Target: jr $ra; nop
 * Mangled: CollideWithObject__6CBruceP5CBody
 *
 * @param pOb  Body with which the skater collided.
 */
void CBruce::CollideWithObject(CBody *pOb)
{
    (void)pOb;
}

/**
 * DoShadowCheck__6CBruce
 *
 * Address:   0x8004353C
 * Mangled:   DoShadowCheck__6CBruce
 * Demangled: CBruce::DoShadowCheck(void)
 *            Cast a downward shadow ray and update the skater shadow when it finds valid ground.
 *
 */
void CBruce::DoShadowCheck()
{
    SLineInfo line_info;

    FRUVectorsFromRotMatrix();

    if (GNumberOfPlayers == 1)
    {
        line_info.StartCoords.vx =
            mPos.vx + mUp.vx * 50;
        line_info.StartCoords.vy =
            mPos.vy + mUp.vy * 50;
        line_info.StartCoords.vz =
            mPos.vz + mUp.vz * 50;
    }
    else
    {
        line_info.StartCoords.vx = mPos.vx;
        line_info.StartCoords.vy = mPos.vy;
        line_info.StartCoords.vz = mPos.vz;
    }

    line_info.EndCoords.vx = line_info.StartCoords.vx;
    line_info.EndCoords.vy = line_info.StartCoords.vy + 0xFA0000;
    line_info.EndCoords.vz = line_info.StartCoords.vz;
    M3dColij_InitLineInfo(&line_info);
    M3dZone_LineToItem(&line_info, 1);

    if (line_info.pItem &&
        line_info.Normal.vy < -1900 &&
        mPhysicsState != 4 &&
        mPhysicsState != 8)
    {
        {
            int _x = line_info.Position.vx;
            int _y = line_info.Position.vy;
            int _z = line_info.Position.vz;
            mShadowPos.vx = _x;
            mShadowPos.vy = _y;
            mShadowPos.vz = _z;
        }
        {
            int _x = line_info.Normal.vx;
            int _y = line_info.Normal.vy;
            int _z = line_info.Normal.vz;
            mShadowNormal.vx = _x;
            mShadowNormal.vy = _y;
            mShadowNormal.vz = _z;
        }
        int players = GNumberOfPlayers;
        if (players == 1)
        {
            int shade = ((4300 - line_info.Distance) << 7) / 4000;
            CVECTOR *rgb = mpShadowRGB;
            mShadowLights = players;
            rgb->b = shade;
            rgb->g = shade;
            rgb->r = shade;
        }
    }
    else
    {
        mShadowLights = 0;
    }
}

/**
 * CBruce::InitItem(char *) — call parent InitItem, then read hooks packet
 *
 * Address: 0x800436F0
 * Mangled: InitItem__6CBrucePc
 *
 * @param bruce  Skater whose item data is initialized.
 * @param pName  Asset / object name string.
 */
void CBruce::InitItem(char *pName)
{
    CItem::InitItem(pName);
    int idx = mSkaterType;
    M3dUtils_ReadHooksPacket(
        this, SkaterHooks[idx]);
}

/**
 * FlipToVelocity__6CBruce
 *
 * Address:   0x80043738
 * Mangled:   FlipToVelocity__6CBruce
 * Demangled: CBruce::FlipToVelocity(void)
 *
 * @return 1 when the orientation was flipped, otherwise 0.
 */
int CBruce::FlipToVelocity()
{
    if (mAnim == 0x22)
        return 0;

    if (Mips_CVecDotProd(
            reinterpret_cast<CVector *>(&mFront),
            reinterpret_cast<CVector *>(
                &mVel)) > 0x5000)
    {
        mRotationMatrix.m[0][2] = -mFront.vx;
        mFront.vx = mRotationMatrix.m[0][2];
        mRotationMatrix.m[1][2] = -mFront.vy;
        mFront.vy = mRotationMatrix.m[1][2];
        mRotationMatrix.m[2][2] = -mFront.vz;
        mFront.vz = mRotationMatrix.m[2][2];
        mRotationMatrix.m[0][0] = -mRight.vx;
        mRight.vx = mRotationMatrix.m[0][0];
        mRotationMatrix.m[1][0] = -mRight.vy;
        mRight.vy = mRotationMatrix.m[1][0];
        mRotationMatrix.m[2][0] = -mRight.vz;
        mRight.vz = mRotationMatrix.m[2][0];
        mExtraFlags ^= 2;
        return 1;
    }

    return 0;
}

/**
 * BloodSplat__6CBruceii
 *
 * Address:   0x80043820
 * Mangled:   BloodSplat__6CBruceii
 * Demangled: CBruce::BloodSplat(int, int)
 *
 * @param BodyPart  Hook index used as the emission point.
 * @param MaxBloodBits  Maximum number of spark particles to create.
 */
void CBruce::BloodSplat(int BodyPart, int MaxBloodBits)
{
    CSVector v;
    CVector Pos;
    CSVector Cone;
    SLineInfo BloodLine;

    if (Cheat_Blood == 0)
        return;

    Video_BloodSplat(this, BodyPart, MaxBloodBits);

    if (BitCount >= 200)
        return;

    v.vx = -0x400;
    v.vy = 0;
    v.vz = 0;
    Bit_SetSparkTrajectory(v);

    switch (BodyPart)
    {
    case 1:
        Cone.vx = 0x640;
        Cone.vy = 0x640;
        Cone.vz = 0;
        break;
    case 0:
    default:
        Cone.vx = 0x4B0;
        Cone.vy = 0x320;
        Cone.vz = 0;
        break;
    }
    Bit_SetSparkTrajectoryCone(Cone);
    Bit_SetSparkRGB(0x48, 0, 0);
    Bit_SetSparkFadeRGB(0, 0, 0);
    GetHookPosition(Pos, (u8)BodyPart);

    SparkSemiTrans = reinterpret_cast<void *>(0);
    UseCacheForBits = 0;

    int Bits = 200 - BitCount;
    if (MaxBloodBits < Bits)
        Bits = MaxBloodBits;

    BloodLine.StartCoords.vx = Pos.vx;
    BloodLine.StartCoords.vy = Pos.vy - 0x28000;
    BloodLine.StartCoords.vz = Pos.vz;
    BloodLine.EndCoords.vx = Pos.vx;
    BloodLine.EndCoords.vy = Pos.vy + 0x320000;
    BloodLine.EndCoords.vz = Pos.vz;
    M3dColij_InitLineInfo(&BloodLine);
    M3dZone_LineToItem(&BloodLine, 1);

    int FloorY;
    if (BloodLine.pItem != 0)
        FloorY = BloodLine.Position.vy - 0x4000;
    else
        FloorY = Pos.vy - 0x4000;

    int i;
    Pos.vy = Pos.vy - 0x1E000;
    i = 0;

    if (Bits > 0)
    {
        int gravity = 0x2800;
        do
        {
            if (Mem_GetFree(1) < 10000)
                return;
            Bit_SetSparkSize((i & 1) + 1);
            CSpark *pSpark = static_cast<CSpark *>(
                CBit::operator new(sizeof(CSpark)));
            if (pSpark != 0)
                pSpark = ::new (pSpark) CSpark(
                    Pos, (i >> 2) + 0xE, gravity, (i & 7) + 0x32);
            reinterpret_cast<CVector &>(pSpark->mVel) +=
                reinterpret_cast<const CVector &>(
                    mVel);
            pSpark->mFloorY = FloorY;
            i++;
            gravity += 0x100;
        } while (i < Bits);
    }

    UseCacheForBits = 1;
    SparkSemiTrans = reinterpret_cast<void *>(1);
}

/**
 * Run the skater's per-frame control, physics, collision, shadow, and debug
 * display updates.
 *
 * Address:   0x80043A74
 * Mangled:   AI__6CBruce
 * Demangled: CBruce::AI(void)
 */
void CBruce::AI()
{
    if (GamePaused != 0)
        return;

    if (((CCamera *)CameraList)->InCompetitionIntro() != 0)
    {
        mPlayTime = XFrames + 3630;
        return;
    }

    if (mRecentEvent1 != 0 &&
        XFrames - mRecentEvent1 > 10)
    {
        mRecentEvent1 = 0;
    }
    if (mRecentEvent2 != 0 &&
        XFrames - mRecentEvent2 > 10)
    {
        mRecentEvent2 = 0;
    }

    SVideoInfo *VInfo;
    if ((CBody *)this == MechList)
        VInfo = &GVInfo1;
    else
        VInfo = &GVInfo2;

    switch (VInfo->VideoMode)
    {
    case 1:
        Video_Record(this);
        break;
    case 2:
        Video_Playback(this);
        return;
    }

    mResponseTimer = 100;
    mRGB = 0x404040;
    ReadAnalogueInput();
    DoPhysics();
    HandleWater();

    if ((((mCollision >> 1) ^ 1) & 1) != 0)
        ++mGroundCounter;
    else
        mGroundCounter = 0;

    if (mInputDelay != 0)
        --mInputDelay;

    CVector nearest;
    CBody *pOb = M3dColij_LineToSphere(
        mOldPos,
        mPos,
        nearest, BaddyList, 0, 0x1000);
    if (pOb != 0)
        CollideWithObject(pOb);

    pOb = M3dColij_LineToSphere(
        mOldPos,
        mPos,
        nearest, PowerUpList, 0, 0x1000);
    if (pOb != 0)
        reinterpret_cast<CPowerUp *>(pOb)->TakeEffect(this);

    if (mPhysicsState != 0 ||
        MechAbs(mPos.vy - mShadowY) >= 65)
    {
        mShadowY = mPos.vy;
        DoShadowCheck();
    }
    else
    {
        mShadowPos.vx = mPos.vx;
        mShadowPos.vz = mPos.vz;
    }

    if (mHealth < 0)
        mHealth = 0;

    if ((Cheat_FPS != 0 || Cheat_StatsOverride != 0) &&
        this == GSkater[0])
    {
        static char lm[30];

        sprintf(
            lm,
            Mech_StatsFormat,
            Cheat_StatsOverride != 0
                ? Cheat_StatsOverride
                : (Stats[mSkaterType].Toughness +
                       ((mMagicTime != 0 || Cheat_Fire != 0)
                            ? 3
                            : 0)) +
                      mpBoardStats->ollie,
            Cheat_StatsOverride != 0
                ? Cheat_StatsOverride
                : (Stats[mSkaterType].Speed +
                       ((mMagicTime != 0 || Cheat_Fire != 0)
                            ? 3
                            : 0)) +
                      mpBoardStats->speed,
            Cheat_StatsOverride != 0
                ? Cheat_StatsOverride
                : (Stats[mSkaterType].Air +
                       ((mMagicTime != 0 || Cheat_Fire != 0)
                            ? 3
                            : 0)) +
                      mpBoardStats->air,
            Cheat_StatsOverride != 0
                ? Cheat_StatsOverride
                : (Stats[mSkaterType].Balance +
                       ((mMagicTime != 0 || Cheat_Fire != 0)
                            ? 3
                            : 0)) +
                      mpBoardStats->balance);
        Font_String(
            0x1A4, 200, lm, 0x5A, 0x5A, 0x64, 0);
    }
}

/**
 * Update the skater's water flag and periodically emit a surface ripple.
 *
 * Address:   0x80043F38
 * Mangled:   HandleWater__6CBruce
 * Demangled: CBruce::HandleWater(void)
 *
 */
void CBruce::HandleWater()
{
    if (GNumberOfPlayers == 2)
        return;

    int WaterLevel;
    if (this == (CBruce *)MechList)
    {
        WaterLevel = CurrentWaterLevel;
    }
    else
    {
        WaterLevel = CurrentWaterLevel2;
    }

    int bottom = mPos.vy + 0x19000;
    if (WaterLevel < bottom)
    {
        int flags = mFlags;
        int splashSfx = 0x2B;
        if ((flags & 8) == 0)
        {
            SFX_PlayX(splashSfx, 0x2000, 0);
            flags = mFlags;
        }

        flags = flags | 8;

        int timer = TTime;
        timer &= 3;
        mFlags = flags;
        if (timer != 0)
            return;

        CVector p;
        p = reinterpret_cast<const CVector &>(
            mPos);
        p.vy = WaterLevel;

        int offset = Rnd(24) + 16;
        int angle = Rnd(0x1000) & 0xFFF;
        s16 *tbl = rcossin_tbl;
        s16 *base = &tbl[angle * 2];
        p.vx += offset * base[0];
        p.vz += offset * base[1];

        CFlatRipple *ripple =
            static_cast<CFlatRipple *>(
                CBit::operator new(sizeof(CFlatRipple)));
        if (ripple != 0)
        {
            int radius = Rnd(24) + 40;
            int segments = Rnd(3) + 4;
            ::new (ripple) CFlatRipple(
                p, radius,
                0xDD, 0xEE, 0xFF, 12, segments);
        }
    }
    else
    {
        mFlags =
            mFlags & ~8;
    }
}

/**
 * SFX_Grunt__FP6CBruce
 *
 * Address:   0x800440E8
 * Mangled:   SFX_Grunt__FP6CBruce
 * Demangled: SFX_Grunt(CBruce *)
 *
 * @param pSkater  Active skater being processed.
 */
void SFX_Grunt(CBruce *pSkater)
{
    int terrain = Face_Terrain;
    int sfxId;

    if (terrain == 7) goto case_7;
    if (terrain == 9) goto case_9;
    goto after_sfx;
case_7:
    sfxId = 0x35;
    goto do_play1;
case_9:
    sfxId = 0x28;
    if (GLevel != 8) goto do_play1;
    sfxId = 0x89;
do_play1:
    SFX_PlayX(sfxId, 0x2000, 0);

after_sfx:;
    int playerIdx = pSkater->mSkaterType;
    int field = Stats[playerIdx].ComboID;

    if (field == 0xA000) goto set_1f;
    if (field != 0xC000) goto rnd_path;
set_1f:
    sfxId = 0x1F;
    goto do_play2;
rnd_path:
    sfxId = Rnd(3) + 0x1C;
do_play2:
    SFX_PlayX(sfxId, 0x2000, 0);
}
