// POWERUP.cpp -- Reconstructed translation unit
// Original: POWERUP.CPP
// Functions: 13 reconstructed
// Address range: 0x8002FB00 - 0x80030F28
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#include "PSX.h"
#define CCLASS_POLY_ITEM_FAMILY
#include "CCLASS_POLY.h"
#define POWERUP_OWNER_DECLARATIONS
#include "POWERUP.h"
#undef POWERUP_OWNER_DECLARATIONS
#include "MAIN.h"
#include "globals.h"

/** Return caller-provided storage for an owner constructor. */
inline void *operator new(unsigned int, void *address)
{
    return address;
}

struct CQuadBit;
struct SLight;
struct CBit;
struct PowerUpCItemOwner;

/** Deleting-destructor prefix shared by particle vtables. */
struct PowerUpBitVtable
{
    void (*Reserved0)(CBit *bit);
    void (*Reserved1)(CBit *bit);
    void (*destroy)(CBit *bit, int flags);
};

/** Particle-base storage embedded at the start of CGlow. */
struct CBit
{
    CBit *mPrevious;
    CBit *mNext;
    short mAge;
    unsigned short mLifetime;
    CVector mTweenPos;
    CVector mPos;
    CVector mVel;
    CVector mAcc;
    CFriction mFric;
    unsigned char mDead;
    unsigned short mFrigDeltaZ;
    unsigned char mProtected;
    unsigned char mType;
    const PowerUpBitVtable *_vf;

    /** Assign the bit's world-space position. */
    void SetPos(const CVector &position);
    /** Allocate zero-initialized storage from the transient-bit heap. */
    static void *operator new(unsigned int size);
    static void operator delete(void *);
};

#include "CGLOW.h"

#include "LOCALTXT.h"

/** Proven CBruce slices needed when awarding a pickup. */
struct CBruce : CBody
{
    /** Start a new airborne trick sequence. */
    void Trick_TakeOff();
    /** Adds one named trick to the active scoring sequence. */
    void Trick_Trick(char *name, int points, int lock);
    /** Finalize the current trick sequence after landing. */
    void Trick_Land();

    unsigned char mStorageBeforeInBail[3964 - sizeof(CBody)];
    int mInBail;
    unsigned char mStorageBeforePhysicsState[236];
    int mPhysicsState;
};

/** Power-up body and its owner-specific state. */
struct CPowerUp : CBody
{
    CGlow *mpGlow;
    unsigned short mGlowRadiusOrg;
    unsigned short mGlowRadiusAmp;
    unsigned char mHasNode;
    unsigned char mIs3d;
    unsigned char mDropping;
    unsigned char mDropForever;
    unsigned char mHoverHeight;
    unsigned short mNodeIndex;
    int mGroundY;
    CVector mOrgPos;
    unsigned short mT;
    unsigned short mMaxWobbleAmplitude;
    unsigned short mWobbleAmplitude;
    unsigned short mWobbleSpeed;
    unsigned short mLifetime;
    unsigned int mTimer;

    CPowerUp(unsigned short PowerupType, const CVector &Pos, const CVector &Vel, unsigned int Flags,
             int Lifetime);
    virtual ~CPowerUp();
    void AI();
    void CheckAge();
    void CreateBit();
    void DeleteStuff();
    void Die();
    void DoPhysics();
    void DontDisplay();
    void SetGravity(int g, int fric);
    void SetNode(int NodeIndex);
    void TakeEffect(struct CBruce *);
};

PSX_LAYOUT_CHECK(powerup_cbit_size_must_be_72, sizeof(CBit) == 72);
PSX_LAYOUT_CHECK(powerup_bit_vtable_size_must_be_12, sizeof(PowerUpBitVtable) == 12);
PSX_LAYOUT_CHECK(powerup_cglow_size_must_be_104, sizeof(CGlow) == 104);
PSX_LAYOUT_CHECK(powerup_local_text_size_must_be_652, sizeof(LocalText) == 652);
PSX_LAYOUT_CHECK(powerup_cbruce_slice_size_must_be_4208, sizeof(CBruce) == 4208);
PSX_LAYOUT_CHECK(powerup_cpowerup_size_must_be_312, sizeof(CPowerUp) == 312);

