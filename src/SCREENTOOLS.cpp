// SCREENTOOLS.cpp -- Reconstructed translation unit
// Original: SCREENTOOLS.CPP
// Functions: 22 reconstructed entries
// Address range: 0x8008A4D4 - 0x8008AC80
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.


#include "PSX.h"
#define SCREENTOOLS_POLYMORPHIC_LAYOUT
#include "SCREENTOOLS.h"
#include "MEM.h"
#include "PUREVIRTUAL.h"
#include <STRINGS.H>

PSX_LAYOUT_CHECK(screentools_font_size_must_be_80, sizeof(Font) == 80);

// === Function implementations (address order) ===

/**
 * ScreenElement::ScreenElement(int, int, int, int)
 *
 * Address:   0x8008A4D4
 * Mangled:   __13ScreenElementiiii
 *            Constructor: sets vtable, stores home/screen positions, clears delay/flags
 *
 * @param self  `this` pointer (explicit — the class is kept vtable-free).
 * @param homeX  Home X coordinate (resting position).
 * @param homeY  Home Y coordinate (resting position).
 * @param screenX  Screen-space X coordinate, or -1 to start at home.
 * @param screenY  Screen-space Y coordinate, or -1 to start at home.
 * @return `this` pointer (GCC 2.x ctor convention).
 */
ScreenElement::ScreenElement(int homeX, int homeY, int screenX, int screenY)
{
    mHomeX = homeX;
    mHomeY = homeY;
    if (screenX == -1)
    {
        mScreenX = homeX;
    }
    else
    {
        mScreenX = screenX;
    }
    if (screenY == -1)
    {
        mScreenY = mHomeY;
    }
    else
    {
        mScreenY = screenY;
    }
    mDrawFirst = 0;
    mHide = 0;
    mDelay = 0;
}


/**
 * ScreenElement::~ScreenElement()
 *
 * Address:   0x8008A530
 * Mangled:   _._13ScreenElement
 *
 */
ScreenElement::~ScreenElement()
{
}


/**
 * ScreenElement::width(void)
 *
 * Address:   0x8008A560
 * Mangled:   width__13ScreenElement
 *            ASM: jr $ra; addiu $v0, $zero, -1
 *
 * @return -1 (pure-virtual-style placeholder width).
 */
int ScreenElement::width()
{
    return -1;
}


/**
 * ScreenElement::update(void)
 *
 * Address:   0x8008A568
 * Mangled:   update__13ScreenElement
 *            Interpolates screenX/Y toward homeX/Y, sets arrived flag when done
 */
void ScreenElement::update()
{
    int v = mDelay;
    if (v > 0)
    {
        mDelay = v - 1;
    }
    else
    {
        // Interpolate X
        int homeX = mHomeX;
        int screenX = mScreenX;
        int distX = homeX - screenX;
        if ((unsigned int)(distX + 1) < 3)
        {
            mScreenX = homeX;
        }
        else
        {
            int add = distX >> 2;
            if (add == 0)
            {
                add = distX >> 1;
            }
            mScreenX = screenX + add;
        }

        // Interpolate Y
        int homeY = mHomeY;
        int screenY = mScreenY;
        int distY = homeY - screenY;
        if ((unsigned int)(distY + 1) < 3)
        {
            mScreenY = homeY;
        }
        else
        {
            int add = distY >> 2;
            if (add == 0)
            {
                add = distY >> 1;
            }
            mScreenY = screenY + add;
        }

        // Check if arrived
        if (mScreenY != mHomeY)
        {
            goto not_at_home;
        }
        if (mScreenX != mHomeX)
        {
            goto not_at_home;
        }
        mAtHome = 1;
        return;
    not_at_home:
        mAtHome = 0;
    }
}


/**
 * ScreenElement::refresh(void)
 *
 * Address:   0x8008A630
 * Mangled:   refresh__13ScreenElement
 *            ASM: jr $ra; nop (no .s file — 2 instr empty function)
 */
void ScreenElement::refresh()
{
}


/**
 * ScreenElement::SnapToHomeX(void)
 *
 * Address:   0x8008A638
 * Mangled:   SnapToHomeX__13ScreenElement
 *            ASM: lw $v0, 4($a0); jr $ra; sw $v0, 0x1c($a0)
 */
void ScreenElement::SnapToHomeX()
{
    mScreenX = mHomeX;
}


/**
 * ScreenElement::GetScreenX(void)
 *
 * Address:   0x8008A644
 * Mangled:   GetScreenX__13ScreenElement
 *            ASM: lw $v0, 0x1c($a0); jr $ra; nop
 *
 * @return Current screen-space X coordinate.
 */
