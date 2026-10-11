// MULTISELECT.cpp -- Reconstructed translation unit
// Original: MULTISELECT.CPP
// Functions: 9 reconstructed entries
// Address range: 0x8008984C - 0x8008A2B8
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.


#include "PSX.h"
#define SCREENTOOLS_POLYMORPHIC_LAYOUT
#include "SCREENTOOLS.h"
#include "MENU.h"
#include "PROMPTSCREENELEMENT.h"
#include "FRONTSCREENS.h"
#include "SFX.h"
#include "MAIN.h"
#include "PAD.h"
#include "UTILS.h"
#include <STDDEF.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "MENUINPUT.h"
#include "DB.h"
#include "FRONTEND2.h"

/** Multiplayer-mode selection screen and its owned menu resources. */
struct MultiSelectScreen : ScreenElementList
{
    Sprite2 *mBackground;
    Font mFont1;
    Font mFont2;
    VerticalMenu2 *mMenu;
    TextMenuProperties *mProps;
    VMenuItem *mItem[5];
    Sprite2 *mpLeftArrow;
    Sprite2 *mpRightArrow;
    FrontPreLoader mFrontPreLoader;
    int mFinishUp;

    MultiSelectScreen();
    virtual ~MultiSelectScreen();
    /** Handle multiplayer-selection confirmation or cancellation input. */
    int handlePress();
    /** Draw the selector and its background. */
    void draw(int x, int y);
    /** Advance menu input and child screen elements. */
    void update();
    /** Return the currently highlighted multiplayer game mode. */
    int GetGameMode();
    /** Begin the preload phase for a completed selection. */
    void InitEndProcess(int press);
    /** Return whether the active preload phase has completed. */
    int EndProcess();
};

PSX_LAYOUT_CHECK(multiselect_screen_size_must_be_360, sizeof(MultiSelectScreen) == 360);

/**
 * MULTISELECT's target-owned menu text and resource names in object order.
 *
 * The six small owners use namespace-scoped C linkage so they remain
 * lexically distinct from the incomplete address views required below.
 */
static char s_SplitscreenModes[20] PSX_SECTION_ALIGNED(".rdata", 4) = "splitscreen modes";
static char s_MultiplayerModes[20] PSX_SECTION_ALIGNED(".rdata", 4) = "multiplayer modes";
static char s_S2bgd4Bmp[12] PSX_SECTION_ALIGNED(".sdata", 4) = "s2bgd4.bmp";
static char s_MainfFnt_MultiSelect[12] PSX_SECTION_ALIGNED(".sdata", 4) = "mainf.fnt";
static char s_S2font2Fnt_MultiSelect[12] PSX_SECTION_ALIGNED(".sdata", 4) = "s2font2.fnt";
static char s_TrickAttack[16] PSX_SECTION_ALIGNED(".sdata", 4) = "trick attack";
static char s_Graffiti[12] PSX_SECTION_ALIGNED(".sdata", 4) = "graffiti";

namespace MultiSelectAddressViewOwners
{
extern "C"
{
static char s_Tag[4] PSX_SECTION_ALIGNED(".sdata", 4) = "tag";
static char s_Contest[8] PSX_SECTION_ALIGNED(".sdata", 4) = "contest";
static char s_Horse[8] PSX_SECTION_ALIGNED(".sdata", 4) = "horse";
}
}

static char s_S2arrow2Bmp_MultiSelect[16] PSX_SECTION_ALIGNED(".sdata", 4) = "s2arrow2.bmp";
static char s_S2arrow1Bmp_MultiSelect[16] PSX_SECTION_ALIGNED(".sdata", 4) = "s2arrow1.bmp";
static char s_S2prmpt4Bmp_MultiSelect[16] PSX_SECTION_ALIGNED(".sdata", 4) = "s2prmpt4.bmp";

namespace MultiSelectAddressViewOwners
{
extern "C"
{
static char s_Select_MultiSelect[8] PSX_SECTION_ALIGNED(".sdata", 4) = "select";
}
}

static char s_S2prmpt1Bmp_MultiSelect[16] PSX_SECTION_ALIGNED(".sdata", 4) = "s2prmpt1.bmp";

