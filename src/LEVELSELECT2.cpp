// LEVELSELECT2.cpp -- Reconstructed translation unit
// Original: LEVELSELECT2.CPP
// Functions: 31 reconstructed functions
// Address range: 0x8007FC88 - 0x80081FCC
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

// Owner-local declarations attributed to LEVELSELECT2.cpp by MAIN.SYM.

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

#define SCREENTOOLS_POLYMORPHIC_LAYOUT
#include "SCREENTOOLS.h"

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
struct SDoubleBuffer;

#include "M3D.h"
#include "FRONTSCREENS.h"

#define FRONTEND2STATE_ABSOLUTE_DECLARATIONS
#define FRONTEND2STATE_DECLARE_GAME_MODE
#define FRONTEND2STATE_DECLARE_TWO_PLAYER
#include "FRONTEND2STATE.h"
#define GAMEFMVSTATE_ABSOLUTE_DECLARATION
#define GAMEFMVSTATE_DECLARE_END_X
#define GAMEFMVSTATE_DECLARE_START_X
#define GAMEFMVSTATE_DECLARE_START_Y
#include "GAMEFMVSTATE.h"
// LevelGenerator owns the shared GridCellWidth object.

#include "GAMEFMV.h"
#include <STDDEF.H>
#include <LIBGTE.H>
#include "globals.h"
#include "PSXREGION.h"
#include <LIBGPU.H>

struct GoalScreenElement;
struct GlobeScreenElement;
struct LevelNameScreenElement;
struct LevelSelectScreen;
struct NameScreenElement;
struct PromptScreenElement;
struct CareerScreenElement;
struct SkaterNameScreenElement;
struct VideoScreenElement;
#define SPOOLER_ABSOLUTE_MANAGER_DECLARATION
#include "SPOOLER.h"
#undef SPOOLER_ABSOLUTE_MANAGER_DECLARATION

#include "SCAMERA.h"

/** Ordering-table fields consumed from the active double buffer. */
struct LevelSelectDoubleBuffer {
    unsigned char pad_00[0x84];
    unsigned int *panelOrderingTable;
    unsigned int *globeOrderingTable;
    unsigned char pad_8c[4];
    unsigned short topY;
    unsigned short pad_92;
};

#include "SVIEWPORT.h"

#include "PAD.h"

/** Typed collaborators used by the level-selection owner. */
#include "DB.h"
#include "STATS.h"
#include "SPOOL.h"
#include "PAL.h"
#include "FRONTEND2.h"
#include "FILEIO.h"
#include "MEM.h"
#define M3DMATHS_TYPED_API
#include "M3DMATHS.h"
#undef M3DMATHS_TYPED_API
#include "IMAGE.h"
typedef char levelselect_item_size_must_be_36[
    (sizeof(Item) == 36) ? 1 : -1];
typedef char levelselect_button_size_must_be_16[
    (sizeof(SButton) == 16) ? 1 : -1];
typedef char levelselect_control_size_must_be_364[
    (sizeof(SControl) == 364) ? 1 : -1];
typedef char levelselect_double_buffer_size_must_be_148[
    (sizeof(LevelSelectDoubleBuffer) == 148) ? 1 : -1];
#include "SFX.h"
#include "M3DINIT.h"
#include "MAIN.h"
#include "RFRONT.h"
#include "PACK.h"
#include "SCREENTOOLS.h"
#include "UTILS.h"
#include <STDIO.H>

// === Forward type declarations ===

typedef char levelselect_image_size_must_be_28[
    (sizeof(Image) == 28) ? 1 : -1];
typedef char levelselect_sliced_image_size_must_be_60[
    (sizeof(SlicedImage2) == 60) ? 1 : -1];
typedef char levelselect_sprite_size_must_be_60[
    (sizeof(Sprite2) == 60) ? 1 : -1];

/** Little-endian views used by the PSX texture and VRAM interfaces. */
union LevelSelectPackedInt {
    int value;
    u16 lowHalf;
    s16 lowSignedHalf;
    u8 lowByte;
};

#include "PROMPTSCREENELEMENT.h"

/** Career-medal row (owned by PLAYERSELECT) used by the level-select screen. */
struct CareerScreenElement : ScreenElementList {
    ScreenElement *mpMedalIcons[3];
    int mDelay[9];

    CareerScreenElement(Font *font, int homeX, int homeY, int screenX,
                        int screenY);
    virtual ~CareerScreenElement();
    void update();
    void draw(int x, int y);
    void refresh();
};

/*
 * The exe has the owner tables in the order Goal, Video, Name, LevelName,
 * Globe, SkaterName, LevelSelectScreen; GCC emits them in reverse declaration
 * order, so the classes are declared LevelSelectScreen first.
 */

/** Complete level-selection screen and its child elements. */
struct LevelSelectScreen : ScreenElementList {
    struct LevelNameScreenElement *mpLevelName;
    struct GlobeScreenElement *mpGlobe;
    struct VideoScreenElement *mpVideo;
    struct GoalScreenElement *mpGoal;
    Sprite2 *mBackground;
    Font mFont1;
    Font mFont2;

    LevelSelectScreen();
    virtual ~LevelSelectScreen();
    void draw();
    void update();
    void refresh();
    int isDone(int *return_value);
};

/** One- or two-player skater portrait/name row. */
struct SkaterNameScreenElement : ScreenElementList {
    SpriteScreenElement *mpFace;
    TextScreenElement *mpName;
    Font mFont;

    SkaterNameScreenElement(bool secondPlayer,
                            int homeX, int homeY, int screenX, int screenY);
    virtual ~SkaterNameScreenElement();
};

/** Globe preview and its crosshair overlay. */
struct GlobeScreenElement : ScreenElement {
    struct Item mGlobeItem;
    union {
        int mGlobeRegion;
        unsigned char mGlobeRegionByte;
    };
    Sprite2 *mpCrosshair;
    int mCrossY;
    int mTargetCrossY;
    union {
        int mGlobeRot;
        u16 mGlobeRotLowHalf;
    };
    int mTargetGlobeRot;

    GlobeScreenElement(int, int, int, int);
    virtual ~GlobeScreenElement();
    void SetLevel(int level);
    void draw(int x, int y);
    void update();
};

/** Composite park/city label with its two local fonts. */
struct LevelNameScreenElement : ScreenElementList {
    TextScreenElement *mpPark;
    TextScreenElement *mpCity;
    Font mFont1;
    Font mFont2;
    int mOriginalHomeX;
    int mSpacing;
    int mLevel;
    int mTargetLevel;
    int mState;

    LevelNameScreenElement(int, int, int, int);
    virtual ~LevelNameScreenElement();
    void SetLevel(int level);
    void update();
};

/** Animated text row used by the level and city labels. */
struct NameScreenElement : TextScreenElement {
    NameScreenElement(char *, Font *, int, int, int, int);
    virtual ~NameScreenElement();
    void update();
};

