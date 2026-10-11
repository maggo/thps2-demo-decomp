// Per-TU header for MENU.cpp
// Class definitions reconstructed from This Dust Remembers MAIN.H
#ifndef MENU_ABI_DECLARATIONS_ONLY
#ifndef MENU_INC_H
#define MENU_INC_H

#ifdef __cplusplus
extern "C" {
#endif

// Primitive types
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

#ifdef __cplusplus
}
#endif

// Forward declarations
class SlicedImage2;

// ============================================================
// CClass -- root base class (polymorphic: virtual destructor, vtable pointer
// only).  MENU.cpp includes CCLASS_POLY.h first so the compiler emits every
// dispatch table of the classes below itself.
// ============================================================
#include "CCLASS_POLY.h"
// Font is seen through its natural polymorphic layout (virtual dtor/draw), so
// `Props.TheFont = *font` is the compiler's vtable-preserving assignment.
#define FONTTOOLS_POLYMORPHIC_LAYOUT
#include "FONTTOOLS.h"
#undef FONTTOOLS_POLYMORPHIC_LAYOUT

// Classes are declared in the original MENU.H order: the compiler emits the
// vtables (.rdata) and the out-of-line copies of the inline members (end of
// .text) in reverse declaration order.

// ============================================================
// MenuItem -- base menu item
// Size: 0x28 (40 bytes)
// ============================================================
class MenuItem : public CClass {
public:
    MenuItem(int id);
    virtual ~MenuItem();
    virtual void setXY(int x, int y) {}
    virtual void draw() {}
    virtual void setHighlightState(bool highlight_state);
    virtual void setItemState(int state);
    virtual void processPress(int press);
    virtual void update();

    int ID;                 // 0x04
    int Selectable;         // 0x08
    int Choosable;          // 0x0C
    int Highlighted;        // 0x10
    int InternalState;      // 0x14
    int W;                  // 0x18
    int H;                  // 0x1C
    int X;                  // 0x20
    int Y;                  // 0x24
};

// ============================================================
// VMenuItem -- menu item with justification
// Size: 0x2C (44 bytes)
// ============================================================
class VMenuItem : public MenuItem {
public:
    VMenuItem(int id);

    int JustX;              // 0x28
};

// ============================================================
// BasicMenu -- base menu container with item array
// Size: 0x68 (104 bytes)
// ============================================================
class BasicMenu : public CClass {
public:
    virtual ~BasicMenu() {}
    virtual void setArrows(SlicedImage2 *left, SlicedImage2 *right, int spacing);
    virtual void activate() {}
    virtual void draw() {}
    virtual void update() {}
    virtual void processPress(int press) {}
    virtual void addItem(VMenuItem *item) {}
    int getHighlighted();
    void setHighlighted(int id);

    SlicedImage2 *LeftArrow;  // 0x04
    SlicedImage2 *RightArrow; // 0x08
    int ArrowSpace;         // 0x0C
    VMenuItem *Item[16];    // 0x10 -- array of 16 pointers (0x40 bytes)
    int HighestSlot;        // 0x50
    int Selected;           // 0x54
    int X;                  // 0x58
    int Y;                  // 0x5C
    int W;                  // 0x60
    int H;                  // 0x64
};

// ============================================================
// TextMenuProperties -- font + color configuration for menus
// Size: 0x80 (128 bytes)
// ============================================================
struct TextMenuProperties : public CClass {
    TextMenuProperties();
    Font TheFont;           // 0x04
    int BigScale;           // 0x54
    int NormalScale;        // 0x58
    int SelectedR;          // 0x5C
    int SelectedG;          // 0x60
    int SelectedB;          // 0x64
    int NormalR;             // 0x68
    int NormalG;             // 0x6C
    int NormalB;             // 0x70
    int GrayR;              // 0x74
    int GrayG;              // 0x78
    int GrayB;              // 0x7C
};

// ============================================================
// TextMenuItem -- text-based menu item
// Size: 0x50 (80 bytes)
// ============================================================
class TextMenuItem : public VMenuItem {
public:
    TextMenuItem(int id, const char *text, TextMenuProperties &properties);
    ~TextMenuItem();
    void setXY(int x, int y);
    void draw();

    char Text[32];          // 0x2C
    TextMenuProperties *TheProperties; // 0x4C
};

// ============================================================
// TitleMenuItem -- title text menu item (no new fields)
// Size: 0x50 (80 bytes)
// ============================================================
class TitleMenuItem : public TextMenuItem {
public:
    TitleMenuItem(int id, const char *text, TextMenuProperties &properties);
    void draw();
};

// ============================================================
// SelectMenuItem -- selection menu item with multiple options
// Size: 0x100 (256 bytes)
// ============================================================
class SelectMenuItem : public VMenuItem {
public:
    ~SelectMenuItem();
    void setXY(int x, int y);
    void draw();
    void processPress(int press);

