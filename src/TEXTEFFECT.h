#ifndef TEXTEFFECT_INC_H
#define TEXTEFFECT_INC_H

#ifdef TEXTEFFECT_POLYMORPHIC_LAYOUT
/** Polymorphic base of every font text effect (TEXTEFFECTS.cpp owner view). */
struct TextEffect : CClass
{
    int mEnabled;

    TextEffect();
    virtual ~TextEffect();
    /** Attach an enabled effect to a font. */
    virtual void bind(Font *pFont);
    /** Detach an enabled effect from a font. */
    virtual void unbind(Font *pFont);
    virtual void init() = 0;
    virtual void update() = 0;
    /** Apply the effect's screen-position adjustment. */
    virtual void getScreenPos(int *pX, int *pY);
    /** Apply the effect's color adjustment. */
    virtual void getColor(unsigned char *pR, unsigned char *pG, unsigned char *pB);
    virtual int handleComplete() = 0;
    /** Run the effect after drawing one character. */
    virtual void PostEffect(int oldX, int oldY, int screenX, int screenY);
    /** Disable the effect. */
    void disable();
};
#else
/** Base state and non-pure operations shared by all font text effects. */
struct TextEffect
{
#ifdef CCLASS_POLY_H
    CClassData CClass;
#else
    CClass CClass;
#endif
    int mEnabled;

    /** Attach an enabled effect to a font. */
    void bind(Font *pFont);

    /** Detach an enabled effect from a font. */
    void unbind(Font *pFont);

    /** Apply the effect's screen-position adjustment. */
    void getScreenPos(int *pX, int *pY);

    /** Apply the effect's color adjustment. */
    void getColor(unsigned char *pR, unsigned char *pG, unsigned char *pB);

    /** Run the effect after drawing one character. */
    void PostEffect(int oldX, int oldY, int screenX, int screenY);

    /** Disable the effect. */
    void disable();
};
#endif // TEXTEFFECT_POLYMORPHIC_LAYOUT

#endif // TEXTEFFECT_INC_H
