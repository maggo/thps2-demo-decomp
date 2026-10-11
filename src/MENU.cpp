// MENU.cpp -- Reconstructed translation unit
// Original: MENU.CPP
// Functions: 56 reconstructed entries
// Address range: 0x80087A98 - 0x80089824
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.


#include "PSX.h"
#include "MENU.h"

struct Slice;

// Image's composed CClass holder (the natural polymorphic CClass is taken by
// MENU's own classes; SlicedImage2 keeps the bare-vtable layout of IMAGE).
#define CClass CClassData
#include "IMAGEBASE.h"
#undef CClass

/** Sliced image used for the optional menu arrows. */
struct SlicedImage2 : Image
{
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

PSX_LAYOUT_CHECK(menu_image_size_must_be_28, sizeof(Image) == 28);
PSX_LAYOUT_CHECK(menu_sliced_image_size_must_be_60, sizeof(SlicedImage2) == 60);

#include "SFX.h"
#include "PAD.h"


class ScrollingMenu2;

inline void *operator new(unsigned int, void *p)
{
    return p;
}

#include <STDIO.H>
#include <STRINGS.H>
#define CClass CClassData
#include "IMAGE.h"
#undef CClass

/** MENU diagnostic text (read-only data, ahead of the compiler's vtables). */
static char processPress_fmt[24] PSX_SECTION_ALIGNED(".rdata", 4) = "Highlighted is %d\n";

// === Function implementations (address order) ===

/**
 * Menu_GetPress__Fv
 *
 * Address:   0x80087A98
 * Mangled:   Menu_GetPress__Fv
 * Demangled: Menu_GetPress(void)
 *
 * @return result
 */
int Menu_GetPress(void)
{
    SControl *pad = &Pad[0];
    int press = -1;
    if (pad->Left.Triggered != 0)
    {
        pad->Left.Triggered = 0;
        press = 0;
        goto done;
    }
    if (pad->Right.Triggered != 0)
    {
        pad->Right.Triggered = 0;
        press = 1;
        goto done;
    }
    if (pad->Up.Triggered != 0)
    {
        pad->Up.Triggered = 0;
        press = 2;
        goto done;
    }
    if (pad->Down.Triggered != 0)
    {
        pad->Down.Triggered = 0;
        press = 3;
    }
done:
    return press;
}


/**
 *
 * Address:   0x80087B14
 * Mangled:   __8MenuItemi
 * Demangled: MenuItem::MenuItem(int)
 *
 * @param id  Identifier.
 */
MenuItem::MenuItem(int id)
{
    this->ID = id;
}


/**
 *
 * Address:   0x80087B2C
 * Mangled:   _._8MenuItem
 * Demangled: MenuItem::~MenuItem()
 */
MenuItem::~MenuItem()
{
}


/**
 *
 * Address:   0x80087B5C
 * Mangled:   setHighlightState__8MenuItemb
 * Demangled: MenuItem::setHighlightState(bool)
 *
 * @param highlight_state  New highlight state.
 */
void MenuItem::setHighlightState(bool highlight_state)
{
    this->Highlighted = highlight_state;
}


/**
 *
 * Address:   0x80087B64
 * Mangled:   setItemState__8MenuItemi
 * Demangled: MenuItem::setItemState(int)
 *
 * @param state  New interaction state for the item.
 */
void MenuItem::setItemState(int state)
{
    this->InternalState = state;
}


/**
 *
 * Address:   0x80087B6C
 * Mangled:   processPress__8MenuItemi
 * Demangled: MenuItem::processPress(int)
 *
 * @param press  Button press code.
 */
void MenuItem::processPress(int press)
{
    printf(processPress_fmt, this->Highlighted);
}


/**
 *
 * Address:   0x80087B94
 * Mangled:   update__8MenuItem
 * Demangled: MenuItem::update(void)
 */
void MenuItem::update()
{
}


/**
 *
 * Address:   0x80087B9C
 * Mangled:   __9VMenuItemi
 * Demangled: VMenuItem::VMenuItem(int)
 *
 */
VMenuItem::VMenuItem(int id) : MenuItem(id)
{
}


/**
 *
 * Address:   0x80087BD0
 * Mangled:   GetHighlightedId__11MenuWrapper
 * Demangled: MenuWrapper::GetHighlightedId(void)
 *
 * @return Identifier cached for the highlighted menu item.
 */
int MenuWrapper::GetHighlightedId()
{
    return this->HighlightedId;
}


/**
 *
 * Address:   0x80087BDC
 * Mangled:   __18TextMenuProperties
 * Demangled: TextMenuProperties::TextMenuProperties(void)
 */
TextMenuProperties::TextMenuProperties()
{
    this->BigScale = 0x1324;
    this->NormalScale = 0x1000;
    this->SelectedR = 0xB6;
    this->SelectedG = 0x84;
    this->SelectedB = 0x24;
    this->NormalR = 0x7A;
    this->NormalG = 0x7A;
    this->NormalB = 0x7A;
    this->GrayR = 0x40;
    this->GrayG = 0x40;
    this->GrayB = 0x40;
}


/**
 *
 * Address:   0x80087C58
 * Mangled:   __12TextMenuItemiPCcR18TextMenuProperties
 * Demangled: TextMenuItem::TextMenuItem(int, const char *, TextMenuProperties &)
 *
 * @param id  Identifier.
 * @param text  Label displayed by the item.
 * @param properties  Shared font and styling properties.
 */
TextMenuItem::TextMenuItem(int id, const char *text, TextMenuProperties &properties) : VMenuItem(id)
{
    strcpy(Text, text);
    ID = id;
    TheProperties = &properties;
    Selectable = 1;
    Choosable = 1;
    properties.TheFont.Scale = properties.BigScale;
    int w = TheProperties->TheFont.width(Text);
    W = w;
    int h = TheProperties->TheFont.height(Text);
    H = h;
}


/**
 *
 * Address:   0x80087D10
 * Mangled:   _._12TextMenuItem
 * Demangled: TextMenuItem::~TextMenuItem()
 */
TextMenuItem::~TextMenuItem()
{
}


/**
 *
 * Address:   0x80087D64
 * Mangled:   setXY__12TextMenuItemii
 * Demangled: TextMenuItem::setXY(int, int)
 *
 * @param x  X coordinate.
 * @param y  Y coordinate.
 */
void TextMenuItem::setXY(int x, int y)
{
    this->X = x;
    this->Y = y;
}


/**
 * Draws a text menu item with the current selection and disabled-state styling.
 *
 * Address:   0x80087D70
 * Mangled:   draw__12TextMenuItem
 * Demangled: TextMenuItem::draw(void)
 *
 */
void TextMenuItem::draw()
{
    TextMenuProperties *props = TheProperties;
    props->TheFont.JustX = JustX;
    TextMenuProperties *props2 = TheProperties;
    props2->TheFont.JustY = 1;
    TextMenuProperties *font = TheProperties;
    font->TheFont.Scale = font->NormalScale;
    if (Selectable == 0)
    {
        TextMenuProperties *p = TheProperties;
        p->TheFont.R = p->GrayR;
        TextMenuProperties *p2 = TheProperties;
        p2->TheFont.G = p2->GrayG;
        TextMenuProperties *p3 = TheProperties;
        p3->TheFont.B = p3->GrayB;
    }
    else if (Highlighted == 0)
    {
        TextMenuProperties *p = TheProperties;
        p->TheFont.R = p->NormalR;
        TextMenuProperties *p2 = TheProperties;
        p2->TheFont.G = p2->NormalG;
        TextMenuProperties *p3 = TheProperties;
        p3->TheFont.B = p3->NormalB;
    }
    else
    {
        TextMenuProperties *p = TheProperties;
        p->TheFont.Scale = p->BigScale;
        TextMenuProperties *p2 = TheProperties;
        p2->TheFont.R = p2->SelectedR;
        TextMenuProperties *p3 = TheProperties;
        p3->TheFont.G = p3->SelectedG;
        TextMenuProperties *p4 = TheProperties;
        p4->TheFont.B = p4->SelectedB;
    }
    if (TheProperties->TheFont.JustX == 1)
    {
        TheProperties->TheFont.draw(X + (W >> 1), Y + (H >> 1), Text, 0);
    }
    else
    {
        TheProperties->TheFont.draw(X, Y + (H >> 1), Text, 0);
    }
}


/**
 *
 * Address:   0x80087F0C
 * Mangled:   __13TitleMenuItemiPCcR18TextMenuProperties
 * Demangled: TitleMenuItem::TitleMenuItem(int, const char *, TextMenuProperties &)
 *
 * @param id  Identifier.
 * @param text  Label displayed by the title.
 * @param properties  Shared font and styling properties.
 */
TitleMenuItem::TitleMenuItem(int id, const char *text, TextMenuProperties &properties)
    : TextMenuItem(id, text, properties)
{
    Selectable = 0;
    int h = H;
    h = h + (h >> 1);
    H = h;
}


/**
 * Draws a title menu item with the selected title color and scale.
 *
 * Address:   0x80087F54
 * Mangled:   draw__13TitleMenuItem
 * Demangled: TitleMenuItem::draw(void)
 *
 */
void TitleMenuItem::draw()
{
    TextMenuProperties *props = TheProperties;
    props->TheFont.JustX = JustX;
    TextMenuProperties *props2 = TheProperties;
    props2->TheFont.JustY = 1;
    TextMenuProperties *fnt = TheProperties;
    fnt->TheFont.Scale = fnt->NormalScale;
    TextMenuProperties *p2 = TheProperties;
    p2->TheFont.R = p2->SelectedR;
    TextMenuProperties *p3 = TheProperties;
    p3->TheFont.G = p3->SelectedG;
    TextMenuProperties *p4 = TheProperties;
    p4->TheFont.B = p4->SelectedB;
    if (TheProperties->TheFont.JustX == 1)
    {
        TheProperties->TheFont.draw(X + (W >> 1), Y + (H >> 1), Text, 0);
    }
    else
    {
        TheProperties->TheFont.draw(X, Y + (H >> 1), Text, 0);
    }
}


/**
 *
 * Address:   0x80088044
 * Mangled:   _._14SelectMenuItem
 * Demangled: SelectMenuItem::~SelectMenuItem()
 */
SelectMenuItem::~SelectMenuItem()
{
}


/**
 *
 * Address:   0x80088098
 * Mangled:   setXY__14SelectMenuItemii
 * Demangled: SelectMenuItem::setXY(int, int)
 *
 * @param x  X coordinate.
 * @param y  Y coordinate.
 */
void SelectMenuItem::setXY(int x, int y)
{
    X = x;
    Y = y;
}


/**
 * Match the original PSX draw-path shape so register allocation stays honest.
 * draw__14SelectMenuItem
 *
 * Address:   0x800880A4
 * Mangled:   draw__14SelectMenuItem
 * Demangled: SelectMenuItem::draw(void)
 *            Reuses the scale local as the denominator to mirror the original draw register lifetime.
 *
 */
void SelectMenuItem::draw(void)
{
    TextMenuProperties *props = TheProperties;
    props->TheFont.JustX = 0;
    TextMenuProperties *props2 = TheProperties;
    props2->TheFont.JustY = 1;
    if (Highlighted != 0)
    {
        TextMenuProperties *p = TheProperties;
        p->TheFont.Scale = p->BigScale;
    }
    else
    {
        TextMenuProperties *p = TheProperties;
        p->TheFont.Scale = p->NormalScale;
    }
    int x;
    if (JustX == 1 && AmHighlighted == 0)
    {
        int scale = (int)TheProperties;
        int w = W;
        int scaled = w * ((TextMenuProperties *)scale)->NormalScale;
        scale = ((TextMenuProperties *)scale)->BigScale;
        scaled = scaled / scale;
        x = X + (w >> 1) - (scaled >> 1);
    }
    else
    {
        x = X;
    }
    int count = NumOptions;
    if (count > 0)
    {
        int i = 0;
        char *str = Option[0];
        do
        {
            TextMenuProperties *p = TheProperties;
            if (i == 0 || i == InternalState)
            {
                if (Highlighted != 0)
                {
                    p->TheFont.R = p->SelectedR;
                    TextMenuProperties *p2 = TheProperties;
                    p2->TheFont.G = p2->SelectedG;
                    TextMenuProperties *p3 = TheProperties;
                    p3->TheFont.B = p3->SelectedB;
                }
                else
                {
                    p->TheFont.R = p->NormalR;
                    TextMenuProperties *p2 = TheProperties;
                    p2->TheFont.G = p2->NormalG;
                    TextMenuProperties *p3 = TheProperties;
                    p3->TheFont.B = p3->NormalB;
                }
            }
            else
            {
                p->TheFont.R = p->GrayR;
                TextMenuProperties *p2 = TheProperties;
                p2->TheFont.G = p2->GrayG;
                TextMenuProperties *p3 = TheProperties;
                p3->TheFont.B = p3->GrayB;
            }
            TextMenuProperties *fnt = TheProperties;
            int h = H;
            int y = Y;
            fnt->TheFont.draw(x, y + (h >> 1), str, 0);
            i++;
            TextMenuProperties *fnt2 = TheProperties;
            x += fnt2->TheFont.width(str);
            str += 0x20;
        } while (i < NumOptions);
    }
}

/**
 * Process a directional press while this selectable item is highlighted.
 *
 * Address:   0x800882C0
 * Mangled:   processPress__14SelectMenuItemi
 * Demangled: SelectMenuItem::processPress(int)
 *
 * @param press  Button press code.
 */
void SelectMenuItem::processPress(int press)
{
    if (Highlighted == 0) return;
    if (press != 0) goto up;
    {
        int state = InternalState - 1;
        InternalState = state;
        if (state > 0) return;
        int wrap = NumOptions - 1;
        InternalState = wrap;
        return;
    }
up:
    if (press != 1) return;
    {
        int state = InternalState;
        int max = NumOptions;
        state++;
        InternalState = state;
        if (state < max) return;
        InternalState = press;
    }
}


/**
 * setArrows__9BasicMenuP12SlicedImage2T1i
 *
 * Address:   0x80088330
 * Mangled:   setArrows__9BasicMenuP12SlicedImage2T1i
 * Demangled: BasicMenu::setArrows(SlicedImage2 *, SlicedImage2 *, int)
 *            Sets up/down arrow references and configures their fields
 *
 * @param left  Up/left navigation arrow sprite.
 * @param right  Down/right navigation arrow sprite.
 * @param spacing  Horizontal offset applied to the arrows.
 */
void BasicMenu::setArrows(SlicedImage2 *left, SlicedImage2 *right, int spacing)
{
    LeftArrow = left;
    RightArrow = right;
    ArrowSpace = spacing;
    if (left)
    {
        left->JustX = 2;
        SlicedImage2 *a = LeftArrow;
        a->JustY = 1;
    }
    {
        SlicedImage2 *d = RightArrow;
        if (d)
        {
            d->JustX = 0;
            SlicedImage2 *d2 = RightArrow;
            d2->JustY = 1;
        }
    }
}


/**
 * Return the identifier of the currently highlighted menu item.
 *
 * Address:   0x80088380
 * Mangled:   getHighlighted__9BasicMenu
 * Demangled: BasicMenu::getHighlighted(void)
 *            Searches items array for highlighted item, returns its id or -1
 *
 * @return Identifier of the highlighted item, or -1 when none is highlighted.
 */
int BasicMenu::getHighlighted(void)
{
    int i = 0;
    VMenuItem **ptr = Item;

    do
    {
        VMenuItem *item = *ptr;
        if (item != 0)
        {
            if (item->Highlighted != 0)
            {
                return item->ID;
            }
        }
        i++;
        ptr++;
    } while (i < 16);
    return -1;
}


/**
 * Highlights the menu item with the requested identifier.
 *
 * Address:   0x800883CC
 * Mangled:   setHighlighted__9BasicMenui
 *
 * @param id Item identifier to select.
 */
void BasicMenu::setHighlighted(int id)
{
    VMenuItem *item = Item[Selected];
    item->setHighlightState(0);
    Selected = 0;
    while (1)
    {
        int selected = Selected;
        VMenuItem *current = Item[selected];
        if (current != 0 && current->ID == id) break;
        int next = selected + 1;
        Selected = next;
        if (next >= 0x10) break;
    }
    item = Item[Selected];
    item->setHighlightState(1);
}


/**
 * __13VerticalMenu2iiiiiii (typed ABI owner)
 *
 * Address:   0x800884A8
 * Mangled:   __13VerticalMenu2iiiiiii
 * Demangled: VerticalMenu2::(int, int, int, int, int, int, int)
 *
 * @param self  Implicit object pointer.
 * @param x  X coordinate.
 * @param y  Y coordinate.
 * @param w  Width.
 * @param h  Height.
 * @param just_x  Horizontal item alignment.
 * @param just_y  Vertical menu alignment.
 * @param spacing  Vertical gap between items.
 * @return `this` pointer (GCC 2.x ctor convention).
 */
VerticalMenu2::VerticalMenu2(int x, int y, int w, int h, int just_x, int just_y, int spacing)
{
    int i = 0;
    VMenuItem **ptr = Item;
    do
    {
        *ptr = 0;
        i++;
        ptr++;
    } while (i < 16);
    H = h;
    JustX = just_x;
    HighestSlot = 0;
    X = x;
    Y = y;
    W = w;
    RightArrow = 0;
    LeftArrow = 0;
    ArrowSpace = 0;
    Selected = 0;
    JustY = just_y;
    Spacing = spacing;
}


/**
 * _._13VerticalMenu2 (typed ABI owner)
 *
 * Address:   0x80088518
 * Mangled:   _._13VerticalMenu2
 * Demangled: VerticalMenu2::~VerticalMenu2()
 *
 * @param self  Implicit object pointer.
 * @param flag  GCC 2.x in-charge flag (bit 0 → also invoke `operator delete` on `this`).
 */
VerticalMenu2::~VerticalMenu2()
{
}


/**
 * Lay out the vertical menu entries and highlight the selected entry.
 *
 * Address:   0x80088548
 * Mangled:   activate__13VerticalMenu2
 * Demangled: VerticalMenu2::activate(void)
 */
void VerticalMenu2::activate()
{
    int total_h;
    int initialCount;
    VMenuItem **items;
    {
        int i = 0;
        total_h = 0;
        initialCount = HighestSlot;
        items = Item;
        if (initialCount > 0)
        {
            int spacing = Spacing;
            VMenuItem **ptr = items;
            do
            {
                VMenuItem *item = *ptr;
                ptr++;
                i++;
                int h = item->H;
                h += spacing;
                total_h += h;
            } while (i < initialCount);
        }
    }
    int y;
    if (JustY == 1)
    {
        int space = H - total_h;
        y = Y + (space >> 1);
    }
    else
    {
        y = Y;
    }
    int arrow_x = ArrowSpace;
    SlicedImage2 *upArrow = LeftArrow;
    if (upArrow != 0)
    {
        int h = upArrow->W;
        h = h << 1;
        arrow_x += h;
    }
    {
        int i = 0;
        if (initialCount > 0)
        {
            VMenuItem **ptr = items;
            do
            {
                (*ptr)->JustX = JustX;
                int alignment = JustX;
                if (alignment == 1)
                {
                    int halfW = W >> 1;
                    int centerX = X + halfW;
                    VMenuItem *item = *ptr;
                    int itemHalfW = item->W >> 1;
                    item->setXY(centerX - itemHalfW, y);
                }
                else
                {
                    VMenuItem *item = *ptr;
                    item->setXY(X + arrow_x, y);
                }
                int h = (*ptr)->H;
                ptr++;
                i++;
                int spacing = Spacing;
                h += spacing;
                y += h;
            } while (i < HighestSlot);
        }
    }
    {
        int i = 0;
        int count = HighestSlot;
        for (; i < count; i++)
        {
            if (Item[Selected]->Selectable == 0)
            {
                Selected++;
                if (Selected == count)
                {
                    Selected = 0;
                }
                break;
            }
            count = HighestSlot;
        }
    }
    Item[Selected]->setHighlightState(1);
}


/**
 * Draw every visible entry and position the optional selection arrows.
 *
 * Address:   0x80088758
 * Mangled:   draw__13VerticalMenu2
 * Demangled: VerticalMenu2::draw(void)
 *
 */
void VerticalMenu2::draw()
{
    SlicedImage2 *upArrow = LeftArrow;
    if (upArrow != 0)
    {
        VMenuItem *item = Item[Selected];
        int x = item->X - ArrowSpace;
        int y = item->Y + (item->H >> 1);
        int *vt = upArrow->CClassData.vtable;
        ((void (*)(SlicedImage2 *, int, int, int))vt[5])(upArrow, x, y + (Spacing >> 1), 0);
    }
    VMenuItem **items = Item;
    SlicedImage2 *downArrow = RightArrow;
    if (downArrow != 0)
    {
        int itemOffset = Selected * sizeof(*items);
        char *itemAddress = (char *)items;
        itemAddress += itemOffset;
        VMenuItem **itemSlot = (VMenuItem **)itemAddress;
        VMenuItem *item = *itemSlot;
        int x = item->X + item->W + ArrowSpace;
        int y = item->Y + (item->H >> 1);
        int *vt = downArrow->CClassData.vtable;
        ((void (*)(SlicedImage2 *, int, int, int))vt[5])(downArrow, x, y + (Spacing >> 1), 0);
    }
    int i = 15;
    VMenuItem **ptr = &Item[15];
    do
    {
        VMenuItem *item = *ptr;
        if (item != 0)
        {
            item->draw();
        }
        i--;
        ptr--;
    } while (i >= 0);
}


/**
 * Update each populated item in this vertical menu.
 *
 * Address:   0x80088878
 * Mangled:   update__13VerticalMenu2
 * Demangled: VerticalMenu2::update(void)
 *            Iterates items, calling each item's virtual update method at vtable[8]
 *
 */
void VerticalMenu2::update(void)
{
    int count = HighestSlot;
    if (count > 0)
    {
        int i = 0;
        VMenuItem **ptr = Item;
        do
        {
            VMenuItem *item = *ptr;
            item->update();
            ptr++;
            count = HighestSlot;
            i++;
        } while (i < count);
    }
}


/**
 * Pass a press to the selected item and move the highlight through selectable
 * entries, wrapping at either end of the menu.
 *
 * Address:   0x800888F0
 * Mangled:   processPress__13VerticalMenu2i
 * Demangled: VerticalMenu2::processPress(int)
 *
 * @param press  Button press code.
 */
void VerticalMenu2::processPress(int press)
{
    Item[Selected]->setHighlightState(0);

    if ((unsigned int)press < 2)
    {
        Item[Selected]->processPress(press);
    }

    if (press == 2)
    {
        do
        {
            Selected--;
            if (Selected < 0)
            {
                Selected = HighestSlot - 1;
            }
        } while (Item[Selected]->Selectable == 0);
    }

    if (press == 3)
    {
        do
        {
            Selected++;
            if (Selected >= HighestSlot)
            {
                Selected = 0;
            }
        } while (Item[Selected]->Selectable == 0);
    }

    Item[Selected]->setHighlightState(1);
}


/**
 *
 * Address:   0x80088A60
 * Mangled:   addItem__13VerticalMenu2P9VMenuItem
 * Demangled: VerticalMenu2::addItem(VMenuItem *)
 *
 * @param item  Menu item to append.
 */
void VerticalMenu2::addItem(VMenuItem *item)
{
    int count = this->HighestSlot;
    this->Item[count] = item;
    this->HighestSlot = this->HighestSlot + 1;
}


/**
 * __14ScrollingMenu2iiiiii (typed ABI owner)
 *
 * Address:   0x80088A88
 * Mangled:   __14ScrollingMenu2iiiiii
 * Demangled: ScrollingMenu2::(int, int, int, int, int, int)
 *
 * @param self  Implicit object pointer.
 * @param x  X coordinate.
 * @param y  Y coordinate.
 * @param w  Width.
 * @param h  Height.
 * @param just_x  Horizontal item alignment.
 * @param slide_amount  Distance moved during each scrolling step.
 * @return `this` pointer (GCC 2.x ctor convention).
 */
ScrollingMenu2::ScrollingMenu2(int x, int y, int w, int h, int just_x, int slide_amount)
{
    int i = 0;
    VMenuItem **ptr = Item;
    do
    {
        *ptr = 0;
        i++;
        ptr++;
    } while (i < 16);
    HighestSlot = 0;
    X = x;
    Y = y;
    W = w;
    H = h;
    RightArrow = 0;
    LeftArrow = 0;
    ArrowSpace = 0;
    Top = 0;
    Bottom = h;
    Selected = 0;
    JustX = just_x;
    ArrowSlide = slide_amount;
}


/**
 * _._14ScrollingMenu2 (typed ABI owner)
 *
 * Address:   0x80088AF8
 * Mangled:   _._14ScrollingMenu2
 * Demangled: ScrollingMenu2::~ScrollingMenu2()
 *
 * @param self  Implicit object pointer.
 * @param flag  GCC 2.x in-charge flag (bit 0 → also invoke `operator delete` on `this`).
 */
ScrollingMenu2::~ScrollingMenu2()
{
}


/**
 * activate__14ScrollingMenu2 (typed ABI owner)
 *
 * Address:   0x80088B28
 * Mangled:   activate__14ScrollingMenu2
 * Demangled: ScrollingMenu2::activate(void)
 *
 * @param self  Implicit object pointer.
 */
void ScrollingMenu2::activate()
{
    int arrow_x = ArrowSpace;
    SlicedImage2 *upArrow = LeftArrow;
    if (upArrow != 0)
    {
        int h = upArrow->W;
        h = h << 1;
        arrow_x += h;
    }
    int j = 0;
    VMenuItem **items = Item;
    int y = Y - Top;
    if (HighestSlot > 0)
    {
        VMenuItem **ptr = items;
        do
        {
            (*ptr)->JustX = JustX;
            int alignment = JustX;
            if (alignment == 1)
            {
                int halfW = W >> 1;
                int centerX = X + halfW;
                VMenuItem *item = *ptr;
                int itemHalfW = item->W >> 1;
                item->setXY(centerX - itemHalfW, y);
            }
            else
            {
                VMenuItem *item = *ptr;
                item->setXY(X + arrow_x, y);
            }
            int h = (*ptr)->H;
            ptr++;
            j++;
            y += h;
        } while (j < HighestSlot);
    }
    int count = HighestSlot;
    ScrollingMenu2 *menu = this;
    for (int i = 0; i < count; i++)
    {
        if (menu->Item[menu->Selected]->Selectable == 0)
        {
            menu->Selected++;
            if (menu->Selected == count)
            {
                menu->Selected = 0;
            }
            break;
        }
        count = HighestSlot;
    }

    menu->Item[menu->Selected]->setHighlightState(1);
}


/**
 * Draw this scrolling menu and its navigation arrows.
 *
 * Address:   0x80088CD8
 * Mangled:   draw__14ScrollingMenu2
 * Demangled: ScrollingMenu2::draw(void)
 *
 */
void ScrollingMenu2::draw(void)
{
    int idx = Selected;
    VMenuItem **items_base = Item;
    char *itemAddress = (char *)items_base;
    itemAddress += idx * sizeof(*items_base);
    VMenuItem **itemSlot = (VMenuItem **)itemAddress;
    VMenuItem *item = *itemSlot;
    int halfH = item->H >> 1;
    int y = item->Y + halfH;
    int startY = Y;
    if (y < startY)
    {
        y = startY;
    }
    else
    {
        int endY = startY + H;
        if (y >= endY)
        {
            y = endY - 1;
        }
    }
    SlicedImage2 *upArrow = LeftArrow;
    if (upArrow != 0)
    {
        int curIdx = Selected;
        char *itemAddress = (char *)items_base;
        itemAddress += curIdx * sizeof(*items_base);
        VMenuItem **itemSlot = (VMenuItem **)itemAddress;
        VMenuItem *curItem = *itemSlot;
        int *vt = upArrow->CClassData.vtable;
        int x = curItem->X - ArrowSpace;
        ((void (*)(SlicedImage2 *, int, int, int))vt[5])(upArrow, x, y, 0);
    }
    SlicedImage2 *downArrow = RightArrow;
    if (downArrow != 0)
    {
        int curIdx = Selected;
        char *itemAddress = (char *)items_base;
        itemAddress += curIdx * sizeof(*items_base);
        VMenuItem **itemSlot = (VMenuItem **)itemAddress;
        VMenuItem *curItem = *itemSlot;
        int x = curItem->X + curItem->W + ArrowSpace;
        int *vt = downArrow->CClassData.vtable;
        ((void (*)(SlicedImage2 *, int, int, int))vt[5])(downArrow, x, y, 0);
    }
    SetClippingBox2(0, 0, 0x200, 0x100);
    int i = 15;
    VMenuItem **ptr = &items_base[15];
    do
    {
        VMenuItem *it = *ptr;
        if (it != 0)
        {
            it->draw();
        }
        i--;
        ptr--;
    } while (i >= 0);
    SetClippingBox2(X, Y, W, H);
}


/**
 * update__14ScrollingMenu2 (typed ABI owner)
 *
 * Address:   0x80088E60
 * Mangled:   update__14ScrollingMenu2
 * Demangled: ScrollingMenu2::update(void)
 *
 * @param self  Implicit object pointer.
 */
void ScrollingMenu2::update()
{
    int *offsets = RY;
    int idx = Selected;
    int idxOff = idx << 2;
    int *offsetPtr = (int *)((char *)offsets + idxOff);
    int curOffset = *offsetPtr;
    int scrollPos = Top;
    if (curOffset < scrollPos)
    {
        int speed = ArrowSlide;
        int newPos = scrollPos - speed;
        int newBottom = Bottom - speed;
        Top = newPos;
        Bottom = newBottom;
        int ofs = *offsetPtr;
        if (newPos < ofs)
        {
            Top = ofs;
            Bottom = ofs + H;
        }
    }
    else
    {
        VMenuItem **itemsBase = Item;
        VMenuItem **itemSlot = (VMenuItem **)((char *)itemsBase + idxOff);
        VMenuItem *item = *itemSlot;
        int itemH = item->H;
        int bottom = curOffset + itemH;
        int viewBottom = Bottom;
        if (viewBottom < bottom)
        {
            int speed = ArrowSlide;
            int newPos = scrollPos + speed;
            int newBottom = viewBottom + speed;
            Top = newPos;
            Bottom = newBottom;
            VMenuItem *item2 = *itemSlot;
            int ofs2 = *offsetPtr;
            int itemH2 = item2->H;
            int top = ofs2 + itemH2;
            if (top < newBottom)
            {
                Bottom = top;
                Top = top - H;
            }
        }
    }
    activate();
    int count = HighestSlot;
    if (count > 0)
    {
        int i = 0;
        VMenuItem **ptr = Item;
        do
        {
            VMenuItem *item = *ptr;
            item->update();
            ptr++;
            count = HighestSlot;
            i++;
        } while (i < count);
    }
}


/**
 * Pass a press to the selected item and move to the next selectable entry
 * without wrapping beyond the ends of a scrolling menu.
 *
 * Address:   0x80088FC4
 * Mangled:   processPress__14ScrollingMenu2i
 * Demangled: ScrollingMenu2::processPress(int)
 *
 * @param press  Button press code.
 */
void ScrollingMenu2::processPress(int press)
{
    /*
     * The integer cursor form is retained after three typed Item/Selected
     * rewrites each reversed a target commutative addu operand. All other
     * ScrollingMenu2 field access is typed; this is the measured exception.
     */
    int self = (int)this;
    int *items = (int *)(self + 0x10);
    Item[Selected]->setHighlightState(0);
    if ((unsigned int)press < 2)
    {
        Item[Selected]->processPress(press);
    }
    if (press == 2)
    {
        int target = *(int *)(self + 0x54) - 1;
        if (target >= 0)
        {
            int *ptr = (int *)(target * 4 + (int)items);
            do
            {
                int *cur = (int *)*ptr;
                if (*(int *)((int)cur + 8) != 0) goto found_up;
                target--;
                ptr--;
            } while (target >= 0);
        }
    found_up:
        if (target >= 0)
        {
            *(int *)(self + 0x54) = target;
        }
    }
    if (press == 3)
    {
        int target = Selected + 1;
        int highestSlot = HighestSlot;
        if (target < highestSlot)
        {
            int *ptr = (int *)(target * 4 + (int)items);
            do
            {
                int *cur = (int *)*ptr;
                if (*(int *)((int)cur + 8) != 0) goto found_down;
                target++;
                ptr++;
            } while (target < highestSlot);
        found_down:
            if (target < HighestSlot)
            {
                Selected = target;
            }
        }
    }
    Item[Selected]->setHighlightState(1);
}


/**
 * Append one item and record its cumulative scroll offset.
 *
 * Address:   0x80089140
 * Mangled:   addItem__14ScrollingMenu2P9VMenuItem
 * Demangled: ScrollingMenu2::addItem(VMenuItem *)
 *            Appends an item and records its cumulative scroll offset.
 *
 * @param item  Menu item to append.
 */
void ScrollingMenu2::addItem(VMenuItem *item)
{
    Item[HighestSlot] = item;
    if (HighestSlot == 0)
    {
        RY[0] = 0;
    }
    else
    {
        RY[HighestSlot] = RY[HighestSlot - 1] + Item[HighestSlot - 1]->H;
    }
    ++HighestSlot;
}


/**
 * Builds a text-menu wrapper, its menu container, and all supplied entries.
 *
 * Address:   0x800891B0
 * Mangled:   __15TextMenuWrapperPCPcPiiPcb
 * Demangled: TextMenuWrapper::(const char **, int *, int, char *, bool)
 *
 * @param self  Wrapper being constructed.
 * @param string_list  Text for each menu entry.
 * @param id_list  Identifier for each entry; -1 denotes a title.
 * @param num_items  Number of entries to create.
 * @param font_name  Font selected for the menu.
 * @param use_scrolling_menu  Selects the scrolling rather than vertical layout.
 * @return `this` pointer (GCC 2.x ctor convention).
 */
TextMenuWrapper::TextMenuWrapper(char *const *string_list, int *id_list, int num_items,
                                 char *font_name, bool use_scrolling_menu)
{
    TextMenuProperties *properties = &Props;
    if (use_scrolling_menu)
    {
        Menu = new ScrollingMenu2(0, 0x50, 0x200, 0x50, 1, 4);
    }
    else
    {
        Menu = new VerticalMenu2(0, 0, 0x200, 0x100, 1, 1, 4);
    }
    Props.TheFont = *FontManager::GetFont(font_name);
    if (strcmp(font_name, "ingame1.fnt") == 0)
    {
        Props.BigScale = 0x1324;
        Props.NormalScale = 0x1000;
    }
    else
    {
        Props.BigScale = 0xe5b;
        Props.NormalScale = 0xc00;
    }
    {
        int i = 0;
        Props.TheFont.ShadowDx = 2;
        Props.TheFont.ShadowDy = 2;
        NumItems = num_items;
        if (num_items > 0)
        {
            int titleId = -1;
            VMenuItem **itemsPtr = ItemList;
            char *const *strPtr = string_list;
            int *idsPtr = id_list;
            do
            {
                if (*idsPtr == titleId)
                {
                    *itemsPtr = new TitleMenuItem(*idsPtr, *strPtr, *properties);
                }
                else
                {
                    *itemsPtr = new TextMenuItem(*idsPtr, *strPtr, *properties);
                }
                Menu->addItem(*itemsPtr);
                itemsPtr++;
                strPtr++;
                idsPtr++;
                i++;
            } while (i < NumItems);
        }
    }
    Menu->activate();
}


/**
 * _._15TextMenuWrapper (typed ABI owner)
 *
 * Address:   0x80089420
 * Mangled:   _._15TextMenuWrapper
 * Demangled: TextMenuWrapper::~TextMenuWrapper()
 *
 * @param self  Implicit object pointer.
 * @param flag  GCC 2.x in-charge flag (bit 0 → also invoke `operator delete` on `this`).
 */
TextMenuWrapper::~TextMenuWrapper()
{
    int i = 0;
    int count = NumItems;
    if (count > 0)
    {
        VMenuItem **ptr = ItemList;
        do
        {
            VMenuItem *item = *ptr;
            if (item != 0)
            {
                delete item;
                count = NumItems;
            }
            i++;
            ptr++;
        } while (i < count);
    }
    BasicMenu *menu = Menu;
    if (menu != 0)
    {
        delete menu;
    }
}


/**
 * Forward the latest menu press through this wrapper's active menu.
 *
 * Address:   0x80089504
 * Mangled:   HandleInput__15TextMenuWrapper
 * Demangled: TextMenuWrapper::HandleInput(void)
 *
 */
void TextMenuWrapper::HandleInput(void)
{
    int press = Menu_GetPress();
    if ((unsigned int)(press - 2) < 2)
    {
        SFX_PlayX(0x90, 0x2000, 0);
    }
    Menu->processPress(press);
    Menu->update();
}


/**
 * Test whether this wrapped menu accepted or cancelled input.
 *
 * Address:   0x80089590
 * Mangled:   TestComplete__15TextMenuWrapper
 * Demangled: TextMenuWrapper::TestComplete(void)
 *
 * @return 1 when the menu accepts or cancels input, otherwise 0.
 */
int TextMenuWrapper::TestComplete(void)
{
    SControl *pad = &Pad[0];
    VMenuItem *item;
    int i;
    if (pad->Start.Triggered != 0) goto do_work;
    if (pad->X.Triggered == 0) goto check_pad1;
do_work:
    i = 0;
    pad->Start.Triggered = 0;
    pad->X.Triggered = 0;
    HighlightedId = -1;
    if (NumItems <= 0) goto sfx_91;
    do
    {
        item = ItemList[i];
        if (item->Highlighted != 0) goto loop_break;
        i++;
    } while (i < NumItems);
sfx_91:
    SFX_PlayX(0x91, 0x2000, 0);
    return 1;
loop_break:
    HighlightedId = item->ID;
    goto sfx_91;
check_pad1:
    {
        int p1 = pad->Triangle.Triggered;
        if (p1 != 0)
        {
            pad->Triangle.Triggered = 0;
            HighlightedId = -1;
            SFX_PlayX(0x93, 0x2000, 0);
            return 1;
        }
    }
ret_zero:
    return 0;
}