    int AmHighlighted;      // 0x2C
    char Option[6][32];     // 0x30 -- 6 options, 32 chars each (0xC0 bytes)
    int NumOptions;         // 0xF0
    int Spacing;            // 0xF4
    TextMenuProperties *TheProperties; // 0xF8
    int SmallW;             // 0xFC
};

// ============================================================
// VerticalMenu2 -- vertical menu layout
// Size: 0x74 (116 bytes)
// ============================================================
class VerticalMenu2 : public BasicMenu {
public:
    VerticalMenu2(int x, int y, int w, int h, int just_x, int just_y,
                  int spacing);
    ~VerticalMenu2();
    void activate();
    void draw();
    void update();
    void processPress(int press);
    void addItem(VMenuItem *item);

    int JustX;              // 0x68
    int JustY;              // 0x6C
    int Spacing;            // 0x70
};

// ============================================================
// ScrollingMenu2 -- scrolling menu layout
// Size: 0xB8 (184 bytes)
// ============================================================
class ScrollingMenu2 : public BasicMenu {
public:
    ScrollingMenu2(int x, int y, int w, int h, int just_x, int slide_amount);
    ~ScrollingMenu2();
    void activate();
    void draw();
    void update();
    void processPress(int press);
    void addItem(VMenuItem *item);

    int JustX;              // 0x68
    int RY[16];             // 0x6C -- render Y offsets (0x40 bytes)
    int ArrowSlide;         // 0xAC
    int Top;                // 0xB0
    int Bottom;             // 0xB4
};

// ============================================================
// MenuWrapper -- base wrapper for menu systems
// Size: 0x0C (12 bytes)
// ============================================================
class MenuWrapper : public CClass {
public:
    virtual ~MenuWrapper() {}
    virtual void HandleInput() {}
    virtual int TestComplete() {}
    virtual int GetHighlightedId();

    BasicMenu *Menu;        // 0x04
    int HighlightedId;      // 0x08
};

// ============================================================
// TextMenuWrapper -- complete text menu system
// Size: 0x110 (272 bytes)
// ============================================================
class TextMenuWrapper : public MenuWrapper {
public:
    TextMenuWrapper(char *const *string_list, int *id_list, int num_items,
                    char *font_name, bool use_scrolling_menu);
    ~TextMenuWrapper();
    void HandleInput();
    int TestComplete();

    TextMenuProperties Props; // 0x0C -- embedded (0x80 bytes)
    VMenuItem *ItemList[32];  // 0x8C -- array of 32 pointers (0x80 bytes)
    int NumItems;             // 0x10C
};

typedef char menu_font_size_must_be_80[(sizeof(Font) == 80) ? 1 : -1];
typedef char menu_properties_size_must_be_128[(sizeof(TextMenuProperties) == 128) ? 1 : -1];
typedef char menu_item_size_must_be_40[(sizeof(MenuItem) == 40) ? 1 : -1];
typedef char menu_vertical_item_size_must_be_44[(sizeof(VMenuItem) == 44) ? 1 : -1];
typedef char menu_text_item_size_must_be_80[(sizeof(TextMenuItem) == 80) ? 1 : -1];
typedef char menu_select_item_size_must_be_256[(sizeof(SelectMenuItem) == 256) ? 1 : -1];
typedef char menu_basic_size_must_be_104[(sizeof(BasicMenu) == 104) ? 1 : -1];
typedef char menu_vertical_size_must_be_116[(sizeof(VerticalMenu2) == 116) ? 1 : -1];
typedef char menu_scrolling_size_must_be_184[(sizeof(ScrollingMenu2) == 184) ? 1 : -1];
typedef char menu_wrapper_size_must_be_12[(sizeof(MenuWrapper) == 12) ? 1 : -1];
typedef char menu_text_wrapper_size_must_be_272[(sizeof(TextMenuWrapper) == 272) ? 1 : -1];

#endif // MENU_INC_H
#endif // MENU_ABI_DECLARATIONS_ONLY

#ifdef MENU_DECLARE_TEXT_WRAPPER_CONSTRUCTOR_ABI
#ifndef MENU_TEXT_WRAPPER_CONSTRUCTOR_RECEIVER
#error "Select the TextMenuWrapper constructor ABI receiver type"
#endif

/** Construct a text-menu wrapper through its target C-linkage entry. */
extern "C" MENU_TEXT_WRAPPER_CONSTRUCTOR_RECEIVER *
__15TextMenuWrapperPCPcPiiPcb(
    MENU_TEXT_WRAPPER_CONSTRUCTOR_RECEIVER *, const char **, int *, int,
    const char *, bool);

#undef MENU_TEXT_WRAPPER_CONSTRUCTOR_RECEIVER
#undef MENU_DECLARE_TEXT_WRAPPER_CONSTRUCTOR_ABI
#endif

