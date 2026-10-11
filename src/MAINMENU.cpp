// MAINMENU.cpp -- Reconstructed translation unit
// Original: MAINMENU.CPP
// Functions: 12
// Address range: 0x80081FF0 - 0x800829E8
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

typedef unsigned char u8;

#define SCREENTOOLS_POLYMORPHIC_LAYOUT
#include "SCREENTOOLS.h"
#include "FRONTSCREENS.h"
#include "PROMPTSCREENELEMENT.h"

struct TextMenuWrapper;
struct WheelElementList;

/** Main-menu screen and its owned UI resources. */
struct MainMenuScreen : ScreenElementList
{
    FrontPreLoader mFrontPreLoader;
    void *FinishUp;
    Font TheFont;
    TextMenuWrapper *Menu;
    Sprite2 *mBackground;
    WheelElementList *mWheel;
    Font mFont1;

    MainMenuScreen();
    virtual ~MainMenuScreen();
    /** Begin the preload phase for a selected menu command. */
    void InitEndProcess(int returnValue);
    /** Draw and advance the active preload phase. */
    int EndProcess();
    /** Accept the current wheel selection when input is triggered. */
    int isDone(int *returnValue);
    /** Draw the menu elements and their full-screen background. */
    void draw();
    /** Update every child element in the main-menu screen. */
    void update();
};

/** Rotating menu-wheel element and selection state. */
struct WheelElementList : ScreenElementList
{
    RotateSprite *Wheel;
    int CurrentRot;
    int TargetRot;
    int NumSlots;
    /** Full runtime slot plus the persisted low-byte view used by the dtor. */
    union
    {
        int Slot;
        unsigned char SlotByte;
    };

    WheelElementList(int homeX, int homeY, int screenX, int screenY);
    virtual ~WheelElementList();
    /** Advance wheel input and child screen elements. */
    void update();
    /** Draw the wheel and its child screen elements. */
    void draw(int x, int y);
};

typedef char mainmenu_wheel_size_must_be_124[(sizeof(WheelElementList) == 124) ? 1 : -1];
typedef char mainmenu_screen_size_must_be_332[(sizeof(MainMenuScreen) == 332) ? 1 : -1];
typedef char mainmenu_prompt_size_must_be_104[(sizeof(PromptScreenElement) == 104) ? 1 : -1];

#include "SFX.h"
#include "MAIN.h"
#include "PACK.h"
#include "PAD.h"
#include "UTILS.h"
#include <STDDEF.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "DB.h"
#include "SPOOL.h"
#include "PAL.h"
#include "FRONTEND2.h"

/** MAINMENU's initialized small-data contribution in original order. */
u8 MainMenu_LastSelection __attribute__((section(".sdata"), aligned(4))) = 2;
static char EndProcess_str[] __attribute__((section(".sdata"), aligned(4))) = "loading";
static char MainMenuBmpName[] __attribute__((section(".sdata"), aligned(4))) = "s2bgd2.bmp";
static char MainMenuFont1[] __attribute__((section(".sdata"), aligned(4))) = "mainf.fnt";
static char MainMenuFont2[] __attribute__((section(".sdata"), aligned(4))) = "s2font2.fnt";
static char MainMenuItemNames[] __attribute__((section(".sdata"), aligned(4))) = "s2prmpt4.bmp";
static char MainMenuItemNames2[] __attribute__((section(".sdata"), aligned(4))) = "select";
static char MainMenuBmpName2[] __attribute__((section(".sdata"), aligned(4))) = "s2prmpt1.bmp";
static char MainMenuBmpName3[] __attribute__((section(".sdata"), aligned(4))) = "accept";
static char WheelBmpName[] __attribute__((section(".sdata"), aligned(4))) = "s2wheel.bmp";
static char WheelItemNames[] __attribute__((section(".sdata"), aligned(4))) = "s2arrow3.bmp";

/** Menu-wheel angle and result mapping at its target `.data` address. */
int RotMap[7][2] __attribute__((section(".data"), aligned(4))) = {
    { 0x0000, 0x27 }, { 0x0D6D, -1 },   { 0x0B56, 0x28 }, { 0x0934, -1 },
    { 0x06EF, -1 },   { 0x04E4, 0x22 }, { 0x02AB, -1 },
};

// === Function implementations (address order) ===

/**
 * Run the main-menu frame loop and return the selected front-end command.
 *
 * Original symbol: `MainMenu_Main__Fv` at 0x80081FF0.
 *
 * @return Selected command from RotMap, or -1 until a selection is made.
 */