namespace MultiSelectAddressViewOwners
{
extern "C"
{
static char s_Accept_MultiSelect[8] PSX_SECTION_ALIGNED(".sdata", 4) = "accept";
}
}

static char s_S2prmpt2Bmp_MultiSelect[16] PSX_SECTION_ALIGNED(".sdata", 4) = "s2prmpt2.bmp";

namespace MultiSelectAddressViewOwners
{
extern "C"
{
static char s_Back_MultiSelect[8] PSX_SECTION_ALIGNED(".sdata", 4) = "back";
}
}

/*
 * These incomplete address views retain the target's absolute lui/addiu
 * materialization while the internal definitions above own the storage.
 */
/** Absolute address views of MULTISELECT's GP-sized resource strings. */
extern char s_Tag[];
extern char s_Contest[];
extern char s_Horse[];
extern char s_Select_MultiSelect[];
extern char s_Accept_MultiSelect[];
extern char s_Back_MultiSelect[];

// === Function implementations (address order) ===

/**
 * __17MultiSelectScreen
 *
 * Address:   0x8008984C
 * Mangled:   __17MultiSelectScreen
 * Demangled: MultiSelectScreen::(void)
 *
 * Constructs the multiplayer mode selector, its fonts, menu items, arrows,
 * prompts, and preload state.
 */
MultiSelectScreen::MultiSelectScreen() : ScreenElementList(0, 0, -1, -1)
{
    mBackground = new Sprite2(s_S2bgd4Bmp, 1, 0x40, 0x40);

    mFinishUp = 0;

    mFont1 = *FontManager::GetFont(s_MainfFnt_MultiSelect);

    mFont1.JustX = 1;
    mFont1.JustY = 3;
    mFont1.R = 0x40;
    mFont1.G = 0x80;
    mFont1.B = 0x80;
    mFont1.Shadow = 0;
    mFont1.SpaceX = 0;
    mFont1.SpaceY = 0;
    mFont1.Scale = 0xC00;

    mFont2 = *FontManager::GetFont(s_S2font2Fnt_MultiSelect);

    mFont2.JustX = 0;
    mFont2.JustY = 3;
    mFont2.R = 0x80;
    mFont2.G = 0x80;
    mFont2.B = 0x80;
    mFont2.Shadow = 0;
    mFont2.SpaceX = 0;

    ScreenElement *item[16];

    {
        int i = 0;
        ScreenElement **itemSlot = item;
        do
        {
            *itemSlot = 0;
            i++;
            itemSlot++;
        } while (i < 16);
    }

    item[0] = new TextScreenElement(s_SplitscreenModes, &mFont1, 0x100, 0x3A, -0x40, 0x3A);
    addItem(item[0]);

    item[1] = new TextScreenElement(s_MultiplayerModes, &mFont1, 0x100, 0x97, 0x240, 0x97);
    addItem(item[1]);

    mMenu = new VerticalMenu2(0, 0x14, 0x200, 0xDC, 1, 0, 3);

    mProps = new TextMenuProperties;
    mProps->TheFont = mFont1;
    mProps->TheFont.R = 0x80;
    mProps->TheFont.G = 0x80;
    mProps->TheFont.B = 0x80;
    mProps->TheFont.Scale = 0xC00;
    mProps->BigScale = 0xC00;
    mProps->NormalScale = 0xC00;

    mItem[0] = new TextMenuItem(5, s_TrickAttack, *mProps);
    mItem[1] = new TextMenuItem(8, s_Graffiti, *mProps);
    mItem[2] = new TextMenuItem(9, s_Tag, *mProps);
    mItem[2]->Selectable = 0;
    mItem[3] = new TextMenuItem(10, s_Contest, *mProps);
    mItem[4] = new TextMenuItem(7, s_Horse, *mProps);

    mItem[0]->Selectable = 1;
    mItem[1]->Selectable = 0;
    mItem[2]->Selectable = 0;
    mItem[3]->Selectable = 0;
    mItem[4]->Selectable = 0;

    {
        int idx = 0;
        VMenuItem **items = mItem;
        do
        {
            mMenu->addItem(*items);
            items++;
            idx++;
        } while (idx < 5);
    }

    mpLeftArrow = new Sprite2(s_S2arrow2Bmp_MultiSelect, 1, 0, 0);
    mpRightArrow = new Sprite2(s_S2arrow1Bmp_MultiSelect, 1, 0, 0);

    mMenu->setArrows(mpLeftArrow, mpRightArrow, 5);
    mMenu->activate();

    mItem[0]->setXY(mItem[0]->X, 0x44);
    mItem[1]->setXY(mItem[1]->X, 0x5B);
    mItem[2]->setXY(mItem[2]->X, 0x72);
    mItem[3]->setXY(mItem[3]->X, 0xA1);
    mItem[4]->setXY(mItem[4]->X, 0xB8);

    addItem(new PromptScreenElement(s_S2prmpt4Bmp_MultiSelect, s_Select_MultiSelect, &mFont2, 0x73,
                                    0xDC, -1, 0x104));
    addItem(new PromptScreenElement(s_S2prmpt1Bmp_MultiSelect, s_Accept_MultiSelect, &mFont2, 0xE4,
                                    0xDC, -1, 0x104));
    addItem(new PromptScreenElement(s_S2prmpt2Bmp_MultiSelect, s_Back_MultiSelect, &mFont2, 0x14D,
                                    0xDC, -1, 0x104));
}


