// CAMERA.cpp -- Reconstructed translation unit
// Original: CAMERA.CPP
// Functions: 35, plus three naturally emitted header destructors
// Address range: 0x800793D0 - 0x8007E614
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#include "PSX.h"
#define CVECTOR_COMPONENT_CTORS
#define CCLASS_POLY_ITEM_FAMILY
#include "CCLASS_POLY.h"
#include "CAMERA.h"
#include "MAIN.h"
#include "STATS.h"
#include "BADDY.h"
#include "FRONT.h"
#include "M3DZONE.h"

#include <STDDEF.H>
#include <LIBGTE.H>
#include <INLINE_C.H>
#define M3DCOLIJ_LINE_INFO_LAYOUT
#include "M3DCOLIJ.h"
#undef M3DCOLIJ_LINE_INFO_LAYOUT

/** Fixed-point quaternion object (20 bytes). */
struct CQuat : CClass
{
    int x;
    int y;
    int z;
    int w;

    CQuat();
};

template <class T> struct AnimParam : CClass
{
    u32 *mTimer;
    T mParam;
    AnimParam(u32 *timer) : mTimer(timer), mParam() {}
    virtual ~AnimParam() {}
};

/** Camera tripod, lens, and focus snapshot (184 bytes). */
struct CamPos : CClass
{
    /** Whether to derive the tripod position from the tracked body. */
    bool calc_mTripod;
    struct CBody *mTripod;
    struct CVector mTripodPos;
    /** Whether to retain the current stick orientation. */
    bool lock_mStickO;
    struct CQuat mStickO;
    struct CVector mStickOffset;
    s16 mStickLength;
    /** Whether to calculate the lens orientation. */
    bool calc_mLenseO;
    struct CQuat mLenseO;
    struct CVector mLenseOffset;
    /** Whether to calculate the tracked focus position. */
    bool calc_mFocusPos;
    struct CBody *mFocus;
    struct CVector mFocusPos;
    struct CQuat mWorldO;
    struct CVector mWorldPos;
    MATRIX mTrans;

    CamPos();
    virtual ~CamPos();
    /** Draw this camera-pose record's tracked values. */
    void Display(u16 x, u16 y, u8 r, u8 g, u8 b);
    /** Draw the shared headings for camera-pose debug values. */
    static void DisplayLabels(u16 x, u16 y, u8 r, u8 g, u8 b);
};

/** Complete runtime camera object (1668 bytes). */
struct CCamera : CBody
{
    /** Enables the camera's owner-local tweak controls. */
    static int Tweaking;
    /** Selected row in the camera tweak menu. */
    static u16 TweakRow PSX_SECTION(".sdata");
    /** Selected camera-position column in the camera tweak menu. */
    static u16 TweakCol PSX_SECTION(".sdata");

    u16 mMikeIndex;
    struct CamPos mPosA;
    struct CamPos mLastPos;
    struct CamPos mCurrentPos;
    struct CamPos mPosB;
    u32 mCamPosDelta;
    u32 mCamPosRate;
    struct CBody *mTripod;
    struct CBody *mOldTripod;
    /** Whether the camera should calculate its tripod position. */
    bool mCalcTripod;
    struct CVector mOldTripodPos;
    /** Whether the focus target changed during this update. */
    bool new_focus;
    struct CVector mTripodPos;
    struct CVector mTripodPosIncrement;
    u32 mTripodTime;
    struct CBody *mFocus;
    /** Whether the camera should calculate its focus position. */
    bool mCalcFocus;
    struct CVector mOldFocusPos;
    struct CVector mFocusPos;
    struct CVector mFocusPosIncrement;
    u32 mFocusTime;
    int mZoom;
    u16 mZoomTime;
    int mZoomIncrement;
    /** Whether the camera is following a rail. */
    bool mOnRail;
    struct CVector mRailStart;
    struct CVector mRailEnd;
    s16 mPitchDamper;
    s16 mTripodPosYDamper;
    struct CVector mUp;
    struct CQuat mO;
    struct CQuat mDesiredO;
    struct CQuat mPrevO;
    struct CQuat mPreFocusO;
    struct CQuat mStoppedO;
    /** Whether mStoppedO contains a usable stopped orientation. */
    bool mStoppedOValid;
    struct CSVector mCamAngles;
    struct CVector mPosOffset;
    struct CVector mDesiredPos;
    struct CVector mDesiredFocusPos;
    int mCollisionRayLR;
    int mCollisionRayBack;
    s16 mCollisionAngLR;
    s16 mCollisionAngBack;
    s16 mCollisionBack;
    int saved_mCollisionRayLR;
    int saved_mCollisionRayBack;
    s16 saved_mCollisionAngLR;
    s16 saved_mCollisionAngBack;
    s16 saved_mCollisionBack;
    struct CSVector mShakeAmplitude;
    struct CFriction mShakeDecay;
    struct CSVector mShakeSpeed;
    int mCameraMode;
    int mCameraModeIncDir;
    int mBossCamSpinRate;
    u32 mTimer;
    struct t9AnimParam1Z5CQuat testQuat;
    s16 mColAngBuffer[8];
    s16 mPrevColAngBuffer[8];
    u8 mColCheckIndex;
    u32 mColCheckCycleCounter;
    int mDownDist;
    int mCompIntroTimer;
    /** Whether the competition-intro camera should run at increased speed. */
    bool mSpeedUpIntro;
    struct CVector mCompIntroEndPos;
    int extra_YRot;
    struct CVector mVFront;
    struct CVector mOldVFront;
    int prev_speed_lag_dist;
    /** Whether the camera is handling a big-air transition. */
    bool big_air;
    int big_air_timer;
    int big_air_end_timer;
    int big_air_mph;
    int new_hang_time;
    int in_pool_timer;
    int jump_acc;
    int jump_uptimer;
    int max_jump_dist;
    int max_jump_dist2;
    int jump_timer;
    int max_timer;
    int landing_timer;
    int landing_pos;
    int turn_delay_timer;
    struct CVector vFront;
    u32 mSpeed;
    int mSpeedBuffer[6];
    s16 mStoppedExtraYRot;
    VECTOR real_cam_offset;
    struct CQuat old_orientation;
    VECTOR old_offset;
    int loose_cam_timer;

    CCamera(struct CBody *tripod, u16 mike_index);
    virtual ~CCamera();
    /** Set the left/right collision-ray distance. */
    void SetCollisionRayLR(int ray);
    /** Set the rear collision-ray distance. */
    void SetCollisionRayBack(int ray);
    /** Set the left/right collision response angle. */
    void SetCollisionAngLR(s16 angle);
    /** Set the rear collision response angle. */
    void SetCollisionAngBack(s16 angle);
    /** Apply a camera-shake envelope from a world-space source. */
    void Shake(const CVector &position, EShakeType magnitude);
    /** Select the complex camera mode. */
    void SetComplexMode(u16 mode);
    /** Copy this camera into the active render-camera record. */
    void LoadIntoMikeCamera();
    /** Rebuild tracking orientation from the followed body. */
    void ResetOrientation();
    void ReactToCollision();
    void MoveToDesiredPos(unsigned int normal_slerp);
    /** Set the camera angle over the requested frame count. */
    void SetCamAngle(s16 angle, u16 frames);
    /** Set the horizontal camera distance over the requested frame count. */
    void SetCamXZDistance(u16 distance, u16 frames);
    /** Set the vertical camera distance over the requested frame count. */
    void SetCamYDistance(s16 distance, u16 frames);
    /** Set the horizontal camera offset over the requested frame count. */
    void SetCamXOffset(s16 offset, u16 frames);
    /** Set the vertical camera offset over the requested frame count. */
    void SetCamYOffset(s16 offset, u16 frames);
    /** Set the depth camera offset over the requested frame count. */
    void SetCamZOffset(s16 offset, u16 frames);
    /** Return the current fixed-point projection zoom. */
    int GetZoom();
    /** Set the zoom target immediately or interpolate it over the frame count. */
    void SetZoom(u16 zoom, u16 time);
    /** Update the owner-local camera tweak menu. */
    void TweakMenu();
    /** Update tracking, tweak controls, and shake response each frame. */
    virtual void AI();
    /** Update ordinary camera tracking. */
    void CM_Normal();
    /** Enter the competition-intro camera mode. */
    void StartCompetitionIntro();
    /** Advance the competition-intro camera mode. */
    void CM_CompetitionIntro();
    /** Return whether the competition-intro camera mode is active. */
    int InCompetitionIntro();
    /** Update the camera without big-air tracking. */
    void CM_NoBigAir();
};

PSX_LAYOUT_CHECK(Camera_CClass_size_must_be_4, sizeof(CClass) == 4);
PSX_LAYOUT_CHECK(Camera_CItem_size_must_be_76, sizeof(CItem) == 76);
PSX_LAYOUT_CHECK(Camera_CBody_size_must_be_264, sizeof(CBody) == 264);
PSX_LAYOUT_CHECK(Camera_Quat_size_must_be_20, sizeof(CQuat) == 20);
PSX_LAYOUT_CHECK(Camera_AnimQuat_size_must_be_28, sizeof(t9AnimParam1Z5CQuat) == 28);
PSX_LAYOUT_CHECK(Camera_CamPos_size_must_be_184, sizeof(CamPos) == 184);
PSX_LAYOUT_CHECK(Camera_Camera_size_must_be_1668, sizeof(CCamera) == 1668);
PSX_LAYOUT_CHECK(Camera_CamPosStruct_size_must_be_16, sizeof(CamPosStruct) == 16);
PSX_LAYOUT_CHECK(Camera_Preset_size_must_be_12, sizeof(SPresetCamera) == 12);

#include "OB.h"
#include "MIPS.h"
#include "UTILS.h"
#include "PAD.h"
#include "FONT.h"
#include <LIBGPU.H>

// === Forward type declarations ===

/** CBruce slice exposing the controller selected by the camera tripod. */
struct CameraBrucePadOwner : CBody
{
    u8 opaque_before_mPad[0xdb4 - sizeof(CBody)];
    SControl *mPad;
};

typedef char
    Camera_BrucePadOwner_size_must_be_0xdb8[(sizeof(CameraBrucePadOwner) == 0xdb8) ? 1 : -1];

/** CBruce state consulted by the camera's movement and pitch dampers. */
struct CameraBruceAiOwner : CBody
{
    u8 opaque_before_mInBail[0xf7c - sizeof(CBody)];
    int mInBail;
    u8 opaque_before_mPhysicsState[0x106c - 0xf80];
    EPhysicsState mPhysicsState;
    u8 opaque_before_mInAirTimer[0x1144 - 0x1070];
    u16 mInAirTimer;
};

typedef char
    Camera_BruceAiOwner_size_must_be_0x1148[(sizeof(CameraBruceAiOwner) == 0x1148) ? 1 : -1];

/** CBruce state consulted while selecting the camera's movement response. */
struct CameraBruceMoveOwner : CBody
{
    u8 opaque_before_mDoingATrick[0xd50 - sizeof(CBody)];
    int mDoingATrick;
    u8 opaque_before_mManIsJumping[0xe18 - 0xd54];
    int mManIsJumping;
    u8 opaque_before_mRotationMatrix[0xe90 - 0xe1c];
    MATRIX mRotationMatrix;
    u8 opaque_before_mBigAirs[0x1010 - 0xeb0];
    int mBigAirs;
    u8 opaque_before_mPhysicsState[0x106c - 0x1014];
    EPhysicsState mPhysicsState;
    u8 opaque_before_mFront[0x10a0 - 0x1070];
    CVector mFront;
    CVector mRight;
    CVector mUp;
};

typedef char
    Camera_BruceMoveOwner_size_must_be_0x10c4[(sizeof(CameraBruceMoveOwner) == 0x10c4) ? 1 : -1];

#include "SVIEWPORT.h"

/** CBruce fields used to halt the skater during a competition intro. */
struct CameraCompetitionSkater
{
    u8 opaque_before_mVel[0x54];
    CVector mVel;
    u8 opaque_before_mFront[0x10a0 - 0x60];
    CVector mFront;
};

