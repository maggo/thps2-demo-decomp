// TEXTEFFECTS.cpp -- Reconstructed translation unit
// Original: TEXTEFFECTS.CPP
// Functions: 31 (31 reconstructed)
// Address range: 0x8006BFBC - 0x8006C988
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#define TEXTEFFECT_POLYMORPHIC_LAYOUT
#include "CCLASS_POLY.h"
#define TEXTEFFECTS_OWNER_DECLARATIONS
#include "TEXTEFFECTS.h"
#undef TEXTEFFECTS_OWNER_DECLARATIONS
// The shared headers below model CClass as the bare vtable-pointer holder
// (`x->CClass.vtable`), so they see globals.h's data view of it.
#define CClass CClassData
#include "MAIN.h"
#include "FRONT.h"
#include "FONTTOOLS.h"
#include "UTILS.h"

/** Return caller-owned storage for an ordinary placement construction. */
inline void *operator new(unsigned int, void *storage) { return storage; }

struct Slice;

#include "IMAGEBASE.h"

struct SlicedImage2 : Image {
    Slice *SliceTab;
    short W;
    short H;
    short SliceW;
    short SliceH;
    short SliceCountX;
    short SliceCountY;
    /** True after owned pixel buffers have been allocated for the slices. */
    bool InMemory;
    /** True after the slice rectangles have been allocated in VRAM. */
    bool Packed;
    int BppShift;
    unsigned short Clut;
};

struct Sprite2 : SlicedImage2 {
};

/** Rotatable sprite prefix returned by the IMAGE-owned constructor. */
struct RotateSprite : Sprite2 {
    unsigned char AspectType;

    /** Build a rotatable sprite from a bitmap file. */
    RotateSprite(char *filename, int pack, int sliceWidth, int sliceHeight);
};

#include "IMAGE.h"
#undef CClass
typedef char text_effect_Image_size_must_be_28[(sizeof(Image) == 28) ? 1 : -1];
typedef char text_effect_SlicedImage2_size_must_be_60[(sizeof(SlicedImage2) == 60) ? 1 : -1];
typedef char text_effect_Sprite2_size_must_be_60[(sizeof(Sprite2) == 60) ? 1 : -1];
typedef char text_effect_RotateSprite_size_must_be_64[
    (sizeof(RotateSprite) == 64) ? 1 : -1];
typedef char text_effect_Font_size_must_be_80[(sizeof(Font) == 80) ? 1 : -1];

// === Forward type declarations ===


/**
 * Virtual dispatch table shared by the image and sprite hierarchy.
 */
struct Sprite2VTable {
    int reserved[2];
    void (*destroy)(Sprite2 *sprite, int flags);
    void (*drawImage)(Sprite2 *sprite, int x, int y);
    void (*setData)(Sprite2 *sprite, void *data);
    void (*draw)(Sprite2 *sprite, int x, int y, int drawFirst);
};

typedef char trick_text_effect_size_must_be_24[
    (sizeof(TrickTextEffect) == 24) ? 1 : -1
];

// === Extern "C" global variable declarations ===
/*
 * Original TEXTEFFECTS.CPP small-data contribution, in target address order.
 * These were undefined `extern` declarations, which `prepare_for_aspsx` turns into
 * `.comm` records that PSYLINK allocates in `.sbss` and exports -- fabricating
 * bytes and XDEFs the original never had.
 */
Sprite2 *FallingTextEffect::mpBloodSprite
    __attribute__((section(".sdata"))) = 0;


// === Function implementations (address order) ===

/**
 * Construct the owner-local TextEffect layout slice.
 *
 * Address:   0x8006BFBC
 * Mangled:   __10TextEffect
 * Demangled: TextEffect::(void)
 *
 */
TextEffect::TextEffect()
{
    mEnabled = 0;
}

/**
 * Destroy a TextEffect through its GCC 2.x destructor ABI entry point.
 *
 * Address:   0x8006BFD4
 * Mangled:   _._10TextEffect
 * Demangled: TextEffect::~TextEffect()
 *
 * @param _this Effect to destroy.
 * @param __in_chrg GCC 2.x in-charge flag; bit zero releases the object.
 */
TextEffect::~TextEffect()
{
}

/**
 * Attach an enabled effect to a font.
 *
 * Address:   0x8006C004
 * Mangled:   bind__10TextEffectP4Font
 * Demangled: TextEffect::bind(Font *)
 *            If active (field+4 != 0), call SetTextEffect(font, this)
 *
 * @param pFont Font used for rendering.
 */
void TextEffect::bind(Font *pFont)
{
    if (mEnabled != 0)
    {
        pFont->SetTextEffect(this);
    }
}