#include "BIT.h"
#include "SFX.h"
#include "OB.h"
#include "MESS.h"
#include "PANEL.h"
#include "SPOOL.h"
#include "TRIG.h"
#include "UTILS.h"

/** Target-proven power-up type values used by this owner. */
enum PowerUpType
{
    PowerUpLetterK = 4,
    PowerUpLetterS = 5,
    PowerUpLetterA = 6,
    PowerUpLetterE = 10,
    PowerUpSpecial14 = 14,
    PowerUpLetterT = 15,
    PowerUpSecretTape = 16,
    PowerUpSpecial18 = 18,
    PowerUpTypeBonus100 = 21,
    PowerUpTypeBonus200 = 22,
    PowerUpTypeBonus500 = 23,
    PowerUpTypeBonus20Spot = 24,
    PowerUpTypeBonusFifty = 25,
    PowerUpTypeBonusRich = 26,
    PowerUpTypeBonusRollAgain = 27,
    PowerUpTypeBonusHead = 28,
    PowerUpTypeBonusShoes = 29,
    PowerUpTypeBonusFly = 30,
    PowerUpTypeBonusPants = 31,
    PowerUpTypeBonusBoard = 32,
    PowerUpMedalA = 0x664,
    PowerUpMedalB = 0x665,
    PowerUpMedalC = 0x666
};

/** Flags accepted by the CPowerUp constructor. */
enum PowerUpCreationFlag
{
    PowerUpDropToGround = 4,
    PowerUpUseDropVelocity = 8,
    PowerUpDropForever = 0x10
};

/** Availability bits in CItem::mFlags. */
enum PowerUpItemFlag
{
    PowerUpUnavailable = 1,
    PowerUpUnavailableToSecondPlayer = 0x40,
    PowerUpUnavailableToEveryone = 0x41
};

/** Death bit in CBody::mCBodyFlags. */
enum PowerUpBodyFlag
{
    PowerUpBodyDead = 0x40
};

enum PowerUpConstant
{
    PowerUpPickupVolume = 0x2000,
    PowerUpLetterSound = 0x14,
    PowerUpBonusSound = 0x12,
    PowerUpInfiniteLifetime = 0xFFFF,
    PowerUpDisplayDistance = 8000
};

// === External globals (absolute via incomplete array) ===
#include "MECHLIST.h"

// === DoPhysics support declarations ===
#include "RCOSSIN.h"
// === Function implementations (address order) ===

/**
 * Purpose: Initialize a world power-up, select its model, and add it to the
 * active power-up list.
 *
 * Address: 0x8002FB00
 * Mangled: __8CPowerUpUsRC7CVectorT2Uii
 *
 * @return `this` pointer (GCC 2.x ctor convention).
 */