/** Video preview, mask sprites, playback state, and textured quad. */
struct VideoScreenElement : ScreenElementList {
    int mLevel;
    int mNewLevel;
    int mState;
    int mCount;
    LevelSelectPackedInt mVideoVramX;
    LevelSelectPackedInt mVideoVramY;
    LevelSelectPackedInt mVideoW;
    LevelSelectPackedInt mVideoH;
    POLY_FT4 *mVideoPoly;
    Sprite2 *mVideoSprite[2];
    int mVideoOffsX;
    int mVideoOffsY;

    VideoScreenElement(int homeX, int homeY, int screenX, int screenY);
    virtual ~VideoScreenElement();
    void SetLevel(int level);
    void draw(int x, int y);
    void update();
};

/** Goal selector and its eight streamed goal-image sprites. */
struct GoalScreenElement : ScreenElement {
    int mW;
    int mH;
    int mState;
    int mLevel;
    int mLastLevel;
    int mTargetLevel;
    int mFreeLastCount;
    Sprite2 *mpSprite[15];
    int mSpoolID[15];
    int mGoalOffsX;
    int mGoalOffsY;
    int mLeavingX;
    int mLeavingDir;
    int mNextDir;

    GoalScreenElement(int, int, int, int);
    virtual ~GoalScreenElement();
    void SetLevel(int level, int dir);
    void draw(int x, int y);
    void update();
};

typedef char levelselect_goal_element_size_must_be_204[
    (sizeof(GoalScreenElement) == 204) ? 1 : -1];
typedef char levelselect_video_element_size_must_be_156[
    (sizeof(VideoScreenElement) == 156) ? 1 : -1];
typedef char levelselect_packed_int_size_must_be_4[
    (sizeof(LevelSelectPackedInt) == 4) ? 1 : -1];
typedef char levelselect_name_element_size_must_be_44[
    (sizeof(NameScreenElement) == 44) ? 1 : -1];
typedef char levelselect_prompt_element_size_must_be_104[
    (sizeof(PromptScreenElement) == 104) ? 1 : -1];
typedef char levelselect_career_element_size_must_be_152[
    (sizeof(CareerScreenElement) == 152) ? 1 : -1];
typedef char levelselect_level_name_element_size_must_be_292[
    (sizeof(LevelNameScreenElement) == 292) ? 1 : -1];
typedef char levelselect_globe_element_size_must_be_96[
    (sizeof(GlobeScreenElement) == 96) ? 1 : -1];
typedef char levelselect_screen_size_must_be_284[
    (sizeof(LevelSelectScreen) == 284) ? 1 : -1];
typedef char levelselect_skater_name_size_must_be_192[
    (sizeof(SkaterNameScreenElement) == 192) ? 1 : -1];

enum {
    LevelSelectLevelCount = 8,
};

enum LevelSelectAbsoluteAddress {
    LevelSelectDoubleBufferAddress = 0x800DA338,
    LevelSelectSpoolerAddress = 0x800DA694,
};

/**
 * Globe preview viewport and the original small-data pointer that owns it.
 */
static SViewport CreateViewport1 = {
    342, 120, 171, 0,
    10, 30000, 0xD55, 0,
    0, 0,
};
static SViewport *pViewport = &CreateViewport1;

/**
 * Level selected by the front-end globe.
 *
 * The original owner keeps this zero-initialized word between the viewport
 * pointer and its filename pool in `.sdata`.
 */
static int SelectedLevel __attribute__((section(".sdata"))) = 0;

// === External object declarations ===
#include "PDOUBLEBUFFER.h"

// === Resource-name address views ===
/*
 * Keep incomplete address views only for owners whose complete extent is at
 * most the translation unit's -G8 threshold.  Larger arrays are addressed
 * directly through their complete owner definitions below; both forms retain
 * the target's small-data versus absolute-address split.
 */
extern char s_Select_LevelSelect[];
extern char s_Accept_LevelSelect[];
extern char s_Back_LevelSelect[];
extern char s_Globe[];
extern char s_MarBmp[];

/**
 * Owner-local font and image-name storage in its original `.sdata` order.
 *
 * Owners larger than eight bytes are used directly through this namespace;
 * the five smaller owners retain incomplete external address views above so
 * GCC preserves their target small-data addressing.  C linkage preserves the
 * natural linker identifiers without source-level assembly aliases.
 */
namespace LevelSelectAddressViewOwners
{
extern "C"
{
static char s_MainfFnt_LevelSelect[]
    __attribute__((section(".sdata"), aligned(4))) = "mainf.fnt";
static char s_S2font2Fnt_LevelSelect[]
    __attribute__((section(".sdata"), aligned(4))) = "s2font2.fnt";
static char s_S2font1Fnt[]
    __attribute__((section(".sdata"), aligned(4))) = "s2font1.fnt";
static char s_Ingame1Fnt[]
    __attribute__((section(".sdata"), aligned(4))) = "ingame1.fnt";
static char s_S2bgd3Bmp[]
    __attribute__((section(".sdata"), aligned(4))) = "s2bgd3.bmp";
static char s_S2prmpt4Bmp_LevelSelect[]
    __attribute__((section(".sdata"), aligned(4))) = "s2prmpt4.bmp";
static char s_Select_LevelSelect[]
    __attribute__((section(".sdata"), aligned(4))) = "select";
static char s_S2prmpt1Bmp_LevelSelect[]
    __attribute__((section(".sdata"), aligned(4))) = "s2prmpt1.bmp";
static char s_Accept_LevelSelect[]
    __attribute__((section(".sdata"), aligned(4))) = "accept";
static char s_S2prmpt2Bmp_LevelSelect[]
    __attribute__((section(".sdata"), aligned(4))) = "s2prmpt2.bmp";
static char s_Back_LevelSelect[]
    __attribute__((section(".sdata"), aligned(4))) = "back";
static char s_S2versusBmp[]
    __attribute__((section(".sdata"), aligned(4))) = "s2versus.bmp";
static char s_Globe[]
    __attribute__((section(".sdata"), aligned(4))) = "globe";
static char s_S2crosshBmp[]
    __attribute__((section(".sdata"), aligned(4))) = "s2crossh.bmp";
static char s_MarBmp[]
    __attribute__((section(".sdata"), aligned(4))) = "mar.bmp";
static char s_LevnaBmp[]
    __attribute__((section(".sdata"), aligned(4))) = "levna.bmp";
static char s_S2win5Bmp[]
    __attribute__((section(".sdata"), aligned(4))) = "s2win5.bmp";
static char s_S2levl00Bmp[]
    __attribute__((section(".sdata"), aligned(4))) = "s2levl00.bmp";
static char s_S2levl0NumBmp[]
    __attribute__((section(".sdata"), aligned(4))) = "s2levl0%d.bmp";
}
}
/** Read the low halfword of an integer-backed PSX screen coordinate. */
static inline u16 LevelSelect_LowHalf(const int &value)
{
    return *reinterpret_cast<const u16 *>(&value);
}