/**
 * _._17MultiSelectScreen - Destroys owned submenu children, release preload/font resources, clear ScreenElementList, and optionally free self.
 *
 * Address:   0x80089F1C
 * Mangled:   _._17MultiSelectScreen
 * Demangled: MultiSelectScreen::~MultiSelectScreen()
 */
MultiSelectScreen::~MultiSelectScreen()
{
    delete mBackground;
    delete mMenu;
    delete mProps;
    delete mpLeftArrow;
    delete mpRightArrow;
    {
        int i = 0;
        VMenuItem **ptr = mItem;
        do
        {
            delete *ptr;
            i++;
            ptr++;
        } while (i < 5);
    }
}


/**
 * draw__17MultiSelectScreenii
 *
 * Address:   0x8008A0A8
 * Mangled:   draw__17MultiSelectScreenii
 * Demangled: MultiSelectScreen::draw(int, int)
 *
 * @param x  X coordinate.
 * @param y  Y coordinate.
 */
void MultiSelectScreen::draw(int x, int y)
{
    ScreenElementList::draw(x, y);
    mBackground->draw(0, 0, 1);
}


/**
 * update__17MultiSelectScreen
 *
 * Address:   0x8008A0EC
 * Mangled:   update__17MultiSelectScreen
 * Demangled: MultiSelectScreen::update(void)
 *            Calls menu->update(), Menu_GetPress(), menu->processPress(press), menu->draw(), then ScreenElementList update
 *
 */
void MultiSelectScreen::update()
{
    mMenu->draw();
    int press = Menu_GetPress();
    mMenu->processPress(press);
    mMenu->update();
    ScreenElementList::update();
}


/**
 * handlePress__17MultiSelectScreen
 *
 * Address:   0x8008A17C
 * Mangled:   handlePress__17MultiSelectScreen
 * Demangled: MultiSelectScreen::handlePress(void)
 *
 * @return 1 when X confirms, 2 when Triangle cancels, or 0 otherwise.
 */
int MultiSelectScreen::handlePress()
{
    if (Pad[0].Up.Triggered != 0 || Pad[0].Down.Triggered != 0)
    {
        SFX_PlayX(0x92, 0x2000, 0);
    }
    if (Pad[0].X.Triggered != 0)
    {
        SFX_PlayX(0x91, 0x2000, 0);
        Pad[0].X.Triggered = 0;
        return 1;
    }
    if (Pad[0].Triangle.Triggered != 0)
    {
        SFX_PlayX(0x93, 0x2000, 0);
        Pad[0].Triangle.Triggered = 0;
        return 2;
    }
    return 0;
}


/**
 * GetGameMode__17MultiSelectScreen
 *
 * Address:   0x8008A224
 * Mangled:   GetGameMode__17MultiSelectScreen
 * Demangled: MultiSelectScreen::GetGameMode(void)
 *
 * @return Identifier of the currently highlighted game mode.
 */