CPowerUp::CPowerUp(unsigned short PowerupType, const CVector &Pos, const CVector &Vel,
                   unsigned int Flags, int Lifetime)
{
    mTimer = 0;
    mType = PowerupType;
    mHoverHeight = 0;
    mLifetime = Lifetime;
    mOrgPos = Pos;
    mPos = Pos;

    if (Flags & PowerUpUseDropVelocity)
        mVel.vy = -(60 << 12);
    else
        mVel = Vel;

    mFric.Set(5, 5, 5);
    mAngVel.vy = 100;
    mAcc.vy = 8 << 12;

    mWobbleSpeed = Rnd(20) + 90;
    mMaxWobbleAmplitude = 50;
    mWobbleAmplitude = 50;

    if (Flags & PowerUpDropForever)
    {
        mDropping = 1;
        mDropForever = 1;
    }
    else if (Flags & PowerUpDropToGround)
    {
        mDropping = 1;
        mGroundY = Utils_GetGroundHeight(mOrgPos, 0, PowerUpDisplayDistance);
    }

    mRMinor = 300;
    ShadowOn();
    mShadowThreshold = 300;
    InitItem("items");

    switch (mType)
    {
        case PowerUpMedalA:
            InitItem("skmedals");
            mIs3d = 1;
            mModel = Spool_GetModel(0x54636518, CurrentMedalsFileRegion);
            break;
        case PowerUpMedalB:
            InitItem("skmedals");
            mIs3d = 1;
            mModel = Spool_GetModel(0xBA6D0434, CurrentMedalsFileRegion);
            break;
        case PowerUpMedalC:
            InitItem("skmedals");
            mIs3d = 1;
            mModel = Spool_GetModel(0x2364558E, CurrentMedalsFileRegion);
            break;
        case PowerUpLetterS:
            mIs3d = 1;
            mModel = Spool_GetModel(0x311D55D4, CurrentItemsFileRegion);
            break;
        case PowerUpLetterK:
            mIs3d = 1;
            mModel = Spool_GetModel(0x2328A71C, CurrentItemsFileRegion);
            break;
        case PowerUpLetterA:
            mIs3d = 1;
            mModel = Spool_GetModel(0x2EBF22CA, CurrentItemsFileRegion);
            break;
        case PowerUpLetterT:
            mIs3d = 1;
            mModel = Spool_GetModel(0x34524351, CurrentItemsFileRegion);
            break;
        case PowerUpLetterE:
            mIs3d = 1;
            mModel = Spool_GetModel(0x29B68A16, CurrentItemsFileRegion);
            break;
        case PowerUpSecretTape:
        case PowerUpSpecial18:
            mAngVel.vy = 150;
            mIs3d = 1;
            mModel = Spool_GetModel(0x7C1B2C4A, CurrentItemsFileRegion);
            break;
        case PowerUpTypeBonus100:
            mAngVel.vy = 200;
            mIs3d = 1;
            mModel = Spool_GetModel(0x6F0F6B9F, CurrentItemsFileRegion);
            break;
        case PowerUpTypeBonus200:
            mAngVel.vy = 200;
            mIs3d = 1;
            mModel = Spool_GetModel(0xF6063A25, CurrentItemsFileRegion);
            break;
        case PowerUpTypeBonus500:
            mAngVel.vy = 200;
            mIs3d = 1;
            mModel = Spool_GetModel(0x81010AB3, CurrentItemsFileRegion);
            break;
        case PowerUpTypeBonus20Spot:
            mAngVel.vy = 200;
            mIs3d = 1;
            mModel = Spool_GetModel(0x694ED947, CurrentItemsFileRegion);
            break;
        case PowerUpTypeBonusFifty:
            mAngVel.vy = 200;
            mIs3d = 1;
            mModel = Spool_GetModel(0x260F4F80, CurrentItemsFileRegion);
            break;
        case PowerUpTypeBonusRich:
            mAngVel.vy = 200;
            mIs3d = 1;
            mModel = Spool_GetModel(0xCC4E141F, CurrentItemsFileRegion);
            break;
        case PowerUpTypeBonusRollAgain:
            mAngVel.vy = 200;
            mIs3d = 1;
            mModel = Spool_GetModel(0x483701E6, CurrentItemsFileRegion);
            break;
        case PowerUpTypeBonusHead:
            mAngVel.vy = 200;
            mIs3d = 1;
            mModel = Spool_GetModel(0x608E06C7, CurrentItemsFileRegion);
            break;
        case PowerUpTypeBonusShoes:
            mAngVel.vy = 200;
            mIs3d = 1;
            mModel = Spool_GetModel(0x10122D2A, CurrentItemsFileRegion);
            break;
        case PowerUpTypeBonusFly:
            mAngVel.vy = 200;
            mIs3d = 1;
            mModel = Spool_GetModel(0xC12ED64B, CurrentItemsFileRegion);
            break;
        case PowerUpTypeBonusPants:
            mAngVel.vy = 200;
            mIs3d = 1;
            mModel = Spool_GetModel(0x22908B06, CurrentItemsFileRegion);
            break;
        case PowerUpTypeBonusBoard:
            mAngVel.vy = 200;
            mIs3d = 1;
            mModel = Spool_GetModel(0x56891A69, CurrentItemsFileRegion);
            break;
    }

    if (GGame != 1)
    {
        switch (mType)
        {
            case PowerUpLetterK:
            case PowerUpLetterS:
            case PowerUpLetterA:
            case PowerUpLetterE:
            case PowerUpLetterT:
            case PowerUpSecretTape: mLifetime = 1; break;
        }
    }
    else
    {
        switch (mType)
        {
            case PowerUpLetterS: GPowS = this; break;
            case PowerUpLetterK: GPowK = this; break;
            case PowerUpLetterA: GPowA = this; break;
            case PowerUpLetterT: GPowT = this; break;
            case PowerUpLetterE: GPowE = this; break;
            case PowerUpSecretTape: GPowTape = this; break;
        }
    }

    AttachTo(&PowerUpList);
    if (mIs3d == 0) DontDisplay();
}