int ScreenElement::GetScreenX()
{
    return mScreenX;
}


/**
 * ScreenElement::GetScreenY(void)
 *
 * Address:   0x8008A650
 * Mangled:   GetScreenY__13ScreenElement
 *            ASM: lw $v0, 0x20($a0); jr $ra; nop
 *
 * @return Current screen-space Y coordinate.
 */
int ScreenElement::GetScreenY()
{
    return mScreenY;
}


/**
 * ScreenElementList::ScreenElementList(int, int, int, int)
 *
 * Address:   0x8008A65C
 * Mangled:   __17ScreenElementListiiii
 *            Constructor: calls parent ScreenElement ctor, clears 16 item slots, sets count=0
 *
 * @param self  `this` pointer (explicit — the class is kept vtable-free).
 * @param homeX  Home X coordinate (resting position).
 * @param homeY  Home Y coordinate (resting position).
 * @param screenX  Screen-space X coordinate.
 * @param screenY  Screen-space Y coordinate.
 * @return `this` pointer (GCC 2.x ctor convention).
 */
ScreenElementList::ScreenElementList(int homeX, int homeY, int screenX, int screenY)
    : ScreenElement(homeX, homeY, screenX, screenY)
{
    int i = 0;
    ScreenElement **ptr = mpItem;
    do
    {
        *ptr = 0;
        i++;
        ptr++;
    } while (i < 16);
    mCount = 0;
}


/**
 * ScreenElementList::~ScreenElementList()
 *
 * Address:   0x8008A6B8
 * Mangled:   _._17ScreenElementList
 *            Virtually destroys every remaining item (flags=3: dtor + free).
 *
 */
ScreenElementList::~ScreenElementList()
{
    int i = 0;
    ScreenElement **ptr = mpItem;
    do
    {
        delete *ptr;
        i++;
        ptr++;
    } while (i < 16);
}


/**
 * ScreenElementList::addItem(ScreenElement *)
 *
 * Address:   0x8008A760
 * Mangled:   addItem__17ScreenElementListP13ScreenElement
 *            Finds first empty slot in items array, stores item, increments count
 *
 * @param pScreenElement  ScreenElement to add to the list.
 */
void ScreenElementList::addItem(ScreenElement *pScreenElement)
{
    int i = 0;
    ScreenElement **ptr = mpItem;
    do
    {
        if (*ptr == 0)
        {
            *ptr = pScreenElement;
            mCount = mCount + 1;
            return;
        }
        i++;
        ptr++;
    } while (i < 16);
}


/**
 * ScreenElementList::update(void)
 *
 * Address:   0x8008A7A4
 * Mangled:   update__17ScreenElementList
 *            Calls each item's virtual update, then updates itself as a ScreenElement
 */
void ScreenElementList::update()
{
    int count = mCount;
    if (count > 0)
    {
        int i = 0;
        ScreenElement **ptr = mpItem;
        do
        {
            (*ptr)->update();
            ptr++;
            count = mCount;
            i++;
        } while (i < count);
    }
    ScreenElement::update();
}


/**
 * ScreenElementList::draw(int, int)
 *
 * Address:   0x8008A824
 * Mangled:   draw__17ScreenElementListii
 *            Virtually draws every item at the list's screen position plus offset
 *
 * @param x  X offset added to the list's screen position.
 * @param y  Y offset added to the list's screen position.
 */
void ScreenElementList::draw(int x, int y)
{
    if (mHide != 0) return;
    int count = mCount;
    if (count <= 0) return;
    int i = 0;
    ScreenElement **ptr = mpItem;
    do
    {
        ScreenElement *item = *ptr;
        ptr++;
        item->draw(mScreenX + x, mScreenY + y);
        count = mCount;
        i++;
    } while (i < count);
}


/**
 * TextScreenElement::TextScreenElement(char *, Font *, int, int, int, int)
 *
 * Address:   0x8008A8CC
 * Mangled:   __17TextScreenElementPcP4Fontiiii
 *            Constructor: calls parent ScreenElement ctor, allocates+copies string, stores font
 *
 * @param self  `this` pointer (explicit — the class is kept vtable-free).
 * @param pString  Text to display (copied into a fresh allocation).
 * @param pFont  Font used for rendering.
 * @param homeX  Home X coordinate (resting position).
 * @param homeY  Home Y coordinate (resting position).
 * @param screenX  Screen-space X coordinate.
 * @param screenY  Screen-space Y coordinate.
 * @return `this` pointer (GCC 2.x ctor convention).
 */
