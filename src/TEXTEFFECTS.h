// Shared text-effect layout and callable C++ interface.
#ifndef TEXTEFFECTS_INC_H
#define TEXTEFFECTS_INC_H

#include "globals.h"

struct Font;
struct Sprite2;

#include "TEXTEFFECT.h"

/** Per-character timing and blood-sprite motion recovered from MAIN.SYM. */
struct myTextEffectInfo {
    short waitTime;
    short bloodOffsetX;
    short bloodOffsetY;
    short bloodRotation;
};

#ifdef TEXTEFFECT_POLYMORPHIC_LAYOUT
/** Falling-character text animation and its shared blood sprite. */
struct FallingTextEffect : TextEffect {
    enum {
        CharacterCount = 32,
        CharacterMask = CharacterCount - 1,
        FixedPointShift = 12
    };

    myTextEffectInfo mTextEffectInfo[CharacterCount];
    int mOffscreenY;
    int mCharCount;
    int mScale;
    int mFallingCount;
    int mBloody;
    int mFrameSize;

    static Sprite2 *mpBloodSprite;

    FallingTextEffect();
    virtual ~FallingTextEffect();

    static void FreeSprite();
    static void InitSprite();

    virtual void PostEffect(int oldX, int oldY, int screenX, int screenY);
    void SetBloodiness(int bloody);
    virtual void bind(Font *pFont);
    void drawBloodyFrame(int x, int y, int width);
    virtual void getColor(unsigned char *pR, unsigned char *pG,
                          unsigned char *pB);
    virtual void getScreenPos(int *pX, int *pY);
    virtual int handleComplete();
    virtual void init();
    void setScale(int scale);
    virtual void update();
};

/** Scale and color animation used for trick and bail text. */
struct TrickTextEffect : TextEffect {
    enum State {
        Idle = 0,
        Growing,
        Settling,
        Holding,
        Shrinking,
        Bailing,
        BailComplete,
        Complete
    };

    int mTrickState;
    int mTrickTime;
    int mScale;
    int mBailStartSize;

    TrickTextEffect();
    virtual ~TrickTextEffect();
    void Bail();
    virtual void bind(Font *);
    virtual void getColor(unsigned char * pR, unsigned char * pG, unsigned char * pB);
    virtual int handleComplete();
    virtual void init();
    virtual void update();
};
#else
/** Falling-character text animation and its shared blood sprite. */
struct FallingTextEffect {
    enum {
        CharacterCount = 32,
        CharacterMask = CharacterCount - 1,
        FixedPointShift = 12
    };

    TextEffect TextEffect;
    myTextEffectInfo mTextEffectInfo[CharacterCount];
    int mOffscreenY;
    int mCharCount;
    int mScale;
    int mFallingCount;
    int mBloody;
    int mFrameSize;

    static Sprite2 *mpBloodSprite;

    FallingTextEffect();
    ~FallingTextEffect();

    static void FreeSprite();
    static void InitSprite();

    void PostEffect(int oldX, int oldY, int screenX, int screenY);
    void SetBloodiness(int bloody);
    void bind(Font *pFont);
    void drawBloodyFrame(int x, int y, int width);
    void getColor(unsigned char *pR, unsigned char *pG,
                  unsigned char *pB);
    void getScreenPos(int *pX, int *pY);
    int handleComplete();
    void init();
    void setScale(int scale);
    void update();
};

/** Scale and color animation used for trick and bail text. */
struct TrickTextEffect {
    enum State {
        Idle = 0,
        Growing,
        Settling,
        Holding,
        Shrinking,
        Bailing,
        BailComplete,
        Complete
    };

    struct TextEffect TextEffect;
    int mTrickState;
    int mTrickTime;
    int mScale;
    int mBailStartSize;

    TrickTextEffect();
    ~TrickTextEffect();
    void Bail();
    void bind(Font *);
    void getColor(unsigned char * pR, unsigned char * pG, unsigned char * pB);
    int handleComplete();
    void init();
    void update();
};

#endif // TEXTEFFECT_POLYMORPHIC_LAYOUT

typedef char TextEffect_size_must_be_8[
    (sizeof(TextEffect) == 8) ? 1 : -1];
typedef char myTextEffectInfo_size_must_be_8[
    (sizeof(myTextEffectInfo) == 8) ? 1 : -1];
typedef char FallingTextEffect_size_must_be_288[
    (sizeof(FallingTextEffect) == 288) ? 1 : -1];

#endif // TEXTEFFECTS_INC_H