int MainMenu_Main(void)
{
    unsigned int oldSkyColor = Db_SkyColor;
    Db_SkyColor = 0;
    Db_UpdateSky();
    Spool_RemoveUnusedTextures();
    Pal_RemoveUnusedPalettes();
    Pack_DefragmentFully();

    MainMenuScreen *pScreen = new MainMenuScreen;

    Pad_ClearTriggers(&Pad[0]);
    Pad_ClearTriggers(&Pad[1]);

    int return_value = -1;
    int Finishing = 0;

    while (1)
    {
        FrontEnd2_UpdateMusicLoop();
        GStartTime = Vblanks;
        Db_FlipClear();
        CalcPolyBufferEnd();
        Pad_Update();

        if (Finishing != 0)
        {
            Pad_ClearTriggers(&Pad[0]);
            Pad_ClearTriggers(&Pad[1]);
        }

        if (pScreen->isDone(&return_value))
        {
            Finishing = 1;
            pScreen->InitEndProcess(return_value);
        }

        pScreen->update();

        if (pScreen->EndProcess() != 0)
        {
            break;
        }

        pScreen->draw();
        DrawSync(0);
        Pause(1);

        // Wait for two vertical blanks before presenting the next frame.
        while ((unsigned int)Vblanks < (unsigned int)(GStartTime + 2))
        {
        }

        Db_DisplayDraw();
        PollHost();
    }

    Db_SkyColor = oldSkyColor;

    delete pScreen;

    return return_value;
}

/**
 * Begin the common preload phase for menu commands that require it.
 *
 * Original symbol: `InitEndProcess__14MainMenuScreeni` at 0x800821C0.
 *
 * @param return_value Selected front-end command.
 */
void MainMenuScreen::InitEndProcess(int return_value)
{
    if ((unsigned int)(return_value - 0x20) < 2 || return_value == 0x28)
    {
        mFrontPreLoader.BeginLoad(1);
    }
}

/**
 * Draw the loading message and advance the active front-end preload.
 *
 * Original symbol: `EndProcess__14MainMenuScreen` at 0x800821FC.
 *
 * @return Zero while idle or the current loader-completion state.
 */
int MainMenuScreen::EndProcess()
{
    int result;
    if (FinishUp == 0)
    {
        result = 0;
    }
    else
    {
        TheFont.draw(256, 129, EndProcess_str, 0);
        result = mFrontPreLoader.DoneLoading();
    }
    return result;
}

/**
 * Construct the main-menu screen, fonts, background, wheel, and prompts.
 *
 * Original symbol: `__14MainMenuScreen` at 0x80082254.
 *
 * @param self Storage allocated for the screen.
 * @return The constructed screen.
 */
MainMenuScreen::MainMenuScreen() : ScreenElementList(0, 0, -1, -1)
{
    // Create the full-screen background sprite.
    mBackground = new Sprite2(MainMenuBmpName, 1, 0, 0);

    // Create and attach the rotating menu wheel.
    mWheel = new WheelElementList(255, 129, -110, 128);
    addItem(mWheel);

    // Load and configure the loading-message font.
    Font *fontData1 = FontManager::LoadFont(MainMenuFont1);
    TheFont = *fontData1;
    TheFont.JustX = 1;
    TheFont.JustY = 1;
    TheFont.Scale = 0x800;
    TheFont.R = 0x40;
    TheFont.G = 0x40;
    TheFont.B = 0xFF;
    FinishUp = 0;

    // Load and configure the prompt font.
    Font *fontData2 = FontManager::LoadFont(MainMenuFont2);
    mFont1 = *fontData2;
    mFont1.JustX = 0;
    mFont1.JustY = 3;
    mFont1.setRGB(128, 128, 128);

    // Create the select prompt.
    mFont1.Shadow = 0;
    mFont1.SpaceX = 0;
    mFont1.SpaceY = 0;
    mFont1.Scale = 0x1000;

    PromptScreenElement *pPromptElement =
        new PromptScreenElement(MainMenuItemNames, MainMenuItemNames2, &mFont1, 159, 220, -1, 260);
    addItem(pPromptElement);

    // Create the accept prompt.
    pPromptElement =
        new PromptScreenElement(MainMenuBmpName2, MainMenuBmpName3, &mFont1, 272, 220, -1, 260);
    addItem(pPromptElement);
}

/**
 * Release the screen-owned sprite, fonts, preloader, and element list.
 *
 * Original symbol: `_._14MainMenuScreen` at 0x800824EC.
 */
MainMenuScreen::~MainMenuScreen()
{
    delete mBackground;
    FontManager::UnloadFont(MainMenuFont1);
    FontManager::UnloadFont(MainMenuFont2);
}

/**
 * Draw the menu elements and their full-screen background.
 *
 * Original symbol: `draw__14MainMenuScreen` at 0x800825A0.
 *
 */
void MainMenuScreen::draw()
{
    ScreenElementList::draw(0, 0);
    mBackground->draw(0, 0, 1);
}

/**
 * Update every child element in the main-menu screen.
 *
 * Original symbol: `update__14MainMenuScreen` at 0x800825EC.
 *
 */
void MainMenuScreen::update()
{
    ScreenElementList::update();
}

/**
 * Accept the current wheel selection when X or Start is triggered.
 *
 * Original symbol: `isDone__14MainMenuScreenPi` at 0x8008260C.
 *
 * @param return_value Receives the selected front-end command.
 * @return One when a valid command is accepted, otherwise zero.
 */