TextScreenElement::TextScreenElement(char *pString, Font *pFont, int homeX, int homeY, int screenX,
                                     int screenY)
    : ScreenElement(homeX, homeY, screenX, screenY)
{
    int len = strlen(pString);
    char *buf = (char *)Mem_New(len + 1, 0, 1);
    mpString = buf;
    strcpy(buf, pString);
    mpFont = pFont;
}


/**
 * TextScreenElement::~TextScreenElement()
 *
 * Address:   0x8008A958
 * Mangled:   _._17TextScreenElement
 *
 */
TextScreenElement::~TextScreenElement()
{
    Mem_Delete(mpString);
}


/**
 * TextScreenElement::setString(char *)
 *
 * Address:   0x8008A9B8
 * Mangled:   setString__17TextScreenElementPc
 *            Frees old string, allocates new, copies
 *
 * @param pString  Replacement text (copied into a fresh allocation).
 */
void TextScreenElement::setString(char *pString)
{
    Mem_Delete(mpString);
    int len = strlen(pString);
    char *buf = (char *)Mem_New(len + 1, 0, 1);
    mpString = buf;
    strcpy(buf, pString);
}


/**
 * TextScreenElement::draw(int, int)
 *
 * Address:   0x8008AA14
 * Mangled:   draw__17TextScreenElementii
 *            Draws the string via the font's virtual draw (slot 3), honoring delay/hide.
 *
 * @param x  X offset added to the element's screen position.
 * @param y  Y offset added to the element's screen position.
 */
void TextScreenElement::draw(int x, int y)
{
    if (mDelay > 0) return;
    if (mHide != 0) return;
    mpFont->draw(mScreenX + x, mScreenY + y, mpString, mDrawFirst);
}


/**
 * TextScreenElement::width(void)
 *
 * Address:   0x8008AA84
 * Mangled:   width__17TextScreenElement
 *            Calls Font::width with this->font and this->string
 *
 * @return Rendered width of the string in the element's font.
 */
int TextScreenElement::width()
{
    return mpFont->width(mpString);
}


/**
 * SpriteScreenElement::SpriteScreenElement(char *, int, int, int, int, int, int)
 *
 * Address:   0x8008AAB0
 * Mangled:   __19SpriteScreenElementPciiiiii
 *            Constructor: calls parent ScreenElement ctor, allocates the Sprite2,
 *            stores it, then sets its justification bytes.
 *
 * @param self  `this` pointer (explicit — the class is kept vtable-free).
 * @param pFileName  Sprite image file name.
 * @param homeX  Home X coordinate (resting position).
 * @param homeY  Home Y coordinate (resting position).
 * @param screenX  Screen-space X coordinate.
 * @param screenY  Screen-space Y coordinate.
 * @param justY  Vertical justification byte for the sprite image.
 * @param justX  Horizontal justification byte for the sprite image.
 * @return `this` pointer (GCC 2.x ctor convention).
 */
SpriteScreenElement::SpriteScreenElement(char *pFileName, int homeX, int homeY, int screenX,
                                         int screenY, int justY, int justX)
    : ScreenElement(homeX, homeY, screenX, screenY)
{
    mSprite = new Sprite2(pFileName, 1, 64, 64);
    mSprite->JustY = (char)justY;
    mSprite->JustX = (char)justX;
}


/**
 * SpriteScreenElement::~SpriteScreenElement()
 *
 * Address:   0x8008AB48
 * Mangled:   _._19SpriteScreenElement
 *            Virtually destroys the owned sprite (flags=3: dtor + free).
 *
 */
SpriteScreenElement::~SpriteScreenElement()
{
    delete mSprite;
}


/**
 * SpriteScreenElement::draw(int, int)
 *
 * Address:   0x8008ABC0
 * Mangled:   draw__19SpriteScreenElementii
 *            Draws the sprite via its virtual draw (slot 5), honoring delay/hide.
 *
 * @param x  X offset added to the element's screen position.
 * @param y  Y offset added to the element's screen position.
 */
void SpriteScreenElement::draw(int x, int y)
{
    if (mDelay > 0) return;
    if (mHide != 0) return;
    mSprite->draw(mScreenX + x, mScreenY + y, mDrawFirst);
}


/**
 * SpriteScreenElement::width(void)
 *
 * Address:   0x8008AC2C
 * Mangled:   width__19SpriteScreenElement
 *            Returns the sprite's screen width via its SlicedImage2 base.
 *
 * @return On-screen width of the owned sprite.
 */
// Shared SpriteScreenElement member function
int SpriteScreenElement::width()
{
    return mSprite->screenWidth();
}