/**
 * GCC 2.x deleting-destructor entry for CPowerUp.
 *
 * Address:   0x8003018C
 * Mangled:   _._8CPowerUp
 * Demangled: CPowerUp::~CPowerUp()
 *
 */
CPowerUp::~CPowerUp()
{
    DeleteFrom(&PowerUpList);
    DeleteStuff();
}

/**
 * Mark this power-up unavailable and release its display resources.
 *
 * Address:   0x800301F4
 * Mangled:   DontDisplay__8CPowerUp
 * Demangled: CPowerUp::DontDisplay(void)
 *
 */
void CPowerUp::DontDisplay()
{
    u16 flags = mFlags;
    flags |= PowerUpUnavailableToEveryone;
    mFlags = flags;
    DeleteStuff();
}

/**
 * Set the vertical acceleration and damping shift.
 *
 * Address:   0x8003022C
 * Mangled:   SetGravity__8CPowerUpii
 * Demangled: CPowerUp::SetGravity(int, int)
 *
 * @param g  Vertical acceleration in world fixed-point units.
 * @param fric  Vertical velocity damping shift.
 */
void CPowerUp::SetGravity(int g, int fric)
{
    this->mAcc.vy = g;
    this->mFric.vy = fric;
}

/**
 * Request deferred creation of power-up particle effects.
 *
 * Address:   0x80030238
 * Mangled:   CreateBit__8CPowerUp
 * Demangled: CPowerUp::CreateBit(void)
 *
 */
void CPowerUp::CreateBit()
{
    UseCacheForBits = 1;
}

/**
 * Release the shadow and glow owned by this power-up.
 *
 * Address:   0x8003024C
 * Mangled:   DeleteStuff__8CPowerUp
 * Demangled: CPowerUp::DeleteStuff(void)
 *
 */
void CPowerUp::DeleteStuff()
{
    KillShadow();
    CGlow *glow = mpGlow;
    if (glow != 0)
    {
        glow->_vf->destroy(static_cast<CBit *>(glow), 3);
    }
    mpGlow = 0;
}

/**
 * Associate the power-up with a trigger node.
 *
 * Address:   0x8003029C
 * Mangled:   SetNode__8CPowerUpi
 * Demangled: CPowerUp::SetNode(int)
 *
 * @param NodeIndex  Rail node index.
 */
void CPowerUp::SetNode(int NodeIndex)
{
    mNodeIndex = NodeIndex;
    mHasNode = 1;
}