typedef char
    Camera_CompetitionSkater_size_must_be_0x10ac[(sizeof(CameraCompetitionSkater) == 0x10ac) ? 1
                                                                                             : -1];

#include "VIDEO.h"

#include "SCAMERA.h"

/** Rebuild the fixed-point tripod offset from a rendered camera position. */
inline void Camera_RebuildOldOffset(CCamera &camera, const long &positionX, const long &positionY,
                                    const long &positionZ)
{
    camera.old_offset.vx = (positionX << 12) - camera.mTripodPos.vx;
    camera.old_offset.vy = (positionY << 12) - camera.mTripodPos.vy;
    camera.old_offset.vz = (positionZ << 12) - camera.mTripodPos.vz;
}

// === Free function declarations ===
#include "CAMERAAPI.h"

// === External function declarations ===
void Competition_ResetMarquee(void);
#include "CVECTOROPS.h"
#define CAMERALIST_OWNER_DECLARATIONS
#include "CAMERALIST.h"
#undef CAMERALIST_OWNER_DECLARATIONS
#include <STDIO.H>
/**
 * Owner-local debug text declared before its users and defined later in the
 * original small-data order. Address-derived labels are bound once here.
 */
static char s_Follow[];
static char s_Fixed[];
static char s_Quaternion[];
static char s_Tripod[];
static char s_X[];
static char s_Y[];
static char s_Z[];
static char s_StickO[];
static char s_StickLength[];
static char s_StickOffset[];
static char s_PosA[];
static char s_PosB[];
void Competition_MarqueeDisplay(void);
#include "M3DMATHS.h"
#include "GSKATER_STATE.h"
#include "GENERATELEVEL.h"
/** Packed fixed-point sine/cosine table used by camera shake. */
struct CameraSinCos
{
    s16 Sin;
    s16 Cos;
};
#define RCOSSIN_DECL_TYPE CameraSinCos
#define RCOSSIN_SCALAR_VIEW
#include "RCOSSIN.h"
#define Camera_Sine(angle) ((&rcossin_tbl)[(angle) & 0xfff].Sin)
/** Construct an identity quaternion. */
inline CQuat::CQuat() : x(0), y(0), z(0), w(0x1000)
{
}

#include "QUAT_API.h"

/** Base camera distance; also anchors CAMERA.CPP's global initializer name. */
int camDist PSX_SECTION(".sdata") = 658;
int camPitch PSX_SECTION(".sdata") = 54;
int camYOffset PSX_SECTION(".sdata") = -220;

static int camXZDistDeltaTimer PSX_SECTION(".sdata") = 0;
static int camYDist PSX_SECTION(".sdata") = -212;
static int camYDistDeltaTimer PSX_SECTION(".sdata") = 0;
static int camXOffset PSX_SECTION(".sdata") = 0;
static int camXOffsetDeltaTimer PSX_SECTION(".sdata") = 0;
static int camYOffsetDeltaTimer PSX_SECTION(".sdata") = 0;
static int camZOffset PSX_SECTION(".sdata") = 0;
static int camZOffsetDeltaTimer PSX_SECTION(".sdata") = 0;
static int Mick_CameraTweak PSX_SECTION(".sdata") = 0;
int Camera_Preset PSX_SECTION(".sdata") = 2;

/** Camera tuning deltas and CAMERA's private random stream (GLOBALS.H statics, MAIN.SYM order). */
static int camXZDistDelta;
static int camYDistDelta;
static int camAngleDelta;
static int camAngleDeltaTimer;
static int camAngleTarget;
static int camXOffsetDelta;
static int camYOffsetDelta;
static int camZOffsetDelta;
static int RandSeed;
static int RandA;
static int RandB;

static CVector LoosePosition = CVector(0, -0x190000, 0);
static CVector LooseFocus = CVector(0, -0x64000, 0);
static CVector StartPosition = CVector(0, -0xa0000, -0x3b6000);
static CVector StartFocus = CVector(0, -0x64000, 0);
static CVector NormalPosition = CVector(0, -0x96000, 0x28a000);
static CVector NormalFocus = CVector(0, -0x64000, 0);
static CVector FarPosition = CVector(0, -0x44c000, 0x514000);
static CVector FarFocus = CVector(0, -0x64000, -0x320000);
static CVector OverheadPosition = CVector(0, -0x8ca000, 0x190000);
static CVector OverheadFocus = CVector(0, -0x64000, -0x12c000);
static CVector FlyFocus = CVector(0, 0x64000, -0x6d60000);
static CVector DemoFocus = CVector(0, -0x64000, 0);
static CSVector BigShakeAmp = CSVector(25, 0, 50);
static CSVector MediumShakeAmp = CSVector(0, 0, 30);
static CSVector SmallShakeAmp = CSVector(0, 0, 25);
static CFriction LandShakeDecay = CFriction(3, 0, 3);
static CSVector LandShakeSpeed = CSVector(600, 0, 600);
static CVector UpDownPosition = CVector(0, -0x6e000, 0);

/** Camera presets and their display names, in the original data order. */
SPresetCamera Presets[5] PSX_SECTION(".data") = {
    { -2000, 654, 6786, "Very Far" }, { -268, 0, 946, "Far" },    { -140, 118, 386, "Default" },
    { -60, 80, 202, "Close" },        { -124, 0, 0, "Headshot" },
};

/** Quaternion probes owned and constructed by CAMERA.CPP. */
CQuat testquat;
CQuat testquat2;
CQuat testquat3;

/** Render-camera storage shared by gameplay and rendering owners. */
SCamera MikeCamera[2] PSX_SECTION(".data") = {};

/** Scratch matrix used while converting recovered camera orientations. */
MATRIX tm PSX_SECTION(".data") = {};


// === Extern "C" forward declarations ===
#define CAMERA_DECLARE_OWNER_ABI
#include "CAMERA.h"
// === Function implementations (address order) ===

/**
 * Camera_InitialRand__Fi
 *
 * Address:   0x800793D0
 * Mangled:   Camera_InitialRand__Fi
 * Demangled: Camera_InitialRand(int)
 *
 * @param a Initial seed for CAMERA's deterministic random stream.
 */
void Camera_InitialRand(int a)
{
    RandSeed = a;
    RandA = 0x12b9b0a1;
    RandB = 0x0aa2fb3f;
}


/**
 * Construct a gameplay camera around a tripod body and controller index.
 *
 * @param tripod Body whose position and controller drive the camera.
 * @param mike_index Initial rendered-camera slot; corrected from the tripod's pad.
 */
CCamera::CCamera(struct CBody *tripod, u16 mike_index)
    : mMikeIndex(mike_index), mTripod(tripod), mCalcTripod(true), new_focus(false), mFocus(tripod),
      mCalcFocus(true), mZoom(0xc0), mOnRail(false), mPitchDamper(0), mTripodPosYDamper(0),
      mCollisionRayLR(-1), mCollisionRayBack(-1), mCollisionAngLR(0x200), mCollisionAngBack(0x310),
      mCollisionBack(0x568), mCameraMode(1), mCameraModeIncDir(0), mBossCamSpinRate(0xf), mTimer(0),
      testQuat(&mTimer), mColCheckIndex(0), mColCheckCycleCounter(0), mDownDist(0),
      mSpeedUpIntro(false), mStoppedExtraYRot(0), loose_cam_timer(0)
{
    real_cam_offset.vx = 0;
    real_cam_offset.vy = 0;
    real_cam_offset.vz = 0;

    // Determine mike index from the tripod's control block
    SControl *ctrl = ((CameraBrucePadOwner *)mTripod)->mPad;
    if (ctrl == &Pad[0])
    {
        mMikeIndex = 0;
    }
    else if (ctrl == &Pad[1])
    {
        mMikeIndex = 1;
    }
    else
    {
        printf("camera can't find pad number!, CCamera constructor\n");
    }

    vFront = CVector(0, 0, 0x1000);

    big_air = false;
    in_pool_timer = 0x3e8;
    extra_YRot = 0;
    mTripodPos = mTripod->mPos;
    mTripodTime = 0;
    mFocusPos = mFocus->mPos;
    mFocusTime = 0;
    mType = 0x63;
    Camera_Preset = 2;

    SPresetCamera *base = Presets;
    SPresetCamera *preset = base + 2;
    camDist = preset->Dist;
    camPitch = preset->Pitch;
    camYOffset = base[2].YOffset;
    mFlags = 1;

    LoadIntoMikeCamera();

    // Attach to camera list
    AttachTo(&CameraList);

    NumCameras++;
    mRMinor = 0;
    mCBodyFlags &= 0xfffd;
}

/**
 * Debug label retained by the original CAMERA object between its constructor
 * diagnostic and virtual dispatch table.
 */
static char s_JumpCompensation[] PSX_SECTION_ALIGNED(".rdata", 4) = "jump compensation";

/** Destroy the camera's body-list attachment and owned value members. */
CCamera::~CCamera()
{
    DeleteFrom(&CameraList);
    NumCameras--;
}

/**
 * SetCollisionRayLR__7CCamerai
 *
 * Address:   0x80079794
 * Mangled:   SetCollisionRayLR__7CCamerai
 * Demangled: CCamera::SetCollisionRayLR(int)
 *            ASM: jr $ra; sw $a1, 0x528($a0)
 *
 * @param r  Red component (0-255).
 */
void CCamera::SetCollisionRayLR(int r)
{
    mCollisionRayLR = r;
}


/**
 * SetCollisionRayBack__7CCamerai
 *
 * Address:   0x8007979C
 * Mangled:   SetCollisionRayBack__7CCamerai
 * Demangled: CCamera::SetCollisionRayBack(int)
 *            ASM: jr $ra; sw $a1, 0x52c($a0)
 *
 * @param r  Red component (0-255).
 */
void CCamera::SetCollisionRayBack(int r)
{
    mCollisionRayBack = r;
}


/**
 * SetCollisionAngLR__7CCameras
 *
 * Address:   0x800797A4
 * Mangled:   SetCollisionAngLR__7CCameras
 * Demangled: CCamera::SetCollisionAngLR(short)
 *            ASM: jr $ra; sh $a1, 0x530($a0)
 *
 * @param a Left/right collision response angle.
 */
void CCamera::SetCollisionAngLR(s16 a)
{
    mCollisionAngLR = a;
}


/**
 * SetCollisionAngBack__7CCameras
 *
 * Address:   0x800797AC
 * Mangled:   SetCollisionAngBack__7CCameras
 * Demangled: CCamera::SetCollisionAngBack(short)
 *            ASM: jr $ra; sh $a1, 0x532($a0)
 *
 * @param a Rear collision response angle.
 */
void CCamera::SetCollisionAngBack(s16 a)
{
    mCollisionAngBack = a;
}


/**
 * SendShake__FRC7CVectorP5CBody10EShakeType
 *
 * Address:   0x800797B4
 * Mangled:   SendShake__FRC7CVectorP5CBody10EShakeType
 * Demangled: SendShake(const CVector &, CBody *, EShakeType)
 *
 * @param pos  Position vector.
 * @param pOb  Ob to operate on.
 * @param ShakeMagnitude Shake envelope to propagate through the list.
 */
static void SendShake(const CVector &pos, CBody *pOb, EShakeType ShakeMagnitude)
{
    while (pOb)
    {
        pOb->mInputFlags = pOb->mInputFlags | 2;
        pOb = (CBody *)pOb->mNextItem;
    }
}


/**
 * Shake__7CCameraRC7CVector10EShakeType
 *
 * Address:   0x800797E4
 * Mangled:   Shake__7CCameraRC7CVector10EShakeType
 * Demangled: CCamera::Shake(const CVector &, EShakeType)
 *
 * @param pos  Position vector.
 * @param ShakeMagnitude Requested camera-shake envelope.
 */