int MainMenuScreen::isDone(int *return_value)
{
    SControl *pad = Pad;
    if (pad->X.Triggered == 0)
    {
        if (pad->Start.Triggered == 0)
        {
            return 0;
        }
    }
    pad->X.Triggered = 0;
    pad->Start.Triggered = 0;

    WheelElementList *wheel = mWheel;
    int sel = wheel->Slot;
    int key = RotMap[sel][1];
    *return_value = key;

    if (key == -1)
    {
        SFX_PlayX(0x92, 0x2000, 0);
        return 0;
    }

    FinishUp = (void *)1;
    SFX_PlayX(0x91, 0x2000, 0);
    return 1;
}

/**
 * Construct the rotating wheel and its overlaid arrow sprite.
 *
 * Original symbol: `__16WheelElementListiiii` at 0x800826B4.
 *
 * @param self Storage allocated for the wheel element list.
 * @param homeX  Home X coordinate (resting position).
 * @param homeY  Home Y coordinate (resting position).
 * @param screenX  Screen-space X coordinate.
 * @param screenY  Screen-space Y coordinate.
 * @return The constructed wheel element list.
 */
WheelElementList::WheelElementList(int homeX, int homeY, int screenX, int screenY)
    : ScreenElementList(homeX, homeY, screenX, screenY)
{
    // Create the rotating wheel sprite.
    Wheel = new RotateSprite(WheelBmpName, 1, 0, 0);
    Wheel->JustX = 1;
    Wheel->JustY = 1;

    // Create the fixed arrow overlay.
    addItem(new SpriteScreenElement(WheelItemNames, 1, -81, 0, 0, 1, 1));

    // Restore the previous selection and its target angle.
    int lastSel = MainMenu_LastSelection;
    NumSlots = 7;
    Slot = lastSel;
    int entry = RotMap[lastSel][0];
    TargetRot = entry;
    CurrentRot = entry;
}

/**
 * Remember the selected slot and release the wheel sprite and element list.
 *
 * Original symbol: `_._16WheelElementList` at 0x8008279C.
 */
WheelElementList::~WheelElementList()
{
    MainMenu_LastSelection = SlotByte;
    delete Wheel;
}

/**
 * Process wheel input and ease the displayed rotation toward its target slot.
 *
 * Original symbol: `update__16WheelElementList` at 0x8008281C.
 *
 */
void WheelElementList::update()
{
    SControl *pad = Pad;

    // Advance the wheel when Left is triggered.
    if (pad->Left.Triggered != 0)
    {
        SFX_PlayX(0xE9, 0x2000, 0);
        pad->Left.Triggered = 0;

        int idx = Slot;
        int maxItems = NumSlots;
        idx = idx + 1;
        Slot = idx;
        if (idx >= maxItems)
        {
            Slot = 0;
        }

        int newIdx = Slot;
        int targetRot = RotMap[newIdx][0];
        int curRot = CurrentRot;
        int diff = targetRot - curRot;
        TargetRot = targetRot;
        if (diff > 0)
        {
            TargetRot = targetRot - 0x1000;
        }
    }

    // Reload the controller pointer after the sound call path.
    pad = Pad;

    // Move back around the wheel when Right is triggered.
    if (pad->Right.Triggered != 0)
    {
        SFX_PlayX(0xE9, 0x2000, 0);
        pad->Right.Triggered = 0;

        int idx = Slot;
        idx = idx - 1;
        Slot = idx;
        if (idx < 0)
        {
            int maxItems = NumSlots;
            Slot = maxItems - 1;
        }

        int newIdx = Slot;
        int targetRot = RotMap[newIdx][0];
        int curRot = CurrentRot;
        int diff = targetRot - curRot;
        TargetRot = targetRot;
        if (diff < 0)
        {
            TargetRot = targetRot + 0x1000;
        }
    }

    // Smooth scroll towards target
    int target = TargetRot;
    int current = CurrentRot;
    int diff = target - current;

    if (diff < -0x258)
    {
        CurrentRot = current - 0x80;
    }
    else if (diff >= 0x259)
    {
        CurrentRot = current + 0x80;
    }
    else if (diff < -0x40)
    {
        CurrentRot = current - 0x40;
    }
    else if (diff >= 0x41)
    {
        CurrentRot = current + 0x40;
    }
    else
    {
        CurrentRot = target;
    }

    // Wrap around
    current = CurrentRot;
    if (current >= 0x1000)
    {
        int wrapped = current - 0x1000;
        CurrentRot = wrapped;
        int t = TargetRot;
        TargetRot = t - 0x1000;
    }

    current = CurrentRot;
    if (current < 0)
    {
        int wrapped = current + 0x1000;
        CurrentRot = wrapped;
        int t = TargetRot;
        TargetRot = t + 0x1000;
    }

    ScreenElementList::update();
}

/**
 * Draw the arrow elements and the wheel at its current rotation.
 *
 * Original symbol: `draw__16WheelElementListii` at 0x800829E8.
 *
 * @param x  X coordinate.
 * @param y  Y coordinate.
 */
void WheelElementList::draw(int x, int y)
{
    ScreenElementList::draw(x, y);
    Wheel->draw(mScreenX + x, mScreenY + y, CurrentRot);
}