// === Function implementations (address order) ===

/**
 * LevelSelect2_Main
 *
 * Address:   0x8007FC88
 * Mangled:   LevelSelect2_Main__Fv
 * Demangled: LevelSelect2_Main(void)
 *
 * @return 0
 */
int LevelSelect2_Main(void)
{
    unsigned int oldSkyColor = Db_SkyColor;
    Db_SkyColor = 0;
    Db_UpdateSky();
    Spool_RemoveUnusedTextures();
    Pal_RemoveUnusedPalettes();
    Pack_DefragmentFully();
    FontManager::LoadFont(
        LevelSelectAddressViewOwners::s_MainfFnt_LevelSelect);
    FontManager::LoadFont(
        LevelSelectAddressViewOwners::s_S2font2Fnt_LevelSelect);
    FontManager::LoadFont(
        LevelSelectAddressViewOwners::s_S2font1Fnt);
    FontManager::LoadFont(
        LevelSelectAddressViewOwners::s_Ingame1Fnt);

    LevelSelectScreen *pScreen = new LevelSelectScreen;

    Pad_ClearTriggers(&Pad[0]);
    Pad_ClearTriggers(&Pad[1]);

    int return_value = -1;
    while (1)
    {
        FrontEnd2_UpdateMusicLoop();
        if (pScreen->isDone(&return_value) != 0)
        {
            break;
        }
        GStartTime = Vblanks;
        Db_FlipClear();
        CalcPolyBufferEnd();
        Pad_Update();

        pScreen->update();
        pScreen->draw();
        DrawSync(0);
        Pause(1);
        while ((unsigned int)Vblanks <
               (unsigned int)(GStartTime + 2))
        {
        }
        Db_DisplayDraw();
        PollHost();
    }

    FontManager::UnloadFont(
        LevelSelectAddressViewOwners::s_MainfFnt_LevelSelect);
    FontManager::UnloadFont(
        LevelSelectAddressViewOwners::s_S2font2Fnt_LevelSelect);
    FontManager::UnloadFont(
        LevelSelectAddressViewOwners::s_S2font1Fnt);
    FontManager::UnloadFont(
        LevelSelectAddressViewOwners::s_Ingame1Fnt);
    Db_SkyColor = oldSkyColor;

    delete pScreen;

    return return_value;
}

/**
 * __17LevelSelectScreen
 *
 * Address:   0x8007FE74
 * Mangled:   __17LevelSelectScreen
 * Demangled: LevelSelectScreen::(void)
 *
 * @return `this` pointer (GCC 2.x ctor convention).
 */
LevelSelectScreen::LevelSelectScreen() : ScreenElementList(0, 0, -1, -1)
{

    Sprite2 *sprite = new Sprite2(
        LevelSelectAddressViewOwners::s_S2bgd3Bmp,
        1, 0, 0);
    mBackground = sprite;

    FontManager::GetFont(
        LevelSelectAddressViewOwners::s_MainfFnt_LevelSelect);
    Font *sourceFont = FontManager::GetFont(
        LevelSelectAddressViewOwners::s_S2font2Fnt_LevelSelect);
    mFont2 = *sourceFont;

    mFont2.JustX = 0;
    mFont2.JustY = 3;
    mFont2.R = 0x80;
    mFont2.G = 0x80;
    mFont2.B = 0x80;
    mFont2.Shadow = 0;
    mFont2.SpaceX = 0;
    mFont2.SpaceY = 0;
    mFont2.Scale = 0x1000;

    PromptScreenElement *pPromptElement[3];
    PromptScreenElement *item = new PromptScreenElement(
        LevelSelectAddressViewOwners::s_S2prmpt4Bmp_LevelSelect,
        s_Select_LevelSelect,
        &mFont2, 115, 220, -1, 260);
    pPromptElement[0] = item;

    item = new PromptScreenElement(
        LevelSelectAddressViewOwners::s_S2prmpt1Bmp_LevelSelect,
        s_Accept_LevelSelect,
        &mFont2, 228, 220, -1, 260);
    pPromptElement[1] = item;

    item = new PromptScreenElement(
        LevelSelectAddressViewOwners::s_S2prmpt2Bmp_LevelSelect,
        s_Back_LevelSelect,
        &mFont2, 333, 220, -1, 260);
    pPromptElement[2] = item;

    int i = 0;
    do
    {
        addItem(
            pPromptElement[i]);
        i++;
    } while (i < 3);

    if (FrontEnd2_GameMode == 1)
    {
        CareerScreenElement *item = new CareerScreenElement(&mFont2, 244, 133, 512, 133);
        addItem(
            item);
    }

    if (FrontEnd2_GameMode == 1)
    {
        SkaterNameScreenElement *item2 = new SkaterNameScreenElement(false, 427, 119, 640, 119);
        addItem(item2);
    }
    else if (FrontEnd2_TwoPlayer != 0)
    {
        SkaterNameScreenElement *item2 = new SkaterNameScreenElement(false, 427, 126, 640, -1);
        addItem(item2);

        item2 = new SkaterNameScreenElement(true, 427, 180, 640, -1);
        addItem(item2);
    }
    else
    {
        SkaterNameScreenElement *item2 = new SkaterNameScreenElement(false, 427, 180, 640, 180);
        addItem(item2);
    }

    {
        GlobeScreenElement *item = new GlobeScreenElement(367, 70, -1, -1);
        mpGlobe = item;
        addItem(item);
    }

    {
        LevelNameScreenElement *item = new LevelNameScreenElement(56, 35, -1, -1);
        mpLevelName = item;
        addItem(item);
    }

    {
        VideoScreenElement *item = new VideoScreenElement(61, 126, -128, 126);
        mpVideo = item;
        addItem(item);
    }

    {
        GoalScreenElement *item = new GoalScreenElement(65, 46, -1, -1);
        mpGoal = item;
        addItem(item);
    }
}

/**
 * LevelSelectScreen::~LevelSelectScreen()
 *
 * Address:   0x800802DC
 * Mangled:   _._17LevelSelectScreen
 * Demangled: LevelSelectScreen::~LevelSelectScreen()
 *
 */
LevelSelectScreen::~LevelSelectScreen()
{
    delete mBackground;
}

/**
 * LevelSelectScreen::draw
 *
 * Address:   0x8008036C
 * Mangled:   draw__17LevelSelectScreen
 * Demangled: LevelSelectScreen::draw(void)
 *
 */
void LevelSelectScreen::draw()
{
    ScreenElementList::draw(0, 0);
    mBackground->draw(0, 0, 1);
}

/**
 * LevelSelectScreen::update
 *
 * Address:   0x800803B8
 * Mangled:   update__17LevelSelectScreen
 * Demangled: LevelSelectScreen::update(void)
 *            Advance the level-selection cursor and propagate the chosen level to child
 *            screen elements whenever the left/right pad flags fire.
 *
 */