void CCamera::Shake(const CVector &pos, EShakeType ShakeMagnitude)
{
    switch (ShakeMagnitude)
    {
        case 0:
        {
            mShakeAmplitude = BigShakeAmp;
            break;
        }
        case 1:
        {
            mShakeAmplitude = MediumShakeAmp;
            break;
        }
        case 2:
        {
            mShakeAmplitude = SmallShakeAmp;
            break;
        }
        default: goto send_shakes;
    }

    mShakeDecay = LandShakeDecay;
    mShakeSpeed = LandShakeSpeed;

send_shakes:
    {
        EShakeType st = ShakeMagnitude;
        SendShake(pos, BaddyList, st);
        SendShake(pos, EnvironmentalObjectList, st);
    }
}


/**
 * SetComplexMode__7CCameraUs (intentional no-op in this build)
 *
 * Address:   0x80079908
 * Mangled:   SetComplexMode__7CCameraUs
 * Demangled: CCamera::SetComplexMode(unsigned short)
 *            ASM: jr $ra; nop
 *
 * @param mode Requested complex camera mode.
 */
void CCamera::SetComplexMode(u16 mode)
{
}


/**
 * LoadIntoMikeCamera__7CCamera
 *
 * Address:   0x80079910
 * Mangled:   LoadIntoMikeCamera__7CCamera
 * Demangled: CCamera::LoadIntoMikeCamera(void)
 *
 */
void CCamera::LoadIntoMikeCamera()
{
    VECTOR v;

    if (((CameraBruceMoveOwner *)mTripod)->mPhysicsState == PHYSICS_IN_WALLRIDE)
    {
        MikeCamera[Camera_CurrentMikeCamera].Position.vx = (mTripodPos.vx + old_offset.vx) >> 12;
        MikeCamera[Camera_CurrentMikeCamera].Position.vy = (mTripodPos.vy + old_offset.vy) >> 12;
        MikeCamera[Camera_CurrentMikeCamera].Position.vz = (mTripodPos.vz + old_offset.vz) >> 12;

        mO = old_orientation;
    }
    else
    {
        MikeCamera[Camera_CurrentMikeCamera].Position.vx = (mPos.vx + real_cam_offset.vx) >> 12;
        MikeCamera[Camera_CurrentMikeCamera].Position.vy = (mPos.vy + real_cam_offset.vy) >> 12;
        MikeCamera[Camera_CurrentMikeCamera].Position.vz = (mPos.vz + real_cam_offset.vz) >> 12;

        old_orientation = mO;
        Camera_RebuildOldOffset(*this, MikeCamera[Camera_CurrentMikeCamera].Position.vx,
                                MikeCamera[Camera_CurrentMikeCamera].Position.vy,
                                MikeCamera[Camera_CurrentMikeCamera].Position.vz);
    }

    MikeCamera[Camera_CurrentMikeCamera].Focus.vx = (mFocusPos.vx + Camera_CamOffset.vx) >> 12;
    MikeCamera[Camera_CurrentMikeCamera].Focus.vy = (mFocusPos.vy + Camera_CamOffset.vy) >> 12;
    MikeCamera[Camera_CurrentMikeCamera].Focus.vz = (mFocusPos.vz + Camera_CamOffset.vz) >> 12;

    QToM(mO, MikeCamera[Camera_CurrentMikeCamera].Transform);
    TransMatrix(&MikeCamera[Camera_CurrentMikeCamera].Transform,
                &MikeCamera[Camera_CurrentMikeCamera].Position);
}


/**
 *
 * Address:   0x80079B94
 * Mangled:   ResetOrientation__7CCamera
 * Demangled: CCamera::ResetOrientation(void)
 *            Rebuilds the camera's forward/up state from the followed body, resets the
 *            position history, and pushes the refreshed orientation into MikeCamera.
 *
 */
void CCamera::ResetOrientation()
{
    VECTOR vtemp1;
    VECTOR vtemp2;
    CameraBruceMoveOwner *pBruce = (CameraBruceMoveOwner *)mTripod;

    vtemp1.vx = 0;
    vtemp1.vy = 0;
    vtemp1.vz = -0x1000;
    ApplyMatrixLV(&pBruce->mRotationMatrix, &vtemp1, &vtemp2);

    vFront.vx = vtemp2.vx;
    vFront.vy = vtemp2.vy;
    vFront.vz = vtemp2.vz;

    mOldVFront = vFront << 12;
    mVFront = mOldVFront;

    mTripodPos = mTripod->mPos;
    mOldTripodPos = mTripodPos;

    Camera_CurrentMikeCamera = mMikeIndex;

    CM_Normal();

    mStoppedO = mPrevO = mO = mDesiredO;
    mStoppedOValid = true;

    LoadIntoMikeCamera();
}


/**
 * Probe the camera's collision rays and apply orientation corrections.
 *
 * Address:   0x80079D3C
 * Mangled:   ReactToCollision__7CCamera
 * Demangled: CCamera::ReactToCollision(void)
 *
 * @param self Camera whose desired orientation and collision history are updated.
 */