/**
 * Detach an enabled effect from a font.
 *
 * Address:   0x8006C038
 * Mangled:   unbind__10TextEffectP4Font
 * Demangled: TextEffect::unbind(Font *)
 *            If active (field+4 != 0), call SetTextEffect(font, 0)
 *
 * @param pFont Font used for rendering.
 */
void TextEffect::unbind(Font *pFont)
{
    if (mEnabled != 0)
    {
        pFont->SetTextEffect(0);
    }
}

/**
 * Default screen-position hook; base effects leave the coordinates unchanged.
 *
 * Address: 0x8006C068
 * Mangled: getScreenPos__10TextEffectPiT1
 *
 * @param pX Screen X coordinate.
 * @param pY Screen Y coordinate.
 */
void TextEffect::getScreenPos(int *pX, int *pY)
{
}

/**
 * Default color hook; base effects leave the color unchanged.
 *
 * Address: 0x8006C070
 * Mangled: getColor__10TextEffectPUcN21
 *
 * @param pR Red component.
 * @param pG Green component.
 * @param pB Blue component.
 */
void TextEffect::getColor(
    unsigned char *pR, unsigned char *pG, unsigned char *pB)
{
}

/**
 * Default post-effect hook; base effects draw nothing.
 *
 * Address:   0x8006C078
 * Mangled:   PostEffect__10TextEffectiiii
 * Demangled: TextEffect::PostEffect(int, int, int, int)
 *
 */
void TextEffect::PostEffect(int, int, int, int)
{
}

/**
 * Disable a text effect.
 *
 * Address:   0x8006C080
 * Mangled:   disable__10TextEffect
 * Demangled: TextEffect::disable(void)
 *
 */
void TextEffect::disable()
{
    mEnabled = 0;
}

/**
 * Construct a falling text effect.
 *
 * Address:   0x8006C088
 * Mangled:   __17FallingTextEffect
 * Demangled: FallingTextEffect::(void)
 *
 */
FallingTextEffect::FallingTextEffect()
{
    mBloody = 0;
}

/**
 * Destroy a falling text effect.
 *
 * Address:   0x8006C0C0
 * Mangled:   _._17FallingTextEffect
 * Demangled: FallingTextEffect::~FallingTextEffect()
 *
 */

FallingTextEffect::~FallingTextEffect()
{
}

/**
 * Select the blood-sprite motion and rendering mode.
 *
 * Address:   0x8006C114
 * Mangled:   SetBloodiness__17FallingTextEffecti
 * Demangled: FallingTextEffect::SetBloodiness(int)
 * @param bloody Nonzero selects the bloody variant.
 */
void FallingTextEffect::SetBloodiness(int bloody)
{
    mBloody = bloody;
}

/**
 * Initialize the per-character falling motion table.
 *
 * Address:   0x8006C11C
 * Mangled:   init__17FallingTextEffect
 * Demangled: FallingTextEffect::init(void)
 *
 */
void FallingTextEffect::init()
{
    mEnabled = 1;
    int i = 0;
    short *bloodRotation = &mTextEffectInfo[0].bloodRotation;
    short *bloodOffsetY = &mTextEffectInfo[0].bloodOffsetY;
    short *bloodOffsetX = &mTextEffectInfo[0].bloodOffsetX;
    short *waitTime = &mTextEffectInfo[0].waitTime;
    do
    {
        int rx = Rnd(0x1E);
        *waitTime = (short)(rx + 0xF);
        int ry = Rnd(0x30);
        *bloodOffsetX = (short)ry;
        *bloodOffsetY = 0;
        int ra = Rnd(0x100);
        *bloodRotation = (short)((ra - 0x80) & 0xFFF);
        bloodRotation += sizeof(myTextEffectInfo) / sizeof(short);
        bloodOffsetY += sizeof(myTextEffectInfo) / sizeof(short);
        bloodOffsetX += sizeof(myTextEffectInfo) / sizeof(short);
        i++;
        waitTime += sizeof(myTextEffectInfo) / sizeof(short);
    } while (i < CharacterCount);
    mOffscreenY = 0x10E;
    int rv = Rnd(2);
    mBloody = (u32)rv < 1;
    mFrameSize = 0;
}

/**
 * Advance every active falling character while gameplay is running.
 *
 * Address:   0x8006C1EC
 * Mangled:   update__17FallingTextEffect
 * Demangled: FallingTextEffect::update(void)
 *            Decrements all 32 wait values and advances the blood-frame timer.
 */