void LevelSelectScreen::update()
{
    if (Pad[0].Left.Triggered != 0)
    {
        SFX_PlayX(0xEA, 0x2000, 0);
        Pad[0].Left.Triggered = 0;
        SelectedLevel--;
        if (SelectedLevel < 0)
        {
            SelectedLevel = LevelSelectLevelCount - 1;
        }

        mpLevelName->SetLevel(SelectedLevel);
        mpGlobe->SetLevel(SelectedLevel);
        mpVideo->SetLevel(SelectedLevel);
        mpGoal->SetLevel(SelectedLevel, 1);
    }

    if (Pad[0].Right.Triggered != 0)
    {
        SFX_PlayX(0xEA, 0x2000, 0);
        Pad[0].Right.Triggered = 0;
        SelectedLevel++;
        if (SelectedLevel >= LevelSelectLevelCount)
        {
            SelectedLevel = 0;
        }

        mpLevelName->SetLevel(SelectedLevel);
        mpGlobe->SetLevel(SelectedLevel);
        mpVideo->SetLevel(SelectedLevel);
        mpGoal->SetLevel(SelectedLevel, 0);
    }

    ScreenElementList::update();
}

/**
 * LevelSelectScreen::refresh
 *
 * Address:   0x800804EC
 * Mangled:   refresh__17LevelSelectScreen
 * Demangled: LevelSelectScreen::refresh(void)
 *
 */
void LevelSelectScreen::refresh()
{
}

/**
 * LevelSelectScreen::isDone
 *
 * Address:   0x800804F4
 * Mangled:   isDone__17LevelSelectScreenPi
 * Demangled: LevelSelectScreen::isDone(int *)
 *
 * @param return_value Receives the selected level, or -1 when backing out.
 * @return Nonzero once the screen has accepted a selection or back command.
 */
int LevelSelectScreen::isDone(int *return_value)
{
    if (Pad[0].X.Triggered != 0 || Pad[0].Start.Triggered != 0)
    {
        Pad[0].Start.Triggered = 0;
        Pad[0].X.Triggered = 0;
        if ((signed char)Levels[SelectedLevel].STR != -27)
        {
            SFX_PlayX(0x92, 0x2000, 0);
            return 0;
        }
        SFX_PlayX(0x91, 0x2000, 0);
        *return_value = SelectedLevel;
        return 1;
    }
    else if (Pad[0].Triangle.Triggered != 0)
    {
        SFX_PlayX(0x93, 0x2000, 0);
        Pad[0].Triangle.Triggered = 0;
        *return_value = -1;
        return 1;
    }
    return 0;
}

/**
 * SkaterNameScreenElement constructor
 *
 * Address:   0x800805E0
 * Mangled:   __23SkaterNameScreenElementbiiii
 * Demangled: SkaterNameScreenElement::(bool, int, int, int, int)
 *
 * @return `this` pointer (GCC 2.x ctor convention).
 */
SkaterNameScreenElement::SkaterNameScreenElement(
    bool secondPlayer,
    int homeX, int homeY, int screenX, int screenY)
    : ScreenElementList(homeX, homeY, screenX, screenY)
{
    Font *font = &mFont;

    Font *sourceFont = FontManager::GetFont(
        LevelSelectAddressViewOwners::s_S2font1Fnt);
    mFont = *sourceFont;

    mFont.JustX = 2;
    mFont.JustY = 2;
    mFont.R = 0x80;
    mFont.G = 0x80;
    mFont.B = 0x80;
    mFont.Shadow = 0;
    mFont.SpaceX = 0;
    mFont.SpaceY = 0;
    mFont.Scale = 0x1000;

    if (secondPlayer)
    {
        SpriteScreenElement *pElement = new SpriteScreenElement(Stats[SelectedSkater2].PortraitName, 0, -32, -1, -1, 0, 0);
        mpFace = pElement;

        TextScreenElement *name = new TextScreenElement(Stats[SelectedSkater2].Name, font, -2, 17, -2, -30);
        mpName = name;

        SpriteScreenElement *versus = new SpriteScreenElement(LevelSelectAddressViewOwners::s_S2versusBmp, -76, -36, -1, -1, 0, 0);
        addItem(versus);
    }
    else
    {
        SpriteScreenElement *pElement = new SpriteScreenElement(Stats[SelectedSkater].PortraitName, 0, -32, -1, -1, 0, 0);
        mpFace = pElement;

        TextScreenElement *name = new TextScreenElement(Stats[SelectedSkater].Name, font, -2, 17, -2, -30);
        mpName = name;
    }

    addItem(mpFace);
    addItem(mpName);
}

/**
 * SkaterNameScreenElement::~SkaterNameScreenElement()
 *
 * Address:   0x800808D8
 * Mangled:   _._23SkaterNameScreenElement
 * Demangled: SkaterNameScreenElement::~SkaterNameScreenElement()
 *
 */
SkaterNameScreenElement::~SkaterNameScreenElement()
{
}

/**
 * GlobeScreenElement constructor
 *
 * Address:   0x8008093C
 * Mangled:   __18GlobeScreenElementiiii
 * Demangled: GlobeScreenElement::(int, int, int, int)
 *
 */
GlobeScreenElement::GlobeScreenElement(
    int homeX, int homeY, int screenX, int screenY)
    : ScreenElement(homeX, homeY, screenX, screenY)
{
    mGlobeRegion = Spool_PSX(s_Globe, 0, 0, 1);
    Spool_Sync();

    Item *pItemList = &mGlobeItem;
    pItemList->Flags = 0;
    pItemList->Inquiry = 0;
    pItemList->Position.vx = 0;
    pItemList->Position.vy = 0;
    pItemList->Position.vz = -0x50000;
    pItemList->Angles.vx = 0;
    pItemList->Angles.vy = 0;
    pItemList->Angles.vz = 0;
    pItemList->Frame = 0;
    pItemList->TintIndex = 0;
    pItemList->Anim = 0;
    pItemList->Model = 0;
    pItemList->Region = mGlobeRegionByte;
    pItemList->RGB = 0xFF00;
    pItemList->NextItem = 0;

    M3dMaths_SetIdentityRotation(
        &MikeCamera->Transform);
    MikeCamera->Position.vx = 0;
    MikeCamera->Position.vy = 0;
    MikeCamera->Position.vz = -300;
    TransMatrix(
        &MikeCamera->Transform,
        &MikeCamera->Position);
    M3dInit_SetFoggingParams(10, 6000, 0x800);
    M3dInit_InitAtStart();

    Sprite2 *crosshair = new Sprite2(
        LevelSelectAddressViewOwners::s_S2crosshBmp,
        1, 0, 0);
    mpCrosshair = crosshair;
    crosshair->JustX = 1;
    mpCrosshair->JustY = 1;

    int level = SelectedLevel;
    mGlobeRot = Levels[level].map_loc[0];
    mCrossY = Levels[level].map_loc[1];
    SetLevel(level);
}

