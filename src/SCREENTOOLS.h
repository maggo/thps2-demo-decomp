// Shared owner header for SCREENTOOLS.cpp.
// This target-proven ABI/layout surface is hand-maintained; do not regenerate blindly.

/*
 * Natural polymorphic screen-element family (vt4).  A TU that defines
 * SCREENTOOLS_POLYMORPHIC_LAYOUT before the first include gets the real class
 * hierarchy derived from CCLASS_POLY.h's CClass, together with the polymorphic
 * Font (FONTTOOLS.h), FrontPreLoader (FRONTPRE.h) and Image/Sprite2 (IMAGE.h)
 * models it needs: GCC then emits the owner's dispatch tables and destructors
 * itself.  Slot order from the target tables (__vt_13ScreenElement ...):
 *   [0] ~  [1] update  [2] draw(int,int) (pure in ScreenElement)  [3] width  [4] refresh
 * SCREENTOOLS.cpp owns ScreenElement, TextScreenElement, SpriteScreenElement and
 * ScreenElementList (declared in that order: the exe has their tables in
 * reverse declaration order, ScreenElementList first).
 */
#if defined(SCREENTOOLS_POLYMORPHIC_LAYOUT) && \
    !defined(SCREENTOOLS_POLYMORPHIC_LAYOUT_EMITTED)
#define SCREENTOOLS_POLYMORPHIC_LAYOUT_EMITTED
#define SCREENTOOLS_AGGREGATE_LAYOUT_EMITTED /* the POD views are superseded */

#include "CCLASS_POLY.h"
#define FONTTOOLS_POLYMORPHIC_LAYOUT
#include "FONTTOOLS.h"
#define FRONTPRE_POLYMORPHIC_LAYOUT
#include "FRONTPRE.h"
#define IMAGE_POLYMORPHIC_LAYOUT
#include "IMAGE.h"

/** Base drawable of the front-end screen hierarchy. */
struct ScreenElement : CClass {
    int mHomeX;
    int mHomeY;
    int mDrawFirst;
    int mHide;
    int mDelay;
    void *mAtHome;
    int mScreenX;
    int mScreenY;

    ScreenElement(int homeX, int homeY, int screenX, int screenY);
    virtual ~ScreenElement();
    /** Advance this element toward its home position. */
    virtual void update();
    /** Draw this element at the supplied parent offset. */
    virtual void draw(int x, int y) = 0;
    /** Return this element's drawable width. */
    virtual int width();
    /** Notify this element that its displayed content changed. */
    virtual void refresh();

    /** Return the current screen-space X coordinate. */
    int GetScreenX();
    /** Return the current screen-space Y coordinate. */
    int GetScreenY();
    /** Move the screen-space X coordinate directly to its home position. */
    void SnapToHomeX();
};

/** Text-bearing screen element. */
struct TextScreenElement : ScreenElement {
    char *mpString;
    Font *mpFont;

    TextScreenElement(char *text, Font *font, int homeX, int homeY,
                      int screenX, int screenY);
    virtual ~TextScreenElement();
    /** Replace the owned display string with a copy of the supplied text. */
    void setString(char *text);
    void draw(int x, int y);
    int width();
};

/** Sprite-bearing screen element. */
struct SpriteScreenElement : ScreenElement {
    Sprite2 *mSprite;

    SpriteScreenElement(char *fileName, int homeX, int homeY, int screenX,
                        int screenY, int justY, int justX);
    virtual ~SpriteScreenElement();
    void draw(int x, int y);
    int width();
};

/** Fixed-capacity list of elements used by composite front-end screens. */
struct ScreenElementList : ScreenElement {
    ScreenElement *mpItem[16];
    int mCount;

    ScreenElementList(int homeX, int homeY, int screenX, int screenY);
    virtual ~ScreenElementList();
    void update();
    void draw(int x, int y);
    /** Add one element to the first unused list slot. */
    void addItem(ScreenElement *element);
};

typedef char frontend_screen_element_size_must_be_36[
    (sizeof(ScreenElement) == 36) ? 1 : -1];