void CCamera::ReactToCollision()
{
    SLineInfo line_info;
    MATRIX m;
    VECTOR vLeft;
    VECTOR vRight;
    VECTOR vBack;
    VECTOR vTemp;
    CVector vVel;
    CVector vStick;
    CVector vColCheck;
    VECTOR vOffset;

    if (GamePaused != 0)
    {
        return;
    }
    if (GameFrozen != 0)
    {
        return;
    }
    if (mTimer < 13)
    {
        return;
    }

    QToM(mDesiredO, m);

    ++mColCheckIndex;
    if (mColCheckIndex > 2)
    {
        mColCheckIndex = 0;
        ++mColCheckCycleCounter;
    }

    if (mColCheckIndex == 2)
    {
        mPrevColAngBuffer[2] = mColAngBuffer[2];
        copyVector(&line_info.StartCoords, &mPos);
        line_info.EndCoords.Set(mPos.vx, mPos.vy, mPos.vz);
        line_info.EndCoords.vy += 0xbb8000;
        M3dColij_InitLineInfo(&line_info);
        line_info.RecordTriggerZoneHits = 0;
        M3dZone_LineToItem(&line_info, 1);

        if (line_info.pItem != 0)
        {
            mDownDist = line_info.Distance;
            if (line_info.Distance < 0x78)
            {
                int ratio = ((0x78 - line_info.Distance) * 0x1000) / 0x78;
                mColAngBuffer[2] = (s16)((ratio * ratio) >> 15);
            }
            else
            {
                mColAngBuffer[2] = 0;
            }
        }
        else
        {
            if (((CameraBruceAiOwner *)mTripod)->mPhysicsState == PHYSICS_IN_AIR)
            {
                mColAngBuffer[2] = 0x200;
            }
            else
            {
                mColAngBuffer[2] = mPrevColAngBuffer[2];
            }
            mDownDist = -1;
        }

        if (((CameraBruceAiOwner *)mTripod)->mPhysicsState == PHYSICS_ON_INVISIBLE)
        {
            setVector(&vTemp, 0, Camera_CamDist << 13, 0);
            ApplyMatrixLV(&m, &vTemp, &vBack);

            line_info.StartCoords.vx = mPos.vx;
            line_info.StartCoords.vy = mPos.vy;
            line_info.StartCoords.vz = mPos.vz;
            line_info.EndCoords.vx = line_info.StartCoords.vx + vBack.vx;
            line_info.EndCoords.vy = line_info.StartCoords.vy + vBack.vy;
            line_info.EndCoords.vz = line_info.StartCoords.vz + vBack.vz;
            M3dColij_InitLineInfo(&line_info);
            line_info.RecordTriggerZoneHits = 0;
            CameraCollisionCheck = 1;
            M3dZone_LineToItem(&line_info, 1);
            CameraCollisionCheck = 0;
            mColAngBuffer[2] = 0;

            if (line_info.pItem != 0)
            {
                if (line_info.Length == 0)
                {
                    line_info.Length = 1;
                }
                int ratio = ((line_info.Length - line_info.Distance) * 0x1000) / line_info.Length;
                ratio *= ratio;
                ratio >>= 12;
                int ang = 300;
                ang *= ratio;
                ang >>= 12;
                mColAngBuffer[2] += (s16)ang;
                mDownDist = line_info.Distance;
            }
            else
            {
                mDownDist = Camera_CamDist;
            }
        }
    }

    vTemp.vx = Camera_CamDist * -0x2000;
    vTemp.vy = vTemp.vz = 0;
    // FIXME(match): asm barrier — keeps the vTemp stores ahead of the ApplyMatrixLV arg setup (without it addiu a0/a1/a2 hoist and an extra addiu $a0,$sp,0xB8 appears; score 16); tried: 7 vTemp assignment forms, setVector inline (18), comma-expression args (16-18).
    asm volatile("");
    ApplyMatrixLV(&m, &vTemp, &vLeft);
    vRight.vx = -vLeft.vx;
    vRight.vy = -vLeft.vy;
    vRight.vz = -vLeft.vz;

    if (mCollisionRayLR != 0)
    {
        if (mColCheckIndex == 0)
        {
            mPrevColAngBuffer[0] = mColAngBuffer[0];
            if ((mColCheckCycleCounter & 1) != 0)
            {
                line_info.StartCoords.vx = mPos.vx;
                line_info.StartCoords.vy = mPos.vy;
                line_info.StartCoords.vz = mPos.vz;
                line_info.EndCoords.vx = line_info.StartCoords.vx + vLeft.vx;
                line_info.EndCoords.vy = line_info.StartCoords.vy + vLeft.vy;
                line_info.EndCoords.vz = line_info.StartCoords.vz + vLeft.vz;
            }
            else
            {
                line_info.StartCoords.vx = mTripodPos.vx;
                line_info.StartCoords.vy = mTripodPos.vy;
                line_info.StartCoords.vz = mTripodPos.vz;
                line_info.EndCoords.vx = ((mPos.vx + line_info.StartCoords.vx) >> 1) + vLeft.vx;
                line_info.EndCoords.vy = ((mPos.vy + line_info.StartCoords.vy) >> 1) + vLeft.vy;
                line_info.EndCoords.vz = ((mPos.vz + line_info.StartCoords.vz) >> 1) + vLeft.vz;
            }
            M3dColij_InitLineInfo(&line_info);
            line_info.RecordTriggerZoneHits = 0;
            CameraCollisionCheck = 1;
            M3dZone_LineToItem(&line_info, 1);
            CameraCollisionCheck = 0;
            mColAngBuffer[0] = 0;
            if (line_info.pItem != 0)
            {
                if (line_info.Length == 0)
                {
                    line_info.Length = 1;
                }
                int ratio = ((line_info.Length - line_info.Distance) * 0x1000) / line_info.Length;
                mColAngBuffer[0] = (s16)((mCollisionAngLR * ((ratio * ratio) >> 12)) >> 12);
            }
        }

        if (mColCheckIndex == 1)
        {
            mPrevColAngBuffer[1] = mColAngBuffer[1];
            if ((mColCheckCycleCounter & 1) != 0)
            {
                line_info.StartCoords.vx = mPos.vx;
                line_info.StartCoords.vy = mPos.vy;
                line_info.StartCoords.vz = mPos.vz;
                line_info.EndCoords.vx = line_info.StartCoords.vx + vRight.vx;
                line_info.EndCoords.vy = line_info.StartCoords.vy + vRight.vy;
                line_info.EndCoords.vz = line_info.StartCoords.vz + vRight.vz;
            }
            else
            {
                line_info.StartCoords.vx = mTripodPos.vx;
                line_info.StartCoords.vy = mTripodPos.vy;
                line_info.StartCoords.vz = mTripodPos.vz;
                line_info.EndCoords.vx = ((mPos.vx + line_info.StartCoords.vx) >> 1) + vRight.vx;
                line_info.EndCoords.vy = ((mPos.vy + line_info.StartCoords.vy) >> 1) + vRight.vy;
                line_info.EndCoords.vz = ((mPos.vz + line_info.StartCoords.vz) >> 1) + vRight.vz;
            }
            M3dColij_InitLineInfo(&line_info);
            line_info.RecordTriggerZoneHits = 0;
            CameraCollisionCheck = 1;
            M3dZone_LineToItem(&line_info, 1);
            CameraCollisionCheck = 0;
            mColAngBuffer[1] = 0;
            if (line_info.pItem != 0)
            {
                if (line_info.Length == 0)
                {
                    line_info.Length = 1;
                }
                int ratio = ((line_info.Length - line_info.Distance) * 0x1000) / line_info.Length;
                mColAngBuffer[1] = -(s16)((mCollisionAngLR * ((ratio * ratio) >> 12)) >> 12);
            }
        }
    }

    setVector(&vTemp, 0, 0, Camera_CamDist * -0x1000);
    ApplyMatrixLV(&m, &vTemp, &vBack);
    setVector(&vTemp, 0x64000, 0, 0);
    ApplyMatrixLV(&m, &vTemp, &vOffset);

    if (big_air_timer < 1 &&
        ((CameraBruceAiOwner *)mTripod)->mPhysicsState != PHYSICS_ON_INVISIBLE &&
        mCollisionBack != 0)
    {
        u32 ratioL;
        u32 ratioR = 0;
        int ang;
        mPrevColAngBuffer[3] = mColAngBuffer[3];

        line_info.StartCoords.vx = mTripodPos.vx + (vOffset.vx >> 1);
        line_info.StartCoords.vy = mTripodPos.vy + (vOffset.vy >> 1);
        line_info.StartCoords.vz = mTripodPos.vz + (vOffset.vz >> 1);
        line_info.EndCoords.vx = mTripodPos.vx - vOffset.vx + vBack.vx * 2;
        line_info.EndCoords.vy = mTripodPos.vy - vOffset.vy + vBack.vy * 2;
        line_info.EndCoords.vz = mTripodPos.vz - vOffset.vz + vBack.vz * 2;
        M3dColij_InitLineInfo(&line_info);
        line_info.RecordTriggerZoneHits = 0;
        CameraCollisionCheck = 1;
        M3dZone_LineToItem(&line_info, 1);
        CameraCollisionCheck = 0;

        ratioL = 0;
        if (line_info.pItem != 0)
        {
            if (line_info.Length == 0)
            {
                line_info.Length = 1;
            }
            ratioL = ((line_info.Length - line_info.Distance) * 0x1000) / line_info.Length;
            ratioL *= ratioL;
            ratioL >>= 12;
        }

        line_info.StartCoords.vx = mTripodPos.vx - (vOffset.vx >> 1);
        line_info.StartCoords.vy = mTripodPos.vy - (vOffset.vy >> 1);
        line_info.StartCoords.vz = mTripodPos.vz - (vOffset.vz >> 1);
        line_info.EndCoords.vx = mTripodPos.vx + vOffset.vx + vBack.vx * 2;
        line_info.EndCoords.vy = mTripodPos.vy + vOffset.vy + vBack.vy * 2;
        line_info.EndCoords.vz = mTripodPos.vz + vOffset.vz + vBack.vz * 2;
        M3dColij_InitLineInfo(&line_info);
        line_info.RecordTriggerZoneHits = 0;
        CameraCollisionCheck = 1;
        M3dZone_LineToItem(&line_info, 1);
        CameraCollisionCheck = 0;

        if (line_info.pItem != 0)
        {
            if (line_info.Length == 0)
            {
                line_info.Length = 1;
            }
            ratioR = ((line_info.Length - line_info.Distance) * 0x1000) / line_info.Length;
            ratioR *= ratioR;
            ratioR >>= 12;
        }

        ang = 0x568;
        if (((CameraBruceAiOwner *)mTripod)->mPhysicsState == PHYSICS_ON_RAIL)
        {
            ratioR = 0;
            ratioL = 0;
        }
        mColAngBuffer[3] = 0;
        if (ratioR != 0 || ratioL != 0)
        {
            if (((mPrevColAngBuffer[1] + mColAngBuffer[1]) >> 1) != 0 &&
                ((mPrevColAngBuffer[0] + mColAngBuffer[0]) >> 1) <
                    -((mPrevColAngBuffer[1] + mColAngBuffer[1]) >> 1))
            {
                ang *= ratioR;
                ang >>= 12;
                mColAngBuffer[3] = -(s16)ang;
            }
            if (((mPrevColAngBuffer[0] + mColAngBuffer[0]) >> 1) != 0)
            {
                if (-((mPrevColAngBuffer[1] + mColAngBuffer[1]) >> 1) <
                    ((mPrevColAngBuffer[0] + mColAngBuffer[0]) >> 1))
                {
                    ang *= ratioL;
                    ang >>= 12;
                    mColAngBuffer[3] = (s16)ang;
                }
            }
        }
        else
        {
            mColAngBuffer[3] = 0;
        }
    }

    if (big_air_timer > 0 || ((CameraBruceAiOwner *)mTripod)->mPhysicsState == PHYSICS_ON_INVISIBLE)
    {
        mColAngBuffer[3] = 0;
        mPrevColAngBuffer[3] = 0;
    }

    Utils_CalcUnit(vVel, mVel);
    if (mColCheckIndex == 4)
    {
        mPrevColAngBuffer[4] = mColAngBuffer[4];
        vVel *= Camera_CamDist;
        line_info.EndCoords.vx = mPos.vx + vVel.vx;
        line_info.EndCoords.vy = mPos.vy + vVel.vy;
        line_info.EndCoords.vz = mPos.vz + vVel.vz;
        line_info.StartCoords.vx = mPos.vx;
        line_info.StartCoords.vy = mPos.vy;
        line_info.StartCoords.vz = mPos.vz;
        M3dColij_InitLineInfo(&line_info);
        line_info.RecordTriggerZoneHits = 0;
        CameraCollisionCheck = 1;
        M3dZone_LineToItem(&line_info, 1);
        CameraCollisionCheck = 0;

        Utils_CalcUnit(vVel, mVel);
        CVector vworlddown = mTripod->mPos - mPos;
        Utils_CalcUnit(vStick, vworlddown);
        mColAngBuffer[4] = 0;
        if (line_info.pItem != 0)
        {
            if (line_info.Length == 0)
            {
                line_info.Length = 1;
            }
            int ratio = ((line_info.Length - line_info.Distance) * 0x1000) / line_info.Length;
            mColAngBuffer[4] = (s16)((ratio * ratio) >> 16);
        }
    }

    int ang = (mPrevColAngBuffer[2] + mColAngBuffer[2]) >> 1;
    if (ang != 0)
    {
        mDesiredO = operator*(mDesiredO, QFromXRot((s16)ang));
    }

    ang = (mPrevColAngBuffer[0] + mColAngBuffer[0]) >> 1;
    if (ang != 0)
    {
        mDesiredO = operator*(mDesiredO, QFromYRot((s16)ang));
    }

    ang = (mPrevColAngBuffer[1] + mColAngBuffer[1]) >> 1;
    if (ang != 0)
    {
        mDesiredO = operator*(mDesiredO, QFromYRot((s16)ang));
    }

    if (mColAngBuffer[4] != 0)
    {
        CVector vworlddown = mTripod->mPos - mPos;
        Utils_CalcUnit(vStick, vworlddown);

        gte_ldopv1(&vVel);
        gte_ldopv2(&vStick);
        gte_op0();
        gte_stlvnl(&vColCheck);
        int correction = mColAngBuffer[4];
        vColCheck.vx *= correction;
        vColCheck.vy *= correction;
        vColCheck.vz *= correction;

        CQuat rotation = QFromV(vColCheck);
        CQuat &desired_o = mDesiredO;
        int ox = desired_o.x;
        int oy = desired_o.y;
        int oz = desired_o.z;
        int ow = desired_o.w;
        int nw = (ow * rotation.w - ox * rotation.x - oy * rotation.y - oz * rotation.z) >> 12;
        desired_o.x = (ow * rotation.x + ox * rotation.w + oy * rotation.z - oz * rotation.y) >> 12;
        desired_o.y = (ow * rotation.y + oy * rotation.w + oz * rotation.x - ox * rotation.z) >> 12;
        desired_o.z = (ow * rotation.z + oz * rotation.w + ox * rotation.y - oy * rotation.x) >> 12;
        desired_o.w = nw;
    }

    ang = (mPrevColAngBuffer[3] + mColAngBuffer[3]) >> 1;
    if (ang != 0)
    {
        CQuat rotation = QFromYRot((s16)ang);
        CQuat &desired_o = mDesiredO;
        int ox = desired_o.x;
        int oy = desired_o.y;
        int oz = desired_o.z;
        int ow = desired_o.w;
        int nw = (ow * rotation.w - ox * rotation.x - oy * rotation.y - oz * rotation.z) >> 12;
        desired_o.x = (ow * rotation.x + ox * rotation.w + oy * rotation.z - oz * rotation.y) >> 12;
        desired_o.y = (ow * rotation.y + oy * rotation.w + oz * rotation.x - ox * rotation.z) >> 12;
        desired_o.z = (ow * rotation.z + oz * rotation.w + ox * rotation.y - oy * rotation.x) >> 12;
        desired_o.w = nw;
    }

    if (mStoppedOValid != 0)
    {
        CVector vworlddown(0, 0x1000, 0);
        VECTOR v_temp;
        VECTOR v_temp2;
        CVector vdown;
        CVector vstop;
        MATRIX mstop;

        v_temp.vx = 0;
        v_temp.vy = 0x1000;
        v_temp.vz = 0;
        ApplyMatrixLV(&m, &v_temp, &v_temp2);
        vdown.vx = v_temp2.vx;
        vdown.vy = v_temp2.vy;
        vdown.vz = v_temp2.vz;

        QToM(mStoppedO, mstop);
        v_temp.vx = 0;
        v_temp.vy = 0;
        v_temp.vz = 0x1000;
        ApplyMatrixLV(&mstop, &v_temp, &v_temp2);
        vstop.vx = v_temp2.vx;
        vstop.vy = v_temp2.vy;
        vstop.vz = v_temp2.vz;

        // The original branchless ABS macro evaluates its argument three times.
        int dot_stop =
            (Mips_CVecDotProd(&vdown, &vstop) ^ (Mips_CVecDotProd(&vdown, &vstop) >> 31)) -
            (Mips_CVecDotProd(&vdown, &vstop) >> 31);
        (void)((Mips_CVecDotProd(&vworlddown, &vstop) ^
                (Mips_CVecDotProd(&vworlddown, &vstop) >> 31)) -
               (Mips_CVecDotProd(&vworlddown, &vstop) >> 31));
        if (mDownDist < 0 || dot_stop > 0x76c)
        {
            mStoppedOValid = 0;
        }
    }

    if (mSpeed < 4 || mTripodPos == mOldTripodPos || ((CameraBruceAiOwner *)mTripod)->mInBail != 0)
    {
        if (mStoppedOValid == 0 && mDownDist >= 0)
        {
            Quat_Slerp(mO, mDesiredO, 0x600, mStoppedO);
            mStoppedOValid = true;
        }

        if (GState == 0 && mStoppedOValid != 0)
        {
            if (((mPrevColAngBuffer[0] + mColAngBuffer[0]) >> 1) == 0 &&
                ((mPrevColAngBuffer[1] + mColAngBuffer[1]) >> 1) == 0 &&
                ((mPrevColAngBuffer[3] + mColAngBuffer[3]) >> 1) == 0)
            {
                if (GenerateLevel == 0)
                {
                    Quat_Slerp(mO, mDesiredO, 0x5e7, mStoppedO);
                }
            }

            mDesiredO = mStoppedO;

            int stopped_angle = (mPrevColAngBuffer[1] + mColAngBuffer[1]) >> 1;
            if (stopped_angle != 0 && ((mPrevColAngBuffer[0] + mColAngBuffer[0]) >> 1) == 0 &&
                ((mPrevColAngBuffer[3] + mColAngBuffer[3]) >> 1) == 0)
            {
                mDesiredO = operator*(mDesiredO, QFromYRot((s16)stopped_angle));
            }
            else if (((mPrevColAngBuffer[1] + mColAngBuffer[1]) >> 1) == 0 &&
                     ((mPrevColAngBuffer[0] + mColAngBuffer[0]) >> 1) != 0 &&
                     ((mPrevColAngBuffer[3] + mColAngBuffer[3]) >> 1) == 0)
            {
                mDesiredO = operator*(
                    mDesiredO, QFromYRot((s16)((mPrevColAngBuffer[0] + mColAngBuffer[0]) >> 1)));
            }
        }
    }
    else
    {
        mStoppedOValid = 0;
        mStoppedExtraYRot = 0;
    }

    if (mStoppedExtraYRot != 0)
    {
        CQuat rotation = QFromYRot(mStoppedExtraYRot);
        CQuat &desired_o = mDesiredO;
        int ox = desired_o.x;
        int oy = desired_o.y;
        int oz = desired_o.z;
        int ow = desired_o.w;
        int nw = (ow * rotation.w - ox * rotation.x - oy * rotation.y - oz * rotation.z) >> 12;
        desired_o.x = (ow * rotation.x + ox * rotation.w + oy * rotation.z - oz * rotation.y) >> 12;
        desired_o.y = (ow * rotation.y + oy * rotation.w + oz * rotation.x - ox * rotation.z) >> 12;
        desired_o.z = (ow * rotation.z + oz * rotation.w + ox * rotation.y - oy * rotation.x) >> 12;
        desired_o.w = nw;
    }
}