void FallingTextEffect::update()
{
    if (mEnabled != 0)
    {
        if (GameFrozen == 0)
        {
            if (GamePaused == 0)
            {
                int i = 0;
                myTextEffectInfo *info = &mTextEffectInfo[0];
                do
                {
                    i++;
                    info->waitTime = info->waitTime - 1;
                    info++;
                } while (i < CharacterCount);
                mFrameSize = mFrameSize + 1;
            }
        }
    }
}

/**
 * Draw and clip the optional blood sprite behind one character.
 *
 * Address:   0x8006C25C
 * Mangled:   PostEffect__17FallingTextEffectiiii
 * Demangled: FallingTextEffect::PostEffect(int, int, int, int)
 *            Draws the blood sprite behind a falling character, then clips
 *            subsequent text drawing to the character's visible screen area.
 *
 * @param oldX  Previous fixed-point screen X coordinate.
 * @param oldY  Previous fixed-point screen Y coordinate.
 * @param ScreenX  Current fixed-point screen X coordinate (unused).
 * @param ScreenY  Current fixed-point screen Y coordinate.
 */
void FallingTextEffect::PostEffect(int oldX, int oldY, int ScreenX, int ScreenY)
{
    if (mEnabled)
    {
        if (mBloody == 1)
        {
            int clipX = oldX >> FixedPointShift;
            int clipY = oldY >> FixedPointShift;
            int clipW;
            int clipH;

            if (clipX + 16 >= 0 && clipX + 16 <= 528)
            {
                SetClippingBox2(0, 0, 512, 240);

                mpBloodSprite->Scale = 0x2000;
                ((Sprite2VTable *)*(int **)mpBloodSprite)->draw(
                    mpBloodSprite,
                    clipX - mTextEffectInfo[mCharCount & CharacterMask].bloodOffsetX,
                    clipY - mTextEffectInfo[mCharCount & CharacterMask].bloodOffsetY,
                    mTextEffectInfo[mCharCount & CharacterMask].bloodRotation);

                clipW = 16;
                clipH = (ScreenY - oldY) >> FixedPointShift;
                if (clipX + clipW > 512)
                {
                    clipW -= (clipX + clipW) - 512;
                }
                if (clipY + clipH > 240)
                {
                    clipH -= (clipY + clipH) - 240;
                }
                SetClippingBox2(clipX, clipY, clipW, clipH);
            }
        }
    }
}

/**
 * Apply one character's falling displacement to its screen position.
 *
 * Address:   0x8006C36C
 * Mangled:   getScreenPos__17FallingTextEffectPiT1
 * Demangled: FallingTextEffect::getScreenPos(int *, int *)
 *            Computes vertical screen position for falling text effect.
 *            The 32-entry motion table is indexed circularly. Bloody text uses
 *            linear motion; the ordinary variant uses quadratic acceleration.
 *
 * @param pX Screen X coordinate (unchanged).
 * @param pY Screen Y coordinate to displace and clamp.
 */
void FallingTextEffect::getScreenPos(int *pX, int *pY)
{
    if (mEnabled == 0)
        return;

    int gravity = -mTextEffectInfo[mCharCount & CharacterMask].waitTime;
    int gravShifted;
    if (mBloody == 1)
        gravShifted = gravity << 13;
    else
        gravShifted = (gravity * gravity) << 12;
    int limit;
    if (mTextEffectInfo[mCharCount & CharacterMask].waitTime < 0)
    {
        int newPos = *pY + gravShifted;
        limit = mOffscreenY << 12;
        if (newPos >= limit)
            goto clamp;
        *pY = newPos;
    }

    mFallingCount = mFallingCount + 1;
    goto done;

clamp:
    *pY = limit;

done:
    mCharCount = mCharCount + 1;
}

/**
 * Tint active falling text red.
 *
 * Address: 0x8006C424
 *          If active, set r=255, g=50, b=50 (red tint for falling text)
 * Mangled: getColor__17FallingTextEffectPUcN21
 *
 * @param pR Red component.
 * @param pG Green component.
 * @param pB Blue component.
 */
void FallingTextEffect::getColor(unsigned char * pR, unsigned char * pG, unsigned char * pB)
{
    if (mEnabled != 0)
    {
        int red = 255;
        *pR = red;
        *pG = 0x32;
        *pB = 0x32;
    }
}

/**
 * Set the font scale used while this effect is bound.
 *
 * Address:   0x8006C44C
 * Mangled:   setScale__17FallingTextEffecti
 * Demangled: FallingTextEffect::setScale(int)
 * @param scale Fixed-point font scale.
 */
void FallingTextEffect::setScale(int scale)
{
    mScale = scale;
}

