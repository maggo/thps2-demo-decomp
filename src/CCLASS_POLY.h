// CCLASS_POLY.h -- polymorphic CClass for owners whose dispatch tables are
// compiler-emitted (virtual destructor), instead of hand-built `__vt_*` words.
//
// globals.h models CClass as a bare vtable-pointer holder shared by every
// composed `struct CClass CClass;` member.  An owner that derives from CClass
// includes this header *first*: globals.h is pulled in with its holder renamed
// out of the way, and the real polymorphic class takes the name CClass.  GCC then
// emits the owner's dispatch table, the destructor and the private
// `CClass::~CClass` copy itself.  Needs -fno-rtti (the originals carry no RTTI
// slot) and a compiler -G (cc_gp) large enough to keep the 16-byte tables in
// small data.
#ifndef CCLASS_POLY_H
#define CCLASS_POLY_H

#define CClass CClassData
#include "globals.h"
#undef CClass

/** Polymorphic base shared by every game object (shared CClass arena). */
struct CClass
{
    static void *operator new(unsigned int size);
    static void operator delete(void *storage);
    virtual ~CClass() {}
};

#endif // CCLASS_POLY_H

// ---------------------------------------------------------------------------
// Natural CItem family (vtable pointer at the END of CItem, as GCC 2.x lays
// out the first polymorphic class of a hierarchy; offset 72, sizeof 76).
// Slot order taken from the target tables (__vt_5CBody, __vt_6CSuper,
// __vt_6CBaddy in MAIN.SYM):  CItem  [0] ~CItem
//                             CBody  [1] Die [2] AI [3] EveryFrame
//                                    [4] DoLightingSetup [5] Hit [6] DeleteStuff
//                             CSuper (no new slots)
//                             CBaddy [7] ExecuteCommand [8] SetVariable [9] GetVariable
// The methods are implemented by OB.cpp / BADDY.cpp; an owner TU that defines
// CCLASS_POLY_ITEM_FAMILY before including this header derives its class from
// the model (struct CTape : CBody { virtual ~CTape(); void DeleteStuff(); })
// and the compiler emits the owner's table itself.
// ---------------------------------------------------------------------------
#ifdef CCLASS_POLY_ITEM_FAMILY
#ifndef CCLASS_POLY_ITEM_FAMILY_DEFINED
#define CCLASS_POLY_ITEM_FAMILY_DEFINED

#include <SYS/TYPES.H>
#include <LIBGTE.H>

/* OB.cpp (the owner of CItem/CBody/CSuper) defines
   CCLASS_POLY_ITEM_FAMILY_IMPLEMENT: the empty CBody virtuals are then in-class
   inline bodies (GCC emits them after the TU's static-init function, where the
   target has them); every other TU only declares them. */
#ifdef CCLASS_POLY_ITEM_FAMILY_IMPLEMENT
#define CCLASS_POLY_EMPTY_VIRTUAL \
    { \
    }
#else
#define CCLASS_POLY_EMPTY_VIRTUAL ;
#endif

struct SLight;

struct CItem
{
    unsigned short mFlags; // 0x00
    unsigned short mInquiry; // 0x02
    CVector mPos; // 0x04
    CSVector mAngles; // 0x10
    unsigned short mModel; // 0x16
    char mDummyFrame; // 0x18
    unsigned char mTintIndex; // 0x19
    unsigned char mDummyAnim; // 0x1a
    unsigned char mRegion; // 0x1b
    CItem *mNextItem; // 0x1c
    unsigned int mRGB; // 0x20
    CSVector mScale; // 0x24
    unsigned short _padScale; // 0x2a
    unsigned int mTRN; // 0x2c
    CItem *mPreviousItem; // 0x30
    unsigned int mStoredRGB; // 0x34
    unsigned char mPredatorEffectType; // 0x38
    unsigned char mPredatorEffectFade; // 0x39
    unsigned short mType; // 0x3a
    SLight *mpLight; // 0x3c
    unsigned short mFlashTimer; // 0x40
    short mFlash_dR; // 0x42
    short mFlash_dG; // 0x44
    short mFlash_dB; // 0x46
    /* vtable pointer                  0x48 */

    CItem();
    virtual ~CItem();
    void Flash(int frames, unsigned char r, unsigned char g, unsigned char b);
    void FlashUpdate();
    void InitItem(char *name);
    static void *operator new(unsigned int size);
    static void operator delete(void *storage);
};