/**
 * Move the camera toward its collision-adjusted desired position.
 *
 * Address:   0x8007B284
 * Mangled:   MoveToDesiredPos__7CCameraUi
 * Demangled: CCamera::MoveToDesiredPos(unsigned int)
 *
 * @param normal_slerp  Orientation interpolation used outside special modes.
 */
void CCamera::MoveToDesiredPos(unsigned int normal_slerp)
{
    mPrevO = mO;

    if (mTripod == 0)
    {
        CVector U;
        CVector V;
        CVector N;
        int dot;

        Utils_CalcUnit(N, mFocusPos - mTripodPos);

        V.vx = 0;
        V.vy = 0x1000;
        V.vz = 0;
        dot = (Mips_CVecDotProd(&N, &V) ^ (Mips_CVecDotProd(&N, &V) >> 31)) -
              (Mips_CVecDotProd(&N, &V) >> 31);

        if (dot >= 0xfe0)
        {
            U.vx = 0x1000;
            U.vy = 0;
            U.vz = 0;

            gte_ldopv1(&N);
            gte_ldopv2(&U);
            gte_op0();
            gte_stlvnl(&V);
            V.vx >>= 12;
            V.vy >>= 12;
            V.vz >>= 12;

            gte_ldopv1(&V);
            gte_ldopv2(&N);
            gte_op0();
            gte_stlvnl(&U);
            U.vx >>= 12;
            U.vy >>= 12;
            U.vz >>= 12;
        }
        else
        {
            gte_ldopv1(&V);
            gte_ldopv2(&N);
            gte_op0();
            gte_stlvnl(&U);
            U.vx >>= 12;
            U.vy >>= 12;
            U.vz >>= 12;

            gte_ldopv1(&N);
            gte_ldopv2(&U);
            gte_op0();
            gte_stlvnl(&V);
            V.vx >>= 12;
            V.vy >>= 12;
            V.vz >>= 12;
        }

        tm.m[0][0] = (s16)U.vx;
        tm.m[1][0] = (s16)U.vy;
        tm.m[2][0] = (s16)U.vz;
        tm.m[0][1] = (s16)V.vx;
        tm.m[1][1] = (s16)V.vy;
        tm.m[2][1] = (s16)V.vz;
        tm.m[0][2] = (s16)N.vx;
        tm.m[1][2] = (s16)N.vy;
        tm.m[2][2] = (s16)N.vz;
        CQuat tempO;
        MToQ(tm, tempO);

        if (new_focus != 0)
        {
            mO = tempO;
            new_focus = 0;
        }
        else
        {
            Quat_Slerp(mPrevO, tempO, 0x7ff, mO);
        }

        mPos = mTripodPos;
        return;
    }

    CVector old_pos;
    CVector Dist;
    int Spd;
    int Frames;
    int mph;
    VECTOR v1;
    VECTOR v2;
    int speed_lag_dist;
    int temptime;

    old_pos = mPos;
    Dist = mTripod->mVel;

    if (((CameraBruceMoveOwner *)mTripod)->mPhysicsState == PHYSICS_ON_GROUND ||
        ((CameraBruceMoveOwner *)mTripod)->mPhysicsState == PHYSICS_ON_RAIL)
    {
        for (int i = 5; i > 0; i--)
        {
            mSpeedBuffer[i] = mSpeedBuffer[i - 1];
        }
        if (Dist.Length() > 100)
        {
            Dist.vx = 0x64000;
            Dist.vy = 0;
            Dist.vz = 0;
        }
        mSpeedBuffer[0] = M3dMaths_SquareRoot0(Mips_CVecDotProd(&Dist, &Dist)) << 6;
    }

    Spd = 0;
    int i = 0;
    int *speed = mSpeedBuffer;
    for (; i < 6; i++)
    {
        Spd += *speed++;
    }

    Spd /= 6;
    Frames = 2;
    mph = Spd / 34 * 60 / Frames * 3600 / 5278;
    mph >>= 12;
    mSpeed = mph;

    v1.vx = 0;
    v1.vy = 0;
    speed_lag_dist = (Camera_CamDist + mph * 4 + prev_speed_lag_dist) >> 1;
    prev_speed_lag_dist = speed_lag_dist;
    v1.vz = -(speed_lag_dist << 12);

    if (turn_delay_timer >= 4)
    {
        CQuat wouldbeO = operator*(mDesiredO, QFromXRot(-450));
        MATRIX m;
        VECTOR v;
        VECTOR vCheck;
        SLineInfo line_info;

        v.vx = 0;
        v.vy = 0;
        v.vz = -(Camera_CamDist << 12);
        QToM(wouldbeO, m);
        ApplyMatrixLV(&m, &v, &vCheck);

        line_info.StartCoords.vx = mTripodPos.vx;
        line_info.StartCoords.vy = mTripodPos.vy;
        line_info.StartCoords.vz = mTripodPos.vz;
        line_info.EndCoords.vx = mTripodPos.vx + vCheck.vx;
        line_info.EndCoords.vy = mTripodPos.vy + vCheck.vy;
        line_info.EndCoords.vz = mTripodPos.vz + vCheck.vz;
        M3dColij_InitLineInfo(&line_info);
        line_info.RecordTriggerZoneHits = 0;
        CameraCollisionCheck = 1;
        M3dZone_LineToItem(&line_info, 1);
        CameraCollisionCheck = 0;

        if (line_info.pItem == 0)
        {
            mDesiredO = wouldbeO;
        }
    }

    if (Mick_CameraTweak == 0 &&
        ((big_air != 0 && ((CameraBruceMoveOwner *)mTripod)->mDoingATrick != 0) ||
         big_air_timer > 0))
    {
        ReactToCollision();

        if (big_air_timer == 0)
        {
            big_air_mph = mph;
        }
        if (big_air_mph > 30)
        {
            big_air_mph = 30;
        }

        if (big_air == 0)
        {
            temptime = big_air_timer;
            if (temptime <= 0)
            {
                temptime = 0;
            }
            else if (big_air_end_timer == 0)
            {
                if (temptime >= 8)
                {
                    temptime = 7;
                }
                big_air_end_timer = temptime + 1;
            }
            else
            {
                temptime = big_air_end_timer - 1;
            }

            if (temptime == 0)
            {
                big_air_end_timer = 1;
                big_air_timer = -1;
                new_hang_time = 0;
            }
            temptime = temptime * temptime;
            --big_air_end_timer;
            int camera_lift = big_air_mph * 8000;
            Camera_CamOffset.vy += (temptime * camera_lift) / 30;
            int scaled_time = temptime * 75;
            v1.vz += (big_air_mph * 8) * scaled_time;
        }
        else
        {
            big_air_end_timer = 0;
            if (big_air_timer >= 7)
            {
                temptime = 49;
                int camera_lift = big_air_mph * 8000;
                Camera_CamOffset.vy += (temptime * camera_lift) / 30;
                int scaled_time = temptime * 600;
                v1.vz += scaled_time * big_air_mph;
                ++new_hang_time;
            }
            else if (big_air_timer >= 0)
            {
                new_hang_time = 0;
                temptime = big_air_timer * big_air_timer;
                int camera_lift = big_air_mph * 8000;
                Camera_CamOffset.vy += (temptime * camera_lift) / 30;
                int scaled_time = temptime * 75;
                v1.vz += (big_air_mph * 8) * scaled_time;
            }
        }

        Quat_Slerp(mPrevO, mDesiredO, 0xde, mO);
        ++big_air_timer;
    }
    else
    {
        void *loosen_up = 0;
        if (loose_cam_timer > 0)
        {
            loosen_up = (void *)1;
            --loose_cam_timer;
        }

        mDesiredO = operator*(mDesiredO, QFromXRot((s16)Camera_CamPitch));
        ReactToCollision();

        if (((CameraBruceMoveOwner *)mTripod)->mManIsJumping != 0)
        {
            if (((CameraBruceMoveOwner *)mTripod)->mPhysicsState == PHYSICS_IN_AIR_STICK_TO)
            {
                loosen_up = (void *)1;
                loose_cam_timer = 20;
            }
            else if (((CameraBruceMoveOwner *)mTripod)->mPhysicsState == PHYSICS_IN_AIR)
            {
                mDesiredO = operator*(mDesiredO, QFromXRot(200));
            }
        }

        if ((u32)(in_pool_timer - 2) < 18)
        {
            Quat_Slerp(mPrevO, mDesiredO, 0x137, mO);
        }
        else
        {
            if (loosen_up)
            {
                int loosen_slerp = (20 - loose_cam_timer) * 13 + 51;
                Quat_Slerp(mPrevO, mDesiredO, loosen_slerp, mO);
            }
            else
            {
                Quat_Slerp(mPrevO, mDesiredO, normal_slerp, mO);
            }
        }
    }

    if (mTimer < 12)
    {
        mPrevO = mO = mDesiredO;
    }

    MATRIX m;
    QToM(mO, m);
    ApplyMatrixLV(&m, &v1, &v2);
    v1.vx = Camera_CamOffset.vx;
    v1.vy = Camera_CamOffset.vy;
    v1.vz = Camera_CamOffset.vz;
    ApplyMatrixLV(&m, &v1, &real_cam_offset);

    mPos.vx = mTripodPos.vx + v2.vx;
    mPos.vy = mTripodPos.vy + v2.vy;
    mPos.vz = mTripodPos.vz + v2.vz;
    mVel = mPos - old_pos;
}


/**
 * SetCamAngle__7CCamerasUs (intentional no-op in this build)
 *
 * Address:   0x8007BFAC
 * Mangled:   SetCamAngle__7CCamerasUs
 * Demangled: CCamera::SetCamAngle(short, unsigned short)
 *            ASM: jr $ra; nop
 *
 * @param y  Y coordinate.
 * @param frames  Frame count.
 */
void CCamera::SetCamAngle(s16 y, u16 frames)
{
}


/**
 * SetCamXZDistance__7CCameraUsUs (intentional no-op in this build)
 *
 * Address:   0x8007BFB4
 * Mangled:   SetCamXZDistance__7CCameraUsUs
 * Demangled: CCamera::SetCamXZDistance(unsigned short, unsigned short)
 *            ASM: jr $ra; nop
 *
 * @param dist Requested horizontal camera distance.
 * @param frames  Frame count.
 */
void CCamera::SetCamXZDistance(u16 dist, u16 frames)
{
}


/**
 * SetCamYDistance__7CCamerasUs (intentional no-op in this build)
 *
 * Address:   0x8007BFBC
 * Mangled:   SetCamYDistance__7CCamerasUs
 * Demangled: CCamera::SetCamYDistance(short, unsigned short)
 *            ASM: jr $ra; nop
 *
 * @param dist Requested vertical camera distance.
 * @param frames  Frame count.
 */
void CCamera::SetCamYDistance(s16 dist, u16 frames)
{
}