/**
 * Bind the falling effect and initialize its character cursor.
 *
 * Address:   0x8006C454
 * Mangled:   bind__17FallingTextEffectP4Font
 * Demangled: FallingTextEffect::bind(Font *)
 *
 * @param pFont Font used for rendering.
 */
void FallingTextEffect::bind(Font *pFont)
{
    TextEffect::bind(pFont);
    if (mEnabled != 0)
    {
        pFont->Scale = mScale;
        mFallingCount = 0;
        mCharCount = 0;
    }
}

/**
 * Finish the effect after every visible character has landed.
 *
 * Address:   0x8006C4A8
 * Mangled:   handleComplete__17FallingTextEffect
 * Demangled: FallingTextEffect::handleComplete(void)
 * @return Nonzero when no falling characters remain active.
 */
int FallingTextEffect::handleComplete()
{
    int active = (u32)mFallingCount > 0;
    mEnabled = active;
    return active ^ 1;
}

/**
 * Fade the shared blood sprite after its initial display interval.
 *
 * Address:   0x8006C4C0
 * Mangled:   drawBloodyFrame__17FallingTextEffectiii
 * Demangled: FallingTextEffect::drawBloodyFrame(int, int, int)
 *            Update the shared blood sprite's tint for this falling text effect frame.
 *
 * @param x  Frame X position (unused by this color update).
 * @param y  Frame Y position (unused by this color update).
 * @param width  Frame width (unused by this color update).
 */
void FallingTextEffect::drawBloodyFrame(int x, int y, int width)
{
    if (mEnabled)
    {
        if (mBloody == 1)
        {
            Sprite2 *sprite = mpBloodSprite;
            sprite->Transparent = (void *)1;
            sprite->TransType = 1;

            if (mFrameSize > 0x32)
            {
                int g = 0x60 - 3 * (mFrameSize - 0x32);
                int r = g;
                int b = g;
                if (r < 0) r = 0;
                if (g < 0) g = 0;
                if (b < 0) b = 0;
                sprite->R = r;
                mpBloodSprite->G = g;
                mpBloodSprite->B = b;
            }
            else
            {
                sprite->R = 0x60;
                mpBloodSprite->G = 0x60;
                mpBloodSprite->B = 0x60;
            }
        }
    }
}

/**
 * Allocate and construct the shared blood sprite.
 *
 * Address:   0x8006C578
 * Mangled:   InitSprite__17FallingTextEffect
 * Demangled: FallingTextEffect::InitSprite(void)
 *            Constructs a 32-by-32 sliced RotateSprite and enables shading.
 */
void FallingTextEffect::InitSprite()
{
    RotateSprite *sprite = (RotateSprite *)::CClass::operator new(
        sizeof(RotateSprite));
    if (sprite != 0)
    {
        sprite = ::new (sprite) RotateSprite(
            "s2blood.bmp", 1, 0x20, 0x20);
    }
    mpBloodSprite = sprite;
    sprite->Shaded = (void *)1;
}

/**
 * Destroy the shared blood sprite if it is loaded.
 *
 * Address:   0x8006C5C8
 * Mangled:   FreeSprite__17FallingTextEffect
 * Demangled: FallingTextEffect::FreeSprite(void)
 *            If mpBloodSprite != NULL, calls vtable destructor with arg 3, then NULLs it
 *
 */
void FallingTextEffect::FreeSprite()
{
    if (mpBloodSprite != 0)
    {
        ((Sprite2VTable *)*(int **)mpBloodSprite)
            ->destroy(mpBloodSprite, 3);
    }
    mpBloodSprite = 0;
}

/**
 * Construct a trick text effect.
 *
 * Address:   0x8006C600
 * Mangled:   __15TrickTextEffect
 * Demangled: TrickTextEffect::(void)
 *
 */
TrickTextEffect::TrickTextEffect()
{
    mTrickState = Idle;
}

/**
 * Destroy a trick text effect.
 *
 * Address:   0x8006C638
 * Mangled:   _._15TrickTextEffect
 * Demangled: TrickTextEffect::~TrickTextEffect()
 *
 */

TrickTextEffect::~TrickTextEffect()
{
}

/**
 * Binds the trick text effect and advances its scale animation.
 *
 * Address:   0x8006C68C
 * Mangled:   bind__15TrickTextEffectP4Font
 * Demangled: TrickTextEffect::bind(Font *)
 *
 * @param pFont Font whose scale is animated by the current trick state.
 */