/**
 * Mark the body dead and hide its display resources once.
 *
 * Address:   0x800302AC
 * Mangled:   Die__8CPowerUp
 * Demangled: CPowerUp::Die(void)
 *
 */
void CPowerUp::Die()
{
    if (IsDead() == 0)
    {
        u16 flags = this->mCBodyFlags;
        flags |= PowerUpBodyDead;
        this->mCBodyFlags = flags;
        this->DontDisplay();
    }
}

/**
 * Advance falling or hover motion and refresh the pickup shadow.
 *
 * Address:   0x800302EC
 * Mangled:   DoPhysics__8CPowerUp
 * Demangled: CPowerUp::DoPhysics(void)
 *            Advances rotation, falling and hover motion, then updates the
 *            power-up's shadow position, distance, and scale.
 *
 */
void CPowerUp::DoPhysics()
{
    this->mAngles += this->mAngVel;
    this->mAngles.Mask();

    if (this->mDropping != 0)
    {
        if (this->mDropForever == 0 && this->mGroundY < 0 && this->mGroundY > -5)
        {
            if (TTime & 1)
            {
                int ground = Utils_GetGroundHeight(this->mOrgPos, 0, PowerUpDisplayDistance);
                if (ground == -1)
                {
                    this->mGroundY--;
                    if (this->mGroundY < -4) this->mDropForever = 1;
                }
                else
                {
                    this->mGroundY = ground;
                }
            }
        }
        else
        {
            CVector *vel = &this->mVel;
            this->mOrgPos += *vel;
            this->mVel.vy += this->mAcc.vy;
            this->mVel.vy -= this->mVel.vy >> this->mFric.vy;
            if (this->mDropForever == 0)
            {
                if (this->mGroundY - (this->mHoverHeight << 12) < this->mOrgPos.vy &&
                    this->mVel.vy > 0)
                {
                    this->mOrgPos.vy = this->mGroundY - (this->mHoverHeight << 12);
                    vel->vx = 0;
                    vel->vy = 0;
                    vel->vz = 0;
                    this->mDropping = 0;
                }
            }
            this->mPos = this->mOrgPos;
        }
    }
    else
    {
        this->mPos = this->mOrgPos;
        this->mPos.vy += ((this->mWobbleAmplitude * rcossin_tbl[(this->mT & 0xFFF) * 2]) / 4096)
                         << 12;
        this->mT += this->mWobbleSpeed;
    }

    this->mShadowPos = this->mOrgPos;
    this->mShadowPos.vy = this->mGroundY;
    this->mShadowDist = (this->mGroundY - this->mPos.vy) >> 12;
    if (this->mShadowDist != 0)
    {
        this->mShadowScale = 140 - this->mShadowDist * 60 / 128;
    }
    else
    {
        this->mShadowScale = 0;
    }
}

/**
 * Age the pickup, animate its expiry blink, and destroy it at zero lifetime.
 *
 * Address:   0x80030530
 * Mangled:   CheckAge__8CPowerUp
 * Demangled: CPowerUp::CheckAge(void)
 *
 */
void CPowerUp::CheckAge()
{
    mTimer++;

    if (mLifetime == PowerUpInfiniteLifetime) return;

    if (mLifetime != 0) mLifetime--;

    if (mLifetime < 60) mWobbleAmplitude = mMaxWobbleAmplitude * mLifetime / 60;

    if (mLifetime > 30 && mLifetime < 60)
    {
        if (TTime & 2)
            mFlags &= ~PowerUpUnavailable;
        else
            DontDisplay();
    }

    if (mLifetime < 31)
    {
        if (TTime & 1)
            mFlags &= ~PowerUpUnavailable;
        else
            DontDisplay();
    }

    if (mLifetime == 0)
    {
        Die();
    }
}