/**
 * GlobeScreenElement destructor
 *
 * Address:   0x80080AB0
 * Mangled:   _._18GlobeScreenElement
 * Demangled: GlobeScreenElement::~GlobeScreenElement()
 *
 */
GlobeScreenElement::~GlobeScreenElement()
{
    ClearRegion(mGlobeRegion, 1, 0);
    PSXRegion[mGlobeRegion].Filename[0] = 0;
    delete mpCrosshair;
}

/**
 *
 * Address:   0x80080B58
 * Mangled:   update__18GlobeScreenElement
 * Demangled: GlobeScreenElement::update(void)
 *            Ease the globe rotation and crosshair toward their selected-level targets.
 *
 */
void GlobeScreenElement::update()
{
    int diff = this->mTargetGlobeRot - this->mGlobeRot;

    this->mGlobeItem.Angles.vy = (short)this->mGlobeRotLowHalf;

    if (diff >= 0x801)
    {
        this->mTargetGlobeRot = this->mTargetGlobeRot - 0x1000;
        diff -= 0x1000;
    }
    else if (diff < -0x800)
    {
        this->mTargetGlobeRot = this->mTargetGlobeRot + 0x1000;
        diff += 0x1000;
    }

    if ((unsigned int)(diff + 3) < 7)
    {
        this->mGlobeRot = this->mTargetGlobeRot;
    }

    int currentRotation = this->mGlobeRot + (diff >> 2);
    this->mGlobeRot = currentRotation;
    if (currentRotation < 0)
    {
        this->mGlobeRot = currentRotation + 0x1000;
        this->mTargetGlobeRot = this->mTargetGlobeRot + 0x1000;
    }

    currentRotation = this->mGlobeRot;
    if (currentRotation >= 0x1000)
    {
        this->mGlobeRot = currentRotation - 0x1000;
        this->mTargetGlobeRot = this->mTargetGlobeRot - 0x1000;
    }

    int crossY = this->mCrossY;
    int targetCrossY = this->mTargetCrossY;
    int crossDelta = targetCrossY - crossY;
    if ((unsigned int)(crossDelta + 3) < 7)
    {
        this->mCrossY = targetCrossY;
        crossY = targetCrossY;
    }
    int crossStep = crossDelta >> 2;
    this->mCrossY = crossY + crossStep;
    ScreenElement::update();
}

/**
 * GlobeScreenElement::draw
 *
 * Address:   0x80080C54
 * Mangled:   draw__18GlobeScreenElementii
 * Demangled: GlobeScreenElement::draw(int, int)
 *
 * @param x  X coordinate.
 * @param y  Y coordinate.
 */
void GlobeScreenElement::draw(int x, int y)
{
    SViewport *vp = pViewport;

    u16 cx1 = LevelSelect_LowHalf(mScreenX);
    vp->xL = (s16)(cx1 + x - 65);

    u16 cy1 = LevelSelect_LowHalf(mScreenY);
    vp->yT = (s16)(cy1 + y - 40);

    u16 cx2 = LevelSelect_LowHalf(mScreenX);
    vp->xR = (s16)(cx2 + x + 65);

    u16 cy2 = LevelSelect_LowHalf(mScreenY);
    LevelSelectDoubleBuffer *db =
        reinterpret_cast<LevelSelectDoubleBuffer *>(pDoubleBuffer);
    vp->yB = (s16)(cy2 + y + 40);

    unsigned int *ot = db->globeOrderingTable;
    M3d_RenderSetup(MikeCamera, vp, ot);
    M3d_Render(&mGlobeItem);
    M3d_RenderCleanup();
    Sprite2 *obj = mpCrosshair;
    int a1 = mScreenX;
    int a2 = mScreenY;
    int crossY = mCrossY;
    obj->draw(a1 + x, a2 + crossY + y, 0);
}

/**
 * Looks up the level entry in GlobeLevelTable and copies the globe element fields.
 *
 * Address:   0x80080D2C, Size: 56 bytes (14 instructions)
 * Mangled:   SetLevel__18GlobeScreenElementi
 * Demangled: GlobeScreenElement::SetLevel(int)
 *            Assembly:
 *            lui $a2, 0x800b             ; table base
 *            addiu $a2, $a2, 0x6764
 *            sll $v0, $a1, 3             ; level*8
 *            subu $v0, $v0, $a1          ; level*7
 *            sll $v0, $v0, 2             ; level*28
 *            addu $v0, $v0, $a1          ; level*29
 *            sll $v0, $v0, 2             ; level*116
 *            addu $v1, $a2, $v0          ; &table[level]
 *            lw $a1, 0x2c($v1)           ; table[level].field_2C
 *            move $a2, $v1               ; (reuse for next load)
 *            sw $a1, 0x5c($a0)           ; this->0x5C = field_2C
 *            lw $v1, 0x30($a2)           ; table[level].field_30
 *            jr $ra
 *            sw $v1, 0x54($a0)           ; this->0x54 = field_30
 *            Update this globe's target rotation and display frame from the selected level entry.
 *
 * @param level Level whose globe rotation and crosshair target should be used.
 */
void GlobeScreenElement::SetLevel(int level)
{
    mTargetGlobeRot = Levels[level].map_loc[0];
    mTargetCrossY = Levels[level].map_loc[1];
}

/**
 * LevelNameScreenElement constructor
 *
 * Address:   0x80080D64
 * Mangled:   __22LevelNameScreenElementiiii
 * Demangled: LevelNameScreenElement::(int, int, int, int)
 *
 * Construct the park/city label pair and initialize its two local font styles.
 *
 * @param homeX Initial home-space X coordinate.
 * @param homeY Initial home-space Y coordinate.
 * @param screenX Initial screen-space X coordinate.
 * @param screenY Initial screen-space Y coordinate.
 */
LevelNameScreenElement::LevelNameScreenElement(int homeX, int homeY, int screenX, int screenY)
    : ScreenElementList(homeX, homeY, screenX, screenY)
{

    Font *sourceFont = FontManager::GetFont(
        LevelSelectAddressViewOwners::s_S2font1Fnt);
    mFont1 = *sourceFont;

    mFont1.JustX = 2;
    mFont1.JustY = 3;
    mFont1.R = 0x80;
    mFont1.G = 0x80;
    mFont1.B = 0x80;
    mFont1.Shadow = 0;
    mFont1.SpaceX = 0;
    mFont1.SpaceY = 0;
    mFont1.Scale = 0x1000;
    mFont2 = mFont1;

    mFont2.JustX = 0;
    mSpacing = 20;

    NameScreenElement *park = new NameScreenElement(Levels[SelectedLevel].pLevelName, &mFont1, -262, 0, -1, -1);
    mpPark = park;

    NameScreenElement *city = new NameScreenElement(Levels[SelectedLevel].pCityName, &mFont2, 522, 0, -1, -1);
    mpCity = city;

    mOriginalHomeX = mHomeX;
    addItem(mpPark);
    addItem(mpCity);
    SetLevel(SelectedLevel);

}