void TrickTextEffect::bind(Font *pFont)
{
    TextEffect::bind(pFont);
    if (mEnabled != 0)
    {
        int Steady = 0xbc0;
        if (GNumberOfPlayers > 1)
            Steady = 0x940;
        int Grown = Steady;
        if (GNumberOfPlayers == 1)
            Grown = 0x1000;

        switch (mTrickState)
        {
        case Bailing:
        {
            int A = mBailStartSize;
            int B = Steady;
            int Pos = mTrickTime;
            int Duration = 10;
            pFont->Scale = A + ((B - A) * Pos) / Duration;
            if (mTrickTime == Duration)
            {
                mTrickTime = 0;
                mTrickState = BailComplete;
            }
            break;
        }
        case Growing:
        {
            int B = Grown;
            int Pos = mTrickTime;
            int Duration = 5;
            pFont->Scale = 0x3c0 + ((B - 0x3c0) * Pos) / Duration;
            if (mTrickTime == Duration)
            {
                mTrickTime = 0;
                mTrickState = Settling;
            }
            break;
        }
        case Settling:
        {
            int A = Grown;
            int B = Steady;
            int Pos = mTrickTime;
            int Duration = 5;
            pFont->Scale = A + ((B - A) * Pos) / Duration;
            if (mTrickTime == Duration)
            {
                mTrickTime = 0;
                mTrickState = Holding;
            }
            break;
        }
        case Holding:
            pFont->Scale = Steady;
            if (mTrickTime == 0x1e)
            {
                mTrickTime = 0;
                mTrickState = Shrinking;
            }
            break;
        case Shrinking:
        {
            int A = Steady;
            int Pos = mTrickTime;
            int Duration = 10;
            pFont->Scale = A + ((0 - A) * Pos) / Duration;
            if (mTrickTime == Duration)
            {
                mTrickTime = 0;
                mTrickState = Complete;
            }
            break;
        }
        case Complete:
            pFont->Scale = 0;
            break;
        case Idle:
        default:
            break;
        }
        mScale = pFont->Scale;
    }
}

/**
 * Start the trick text grow animation.
 *
 * Address:   0x8006C86C
 * Mangled:   init__15TrickTextEffect
 * Demangled: TrickTextEffect::init(void)
 *
 */
void TrickTextEffect::init()
{
    mEnabled = 1;
    mTrickTime = 0;
    mTrickState = Growing;
}

/**
 * Advance the trick animation timer while gameplay is running.
 *
 * Address:   0x8006C880
 * Mangled:   update__15TrickTextEffect
 * Demangled: TrickTextEffect::update(void)
 *            Increments frame counter if active and not paused/frozen
 *
 */
void TrickTextEffect::update()
{
    if (mEnabled != 0)
    {
        if (GameFrozen == 0)
        {
            if (GamePaused == 0)
            {
                mTrickTime = mTrickTime + 1;
            }
        }
    }
}

/**
 * Fade bailed trick text from neutral gray toward red.
 *
 * Address: 0x8006C8D0
 *          Computes the bail trick text fade color from the current trick timer.
 * Mangled: getColor__15TrickTextEffectPUcN21
 *
 * @param pR Red component.
 * @param pG Green component.
 * @param pB Blue component.
 */
void TrickTextEffect::getColor(unsigned char * pR, unsigned char * pG, unsigned char * pB)
{
    if (mEnabled == 0)
        return;
    if ((u32)(mTrickState - Bailing) >= 2)
        return;
    if (mTrickState == BailComplete)
    {
        mTrickTime = 10;
    }
    int Pos = mTrickTime;
    int mul_r = 127;
    int rnum = Pos * mul_r;
    int divisor = 10;
    int rv = rnum / divisor;
    int mul_g = -78;
    int gnum = Pos * mul_g;
    int gv = gnum / divisor;
    int rbv = rv + 128;
    *pR = rbv;
    int gbv = gv + 128;
    *pG = gbv;
    *pB = gbv;
}

/**
 * Disable a completed bail animation.
 *
 * Address:   0x8006C968
 * Mangled:   handleComplete__15TrickTextEffect
 * Demangled: TrickTextEffect::handleComplete(void)
 *            If state==6, disable (active=0). Returns !active (1 if done)
 *
 * @return Nonzero when the effect is disabled.
 */
int TrickTextEffect::handleComplete()
{
    if (mTrickState == BailComplete)
    {
        mEnabled = 0;
    }
    return (u32)mEnabled < 1;
}

/**
 * Begin the bail shrink animation from the current font scale.
 *
 * Address:   0x8006C988
 * Mangled:   Bail__15TrickTextEffect
 * Demangled: TrickTextEffect::Bail(void)
 *
 */
void TrickTextEffect::Bail()
{
    mBailStartSize = mScale;
    mTrickState = Bailing;
    mTrickTime = 0;
}