int MultiSelectScreen::GetGameMode()
{
    return mMenu->getHighlighted();
}


/**
 * InitEndProcess__17MultiSelectScreeni
 *
 * Address:   0x8008A248
 * Mangled:   InitEndProcess__17MultiSelectScreeni
 * Demangled: MultiSelectScreen::InitEndProcess(int)
 *            Starts the preloader when press == 1, then sets mFinishUp.
 *
 * @param press  Button press code.
 */
void MultiSelectScreen::InitEndProcess(int press)
{
    int one = 1;
    if (press == one)
    {
        mFrontPreLoader.BeginLoad(1);
    }
    mFinishUp = one;
}


/**
 * EndProcess__17MultiSelectScreen
 *
 * Address:   0x8008A288
 * Mangled:   EndProcess__17MultiSelectScreen
 * Demangled: MultiSelectScreen::EndProcess(void)
 *            Once mFinishUp is set, reports whether mFrontPreLoader is done.
 *
 * @return 0 until mFinishUp is set, then the preloader's DoneLoading result.
 */
int MultiSelectScreen::EndProcess()
{
    if (mFinishUp == 0) return 0;
    return mFrontPreLoader.DoneLoading();
}


/**
 * MultiSelect_Main__FPi
 *
 * Address:   0x8008A2B8
 * Mangled:   MultiSelect_Main__FPi
 * Demangled: MultiSelect_Main(int *)
 *
 * @param pGameMode  Receives the selected game mode.
 * @return `-1` when the player backs out; otherwise `0`.
 */
int MultiSelect_Main(int *pGameMode)
{
    unsigned int oldSkyColor;
    MultiSelectScreen *pMultiSelectScreen;
    int press;
    int exitPress;

    oldSkyColor = Db_SkyColor;
    Db_SkyColor = 0;

    Db_UpdateSky();

    // Load the two selector fonts (%hi addresses are CSE'd into saved regs).
    FontManager::LoadFont(s_MainfFnt_MultiSelect);
    FontManager::LoadFont(s_S2font2Fnt_MultiSelect);

    // Allocate and construct MultiSelectScreen
    pMultiSelectScreen = new MultiSelectScreen;

    Pad_ClearTriggers(Pad);
    Pad_ClearTriggers(Pad + 1);

    // Main loop
    while (1)
    {
        FrontEnd2_UpdateMusicLoop();

        // Save current Vblanks to GStartTime
        GStartTime = Vblanks;

        Db_FlipClear();
        Pad_Update();

        // Call handlePress(screen)
        {
            press = pMultiSelectScreen->handlePress();
            if (press == 1)
            {
                // Start pressed - get game mode and begin end process
                *pGameMode = pMultiSelectScreen->GetGameMode();
                pMultiSelectScreen->InitEndProcess(1);
                exitPress = 1;
            }
            else if (press == 2)
            {
                // Back pressed
                *pGameMode = press;
                pMultiSelectScreen->InitEndProcess(2);
                exitPress = 2;
            }
        }

        // Call EndProcess, if done then break
        if (pMultiSelectScreen->EndProcess() != 0)
        {
            break;
        }

        // Call screen->update() via vtable offset 0x0C
        pMultiSelectScreen->update();
        // Call screen->draw(0, 0) via vtable offset 0x10
        pMultiSelectScreen->draw(0, 0);

        DrawSync(0);
        Pause(1);

        // Wait for vblanks: while (Vblanks < GStartTime + 2)
        {
            int target = GStartTime + 2;
            while ((unsigned)Vblanks < (unsigned)target)
            {
                // spin
            }
        }

        Db_DisplayDraw();
        PollHost();
    }

    // Restore sky color
    Db_SkyColor = oldSkyColor;

    // Destroy screen
    delete pMultiSelectScreen;

    // Unload fonts
    FontManager::UnloadFont(s_MainfFnt_MultiSelect);
    FontManager::UnloadFont(s_S2font2Fnt_MultiSelect);

    // Return -1 if the player backed out, else 0.
    if (exitPress == 2) return -1;
    return 0;
}