/**
 * SetCamXOffset__7CCamerasUs (intentional no-op in this build)
 *
 * Address:   0x8007BFC4
 * Mangled:   SetCamXOffset__7CCamerasUs
 * Demangled: CCamera::SetCamXOffset(short, unsigned short)
 *            ASM: jr $ra; nop
 *
 * @param offset Requested horizontal camera offset.
 * @param frames  Frame count.
 */
void CCamera::SetCamXOffset(s16 offset, u16 frames)
{
}


/**
 * SetCamYOffset__7CCamerasUs (intentional no-op in this build)
 *
 * Address:   0x8007BFCC
 * Mangled:   SetCamYOffset__7CCamerasUs
 * Demangled: CCamera::SetCamYOffset(short, unsigned short)
 *            ASM: jr $ra; nop
 *
 * @param offset Requested vertical camera offset.
 * @param frames  Frame count.
 */
void CCamera::SetCamYOffset(s16 offset, u16 frames)
{
}


/**
 * SetCamZOffset__7CCamerasUs (intentional no-op in this build)
 *
 * Address:   0x8007BFD4
 * Mangled:   SetCamZOffset__7CCamerasUs
 * Demangled: CCamera::SetCamZOffset(short, unsigned short)
 *            ASM: jr $ra; nop
 *
 * @param offset Requested depth camera offset.
 * @param frames  Frame count.
 */
void CCamera::SetCamZOffset(s16 offset, u16 frames)
{
}


/**
 *
 * Address:   0x8007BFDC
 * Mangled:   SetZoom__7CCameraUsUs
 * Demangled: CCamera::SetZoom(unsigned short, unsigned short)
 *            Store a new zoom target immediately, or compute a per-frame zoom delta.
 *
 * @param zoom Target fixed-point projection zoom.
 * @param time Number of frames over which to interpolate.
 */
void CCamera::SetZoom(u16 zoom, u16 time)
{
    mZoomTime = time;
    if (mZoomTime != 0)
    {
        mZoomIncrement = (zoom - mZoom) / (int)mZoomTime;
    }
    else
    {
        mZoom = zoom;
    }
}


/**
 * GetZoom__7CCamera
 *
 * Address:   0x8007C014
 * Mangled:   GetZoom__7CCamera
 * Demangled: CCamera::GetZoom(void)
 *
 * @return Current fixed-point projection zoom.
 */
int CCamera::GetZoom()
{
    return mZoom;
}


/**
 * TweakMenu__7CCamera
 *
 * Address:   0x8007C020
 * Mangled:   TweakMenu__7CCamera
 * Demangled: CCamera::TweakMenu(void)
 *
 */
void CCamera::TweakMenu()
{
    u8 c8 = 0xc8;

    // Display labels and camera positions
    CamPos::DisplayLabels(0x64, 0x32, c8, c8, c8);
    Font_String(0xc8, 0x28, s_PosA, c8, c8, c8, 0);
    CamPos *camPos0 = &mPosA;
    camPos0->Display(0xc8, 0x32, 0x50, 0, 0);
    Font_String(0x12c, 0x28, s_PosB, c8, c8, c8, 0);
    CamPos *camPos1 = &mPosB;
    camPos1->Display(0x12c, 0x32, 0x50, 0, 0);

    // Check Right.Triggered (Pad[1])
    if (Pad[1].Right.Triggered != 0)
    {
        u16 col = TweakCol;
        switch (col)
        {
            case 0: TweakCol = 1; break;
            case 1: TweakCol = col; break;
            default: Pad[1].Right.Triggered = 0; goto check_left;
        }
        Pad[1].Right.Triggered = 0;
    }
check_left:
    // Check Left.Triggered (Pad[1])
    if (Pad[1].Left.Triggered != 0)
    {
        u16 col = TweakCol;
        switch (col)
        {
            case 0: TweakCol = 0; break;
            case 1: TweakCol = 0; break;
        }
        Pad[1].Left.Triggered = 0;
    }

    // Check Down.Triggered
    if (Pad[1].Down.Triggered != 0)
    {
        u16 row = TweakRow;
        if (row < 11)
        {
            switch (row)
            {
                case 0: TweakRow = 1; break;
                case 1: TweakRow = 2; break;
                case 2: TweakRow = 3; break;
                case 3: TweakRow = 5; break;
                case 4: break;
                case 5: TweakRow = 6; break;
                case 6: TweakRow = 8; break;
                case 7: break;
                case 8: TweakRow = 9; break;
                case 9: TweakRow = 10; break;
                case 10: TweakRow = 0; break;
            }
        }
        Pad[1].Down.Triggered = 0;
    }

    // Check Up.Triggered
    if (Pad[1].Up.Triggered != 0)
    {
        u16 row = TweakRow;
        if (row < 11)
        {
            switch (row)
            {
                case 0: TweakRow = 10; break;
                case 1: TweakRow = 0; goto clear_up;
                case 2: TweakRow = 1; break;
                case 3: TweakRow = 2; break;
                case 4: break;
                case 5: TweakRow = 3; break;
                case 6: TweakRow = 5; break;
                case 7: break;
                case 8: TweakRow = 6; break;
                case 9: TweakRow = 8; break;
                case 10: TweakRow = 9; break;
            }
        }
    clear_up:
        Pad[1].Up.Triggered = 0;
    }

    // Select active CamPos based on TweakCol
    CamPos *cp;
    u16 col = TweakCol;
    switch (col)
    {
        case 0: cp = camPos0; break;
        case 1: cp = camPos1; break;
    }
    // Triangle.Pressed (Pad[1], offset 0x16c)
    if (Pad[1].Triangle.Pressed != 0)
    {
        switch (TweakRow)
        {
            case 5: cp->mStickO = operator*(cp->mStickO, QFromXRot(0xa)); break;
            case 6: cp->mStickLength -= 10; break;
        }
    }

    // X.Pressed (Pad[1], offset 0x19c)
    if (Pad[1].X.Pressed != 0)
    {
        switch (TweakRow)
        {
            case 5: cp->mStickO = operator*(cp->mStickO, QFromXRot(-0xa)); break;
            case 6: cp->mStickLength += 10; break;
        }
    }

    // Square.Pressed (Pad[1], offset 0x17c)
    if (Pad[1].Square.Pressed != 0 && TweakRow == 5)
    {
        cp->mStickO = operator*(cp->mStickO, QFromYRot(-0xa));
    }

    // Circle.Pressed (Pad[1], offset 0x18c)
    if (Pad[1].Circle.Pressed != 0 && TweakRow == 5)
    {
        cp->mStickO = operator*(cp->mStickO, QFromYRot(0xa));
    }

    // RightOne.Pressed (Pad[1], offset 0x1cc)
    if (Pad[1].RightOne.Pressed != 0 && TweakRow == 5)
    {
        cp->mStickO = operator*(cp->mStickO, QFromZRot(0xa));
    }

    // RightTwo.Pressed (Pad[1], offset 0x1dc)
    if (Pad[1].RightTwo.Pressed != 0)
    {
        if (TweakRow == 5)
        {
            cp->mStickO = operator*(cp->mStickO, QFromZRot(-0xa));
        }
    }
}


// === CAMERA-owned small-data prefix needed by CCamera::AI ===

/*
 * CAMERA's initialized render values and list state. The public scalar
 * declarations above retain the target's proven gp-relative access pattern.
 */
static int CameraOwnerCamPitch PSX_SECTION(".sdata") = 54;
static int CameraOwnerCamDist PSX_SECTION(".sdata") = 850;
static int CameraOwnerCamOffset[3] PSX_SECTION(".sdata") = { 0, 0, 0 };
static int CameraOwnerNumCameras PSX_SECTION(".sdata") = 0;
static CBody *CameraOwnerList PSX_SECTION(".sdata") = 0;
static u32 CameraOwnerCurrentMike PSX_SECTION(".sdata") = 0;

/** Camera-mode diagnostics retained by the original debug build. */
static char CameraBigAirOverText[] PSX_SECTION_ALIGNED(".sdata", 4) = "big air over";
static char CameraBigAirText[] PSX_SECTION_ALIGNED(".sdata", 4) = "big air";
static char CameraResettingText[] PSX_SECTION_ALIGNED(".sdata", 4) = "reseting";
static char CameraRampingText[] PSX_SECTION_ALIGNED(".sdata", 4) = "ramping";
static char CameraNormalText[] PSX_SECTION_ALIGNED(".sdata", 4) = "normal";
static char CameraLooseText[] PSX_SECTION_ALIGNED(".sdata", 4) = "loose cam";

/** Initial state for CCamera's owner-local tweak controls. */
int CCamera::Tweaking PSX_SECTION(".sdata") = 0;
/*
 * Keep the row and column backing bytes at their target-proven .sdata offsets.
 * Their natural static-member references must remain unresolved here: ASPSX
 * expands same-TU definitions into absolute sequences, while the target uses
 * GP-relative halfword relocations for all 25 accesses in TweakMenu.
 */
static u16 CameraOwnerTweakRow PSX_SECTION(".sdata") = 0;
static u16 CameraOwnerTweakCol PSX_SECTION(".sdata") = 0;

/** Headings used by CCamera and CamPos's debug displays. */
static char s_PosA[] PSX_SECTION_ALIGNED(".sdata", 4) = "Pos A";
static char s_PosB[] PSX_SECTION_ALIGNED(".sdata", 4) = "Pos B";

/* Owner-private AI state immediately follows the tweak labels in the target. */
namespace
{
static int Released PSX_SECTION(".sdata") = 1;
static int Mick_DisplayCameraValues PSX_SECTION(".sdata") = 1;
static int old_GlobalZoom PSX_SECTION(".sdata") = 0x100;
static int Mick_Select_Triggered PSX_SECTION(".sdata") = 0;
static int Mick_Select_Released PSX_SECTION(".sdata") = 0;
}

/**
 * Update the active camera's tracking, tweak controls, and shake response.
 *
 * Address:   0x8007C6C4
 * Mangled:   AI__7CCamera
 * Demangled: CCamera::AI(void)
 *
 */