/**
 * Apply this pickup's letter, tape, bonus, and trigger effects.
 *
 * Address:   0x8003068C
 * Mangled:   TakeEffect__8CPowerUpP6CBruce
 * Demangled: CPowerUp::TakeEffect(CBruce *)
 *
 * Applies letter, tape, and bonus pickups to a skater, then pulses any linked
 * trigger and consumes pickups which had an effect.
 */
void CPowerUp::TakeEffect(CBruce *pMech)
{
    unsigned short unavailable;
    if (GNumberOfPlayers != 1 && pMech == MechList)
        unavailable = mFlags & PowerUpUnavailableToSecondPlayer;
    else
        unavailable = mFlags & PowerUpUnavailable;

    int HadEffect = 0;
    if (unavailable) return;

    int sound = 0;
    switch (mType)
    {
        case PowerUpLetterK:
        case PowerUpLetterS:
        case PowerUpLetterA:
        case PowerUpLetterE:
        case PowerUpSpecial14:
        case PowerUpLetterT:
        case PowerUpSecretTape:
        {
            HadEffect = 1;
            Mess_DeleteAll();

            char *pMess = 0;
            switch (mType)
            {
                case PowerUpLetterS:
                    SFX_PlayX(PowerUpLetterSound, PowerUpPickupVolume, 0);
                    if (!Panel_Letter(0)) pMess = GameText.pSPickup;
                    break;
                case PowerUpLetterK:
                    SFX_PlayX(PowerUpLetterSound, PowerUpPickupVolume, 0);
                    if (!Panel_Letter(1)) pMess = GameText.pKPickup;
                    break;
                case PowerUpLetterA:
                    SFX_PlayX(PowerUpLetterSound, PowerUpPickupVolume, 0);
                    if (!Panel_Letter(2)) pMess = GameText.pAPickup;
                    break;
                case PowerUpLetterT:
                    SFX_PlayX(PowerUpLetterSound, PowerUpPickupVolume, 0);
                    if (!Panel_Letter(3)) pMess = GameText.pTPickup;
                    break;
                case PowerUpLetterE:
                    SFX_PlayX(PowerUpLetterSound, PowerUpPickupVolume, 0);
                    if (!Panel_Letter(4)) pMess = GameText.pEPickup;
                    break;
                case PowerUpSecretTape:
                    Panel_Tape(3);
                    pMess = 0;
                    break;
            }

            if (pMess) Mess_Message(pMess, Messprog_Zoom, 1, 0, 0);
            break;
        }

        case PowerUpTypeBonus100:
        case PowerUpTypeBonus200:
        case PowerUpTypeBonus500:
        case PowerUpTypeBonus20Spot:
        case PowerUpTypeBonusFifty:
        case PowerUpTypeBonusRich:
        case PowerUpTypeBonusRollAgain:
        case PowerUpTypeBonusHead:
        case PowerUpTypeBonusShoes:
        case PowerUpTypeBonusFly:
        case PowerUpTypeBonusPants:
        case PowerUpTypeBonusBoard:
        {
            if (pMech->mInBail) break;

            HadEffect = 1;
            if (pMech->mPhysicsState == 0) pMech->Trick_TakeOff();

            int Pong = SFX_PlayX(PowerUpBonusSound, PowerUpPickupVolume, 0);
            switch (mType)
            {
                case PowerUpTypeBonus100:
                    pMech->Trick_Trick("Bonus 100", -100, 2);
                    SFX_SetVoicePitch(Pong, 900);
                    break;
                case PowerUpTypeBonus200:
                    pMech->Trick_Trick("Bonus 200", -200, 2);
                    SFX_SetVoicePitch(Pong, 1114);
                    break;
                case PowerUpTypeBonus500:
                    pMech->Trick_Trick("Bonus 500", -500, 2);
                    SFX_SetVoicePitch(Pong, 1500);
                    break;
                case PowerUpTypeBonus20Spot:
                    pMech->Trick_Trick("20 Spot", -100, 2);
                    SFX_SetVoicePitch(Pong, 900);
                    break;
                case PowerUpTypeBonusFifty:
                    pMech->Trick_Trick("Fitty Bucks", -200, 2);
                    SFX_SetVoicePitch(Pong, 1114);
                    break;
                case PowerUpTypeBonusRich:
                    pMech->Trick_Trick("100 Bucks! You're rich!", -500, 2);
                    SFX_SetVoicePitch(Pong, 1500);
                    break;
                case PowerUpTypeBonusRollAgain:
                    pMech->Trick_Trick("Roll Another", -200, -2);
                    SFX_SetVoicePitch(Pong, 1114);
                    break;
                case PowerUpTypeBonusHead:
                    pMech->Trick_Trick("You got head - excellent", -200, 2);
                    SFX_SetVoicePitch(Pong, 1114);
                    break;
                case PowerUpTypeBonusShoes:
                    pMech->Trick_Trick("Gotta be the shoes", -200, 2);
                    SFX_SetVoicePitch(Pong, 1114);
                    break;
                case PowerUpTypeBonusFly:
                    pMech->Trick_Trick("You'll look fly in this", -200, 2);
                    SFX_SetVoicePitch(Pong, 1114);
                    break;
                case PowerUpTypeBonusPants:
                    pMech->Trick_Trick("Change yo pants!", -200, 2);
                    SFX_SetVoicePitch(Pong, 1114);
                    break;
                case PowerUpTypeBonusBoard:
                    pMech->Trick_Trick("I'm Board", -200, 2);
                    SFX_SetVoicePitch(Pong, 1114);
                    break;
            }

            if (pMech->mPhysicsState == 0) pMech->Trick_Land();
            break;
        }
    }

    if (mHasNode) Trig_SendPulse(Trig_GetLinksPointer(mNodeIndex));

    if (HadEffect)
    {
        Die();

        if (sound) SFX_PlayX(0, PowerUpPickupVolume, 0);
    }
}