/**
 * LevelNameScreenElement destructor
 *
 * Address:   0x80080F88
 * Mangled:   _._22LevelNameScreenElement
 * Demangled: LevelNameScreenElement::~LevelNameScreenElement()
 *
 */
LevelNameScreenElement::~LevelNameScreenElement()
{
}

/**
 * SetLevel__22LevelNameScreenElementi — Set level, animation state, and sub-element targets
 *
 * Address:   0x80080FF8, Size: 40 bytes (10 instructions)
 * Mangled:   SetLevel__22LevelNameScreenElementi
 * Demangled: LevelNameScreenElement::SetLevel(int)
 *            Assembly:
 *            addiu $v0, $zero, 2        ; state = 2
 *            sw $a1, 0x11c($a0)         ; this->level = level
 *            lw $a1, 0x68($a0)          ; elem1 = this->elem1
 *            addiu $v1, $zero, -0x106   ; target1 = -0x106
 *            sw $v0, 0x120($a0)         ; this->state = 2
 *            sw $v1, 4($a1)             ; elem1->target = -0x106
 *            lw $a2, 0x6c($a0)          ; elem2 = this->elem2
 *            addiu $v0, $zero, 0x20a    ; target2 = 0x20A
 *            jr $ra
 *            sw $v0, 4($a2)             ; elem2->target = 0x20A
 *
 * @param level Level whose park/city labels should be displayed.
 */
void LevelNameScreenElement::SetLevel(int level)
{
    mTargetLevel = level;
    mState = 2;
    mpPark->mHomeX = -262;
    mpCity->mHomeX = 522;
}

/**
 * LevelNameScreenElement::update
 *
 * Address:   0x80081020
 * Mangled:   update__22LevelNameScreenElement
 * Demangled: LevelNameScreenElement::update(void)
 *            Drive the level-name transition state machine and keep the two text children
 *            aligned while their scroll animation settles.
 *
 */
void LevelNameScreenElement::update()
{
    ScreenElementList::update();

    switch (mState)
    {
    case 0:
        mLevel = mTargetLevel;
        mpPark->mHomeX = (-mSpacing) >> 1;
        mpCity->mHomeX = mSpacing >> 1;

        mpPark->setString(Levels[mLevel].pLevelName);
        mpCity->setString(Levels[mLevel].pCityName);

        {
            int width = mpPark->width();
            int homeX = mOriginalHomeX + width + (mSpacing >> 1);
            mState = 1;
            mHomeX = homeX;
            mScreenX = homeX;
        }
        break;

    case 2:
        if (mpCity->mAtHome != 0)
        {
            if (mpPark->mAtHome != 0)
            {
                mState = 0;
            }
        }
        break;
    }
}

/**
 * Construct the animated text row and install its owner dispatch table.
 *
 * Address: 0x80081174
 * Mangled: __17NameScreenElementPcP4Fontiiii
 */
NameScreenElement::NameScreenElement(
    char *pString, Font *pFont,
    int homeX, int homeY, int screenX, int screenY)
    : TextScreenElement(pString, pFont, homeX, homeY, screenX, screenY)
{
}

/**
 * NameScreenElement destructor
 *
 * Address:   0x800811C0
 * Mangled:   _._17NameScreenElement
 * Demangled: NameScreenElement::~NameScreenElement()
 *
 */
NameScreenElement::~NameScreenElement()
{
}

/**
 * Ease this element toward its home position, then latch the at-home flag.
 *
 * Address: 0x80081214
 * Mangled: update__17NameScreenElement
 */
void NameScreenElement::update()
{
    ScreenElement *elem = this;
    int distX;
    int distY;

    if (0 < elem->mDelay)
    {
        elem->mDelay -= 1;
        return;
    }

    distX = elem->mHomeX - elem->mScreenX;
    if ((unsigned int)(distX + 1) < 3)
    {
        elem->mScreenX = elem->mHomeX;
    }
    else
    {
        int add = distX >> 1;
        elem->mScreenX += add;
    }

    distY = elem->mHomeY - elem->mScreenY;
    if ((unsigned int)(distY + 1) < 3)
    {
        elem->mScreenY = elem->mHomeY;
    }
    else
    {
        int add = distY >> 1;
        elem->mScreenY += add;
    }

    if ((elem->mScreenY == elem->mHomeY) &&
        (elem->mScreenX == elem->mHomeX))
    {
        elem->mAtHome = (void *)1;
        return;
    }

    elem->mAtHome = 0;
}

/**
 * Build the level preview element tree and initialize playback state.
 *
 * Address: 0x800812C4
 * Mangled: __18VideoScreenElementiiii
 *
 * @param homeX  Home X coordinate (resting position).
 * @param homeY  Home Y coordinate (resting position).
 * @param screenX  Screen-space X coordinate.
 * @param screenY  Screen-space Y coordinate.
 */
VideoScreenElement::VideoScreenElement(int homeX, int homeY, int screenX, int screenY)
    : ScreenElementList(homeX, homeY, screenX, screenY)
{
    {
        Sprite2 *sprite = new Sprite2(s_MarBmp, 1, 0, 0);
        mVideoSprite[0] = sprite;
    }

    {
        Sprite2 *sprite = new Sprite2(
            LevelSelectAddressViewOwners::s_LevnaBmp,
            1, 0, 0);
        mVideoSprite[1] = sprite;
    }

    {
        SpriteScreenElement *item = new SpriteScreenElement(LevelSelectAddressViewOwners::s_S2win5Bmp, 0, 0, -1, -1, 0, 0);
        addItem(item);
    }

    mVideoW.value = 176;
    mVideoH.value = 48;
    Pack_Pack(0, 176, 48,
              &mVideoVramX.value, &mVideoVramY.value, 16, 0, 0);

    {
        POLY_FT4 *videoPoly = (POLY_FT4 *)Mem_New(sizeof(POLY_FT4), 1, 1);
        mVideoPoly = videoPoly;
        setlen(videoPoly, 9);
        mVideoPoly->code = 0x2C;
        mVideoPoly->r0 = 0x80;
        mVideoPoly->g0 = 0x80;
        mVideoPoly->b0 = 0x80;
        mVideoPoly->u0 = mVideoVramX.lowByte & 0x3F;
        mVideoPoly->v0 = mVideoVramY.lowByte;
        mVideoPoly->u1 = (u8)(mVideoW.lowByte +
                              (mVideoVramX.lowByte & 0x3F));
        mVideoPoly->v1 = mVideoVramY.lowByte;
        mVideoPoly->u2 = mVideoVramX.lowByte & 0x3F;
        {
            u8 videoY = mVideoVramY.lowByte;
            u8 videoH = mVideoH.lowByte;
            mVideoPoly->v2 = (u8)(videoH + videoY);
        }
        mVideoPoly->u3 = (u8)(mVideoW.lowByte +
                              (mVideoVramX.lowByte & 0x3F));
        {
            u8 videoY = mVideoVramY.lowByte;
            u8 videoH = mVideoH.lowByte;
            mVideoPoly->v3 = (u8)(videoH + videoY);
        }

        mVideoPoly->code = (u8)(mVideoPoly->code & 0xFD);
        mVideoPoly->code = (u8)(mVideoPoly->code & 0xFE);

        u8 *videoBytes = (u8 *)mVideoPoly;
        int level = SelectedLevel;
        int tpage = (mVideoVramY.value & 0x100) >> 4;
        int xPage = ((mVideoVramX.value & 0x3FF) >> 6) | 0x100;
        tpage |= xPage;
        tpage |= (mVideoVramY.lowHalf & 0x200) << 2;
        ((POLY_FT4 *)videoBytes)->tpage = (u16)tpage;

        mLevel = level;
    }

    mNewLevel = -1;
    mState = 0;
    mCount = 32;
    mVideoOffsX = 10;
    mVideoOffsY = 19;
}