typedef char frontend_screen_element_list_size_must_be_104[
    (sizeof(ScreenElementList) == 104) ? 1 : -1];
typedef char frontend_text_screen_element_size_must_be_44[
    (sizeof(TextScreenElement) == 44) ? 1 : -1];
typedef char frontend_sprite_screen_element_size_must_be_40[
    (sizeof(SpriteScreenElement) == 40) ? 1 : -1];

#endif // SCREENTOOLS_POLYMORPHIC_LAYOUT

/*
 * Target-proven aggregate ABI/storage views shared by the four menu owners.
 * These POD prefixes model embedding and field offsets only; SCREENTOOLS.cpp
 * retains the natural inherited class identities that own their methods and
 * vtables.  The block is deliberately re-entrant so a menu TU can request the
 * storage views before including the ordinary API later in its source.
 */
#if defined(SCREENTOOLS_AGGREGATE_LAYOUT) && \
    !defined(SCREENTOOLS_AGGREGATE_LAYOUT_EMITTED)
#define SCREENTOOLS_AGGREGATE_LAYOUT_EMITTED

#include "FONTTOOLS.h"
#include "FRONTPRE.h"
#include "globals.h"

struct Sprite2;

/** Base drawable storage used by the front-end screen hierarchy. */
struct ScreenElement {
    struct CClass CClass;
    int mHomeX;
    int mHomeY;
    int mDrawFirst;
    int mHide;
    int mDelay;
    void *mAtHome;
    int mScreenX;
    int mScreenY;

    /** Return the current screen-space X coordinate. */
    int GetScreenX();
    /** Return the current screen-space Y coordinate. */
    int GetScreenY();
    /** Advance this element toward its home position. */
    void update();
    /** Move the screen-space X coordinate directly to its home position. */
    void SnapToHomeX();
    /** Return this element's drawable width. */
    int width();
    /** Notify this element that its displayed content changed. */
    void refresh();
};

/** Fixed-capacity aggregate list used by composite front-end screens. */
struct ScreenElementList {
    struct ScreenElement ScreenElement;
    struct ScreenElement *mpItem[16];
    int mCount;

    /** Update every active element in the list. */
    void update();
    /** Draw every active element at the supplied parent offset. */
    void draw(int x, int y);
    /** Add one element to the first unused list slot. */
    void addItem(struct ScreenElement *element);
};

/** Text-bearing screen-element storage. */
struct TextScreenElement {
    struct ScreenElement ScreenElement;
    char *mpString;
    struct Font *mpFont;

    /** Replace the owned display string with a copy of the supplied text. */
    void setString(char *text);
    /** Return the rendered width of the owned string. */
    int width();
};

/** Sprite-bearing screen-element storage. */
struct SpriteScreenElement {
    struct ScreenElement ScreenElement;
    struct Sprite2 *mSprite;
};

typedef char frontend_screen_element_size_must_be_36[
    (sizeof(ScreenElement) == 36) ? 1 : -1];
typedef char frontend_screen_element_list_size_must_be_104[
    (sizeof(ScreenElementList) == 104) ? 1 : -1];
typedef char frontend_text_screen_element_size_must_be_44[
    (sizeof(TextScreenElement) == 44) ? 1 : -1];
typedef char frontend_sprite_screen_element_size_must_be_40[
    (sizeof(SpriteScreenElement) == 40) ? 1 : -1];

#endif // SCREENTOOLS_AGGREGATE_LAYOUT

/*
 * Re-entrant lifecycle ABI selectors.  Define only the declarations needed at
 * a call site's original declaration point, then include this header.  The
 * selectors clear themselves so later includes can preserve declaration order.
 */
#if defined(SCREENTOOLS_DECLARE_SCREEN_ELEMENT_CONSTRUCTOR)
struct ScreenElement;
extern "C" ScreenElement *__13ScreenElementiiii(
    ScreenElement *element, int homeX, int homeY, int screenX, int screenY);
#undef SCREENTOOLS_DECLARE_SCREEN_ELEMENT_CONSTRUCTOR
#endif