/**
 * Update visibility, physics, and glow animation.
 *
 * Address:   0x80030AAC
 * Mangled:   AI__8CPowerUp
 * Demangled: CPowerUp::AI(void)
 *
 * Updates range culling and physics, creates the pickup glow on demand, and
 * animates its fringe radius.
 */
void CPowerUp::AI()
{
    CheckAge();

    if (GNumberOfPlayers == 1)
    {
        if (mFlags & PowerUpUnavailable) return;
        if (mPlayerDist > PowerUpDisplayDistance)
        {
            DeleteStuff();
            return;
        }
    }
    else
    {
        if ((mFlags & PowerUpUnavailableToEveryone) == PowerUpUnavailableToEveryone) return;

        if (mPlayerDist > PowerUpDisplayDistance &&
            Utils_CrapDist(MechList->mNextItem->mPos, mPos) > PowerUpDisplayDistance)
        {
            DeleteStuff();
            return;
        }
    }

    DoPhysics();
    if (!mIs3d) CreateBit();

    if (!mpGlow)
    {
        // The target keeps base allocation and conditional construction separate.
        CGlow *glow = static_cast<CGlow *>(CBit::operator new(sizeof(CGlow)));
        if (glow) glow = ::new (glow) CGlow(4, 2);
        mpGlow = glow;

        mpGlow->mSkipTriangles = 1;
        mpGlow->SetCentreRGB(0, 0, 0);
        mpGlow->SetRGB(0, 0, 0);
        mpGlow->SetFringeRGB(1, 0, 0, 0);
        mpGlow->SetRadius(0);
        mpGlow->mProtected = 1;

        switch (mType)
        {
            case PowerUpSpecial18:
                for (int i = 0; i < mpGlow->mNumSections; i++)
                {
                    if (i & 1)
                        mpGlow->SetRadialRGB(i, 0x60, 0x60, 0);
                    else
                        mpGlow->SetRadialRGB(i, 0x40, 0x40, 0x40);
                }
                mpGlow->SetRGB(0x20, 0, 0);
                mpGlow->SetFringeRGB(1, 0, 0, 0);
                mGlowRadiusOrg = 10;
                mGlowRadiusAmp = 3;
                break;

            case PowerUpLetterK:
            case PowerUpLetterS:
            case PowerUpLetterA:
            case PowerUpLetterE:
            case PowerUpLetterT:
                for (int i = 0; i < mpGlow->mNumSections; i++)
                {
                    if (i & 1)
                        mpGlow->SetRadialRGB(i, 0, 0, 0x60);
                    else
                        mpGlow->SetRadialRGB(i, 0, 0, 0);
                }
                mpGlow->SetRGB(0, 0, 0);
                mpGlow->SetFringeRGB(1, 0, 0, 0);
                mGlowRadiusOrg = 60;
                mGlowRadiusAmp = 10;
                break;

            case PowerUpSecretTape:
                for (int i = 0; i < mpGlow->mNumSections; i++)
                {
                    if (i & 1)
                        mpGlow->SetRadialRGB(i, 0x60, 0x60, 0);
                    else
                        mpGlow->SetRadialRGB(i, 0x40, 0x40, 0x40);
                }
                mpGlow->SetRGB(0, 0, 0);
                mpGlow->SetFringeRGB(1, 0, 0, 0);
                mGlowRadiusOrg = 60;
                mGlowRadiusAmp = 10;
                break;

            case PowerUpTypeBonus100:
                mpGlow->SetFringeRGB(0, 0x30, 0x30, 0);
                mGlowRadiusOrg = 60;
                mGlowRadiusAmp = 10;
                break;

            case PowerUpTypeBonusFifty:
                mpGlow->SetFringeRGB(0, 0x30, 0x30, 0);
                mGlowRadiusOrg = 60;
                mGlowRadiusAmp = 10;
                break;

            case PowerUpTypeBonus200:
            case PowerUpTypeBonusRich:
                mpGlow->SetFringeRGB(0, 0x40, 0x20, 8);
                mGlowRadiusOrg = 60;
                mGlowRadiusAmp = 10;
                break;

            case PowerUpTypeBonus500:
            case PowerUpTypeBonus20Spot:
                mpGlow->SetFringeRGB(0, 0x30, 0, 0);
                mGlowRadiusOrg = 60;
                mGlowRadiusAmp = 10;
                break;
        }
    }

    static_cast<CBit *>(mpGlow)->SetPos(mPos);
    int m = TTime * 150;
    int width = mGlowRadiusOrg + mGlowRadiusAmp * rcossin_tbl[(m & 0xFFF) * 2] / 4096;
    mpGlow->SetFringeWidth(0, width);
    mpGlow->SetFringeWidth(1, width);
}

/**
 * Allocate and construct one world power-up.
 *
 * Address:   0x80030F28
 * Mangled:   PowerUp_Create__FUsRC7CVectorUiiR7CVector
 * Demangled: PowerUp_Create(unsigned short, const CVector &, unsigned int, int, CVector &)
 *
 * @param Type  Type code.
 * @param Pos  Position vector.
 * @param Flags  Creation behavior flags.
 * @param LifeTime  Number of frames to keep the pickup alive.
 * @param Vel  Initial velocity for a moving pickup.
 * @return The constructed power-up, or null when allocation fails.
 */
CPowerUp *PowerUp_Create(unsigned short Type, const CVector &Pos, unsigned int Flags, int LifeTime,
                         CVector &Vel)
{
    // Preserve the target's explicit null check before invoking the constructor.
    CPowerUp *pNewPowerUp = static_cast<CPowerUp *>(::CItem::operator new(sizeof(CPowerUp)));
    if (pNewPowerUp)
    {
        pNewPowerUp = ::new (pNewPowerUp) CPowerUp(Type, Pos, Vel, Flags, LifeTime);
    }
    return pNewPowerUp;
}