/**
 * VideoScreenElement destructor
 *
 * Address:   0x80081548
 * Mangled:   _._18VideoScreenElement
 * Demangled: VideoScreenElement::~VideoScreenElement()
 *
 */
VideoScreenElement::~VideoScreenElement()
{
    delete mVideoSprite[0];
    delete mVideoSprite[1];
    Mem_Delete(mVideoPoly);
    Pack_Unpack(mVideoVramX.lowSignedHalf, mVideoVramY.lowSignedHalf);
}

/**
 * VideoScreenElement::draw(int, int) - draw the level preview video quad or
 * placeholder sprite, copy the ready frame into VRAM, then draw child elements.
 *
 * Address: 0x80081604
 * Mangled: draw__18VideoScreenElementii
 *
 * @param x  X coordinate.
 * @param y  Y coordinate.
 */
void VideoScreenElement::draw(int x, int y)
{
    int video_x = mScreenX + x + mVideoOffsX;
    int video_y = mScreenY + y + mVideoOffsY;

    if ((unsigned int)(mState - 3) < 2)
    {
        LevelSelectDoubleBuffer *db =
            *(LevelSelectDoubleBuffer **)LevelSelectDoubleBufferAddress;
        mVideoPoly->x0 = (s16)video_x;
        mVideoPoly->y0 = (s16)video_y;
        mVideoPoly->x1 = (s16)(mVideoW.lowHalf + video_x);
        mVideoPoly->y1 = (s16)video_y;
        mVideoPoly->x2 = (s16)video_x;
        mVideoPoly->y2 = (s16)(mVideoH.lowHalf + video_y);
        mVideoPoly->x3 = (s16)(mVideoW.lowHalf + video_x);
        mVideoPoly->y3 = (s16)(mVideoH.lowHalf + video_y);

        unsigned int *panelOT = db->panelOrderingTable;
        mVideoPoly->tag =
            (mVideoPoly->tag & 0xFF000000) | (*panelOT & 0x00FFFFFF);
        unsigned int *panelOT2 = db->panelOrderingTable;
        *panelOT2 =
            (*panelOT2 & 0xFF000000) |
            ((unsigned int)mVideoPoly & 0x00FFFFFF);
    }
    else
    {
        SLevel *table = Levels;
        int level = mLevel;
        SLevel *entry = &table[level];
        signed char movie = entry->STR;
        if (movie == -27)
        {
            Sprite2 *sprite = mVideoSprite[0];
            sprite->draw(video_x, video_y, 0);
        }
        else
        {
            Sprite2 *sprite = mVideoSprite[1];
            sprite->draw(video_x, video_y, 0);
        }
    }

    if (mState == 2)
    {
        if (mCount == 0)
        {
            RECT r;
            LevelSelectDoubleBuffer *db =
                *(LevelSelectDoubleBuffer **)LevelSelectDoubleBufferAddress;
            r.x = (s16)video_x;
            u16 videoW = mVideoW.lowHalf;
            u16 videoH = mVideoH.lowHalf;
            int topY = db->topY;
            r.w = videoW;
            r.h = videoH;
            r.y = (s16)(topY + video_y);
            MoveImage(
                &r, mVideoVramX.value, mVideoVramY.value);
            mState = 3;
        }
    }

    ScreenElementList::draw(x, y);
}

/**
 * VideoScreenElement::update(void) - advances the level-preview state machine:
 * wait for the preload spooler, start/sync/stop FMV playback, and swap levels.
 *
 * Address: 0x80081804
 * Mangled: update__18VideoScreenElement
 *
 */
void VideoScreenElement::update()
{
    switch (mState)
    {
    case 0:
    {
        int count = mCount;
        if (count != 0)
        {
            count--;
            mCount = count;
            if (count != 0)
            {
                break;
            }
        }
        if ((*(Spooler **)LevelSelectSpoolerAddress)->IsSetDone())
        {
            mState = 1;
        }
        break;
    }
    case 1:
    {
        int level = mLevel;
        SLevel *table = Levels;
        signed char movie = table[level].STR;
        if (movie != 0)
        {
            GameFMV_SetStartTrack(movie);
            int videoX = mVideoVramX.lowHalf;
            int videoW = mVideoW.lowHalf;
            int videoY = mVideoVramY.lowHalf;
            GameFMV_StartX = videoX;
            GameFMV_EndX = videoX + videoW;
            GameFMV_StartY = videoY;
            GameFMV_StartFMV(1);
        }
        mState = 2;
        mCount = 2;
        break;
    }
    case 2:
        mCount = mCount - 1;
        break;
    case 3:
        GameFMV_SyncFMV(1);
        if (mNewLevel != -1)
        {
            mState = 4;
        }
        break;
    case 4:
    {
        int level = mLevel;
        SLevel *table = Levels;
        signed char movie = table[level].STR;
        if (movie != 0)
        {
            GameFMV_StopFMV();
        }
        int newLevel = mNewLevel;
        mNewLevel = -1;
        mState = 1;
        mLevel = newLevel;
        break;
    }
    }
    ScreenElementList::update();
}

/**
 * VideoScreenElement::SetLevel — queue a new level preview.
 *
 * Address:   0x80081998, Size: 8 bytes (2 instructions)
 * Mangled:   SetLevel__18VideoScreenElementi
 * Demangled: VideoScreenElement::SetLevel(int)
 *            Assembly: jr $ra; sw $a1, 0x6c($a0)
 *
 * @param level Level whose preview should be queued.
 */
void VideoScreenElement::SetLevel(int level)
{
    mNewLevel = level;
}

/**
 * GoalScreenElement constructor
 *
 * Address:   0x800819A0
 * Mangled:   __17GoalScreenElementiiii
 * Demangled: GoalScreenElement::(int, int, int, int)
 *
 */