void CCamera::AI()
{
    static int old_camYOffset;
    static int old_camDist;
    static int old_camPitch;

    Camera_CurrentMikeCamera = mMikeIndex;

    if (mCalcTripod != 0)
    {
        mOldTripodPos = mTripodPos;
        if (new_focus != 0)
        {
            mTripodPos = mTripod->mPos;
        }
        else
        {
            mTripodPos = ((mTripod->mPos << 1) + mOldTripodPos) / 3;
        }
    }

    if (mCalcFocus != 0)
    {
        mOldFocusPos = mFocusPos;
        if (new_focus != 0)
        {
            mFocusPos = mFocus->mPos;
        }
        else
        {
            mFocusPos = ((mFocus->mPos << 1) + mOldFocusPos) / 3;
        }
    }

    if (Pad[0].Select.Pressed != 0)
    {
        if (Mick_Select_Released != 0)
        {
            Mick_Select_Triggered = 1;
        }
        Mick_Select_Released = 0;
    }
    else
    {
        Mick_Select_Released = 1;
    }

    if (Cheat_ScreenShots != 0 && Mick_Select_Triggered != 0 && Pad[0].Select.Pressed != 0)
    {
        Pad[1].RightOne.Triggered = 0;
        Pad[1].RightTwo.Triggered = 0;
        Mick_DisplayCameraValues = 0;
        Pad[0].LeftTwo.Triggered = 0;
        Mick_Select_Triggered = 0;
        Pad[0].Select.Triggered = 0;
        Pad[0].Start.Triggered = 0;
        Mick_CameraTweak ^= 1;
        GameFrozen = Mick_CameraTweak;

        if (Mick_CameraTweak != 0)
        {
            old_camYOffset = camYOffset;
            old_camDist = camDist;
            old_camPitch = camPitch;
            old_GlobalZoom = mZoom;
        }
    }

    if (Mick_CameraTweak != 0)
    {
        if (Pad[1].Start.Pressed != 0)
        {
            camYOffset = old_camYOffset;
            camDist = old_camDist;
            camPitch = old_camPitch;
            mZoom = old_GlobalZoom;
        }
        if (Pad[0].Square.Pressed != 0)
        {
            --mZoom;
        }
        if (Pad[0].Circle.Pressed != 0)
        {
            ++mZoom;
        }
        if (Pad[0].Triangle.Pressed != 0)
        {
            mZoom = 0x100;
        }
        if (Pad[1].Square.Pressed != 0)
        {
            extra_YRot -= 10;
        }
        if (Pad[1].Circle.Pressed != 0)
        {
            extra_YRot += 10;
        }
        if (Pad[1].Left.Pressed != 0)
        {
            camDist -= Pad[1].Select.Pressed != 0 ? 32 : 8;
        }
        if (Pad[1].Right.Pressed != 0)
        {
            camDist += Pad[1].Select.Pressed != 0 ? 32 : 8;
        }
        if (Pad[1].Up.Pressed != 0)
        {
            camPitch -= Pad[1].Select.Pressed != 0 ? 32 : 8;
        }
        if (Pad[1].Down.Pressed != 0)
        {
            camPitch += Pad[1].Select.Pressed != 0 ? 32 : 8;
        }
        camPitch &= 0xfff;
        if (Pad[1].LeftOne.Pressed != 0)
        {
            camYOffset -= Pad[1].Select.Pressed != 0 ? 32 : 8;
        }
        if (Pad[1].LeftTwo.Pressed != 0)
        {
            camYOffset += Pad[1].Select.Pressed != 0 ? 32 : 8;
        }
    }

    Camera_CamDist = camDist;
    Camera_CamPitch = camPitch;
    Camera_CamOffset.vx = 0;
    Camera_CamOffset.vy = camYOffset << 12;
    Camera_CamOffset.vz = 0;

    if (GamePaused != 0)
    {
        if (Mick_CameraTweak == 0)
        {
            return;
        }
        CM_Normal();
        MoveToDesiredPos(0x137);
        return;
    }

    ++mTimer;
    if (mZoomTime != 0)
    {
        --mZoomTime;
        mZoom += mZoomIncrement;
    }
    pCurrentViewport->Zoom = (u16)mZoom;

    Utils_CalcAim(mAngles, mPos, mFocusPos);

    if (((CameraBruceAiOwner *)mTripod)->mInAirTimer != 0 && mTripodPosYDamper != 0)
    {
        if (((CameraBruceAiOwner *)mTripod)->mVel.vy < 0)
        {
            ++jump_uptimer;
        }
        else
        {
            --jump_uptimer;
        }
        jump_acc += ((-((CameraBruceAiOwner *)mTripod)->mVel.vy >> 12) * mTripodPosYDamper);
        if (jump_uptimer > 0)
        {
            mTripodPos.vy += jump_acc;
        }
    }
    else
    {
        jump_acc = 0;
        jump_uptimer = 0;
    }

    if (mPitchDamper != 0)
    {
        if (((CameraBruceAiOwner *)mTripod)->mVel.vy < 0)
        {
            Camera_CamPitch -= mPitchDamper;
        }
        if (((CameraBruceAiOwner *)mTripod)->mVel.vy > 0)
        {
            Camera_CamPitch -= mPitchDamper >> 1;
        }
        Camera_CamPitch &= 0xfff;
    }

    switch (mCameraMode)
    {
        case 1: CM_Normal(); break;
        case 2: CM_NoBigAir(); break;
        case 0x17:
            CM_CompetitionIntro();
            LoadIntoMikeCamera();
            return;
        default: break;
    }

    if (((CameraBruceAiOwner *)mTripod)->mInBail == 0)
    {
        if (mTripodPos == mOldTripodPos)
        {
            MoveToDesiredPos(0x97);
        }
        else if (mSpeed < 4)
        {
            MoveToDesiredPos(0x97);
        }
        else if (((CameraBruceAiOwner *)mTripod)->mPhysicsState != PHYSICS_IN_AIR)
        {
            MoveToDesiredPos(0x137);
        }
        else if (mTimer < 0x12)
        {
            MoveToDesiredPos(0x137);
        }
        else
        {
            MoveToDesiredPos(0x97);
        }
    }
    else
    {
        MoveToDesiredPos(0x137);
    }
    Utils_CalcAim(mAngles, mPos, mFocusPos);

    if (mShakeAmplitude.vx != 0 || mShakeAmplitude.vy != 0 || mShakeAmplitude.vz != 0)
    {
        mO = operator*(
            operator*(operator*(QFromYRot((s16)((mShakeAmplitude.vy *
                                                 Camera_Sine(mShakeSpeed.vy * TTime)) /
                                                0x1000)),
                                mO),
                      QFromXRot((s16)((mShakeAmplitude.vx * Camera_Sine(mShakeSpeed.vx * TTime)) /
                                      0x1000))),
            QFromZRot((s16)((mShakeAmplitude.vz * Camera_Sine(mShakeSpeed.vz * TTime)) / 0x1000)));

        CSVector oldamp = mShakeAmplitude;
        if (mShakeAmplitude.vx < 0)
        {
            mShakeAmplitude.vx += mShakeDecay.vx;
        }
        else
        {
            mShakeAmplitude.vx -= mShakeDecay.vx;
        }
        if (mShakeAmplitude.vy < 0)
        {
            mShakeAmplitude.vy += mShakeDecay.vy;
        }
        else
        {
            mShakeAmplitude.vy -= mShakeDecay.vy;
        }
        if (mShakeAmplitude.vz < 0)
        {
            mShakeAmplitude.vz += mShakeDecay.vz;
        }
        else
        {
            mShakeAmplitude.vz -= mShakeDecay.vz;
        }

        if (((u16)oldamp.vx ^ (u16)mShakeAmplitude.vx) & 0x8000)
        {
            mShakeAmplitude.vx = 0;
        }
        if (((u16)oldamp.vy ^ (u16)mShakeAmplitude.vy) & 0x8000)
        {
            mShakeAmplitude.vy = 0;
        }
        if (((u16)oldamp.vz ^ (u16)mShakeAmplitude.vz) & 0x8000)
        {
            mShakeAmplitude.vz = 0;
        }
    }

    LoadIntoMikeCamera();
}


/**
 * CM_Normal__7CCamera
 *
 * Address:   0x8007D138
 * Mangled:   CM_Normal__7CCamera
 * Demangled: CCamera::CM_Normal(void)
 */
void CCamera::CM_Normal()
{
    CVector vUp;
    CVector vRight;
    CSVector ang1;
    int dot_front;
    CVector temp_vel = mTripodPos - mOldTripodPos;

    vUp = ((CameraBruceMoveOwner *)mTripod)->mUp;

    CVector Down(0, 0x1000, 0);
    CVector Zero(0, 0, 0);

    // The original branchless ABS macro evaluates its argument three times.
    int dot_up = (Mips_CVecDotProd(&Down, &vUp) ^ (Mips_CVecDotProd(&Down, &vUp) >> 31)) -
                 (Mips_CVecDotProd(&Down, &vUp) >> 31);

    Utils_CalcAim(ang1, Zero, temp_vel);
    CVector temp_front;
    Utils_GetVecFromMagDir(temp_front, 0x1000, ang1);
    dot_front =
        (Mips_CVecDotProd(&temp_front, &vUp) ^ (Mips_CVecDotProd(&temp_front, &vUp) >> 31)) -
        (Mips_CVecDotProd(&temp_front, &vUp) >> 31);

    ++in_pool_timer;
    if (dot_up < 0xdf4)
    {
        if (((CameraBruceMoveOwner *)mTripod)->mPhysicsState == PHYSICS_ON_INVISIBLE ||
            ((CameraBruceMoveOwner *)mTripod)->mPhysicsState == PHYSICS_IN_HANDPLANT)
        {
            if (big_air == 0 && ((CameraBruceMoveOwner *)mTripod)->mManIsJumping != 0)
            {
                ++((CameraBruceMoveOwner *)mTripod)->mBigAirs;
            }

            ++turn_delay_timer;
            if (turn_delay_timer >= 4)
            {
                CVector U(0, 0x1000000, 0);
                vFront = U;
            }
            else
            {
                Utils_GetVecFromMagDir(vFront, 0x1000, ang1);
            }
            big_air = true;
            in_pool_timer = 0;
            goto front_selected;
        }
    }

    if ((dot_front >> 12) >= 0x7d1 || temp_vel.Length() < 5)
    {
        turn_delay_timer = 0;
        if (dot_up < 0xdf4 && big_air == true)
        {
            in_pool_timer = 0;
        }
        big_air = 0;
    }
    else
    {
        turn_delay_timer = 0;
        Utils_GetVecFromMagDir(vFront, 0x1000, ang1);
        if (dot_up < 0xdf4 && big_air == true)
        {
            in_pool_timer = 0;
        }
        big_air = 0;
    }

front_selected:
    mOldVFront = mVFront;
    if (mTripodPos == mOldTripodPos)
    {
        mVFront = mOldVFront;
    }
    else
    {
        mVFront = (mOldVFront + vFront) >> 1;
    }

    if (mTimer < 12)
    {
        mVFront = reinterpret_cast<CameraCompetitionSkater *>(GSkater[0])->mFront.operator-() << 12;
        mOldVFront = mVFront;
        vFront = mOldVFront;
    }

    vFront = mVFront;
    CVector U;
    CVector V;
    CVector N;
    N = vFront >> 12;
    V.vx = -vUp.vx;
    V.vy = -vUp.vy;
    V.vz = -vUp.vz;

    gte_ldopv1(&V);
    gte_ldopv2(&N);
    gte_op0();
    gte_stlvnl(&U);
    U.vx >>= 12;
    U.vy >>= 12;
    U.vz >>= 12;

    gte_ldopv1(&U);
    gte_ldopv2(&V);
    gte_op0();
    gte_stlvnl(&N);
    N.vx >>= 12;
    N.vy >>= 12;
    N.vz >>= 12;

    tm.m[0][0] = (s16)U.vx;
    tm.m[1][0] = (s16)U.vy;
    tm.m[2][0] = (s16)U.vz;
    tm.m[0][1] = (s16)V.vx;
    tm.m[1][1] = (s16)V.vy;
    tm.m[2][1] = (s16)V.vz;
    tm.m[0][2] = (s16)N.vx;
    tm.m[1][2] = (s16)N.vy;
    tm.m[2][2] = (s16)N.vz;
    MToQ(tm, mDesiredO);

    mDesiredO = operator*(mDesiredO, QFromYRot((s16)extra_YRot));
}


/**
 * StartCompetitionIntro__7CCamera
 *
 * Address:   0x8007D708
 * Mangled:   StartCompetitionIntro__7CCamera
 * Demangled: CCamera::StartCompetitionIntro(void)
 *
 */
void CCamera::StartCompetitionIntro()
{
    mCompIntroTimer = 0;
    mCameraMode = 0x17;
    Competition_ResetMarquee();
}


/**
 * Advance the competition-intro camera and transition into the run video.
 *
 * Address:   0x8007D730
 * Mangled:   CM_CompetitionIntro__7CCamera
 * Demangled: CCamera::CM_CompetitionIntro(void)
 *
 */