struct CBody : CItem
{
    CBody **mppOriginalList; // 0x4c
    unsigned short mInputFlags; // 0x50
    unsigned short mCBodyFlags; // 0x52
    CVector mVel; // 0x54
    CVector mAcc; // 0x60
    CFriction mFric; // 0x6c
    CSVector mAngVel; // 0x70
    CSVector mAngAcc; // 0x76
    CFriction mAngFric; // 0x7c
    CSVector mNormal; // 0x80
    unsigned char mEventFlags; // 0x86
    unsigned int mEllipsoidRGB; // 0x88
    unsigned short mEllipsoidScale; // 0x8c
    short mEllipsoidOTPushback; // 0x8e
    CVector mShadowPos; // 0x90
    CSVector mShadowNormal; // 0x9c
    void *mpShadow; // 0xa4
    unsigned short mShadowScale; // 0xa8
    short mShadowDist; // 0xaa
    short mShadowThreshold; // 0xac
    int mPushVal; // 0xb0
    unsigned short mRMinor; // 0xb4
    unsigned short mNode; // 0xb6
    unsigned short mCollision; // 0xb8
    short mHealth; // 0xba
    unsigned int mPlayerDist; // 0xbc
    unsigned char mAIFrequency; // 0xc0
    unsigned char mAICount; // 0xc1
    CVector mOldPos; // 0xc4
    CVector mTweenPos; // 0xd0
    CVector mNewPos; // 0xdc
    CVector mDPos; // 0xe8
    CSVector mOldAngles; // 0xf4
    CSVector mNewAngles; // 0xfa
    CSVector mDAngles; // 0x100
    /* sizeof 0x108 */

    CBody();
    virtual ~CBody();
    virtual void Die();
    virtual void AI() CCLASS_POLY_EMPTY_VIRTUAL virtual void EveryFrame() CCLASS_POLY_EMPTY_VIRTUAL
        virtual void DoLightingSetup() CCLASS_POLY_EMPTY_VIRTUAL
        virtual int Hit(int damage, const CVector &knock, int whatHit);
    virtual void DeleteStuff() CCLASS_POLY_EMPTY_VIRTUAL void InterleaveAI();
    void AttachTo(CBody **list);
    void DeleteFrom(CBody **list);
    short *SquirtPos(short *info);
    short *SquirtAngles(short *info);
    void Suspend(CBody **originalList);
    void UnSuspend();
    void ShadowOn();
    void KillShadow();
    void UpdateShadow();
    int IsDead() const;
};

struct CSuper : CBody
{
    unsigned int mExtraFlags; // 0x108
    unsigned short *mpCalculationOrder; // 0x10c
    void *mpDecompressedFrame; // 0x110
    unsigned short mRoot; // 0x114
    unsigned char mDecompressedAnim; // 0x116
    signed char mDecompressedFrame; // 0x117
    short mFrame; // 0x118
    unsigned short mAnim; // 0x11a
    unsigned char mAnimMode; // 0x11c
    short mPingPongStart; // 0x11e
    short mPingPongEnd; // 0x120
    short mPingPongFrame; // 0x122
    signed char mAnimDir; // 0x124
    signed char mTargetFrame; // 0x125
    signed char mTargetFrame2; // 0x126
    unsigned short mFrameFrac; // 0x128
    unsigned char mNumFrames; // 0x12a
    unsigned char mAnimFinished; // 0x12b
    int mAnimSpeed; // 0x12c
    short mOldFrame; // 0x130
    short mNewFrame; // 0x132
    unsigned char mOldAnim; // 0x134
    signed char mOldAnimDir; // 0x135
    short mStartFrame; // 0x136
    unsigned char mShadowLights; // 0x138
    SVECTOR *mpShadowSource; // 0x13c
    CVECTOR *mpShadowRGB; // 0x140
    MATRIX mTransform; // 0x144
    void *mpPoseBuffer; // 0x164
    void *mpJoints; // 0x168
    void *mpLinks; // 0x16c
    short *mpHierarchy; // 0x170
    unsigned int mSubObjectDisplayMask; // 0x174
    unsigned int mUseAnimOrder; // 0x178
    unsigned char mAnimOrder[19]; // 0x17c
    /* sizeof 0x190 */

    CSuper();
    virtual ~CSuper();
    void UpdateFrame();
    void RunAnim(int anim, int from, int to, int to2);
    void CycleAnim(int animation, signed char direction);
    void SetAnimOrder(unsigned char modelId, unsigned char animOrder);
    void CalculateAnimOrder(char **animHierarchy, int animPartCount, char **modelHierarchy,
                            int modelPartCount);
};

#ifdef CCLASS_POLY_BADDY_FAMILY
struct CBruce;