GoalScreenElement::GoalScreenElement(int homeX, int homeY, int screenX, int screenY)
    : ScreenElement(homeX, homeY, screenX, screenY)
{
    unsigned int size = FileIO_Open(
        LevelSelectAddressViewOwners::s_S2levl00Bmp);
    unsigned char *bmpBuf = (unsigned char *)Mem_New(size, 1, 1);
    FileIO_Load(bmpBuf);
    FileIO_Sync();

    {
        int i = 0;
        do
        {
            Sprite2 *sprite = new Sprite2(bmpBuf, 0, 0, 0);
            mpSprite[i] = sprite;
            mpSprite[i]->JustX = 1;
            mpSprite[i]->JustY = 1;
            i++;
        } while (i < LevelSelectLevelCount);
    }

    Mem_Delete(bmpBuf);

    int i = 0;
    int level = SelectedLevel;
    mLevel = level;
    mpSprite[level]->pack();
    mW = mpSprite[mLevel]->screenWidth();
    mH = mpSprite[mLevel]->screenHeight();
    mGoalOffsY = mH >> 1;
    mState = 0;
    mTargetLevel = -1;
    mFreeLastCount = 0;
    mGoalOffsX = mW >> 1;

    Spooler::SpoolMgr->Reset();

    int order[LevelSelectLevelCount];
    Spooler::OrderHelper(order, 8, SelectedLevel);

    char name[16];
    do
    {
        int num = order[i];
        sprintf(name,
                LevelSelectAddressViewOwners::s_S2levl0NumBmp,
                num % 9 + 1);
        mSpoolID[num] = Spooler::SpoolMgr->AddFile(name, 0);
        i++;
    } while (i < LevelSelectLevelCount);

    Spooler::SpoolMgr->Spooool();
}

/**
 * GoalScreenElement destructor
 *
 * Address:   0x80081BB4
 * Mangled:   _._17GoalScreenElement
 * Demangled: GoalScreenElement::~GoalScreenElement()
 *            Destroy goal sprites and reset the front-end preload spooler.
 *
 */
GoalScreenElement::~GoalScreenElement()
{
    int i = 0;
    Sprite2 **ptr = mpSprite;
    do
    {
        delete *ptr;
        i++;
        ptr++;
    } while (i < LevelSelectLevelCount);
    Spooler::SpoolMgr->Reset();
}

/**
 * GoalScreenElement::update
 *
 * Address:   0x80081C6C
 * Mangled:   update__17GoalScreenElement
 * Demangled: GoalScreenElement::update(void)
 *
 * Poll the eight goal-image spools, install completed sprite data, and advance
 * the outgoing-goal scale/slide state machine.
 */
void GoalScreenElement::update()
{
    Spooler::SpoolMgr->Update();

    for (int i = 0; i < LevelSelectLevelCount; i++)
    {
        if (Spooler::SpoolMgr->IsFileLoaded(mSpoolID[i]))
        {
            void *theData = Spooler::SpoolMgr->GetFile(mSpoolID[i]);
            Sprite2 *sprite = mpSprite[i];
            sprite->setData(theData);
            Mem_Delete(theData);
        }
    }

    switch (mState)
    {
    case 0:
        if (mTargetLevel != -1)
        {
            int newLevel = mTargetLevel;
            int oldLevel = mLevel;
            mLevel = newLevel;
            mTargetLevel = -1;
            mLastLevel = oldLevel;
            mpSprite[newLevel]->pack();
            mLeavingX = 0;
            mState = 1;
            mLeavingDir = mNextDir;
        }
        break;

    case 1:
    {
        mpSprite[mLastLevel]->Scale += 400;

        int scale_offs = ((mpSprite[mLastLevel]->Scale * mW) >> 13)
            + (mW >> 1);
        mLeavingX += mLeavingDir;

        if (mLeavingDir > 0)
        {
            mLeavingDir += (mLeavingDir >> 1) + 1;
        }
        else
        {
            mLeavingDir += (mLeavingDir >> 1) - 1;
        }

        if (scale_offs < mLeavingX || mLeavingX < -scale_offs)
        {
            mFreeLastCount = 2;
            mState = 2;
        }
        break;
    }

    case 2:
        if (mFreeLastCount != 0)
        {
            mFreeLastCount--;
            if (mFreeLastCount == 0)
            {
                mpSprite[mLastLevel]->Scale = 0x1000;
                mpSprite[mLastLevel]->unpack();
                mState = 0;
            }
        }
        break;
    }

    ScreenElement::update();
}

/**
 * GoalScreenElement::draw
 *
 * Address:   0x80081EC8
 * Mangled:   draw__17GoalScreenElementii
 * Demangled: GoalScreenElement::draw(int, int)
 *
 * @param x  X coordinate.
 * @param y  Y coordinate.
 */
// Draw the scrolling goal entry pair, then restore this element's clipping box.
void GoalScreenElement::draw(int x, int y)
{
    SetClippingBox2(0, 0, 512, 256);
    if (mState == 1)
    {
        int sx = mScreenX;
        int offsetX = mGoalOffsX;
        int offsetX2 = mLeavingX;
        int idx = mLastLevel;
        int sy = mScreenY;
        sx = sx + x + offsetX + offsetX2;
        Sprite2 *item = mpSprite[idx];
        int offsetY = mGoalOffsY;
        sy = sy + y + offsetY;
        item->draw(sx, sy, 0);
    }
    int sx2 = mScreenX;
    int offsetX3 = mGoalOffsX;
    int idx3 = mLevel;
    int sy2 = mScreenY;
    sx2 = sx2 + x + offsetX3;
    Sprite2 *item2 = mpSprite[idx3];
    int offsetY2 = mGoalOffsY;
    sy2 = sy2 + y + offsetY2;
    item2->draw(sx2, sy2, 0);
    int clipW = mW;
    int clipH = mH;
    int cx = mScreenX;
    int cy = mScreenY;
    SetClippingBox2(cx + x, cy + y, clipW, clipH);
}

/**
 * SetLevel__17GoalScreenElementii — Conditionally update level and direction
 *
 * Address:   0x80081FCC, Size: 36 bytes (9 instructions)
 * Mangled:   SetLevel__17GoalScreenElementii
 * Demangled: GoalScreenElement::SetLevel(int, int)
 *            Assembly:
 *            lw $v0, 0x30($a0)          ; old = this->0x30
 *            nop
 *            beq $a1, $v0, .exit        ; if (level == old) skip
 *            sll $v0, $a2, 1            ; dir = param2 * 2
 *            addiu $v0, $v0, -1         ; dir = param2*2 - 1
 *            sw $v0, 0xc8($a0)          ; this->0xC8 = dir
 *            sw $a1, 0x38($a0)          ; this->0x38 = level
 *            .exit:
 *            jr $ra
 *            nop
 *
 * @param level Level whose goal list should replace the current one.
 * @param dir  Direction.
 */
void GoalScreenElement::SetLevel(int level, int dir)
{
    if (level != mLevel)
    {
        mNextDir = dir * 2 - 1;
        mTargetLevel = level;
    }
}