#if defined(SCREENTOOLS_DECLARE_SCREEN_ELEMENT_LIST_CONSTRUCTOR)
struct ScreenElementList;
extern "C" ScreenElementList *__17ScreenElementListiiii(
    ScreenElementList *list, int homeX, int homeY, int screenX, int screenY);
#undef SCREENTOOLS_DECLARE_SCREEN_ELEMENT_LIST_CONSTRUCTOR
#endif

#if defined(SCREENTOOLS_DECLARE_TEXT_MENU_PROPERTIES_CONSTRUCTOR)
struct TextMenuProperties;
namespace TextMenuPropertiesConstructorABI
{
/** Construct the shared menu-text style in caller-owned storage. */
extern "C" TextMenuProperties *__18TextMenuProperties(
    TextMenuProperties *properties);
}
#undef SCREENTOOLS_DECLARE_TEXT_MENU_PROPERTIES_CONSTRUCTOR
#endif

#if defined(SCREENTOOLS_DECLARE_TEXT_MENU_ITEM_CONSTRUCTOR)
struct VMenuItem;
struct TextMenuProperties;
namespace TextMenuItemConstructorABI
{
/** Construct a text menu item in caller-owned storage. */
extern "C" VMenuItem *__12TextMenuItemiPCcR18TextMenuProperties(
    VMenuItem *item, int id, char *text, TextMenuProperties *properties);
}
#undef SCREENTOOLS_DECLARE_TEXT_MENU_ITEM_CONSTRUCTOR
#endif

#if defined(SCREENTOOLS_DECLARE_VERTICAL_MENU2_CONSTRUCTOR)
struct VerticalMenu2;
namespace VerticalMenu2ConstructorABI
{
/** Construct a shared vertical menu in caller-owned storage. */
extern "C" VerticalMenu2 *__13VerticalMenu2iiiiiii(
    VerticalMenu2 *menu, int x, int y, int width, int height,
    int justX, int justY, int spacing);
}
#undef SCREENTOOLS_DECLARE_VERTICAL_MENU2_CONSTRUCTOR
#endif

#if defined(SCREENTOOLS_DECLARE_TEXT_SCREEN_ELEMENT_CONSTRUCTOR)
struct TextScreenElement;
struct Font;
extern "C" TextScreenElement *__17TextScreenElementPcP4Fontiiii(
    TextScreenElement *element, char *text, Font *font,
    int homeX, int homeY, int screenX, int screenY);
#undef SCREENTOOLS_DECLARE_TEXT_SCREEN_ELEMENT_CONSTRUCTOR
#endif

#if defined(SCREENTOOLS_DECLARE_SPRITE_SCREEN_ELEMENT_CONSTRUCTOR)
struct SpriteScreenElement;
extern "C" SpriteScreenElement *__19SpriteScreenElementPciiiiii(
    SpriteScreenElement *element, char *fileName,
    int homeX, int homeY, int screenX, int screenY, int justY, int justX);
#undef SCREENTOOLS_DECLARE_SPRITE_SCREEN_ELEMENT_CONSTRUCTOR
#endif

#ifndef SCREENTOOLS_AGGREGATE_LAYOUT_ONLY
#ifndef SCREENTOOLS_INC_H
#define SCREENTOOLS_INC_H

struct ScreenElement;
struct TextScreenElement;

#ifdef SCREENTOOLS_OWNER_DECLARATIONS

#ifdef __cplusplus
extern "C" {
#endif

// Additional shared forward declarations
struct CBit;
struct CGlow;
struct CSpecialDisplay;
struct CFlatBit;
struct Font;
struct TextEffect;
struct FontManager;
struct RailPoint;
struct SCardHead;
struct SCamera;
struct STexWibVertInfo;
struct SViewport;
struct SColCache;
struct SLineInfo;
struct STexWibItemInfo;
struct SBlockHeader;
struct ControllerData;

#ifdef __cplusplus
}
#endif

#endif // SCREENTOOLS_OWNER_DECLARATIONS

#endif // SCREENTOOLS_INC_H
#endif // SCREENTOOLS_AGGREGATE_LAYOUT_ONLY