/** Scripted environmental actor (BADDY.cpp is the owner).  Slots: [1] Die
    (overrides CBody::Die) and [7] ExecuteCommand [8] SetVariable [9]
    GetVariable.  Derived owners: CScriptOnlyBaddy (BADDY), CCar, CPlatform. */
struct CBaddy : CSuper
{
    unsigned int mMode; // 0x190
    unsigned char mDoScript;
    unsigned char mReadHooks;
    unsigned char mApplyGravity;
    unsigned char mHit;
    unsigned char mInputSignal;
    unsigned char mDeathPulseSent;
    unsigned char mComplexSurfaceInterval;
    unsigned char mComplexSurfaceTimer;
    unsigned short mInputFlagsCopy;
    unsigned short mSubType;
    unsigned short mVerticalCompliance;
    unsigned int mSpecificFlags;
    unsigned short *mpScript;
    unsigned short *mpScriptLabel[8];
    unsigned short mBaddyAttributes[6];
    unsigned short *mpWeaponAttributes;
    unsigned char mWeapons;
    unsigned char mAttributesPerWeapon;
    unsigned char mCollisionOn;
    unsigned char _padToGroundToOrigin;
    short mGroundToOrigin;
    short mOriginToEye;
    short mRegister[6];
    unsigned short mPattern;
    unsigned short mSubPattern;
    unsigned short mWaitTimer;
    unsigned short _padToDeadChecksum;
    unsigned int mDeadChecksum;
    CVector mTargetPos;
    unsigned int mLoopingSound;
    int mLoopingSoundUpdate;
    struct CBruce *mpCreatedByPlayer;
    /* sizeof 0x214 */

    CBaddy();
    virtual ~CBaddy();
    virtual void Die();
    virtual int ExecuteCommand(unsigned short command);
    virtual void SetVariable(unsigned short variable);
    virtual short GetVariable(unsigned short variable);
    unsigned short GetScriptValue();
    void SendDeathPulse();
    void SkipToEndif();
    void ParseScript(unsigned short *pScript);
};

typedef char CBaddy_poly_size_must_be_532[(sizeof(CBaddy) == 532) ? 1 : -1];
#endif // CCLASS_POLY_BADDY_FAMILY

typedef char CItem_poly_size_must_be_76[(sizeof(CItem) == 76) ? 1 : -1];
typedef char CBody_poly_size_must_be_264[(sizeof(CBody) == 264) ? 1 : -1];
typedef char CSuper_poly_size_must_be_400[(sizeof(CSuper) == 400) ? 1 : -1];

#endif // CCLASS_POLY_ITEM_FAMILY_DEFINED
#endif // CCLASS_POLY_ITEM_FAMILY

// ---------------------------------------------------------------------------
// Natural CBit family (particles; vtable pointer at the END of CBit, offset
// 68, sizeof 72).  Slots from the target tables: [0] ~CBit [1] Move, and
// CSpecialDisplay adds [2] Display.  Implementations live in BIT.cpp; an owner
// TU defines CCLASS_POLY_BIT_FAMILY before including this header.  The shared
// per-class headers (CGLINE.h, CPOLYLINE.h, CSMOKEJET.h, ...) mark their
// virtual members with CBIT_VIRTUAL, which is `virtual` here and empty for the
// TUs that still use the hand-built layouts.
// ---------------------------------------------------------------------------
#ifdef CCLASS_POLY_BIT_FAMILY
#ifndef CCLASS_POLY_BIT_FAMILY_DEFINED
#define CCLASS_POLY_BIT_FAMILY_DEFINED
#define CBIT_VIRTUAL virtual

struct CBit
{
    CBit *mPrevious; // 0x00
    CBit *mNext; // 0x04
    short mAge; // 0x08
    unsigned short mLifetime; // 0x0a
    CVector mTweenPos; // 0x0c
    CVector mPos; // 0x18
    CVector mVel; // 0x24
    CVector mAcc; // 0x30
    CFriction mFric; // 0x3c
    unsigned char mDead; // 0x3f
    unsigned short mFrigDeltaZ; // 0x40
    unsigned char mProtected; // 0x42
    unsigned char mType; // 0x43
    /* vtable pointer                  0x44 */

    CBit();
    virtual ~CBit();
    virtual void Move();
    void AttachTo(void *list);
    void DeleteFrom(void *list);
    void Die();
    void SetPos(const CVector &position);
    static void *operator new(unsigned int size);
    static void operator delete(void *p);
};

typedef char CBit_poly_size_must_be_72[(sizeof(CBit) == 72) ? 1 : -1];

#endif // CCLASS_POLY_BIT_FAMILY_DEFINED
#endif // CCLASS_POLY_BIT_FAMILY