void CCamera::CM_CompetitionIntro()
{

    if (mCompIntroTimer == 0)
    {
        VECTOR v1;
        VECTOR v2;
        int speed_lag_dist;
        MATRIX m;

        mCameraMode = 1;
        reinterpret_cast<CameraCompetitionSkater *>(GSkater[0])->mVel.vx =
            reinterpret_cast<CameraCompetitionSkater *>(GSkater[0])->mFront.vx * 20;
        reinterpret_cast<CameraCompetitionSkater *>(GSkater[0])->mVel.vy =
            reinterpret_cast<CameraCompetitionSkater *>(GSkater[0])->mFront.vy * 20;
        reinterpret_cast<CameraCompetitionSkater *>(GSkater[0])->mVel.vz =
            reinterpret_cast<CameraCompetitionSkater *>(GSkater[0])->mFront.vz * 20;

        int i = 0;
        do
        {
            ++i;
            Ob_AI(&CameraList);
        } while (i < 10);

        reinterpret_cast<CameraCompetitionSkater *>(GSkater[0])->mVel.vx = 0;
        reinterpret_cast<CameraCompetitionSkater *>(GSkater[0])->mVel.vy = 0;
        speed_lag_dist = Camera_CamDist >> 1;
        reinterpret_cast<CameraCompetitionSkater *>(GSkater[0])->mVel.vz = 0;
        mCameraMode = 0x17;

        prev_speed_lag_dist = speed_lag_dist;
        v1.vx = 0;
        v1.vy = 0;
        v1.vz = -(speed_lag_dist << 12);

        QToM(mO, m);
        ApplyMatrixLV(&m, &v1, &v2);
        v1.vx = Camera_CamOffset.vx;
        v1.vy = Camera_CamOffset.vy;
        v1.vz = Camera_CamOffset.vz;
        ApplyMatrixLV(&m, &v1, &real_cam_offset);

        mPos.vx = mTripodPos.vx + v2.vx;
        mPos.vy = mTripodPos.vy + v2.vy;
        mCompIntroEndPos.vx = mPos.vx;
        mPos.vz = mTripodPos.vz + v2.vz;
        mCompIntroEndPos.vy = mPos.vy;
        mCompIntroEndPos.vz = mPos.vz;
    }

    CQuat begin_o;
    CQuat end_o;
    CVector begin_pos;
    end_o = mDesiredO;
    begin_o = operator*(operator*(QFromYRot(Levels[GLevel].IntroStartAngY),
                                  QFromXRot(Levels[GLevel].IntroStartAngX)),
                        QFromZRot(Levels[GLevel].IntroStartAngZ));

    int slerp_time = (int)(((u32)mCompIntroTimer << 12) / 130u);
    Quat_Slerp(begin_o, end_o, slerp_time, mO);

    if ((u32)mCompIntroTimer >= 131u)
    {
        Video_Start(GSkater[0], VIDEO_RECORD, 1, 0x7fffffff);
        mCameraMode = 1;
        return;
    }
    Competition_MarqueeDisplay();
    begin_pos.vx = Levels[GLevel].IntroStartPosX << 12;
    begin_pos.vy = Levels[GLevel].IntroStartPosY << 12;
    begin_pos.vz = Levels[GLevel].IntroStartPosZ << 12;
    CVector offset_inc;
    offset_inc = (begin_pos - mCompIntroEndPos) / 130;
    CVector offset = (offset_inc * 130) - (mCompIntroTimer * offset_inc);

    mPos.vx = mCompIntroEndPos.vx + offset.vx;
    mPos.vy = mCompIntroEndPos.vy + offset.vy;
    mPos.vz = mCompIntroEndPos.vz + offset.vz;

    int activated = 0;
    if (Pad[0].X.Pressed != 0 || Pad[1].X.Pressed != 0)
    {
        activated = 1;
    }
    if (activated)
    {
        mSpeedUpIntro = true;
    }

    if (mSpeedUpIntro != 0)
    {
        mCompIntroTimer += 6;
    }
    else
    {
        mCompIntroTimer += 1;
    }
}


/**
 * InCompetitionIntro__7CCamera
 *
 * Address:   0x8007DC78
 * Mangled:   InCompetitionIntro__7CCamera
 * Demangled: CCamera::InCompetitionIntro(void)
 *
 * @return Nonzero while competition-intro mode is active.
 */
int CCamera::InCompetitionIntro()
{
    return mCameraMode == 0x17;
}


/**
 * CM_NoBigAir__7CCamera
 *
 * Address:   0x8007DC8C
 * Mangled:   CM_NoBigAir__7CCamera
 * Demangled: CCamera::CM_NoBigAir(void)
 *
 */
void CCamera::CM_NoBigAir()
{
    CVector vUp;
    CVector vRight;
    CSVector ang1;
    int dot_front;
    CVector temp_vel = mTripodPos - mOldTripodPos;

    if (mTripod == 0)
    {
        vUp = CVector(0, -0x1000, 0);
    }
    else
    {
        vUp = ((CameraBruceMoveOwner *)mTripod)->mUp;
    }

    CVector Down(0, 0x1000, 0);
    CVector Zero(0, 0, 0);

    // The original branchless ABS macro evaluates its argument three times.
    int dot_up = ((Mips_CVecDotProd(&Down, &vUp) ^ (Mips_CVecDotProd(&Down, &vUp) >> 31)) -
                  (Mips_CVecDotProd(&Down, &vUp) >> 31)) >>
                 12;
    (void)dot_up;

    Utils_CalcAim(ang1, Zero, temp_vel);
    CVector temp_front;
    Utils_GetVecFromMagDir(temp_front, 0x1000, ang1);
    dot_front =
        ((Mips_CVecDotProd(&temp_front, &vUp) ^ (Mips_CVecDotProd(&temp_front, &vUp) >> 31)) -
         (Mips_CVecDotProd(&temp_front, &vUp) >> 31)) >>
        12;

    if (dot_front >= 0x7d1)
    {
        big_air = 0;
    }
    else if (temp_vel.Length() < 5)
    {
        big_air = 0;
    }
    else
    {
        big_air = 0;
        Utils_GetVecFromMagDir(vFront, 0x1000, ang1);
    }

    mOldVFront = mVFront;
    if (mTripodPos == mOldTripodPos)
    {
        mVFront = mOldVFront;
    }
    else
    {
        mVFront = (mOldVFront + vFront) >> 1;
    }

    vFront = mVFront;
    CVector U;
    CVector V;
    CVector N;
    N = vFront >> 12;
    V.vx = -vUp.vx;
    V.vy = -vUp.vy;
    V.vz = -vUp.vz;

    gte_ldopv1(&V);
    gte_ldopv2(&N);
    gte_op0();
    gte_stlvnl(&U);
    U.vx >>= 12;
    U.vy >>= 12;
    U.vz >>= 12;

    gte_ldopv1(&U);
    gte_ldopv2(&V);
    gte_op0();
    gte_stlvnl(&N);
    N.vx >>= 12;
    N.vy >>= 12;
    N.vz >>= 12;

    tm.m[0][0] = (s16)U.vx;
    tm.m[1][0] = (s16)U.vy;
    tm.m[2][0] = (s16)U.vz;
    tm.m[0][1] = (s16)V.vx;
    tm.m[1][1] = (s16)V.vy;
    tm.m[2][1] = (s16)V.vz;
    tm.m[0][2] = (s16)N.vx;
    tm.m[1][2] = (s16)N.vy;
    tm.m[2][2] = (s16)N.vz;
    MToQ(tm, mDesiredO);

    mDesiredO = operator*(mDesiredO, QFromYRot((s16)extra_YRot));
    big_air = 0;
}


/**
 * Construct a camera-pose record and its embedded quaternion values.
 *
 * Address:   0x8007E0E8
 * Mangled:   __6CamPos
 * Demangled: CamPos::(void)
 *
 */
CamPos::CamPos()
{
}


/**
 * Restore CamPos's table while its embedded quaternion members unwind.
 *
 * Address:   0x8007E148
 * Mangled:   _._6CamPos
 * Demangled: CamPos::~CamPos()
 *
 * The compiler supplies the original hidden in-charge flag and emits the
 * target `_._6CamPos` ABI entry.
 */
CamPos::~CamPos()
{
}


/**
 * Draw this camera-pose record's tracked tripod and stick values.
 *
 * Address: 0x8007E18C
 * Demangled: CamPos::Display(unsigned short, unsigned short, unsigned char, unsigned char, unsigned char)
 */
void CamPos::Display(u16 x, u16 y, u8 r, u8 g, u8 b)
{
    if (calc_mTripod != 0)
    {
        Font_String(x, y, s_Follow, r, g, b, 0);
        Font_Number(x, (u16)(y + 8), mTripod->mPos.vx >> 12, r, g, b, 0);
        Font_Number(x, (u16)(y + 16), mTripod->mPos.vy >> 12, r, g, b, 0);
        Font_Number(x, (u16)(y + 24), mTripod->mPos.vz >> 12, r, g, b, 0);
    }
    else
    {
        Font_String(x, y, s_Fixed, r, g, b, 0);
        Font_Number(x, (u16)(y + 8), mTripodPos.vx >> 12, r, g, b, 0);
        Font_Number(x, (u16)(y + 16), mTripodPos.vy >> 12, r, g, b, 0);
        Font_Number(x, (u16)(y + 24), mTripodPos.vz >> 12, r, g, b, 0);
    }
    Font_String(x, (u16)(y + 40), s_Quaternion, r, g, b, 0);
    Font_Number(x, (u16)(y + 48), mStickLength, r, g, b, 0);
    Font_Number(x, (u16)(y + 64), mStickOffset.vx >> 12, r, g, b, 0);
    Font_Number(x, (u16)(y + 72), mStickOffset.vy >> 12, r, g, b, 0);
    Font_Number(x, (u16)(y + 80), mStickOffset.vz >> 12, r, g, b, 0);
}


/**
 * DisplayLabels__6CamPosUsUsUcUcUc - Draw the static headings for the camera
 * position debug readout; CamPos::Display prints the matching numeric values.
 *
 * Address:   0x8007E3E8
 * Mangled:   DisplayLabels__6CamPosUsUsUcUcUc
 * Demangled: CamPos::DisplayLabels(unsigned short, unsigned short, unsigned char, unsigned char, unsigned char)
 *
 * @param x  X coordinate.
 * @param y  Y coordinate.
 * @param r  Red component (0-255).
 * @param g  Green component (0-255).
 * @param b  Blue component (0-255).
 */
void CamPos::DisplayLabels(u16 x, u16 y, u8 r, u8 g, u8 b)
{
    Font_String(x, y, s_Tripod, r, g, b, 0);
    u16 x2 = (u16)(x + 0x14);
    Font_String(x2, (u16)(y + 8), s_X, r, g, b, 0);
    Font_String(x2, (u16)(y + 0x10), s_Y, r, g, b, 0);
    Font_String(x2, (u16)(y + 0x18), s_Z, r, g, b, 0);
    Font_String(x, (u16)(y + 0x28), s_StickO, r, g, b, 0);
    Font_String(x, (u16)(y + 0x30), s_StickLength, r, g, b, 0);
    Font_String(x, (u16)(y + 0x38), s_StickOffset, r, g, b, 0);
    Font_String(x2, (u16)(y + 0x40), s_X, r, g, b, 0);
    Font_String(x2, (u16)(y + 0x48), s_Y, r, g, b, 0);
    Font_String(x2, (u16)(y + 0x50), s_Z, r, g, b, 0);
}


/**
 * _GLOBAL_.D.camDist [SKIP] — compiler-generated static init
 *
 *
 * ====== 0x8007E614 _GLOBAL_.I.camDist ==========================================
 * _GLOBAL_.I.camDist [SKIP] — compiler-generated static init
 *
 * Shared CBruce member function
 *
 * Address: 0x8007E5EC
 * Mangled: _GLOBAL_.D.camDist
 *
 */

int yangle PSX_SECTION(".sdata") = 0;

static char s_Follow[] PSX_SECTION_ALIGNED(".sdata", 4) = "Follow";
static char s_Fixed[] PSX_SECTION_ALIGNED(".sdata", 4) = "Fixed";
static char s_Quaternion[] PSX_SECTION_ALIGNED(".sdata", 4) = "quaternion";
static char s_Tripod[] PSX_SECTION_ALIGNED(".sdata", 4) = "Tripod";
static char s_X[] PSX_SECTION_ALIGNED(".sdata", 4) = "x";
static char s_Y[] PSX_SECTION_ALIGNED(".sdata", 4) = "y";
static char s_Z[] PSX_SECTION_ALIGNED(".sdata", 4) = "z";
static char s_StickO[] PSX_SECTION_ALIGNED(".sdata", 4) = "Stick O";
static char s_StickLength[] PSX_SECTION_ALIGNED(".sdata", 4) = "Stick Length";
static char s_StickOffset[] PSX_SECTION_ALIGNED(".sdata", 4) = "Stick Offset";
