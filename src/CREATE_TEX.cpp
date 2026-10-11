// CREATE_TEX.cpp -- Reconstructed translation unit
// Original: CREATE_TEX.CPP
// Functions: 9 reconstructed entries
// Address range: 0x8006D0C0 - 0x8006D86C
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#include "CCLASS_POLY.h"
#define CREATE_TEX_POLYMORPHIC_LAYOUT

#define CREATE_TEX_LIST_LAYOUT
#define CREATE_TEX_LIST_LAYOUT_ONLY
#include "CREATE.h"
#undef CREATE_TEX_LIST_LAYOUT_ONLY
#undef CREATE_TEX_LIST_LAYOUT

#define CREATE_TEX_SPEC_LAYOUT
#define CREATE_TEX_SPEC_LAYOUT_ONLY
#include "CREATE.h"
#undef CREATE_TEX_SPEC_LAYOUT_ONLY
#undef CREATE_TEX_SPEC_LAYOUT

typedef char CreateTex_Spec_size_must_be_72[(sizeof(CCreateTexSpec) == 72) ? 1 : -1];
/** Shared declarations for the process-lifetime specification catalogs. */
#include "CREATETEXSPECS.h"

/*
 * CREATE_TEX's complete initialized small-data contribution.  The texture
 * names, menu labels, and two-entry texture lists occupy
 * 0x800DAB50-0x800DB260 in the target.  Keeping the semantic objects in target
 * order preserves every pointer relocation without raw-address initializers.
 */
static char CreateTex_faceSkin2[] __attribute__((section(".sdata"), aligned(4))) = "fceskin2";
static char CreateTex_buzzCut[] __attribute__((section(".sdata"), aligned(4))) = "Buzz cut";
static char CreateTex_faceAsian3[] __attribute__((section(".sdata"), aligned(4))) = "fceAsn_3";
namespace CreateTexAddressViewOwners
{
extern "C"
{
static char CreateTex_asianGuyLabel[] __attribute__((section(".sdata"), aligned(4))) = "Asian Guy";
}
}
_SCreateTexList DefaultFace[3] __attribute__((section(".data"))) = {
    { CreateTex_faceSkin2, CreateTex_buzzCut },
    { CreateTex_faceAsian3, CreateTexAddressViewOwners::CreateTex_asianGuyLabel },
    { 0, 0 },
};

static char CreateTex_faceShadow[] __attribute__((section(".sdata"), aligned(4))) = "fceshdw1";
static char CreateTex_capOn[] __attribute__((section(".sdata"), aligned(4))) = "Cap on";
_SCreateTexList ShadowedFace __attribute__((section(".sdata"))) = {
    CreateTex_faceShadow,
    CreateTex_capOn,
};
static _SCreateTexList CreateTex_ShadowedFaceEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_faceBlackBald[] __attribute__((section(".sdata"), aligned(4))) = "fcebkbd1";
static char CreateTex_bald[] __attribute__((section(".sdata"), aligned(4))) = "Bald";
static char CreateTex_faceAfro1[] __attribute__((section(".sdata"), aligned(4))) = "fceafro1";
static char CreateTex_shortHair[] __attribute__((section(".sdata"), aligned(4))) = "Short hair";
static char CreateTex_faceCurly2[] __attribute__((section(".sdata"), aligned(4))) = "fcecrly2";
static char CreateTex_curlyHairLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "Curly Hair";
static char CreateTex_faceAfroWig2[] __attribute__((section(".sdata"), aligned(4))) = "fceawig2";
static char CreateTex_bleachedAfro[] __attribute__((section(".sdata"), aligned(4))) =
    "Bleached Afro";
static char CreateTex_helmetTopTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "helmet_0";
static char CreateTex_helmetLabel[] __attribute__((section(".sdata"), aligned(4))) = "Helmet";
_SCreateTexList HelmetTop __attribute__((section(".sdata"))) = {
    CreateTex_helmetTopTexture,
    CreateTex_helmetLabel,
};
static _SCreateTexList CreateTex_HelmetTopEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_helmetFaceTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "fcehlmt1";
static char CreateTex_chinStrap[] __attribute__((section(".sdata"), aligned(4))) = "Chin Strap";
_SCreateTexList HelmetFace __attribute__((section(".sdata"))) = {
    CreateTex_helmetFaceTexture,
    CreateTex_chinStrap,
};
static _SCreateTexList CreateTex_HelmetFaceEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_capBirdTexture[] __attribute__((section(".sdata"), aligned(4))) = "capbird0";
static char CreateTex_birdLogo[] __attribute__((section(".sdata"), aligned(4))) = "Bird Logo";
static char CreateTex_capSkullTexture[] __attribute__((section(".sdata"), aligned(4))) = "capskul0";
static char CreateTex_skullLogo[] __attribute__((section(".sdata"), aligned(4))) = "Skull Logo";
static char CreateTex_beanieTexture[] __attribute__((section(".sdata"), aligned(4))) = "beanie_0";
static char CreateTex_beanieLabel[] __attribute__((section(".sdata"), aligned(4))) = "Beanie";
_SCreateTexList BeanieTop __attribute__((section(".sdata"))) = {
    CreateTex_beanieTexture,
    CreateTex_beanieLabel,
};
static _SCreateTexList CreateTex_BeanieTopEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_afroALabel[] __attribute__((section(".sdata"), aligned(4))) = "Afro A";
_SCreateTexList AfroFace __attribute__((section(".sdata"))) = {
    CreateTex_faceAfro1,
    CreateTex_afroALabel,
};
static _SCreateTexList CreateTex_AfroFaceEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_rastaTexture[] __attribute__((section(".sdata"), aligned(4))) = "fcersta1";
static char CreateTex_rastaLabel[] __attribute__((section(".sdata"), aligned(4))) = "Rasta";
_SCreateTexList RastaFace __attribute__((section(".sdata"))) = {
    CreateTex_rastaTexture,
    CreateTex_rastaLabel,
};
static _SCreateTexList CreateTex_RastaFaceEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_skinTexture[] __attribute__((section(".sdata"), aligned(4))) = "fcebald2";
static char CreateTex_baldieLabel[] __attribute__((section(".sdata"), aligned(4))) = "Baldie";
_SCreateTexList SkinFace __attribute__((section(".sdata"))) = {
    CreateTex_skinTexture,
    CreateTex_baldieLabel,
};
static _SCreateTexList CreateTex_SkinFaceEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_whiteFroLabel[] __attribute__((section(".sdata"), aligned(4))) = "White Fro";
_SCreateTexList WhiteAfroFace __attribute__((section(".sdata"))) = {
    CreateTex_faceAfroWig2,
    CreateTex_whiteFroLabel,
};
static _SCreateTexList CreateTex_WhiteAfroFaceEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_gilliganTexture[] __attribute__((section(".sdata"), aligned(4))) = "GlgnHat0";
static char CreateTex_gilliganLabel[] __attribute__((section(".sdata"), aligned(4))) = "Gilligan";
_SCreateTexList GilliganTop __attribute__((section(".sdata"))) = {
    CreateTex_gilliganTexture,
    CreateTex_gilliganLabel,
};
static _SCreateTexList CreateTex_GilliganTopEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_asianFaceTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "fceasn_3";
_SCreateTexList AsianFace __attribute__((section(".sdata"))) = {
    CreateTex_asianFaceTexture,
    CreateTexAddressViewOwners::CreateTex_asianGuyLabel,
};
static _SCreateTexList CreateTex_AsianFaceEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_slickFaceTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "fcestrt2";
namespace CreateTexAddressViewOwners
{
extern "C"
{
static char CreateTex_slickLabel[] __attribute__((section(".sdata"), aligned(4))) = "Slick";
}
}
_SCreateTexList SlickFace __attribute__((section(".sdata"))) = {
    CreateTex_slickFaceTexture,
    CreateTexAddressViewOwners::CreateTex_slickLabel,
};
static _SCreateTexList CreateTex_SlickFaceEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_openHandTexture[] __attribute__((section(".sdata"), aligned(4))) = "handopn1";
static char CreateTex_openHandLabel[] __attribute__((section(".sdata"), aligned(4))) = "Open hand";
_SCreateTexList GenericHand __attribute__((section(".sdata"))) = {
    CreateTex_openHandTexture,
    CreateTex_openHandLabel,
};
static _SCreateTexList CreateTex_GenericHandEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_genericShoeTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "handopn2";
static char CreateTex_shoeALabel[] __attribute__((section(".sdata"), aligned(4))) = "Shoe A";
_SCreateTexList GenericShoe __attribute__((section(".sdata"))) = {
    CreateTex_genericShoeTexture,
    CreateTex_shoeALabel,
};
static _SCreateTexList CreateTex_GenericShoeEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_tshirtTexture[] __attribute__((section(".sdata"), aligned(4))) = "tshirt_0";
static char CreateTex_tshirtLabel[] __attribute__((section(".sdata"), aligned(4))) = "T Shirt";
_SCreateTexList DefaultChest __attribute__((section(".sdata"))) = {
    CreateTex_tshirtTexture,
    CreateTex_tshirtLabel,
};
static _SCreateTexList CreateTex_DefaultChestEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_shortSleeveTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "shtslve0";
_SCreateTexList DefaultBicep __attribute__((section(".sdata"))) = {
    CreateTex_shortSleeveTexture,
    CreateTex_tshirtLabel,
};
static _SCreateTexList CreateTex_DefaultBicepEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_forearmTexture[] __attribute__((section(".sdata"), aligned(4))) = "forearm1";
static char CreateTex_forearmLabel[] __attribute__((section(".sdata"), aligned(4))) = "Forearm";
_SCreateTexList DefaultForearm __attribute__((section(".sdata"))) = {
    CreateTex_forearmTexture,
    CreateTex_forearmLabel,
};
static _SCreateTexList CreateTex_DefaultForearmEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_buttonShirtTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "btnshrt0";
static char CreateTex_buttonShirtLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "Button Shirt";
_SCreateTexList LongSleeveChest __attribute__((section(".sdata"))) = {
    CreateTex_buttonShirtTexture,
    CreateTex_buttonShirtLabel,
};
static _SCreateTexList CreateTex_LongSleeveChestEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_longSleeveTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "lngslve0";
static char CreateTex_longSleeve2Label[] __attribute__((section(".sdata"), aligned(4))) =
    "Long Sleeve 2";
_SCreateTexList LongSleeveFullArm __attribute__((section(".sdata"))) = {
    CreateTex_longSleeveTexture,
    CreateTex_longSleeve2Label,
};
static _SCreateTexList CreateTex_LongSleeveFullArmEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_noShirtTexture[] __attribute__((section(".sdata"), aligned(4))) = "noshirt1";
static char CreateTex_shirtlessLabel[] __attribute__((section(".sdata"), aligned(4))) = "Shirtless";
_SCreateTexList NoShirtChest __attribute__((section(".sdata"))) = {
    CreateTex_noShirtTexture,
    CreateTex_shirtlessLabel,
};
static _SCreateTexList CreateTex_NoShirtChestEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_bareArmTexture[] __attribute__((section(".sdata"), aligned(4))) = "barearm1";
static char CreateTex_sleevelessLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "Sleeveless";
_SCreateTexList NoShirtFullArm __attribute__((section(".sdata"))) = {
    CreateTex_bareArmTexture,
    CreateTex_sleevelessLabel,
};
static _SCreateTexList CreateTex_NoShirtFullArmEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_hoodyTexture[] __attribute__((section(".sdata"), aligned(4))) = "hoody__0";
static char CreateTex_hoodyLabel[] __attribute__((section(".sdata"), aligned(4))) = "Hoody";
_SCreateTexList HoodyChest __attribute__((section(".sdata"))) = {
    CreateTex_hoodyTexture,
    CreateTex_hoodyLabel,
};
static _SCreateTexList CreateTex_HoodyChestEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_longSleeveLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "Long Sleeve";
_SCreateTexList HoodyFullArm __attribute__((section(".sdata"))) = {
    CreateTex_longSleeveTexture,
    CreateTex_longSleeveLabel,
};
static _SCreateTexList CreateTex_HoodyFullArmEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_tankTopTexture[] __attribute__((section(".sdata"), aligned(4))) = "tanktop1";
static char CreateTex_johnMcLaneLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "John McLane";
_SCreateTexList TanktopChest __attribute__((section(".sdata"))) = {
    CreateTex_tankTopTexture,
    CreateTex_johnMcLaneLabel,
};
static _SCreateTexList CreateTex_TanktopChestEnd __attribute__((section(".sdata"))) = { 0, 0 };
_SCreateTexList TanktopFullArm __attribute__((section(".sdata"))) = {
    CreateTex_bareArmTexture,
    CreateTex_sleevelessLabel,
};
static _SCreateTexList CreateTex_TanktopFullArmEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_elbowPadsLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "Elbow Pads";
_SCreateTexList ElbowPadsChest __attribute__((section(".sdata"))) = {
    CreateTex_tshirtTexture,
    CreateTex_elbowPadsLabel,
};
static _SCreateTexList CreateTex_ElbowPadsChestEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_shortSleeveLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "Short Sleeve";
_SCreateTexList ElbowPadsBicep __attribute__((section(".sdata"))) = {
    CreateTex_shortSleeveTexture,
    CreateTex_shortSleeveLabel,
};
static _SCreateTexList CreateTex_ElbowPadsBicepEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_elbowPadTexture[] __attribute__((section(".sdata"), aligned(4))) = "elbwpad1";
_SCreateTexList ElbowPadsForearm __attribute__((section(".sdata"))) = {
    CreateTex_elbowPadTexture,
    CreateTex_elbowPadsLabel,
};
static _SCreateTexList CreateTex_ElbowPadsForearmEnd __attribute__((section(".sdata"))) = { 0, 0 };

static char CreateTex_shortsTexture[] __attribute__((section(".sdata"), aligned(4))) = "shorts_0";
static char CreateTex_shortsLabel[] __attribute__((section(".sdata"), aligned(4))) = "Shorts";
static char CreateTex_cargoShortsTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "cgshort0";
static char CreateTex_cargoShortsLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "Cargo Shorts";
static char CreateTex_bareShinTexture[] __attribute__((section(".sdata"), aligned(4))) = "shinnkd1";
static char CreateTex_noSocksLabel[] __attribute__((section(".sdata"), aligned(4))) = "No Socks";
static char CreateTex_ankleSocksTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "shinsok1";
static char CreateTex_ankleSocksLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "Ankle Socks";
static char CreateTex_highSocksWhiteTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "shinhskw";
static char CreateTex_highSocksLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "High Socks";
static char CreateTex_highSocksTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "shinhsok";
static char CreateTex_mervynsLabel[] __attribute__((section(".sdata"), aligned(4))) = "Mervyns";
static char CreateTex_longPantsTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "lngpant0";
static char CreateTex_regularPantsLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "Regular Pants";
static char CreateTex_cargoPantsTexture[] __attribute__((section(".sdata"), aligned(4))) =
    "cgpants0";
static char CreateTex_cargoPantsLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "Cargo Pants";
static char CreateTex_kneepadTexture[] __attribute__((section(".sdata"), aligned(4))) = "kneepad0";
static char CreateTex_kneepadsLabel[] __attribute__((section(".sdata"), aligned(4))) = "Kneepads";
_SCreateTexList KneepadThigh __attribute__((section(".sdata"))) = {
    CreateTex_kneepadTexture,
    CreateTex_kneepadsLabel,
};
static _SCreateTexList CreateTex_KneepadThighEnd __attribute__((section(".sdata"))) = { 0, 0 };
static char CreateTex_noSocksLowerLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "No socks";
static char CreateTex_ankleSocksLowerLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "Ankle socks";

/*
 * Geometry and front-end labels consumed by the global constructor. Their
 * target identifiers are retained under scoped C linkage so the definitions
 * remain lexically distinct from the address-only views below.
 */
namespace CreateTexAddressViewOwners
{
extern "C"
{
static char CreateTex_defaultKey[] __attribute__((section(".sdata"), aligned(4))) = "default";
static char CreateTex_defaultLabel[] __attribute__((section(".sdata"), aligned(4))) = "Default";
static char CreateTex_capHelmetKey[] __attribute__((section(".sdata"), aligned(4))) = "caphelmet";
static char CreateTex_helmetAltLabel[] __attribute__((section(".sdata"), aligned(4))) = "helmet";
static char CreateTex_capBackwardKey[] __attribute__((section(".sdata"), aligned(4))) =
    "capbackward";
static char CreateTex_capBackLabel[] __attribute__((section(".sdata"), aligned(4))) = "cap back";
static char CreateTex_capForwardKey[] __attribute__((section(".sdata"), aligned(4))) = "capforward";
static char CreateTex_capForwardLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "cap forward";
static char CreateTex_capBeanieKey[] __attribute__((section(".sdata"), aligned(4))) = "capbeanie";
static char CreateTex_beanieAltLabel[] __attribute__((section(".sdata"), aligned(4))) = "beanie";
static char CreateTex_curlyHairKey[] __attribute__((section(".sdata"), aligned(4))) = "curlyhair";
static char CreateTex_curlyLabel[] __attribute__((section(".sdata"), aligned(4))) = "curly";
static char CreateTex_afroKey[] __attribute__((section(".sdata"), aligned(4))) = "afro";
static char CreateTex_afroGuyLabel[] __attribute__((section(".sdata"), aligned(4))) = "afro guy";
static char CreateTex_dreadsKey[] __attribute__((section(".sdata"), aligned(4))) = "dreads";
static char CreateTex_rastaGuyLabel[] __attribute__((section(".sdata"), aligned(4))) = "rasta guy";
static char CreateTex_skinKey[] __attribute__((section(".sdata"), aligned(4))) = "skin";
static char CreateTex_skinheadLabel[] __attribute__((section(".sdata"), aligned(4))) = "skinhead";
static char CreateTex_afroWhiteKey[] __attribute__((section(".sdata"), aligned(4))) = "afrowhite";
static char CreateTex_whiteFroAltLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "whitefro";
static char CreateTex_gilliganKey[] __attribute__((section(".sdata"), aligned(4))) = "gilligan";
static char CreateTex_heySkipperLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "hey skipper";
static char CreateTex_baldBlackKey[] __attribute__((section(".sdata"), aligned(4))) = "baldblack";
static char CreateTex_blackBaldLabel[] __attribute__((section(".sdata"), aligned(4))) =
    "black bald";
static char CreateTex_slickKey[] __attribute__((section(".sdata"), aligned(4))) = "slick";
static char CreateTex_asianKey[] __attribute__((section(".sdata"), aligned(4))) = "asian";
static char CreateTex_emptyKey[] __attribute__((section(".sdata"), aligned(4))) = "";
static char CreateTex_normalLabel[] __attribute__((section(".sdata"), aligned(4))) = "normal";
static char CreateTex_longSleeveKey[] __attribute__((section(".sdata"), aligned(4))) = "longsleve";
static char CreateTex_jacketLabel[] __attribute__((section(".sdata"), aligned(4))) = "jacket";
static char CreateTex_noShirtKey[] __attribute__((section(".sdata"), aligned(4))) = "noshirt";
static char CreateTex_nudeLabel[] __attribute__((section(".sdata"), aligned(4))) = "nude";
static char CreateTex_hoodyKey[] __attribute__((section(".sdata"), aligned(4))) = "hoody";
static char CreateTex_hoodLabel[] __attribute__((section(".sdata"), aligned(4))) = "hood";
static char CreateTex_tankTopKey[] __attribute__((section(".sdata"), aligned(4))) = "tanktop";
static char CreateTex_tankLabel[] __attribute__((section(".sdata"), aligned(4))) = "tank";
static char CreateTex_elbowPadsKey[] __attribute__((section(".sdata"), aligned(4))) = "elbowpads";
static char CreateTex_padsLabel[] __attribute__((section(".sdata"), aligned(4))) = "pads";
static char CreateTex_standardLabel[] __attribute__((section(".sdata"), aligned(4))) = "standard";
static char CreateTex_longPantsKey[] __attribute__((section(".sdata"), aligned(4))) = "longpants";
static char CreateTex_slacksLabel[] __attribute__((section(".sdata"), aligned(4))) = "slacks";
static char CreateTex_kneePadKey[] __attribute__((section(".sdata"), aligned(4))) = "kneepad";
static char CreateTex_baggyPantsKey[] __attribute__((section(".sdata"), aligned(4))) = "baggypants";
static char CreateTex_baggyLabel[8] __attribute__((section(".sdata"), aligned(4))) = "baggy";
}
}

/*
 * The initialized texture-list catalogs precede the three mutable
 * CCreateTexSpec tables at 0x800C44A0-0x800C4588.
 */

_SCreateTexList BlackBald[3] __attribute__((section(".data"))) = {
    { CreateTex_faceBlackBald, CreateTex_bald },
    { CreateTex_faceAfro1, CreateTex_shortHair },
    { 0, 0 },
};
_SCreateTexList CurlyHair[3] __attribute__((section(".data"))) = {
    { CreateTex_faceCurly2, CreateTex_curlyHairLabel },
    { CreateTex_faceAfroWig2, CreateTex_bleachedAfro },
    { 0, 0 },
};
_SCreateTexList CapTop[3] __attribute__((section(".data"))) = {
    { CreateTex_capBirdTexture, CreateTex_birdLogo },
    { CreateTex_capSkullTexture, CreateTex_skullLogo },
    { 0, 0 },
};
_SCreateTexList DefaultThigh[3] __attribute__((section(".data"))) = {
    { CreateTex_shortsTexture, CreateTex_shortsLabel },
    { CreateTex_cargoShortsTexture, CreateTex_cargoShortsLabel },
    { 0, 0 },
};
_SCreateTexList DefaultShin[5] __attribute__((section(".data"))) = {
    { CreateTex_bareShinTexture, CreateTex_noSocksLabel },
    { CreateTex_ankleSocksTexture, CreateTex_ankleSocksLabel },
    { CreateTex_highSocksWhiteTexture, CreateTex_highSocksLabel },
    { CreateTex_highSocksTexture, CreateTex_mervynsLabel },
    { 0, 0 },
};
_SCreateTexList LongPantsFullLeg[3] __attribute__((section(".data"))) = {
    { CreateTex_longPantsTexture, CreateTex_regularPantsLabel },
    { CreateTex_cargoPantsTexture, CreateTex_cargoPantsLabel },
    { 0, 0 },
};
_SCreateTexList KneepadShin[3] __attribute__((section(".data"))) = {
    { CreateTex_bareShinTexture, CreateTex_noSocksLowerLabel },
    { CreateTex_ankleSocksTexture, CreateTex_ankleSocksLowerLabel },
    { 0, 0 },
};
_SCreateTexList BaggyPantsFullLeg[3] __attribute__((section(".data"))) = {
    { CreateTex_longPantsTexture, CreateTex_regularPantsLabel },
    { CreateTex_cargoPantsTexture, CreateTex_cargoPantsLabel },
    { 0, 0 },
};

/*
 * The backing arrays above are known `.sdata` objects.  The target global
 * initializer nevertheless addresses these strings as ordinary externals,
 * using `lui`/`addiu` pairs instead of GP-relative loads.  These second
 * declarations deliberately hide the storage class from cc1plus while their
 * identifiers resolve to the same owner-local labels. Referencing the
 * definitions directly makes CreateTex_GlobalInit use GP-relative loads.
 */
/** Absolute address views of CREATE_TEX's GP-sized specification strings. */
extern char CreateTex_defaultKey[];
extern char CreateTex_defaultLabel[];
extern char CreateTex_capHelmetKey[];
extern char CreateTex_helmetAltLabel[];
extern char CreateTex_capBackwardKey[];
extern char CreateTex_capBackLabel[];
extern char CreateTex_capForwardKey[];
extern char CreateTex_capForwardLabel[];
extern char CreateTex_capBeanieKey[];
extern char CreateTex_beanieAltLabel[];
extern char CreateTex_curlyHairKey[];
extern char CreateTex_curlyLabel[];
extern char CreateTex_afroKey[];
extern char CreateTex_afroGuyLabel[];
extern char CreateTex_dreadsKey[];
extern char CreateTex_rastaGuyLabel[];
extern char CreateTex_skinKey[];
extern char CreateTex_skinheadLabel[];
extern char CreateTex_afroWhiteKey[];
extern char CreateTex_whiteFroAltLabel[];
extern char CreateTex_gilliganKey[];
extern char CreateTex_heySkipperLabel[];
extern char CreateTex_baldBlackKey[];
extern char CreateTex_blackBaldLabel[];
extern char CreateTex_slickKey[];
extern char CreateTex_slickLabel[];
extern char CreateTex_asianKey[];
extern char CreateTex_asianGuyLabel[];
extern char CreateTex_emptyKey[];
extern char CreateTex_normalLabel[];
extern char CreateTex_longSleeveKey[];
extern char CreateTex_jacketLabel[];
extern char CreateTex_noShirtKey[];
extern char CreateTex_nudeLabel[];
extern char CreateTex_hoodyKey[];
extern char CreateTex_hoodLabel[];
extern char CreateTex_tankTopKey[];
extern char CreateTex_tankLabel[];
extern char CreateTex_elbowPadsKey[];
extern char CreateTex_padsLabel[];
extern char CreateTex_standardLabel[];
extern char CreateTex_longPantsKey[];
extern char CreateTex_slacksLabel[];
extern char CreateTex_kneePadKey[];
extern char CreateTex_baggyPantsKey[];
extern char CreateTex_baggyLabel[];

// === Function implementations (address order) ===

#include <STRINGS.H>

/**
 * Initialize a create-a-skater texture specification.
 *
 * @param name Geometry name shown to the model builder.
 * @param frontEndName Label shown by the front end.
 * @param hue Default palette hue.
 * @param list0 First texture-list choice.
 * @param list1 Second texture-list choice.
 * @param list2 Third texture-list choice.
 * @param list3 Fourth texture-list choice.
 */
CCreateTexSpec::CCreateTexSpec(char *name, char *frontEndName, int hue, _SCreateTexList *list0,
                               _SCreateTexList *list1, _SCreateTexList *list2,
                               _SCreateTexList *list3)
{
    strcpy(mGeometryName, name);
    strcpy(mFrontEndName, frontEndName);
    mpTextureList[0] = list0;
    mpTextureList[1] = list1;
    mpTextureList[2] = list2;
    mpTextureList[3] = list3;
    mDefaultHue = hue;
}


/**
 * Return the geometry name used by this specification.
 *
 * @return Mutable geometry-name storage owned by the specification.
 */
char *CCreateTexSpec::GetGeometryName()
{
    return mGeometryName;
}


/**
 * Return the front-end label used by this specification.
 *
 * @return Mutable front-end-name storage owned by the specification.
 */
char *CCreateTexSpec::GetFrontEndName()
{
    return mFrontEndName;
}


/**
 * Return one of the specification's four texture lists.
 *
 * @param i Texture-list slot in the range 0 through 3.
 * @return The selected texture list, or null when that slot is unused.
 */
_SCreateTexList *CCreateTexSpec::GetTextureList(int i)
{
    return mpTextureList[i];
}


/**
 * Return the default palette hue for this specification.
 *
 * @return Default hue value.
 */
int CCreateTexSpec::GetDefaultHue()
{
    return mDefaultHue;
}


/** Geometry and texture catalogs constructed and destroyed by the C++ runtime. */
CCreateTexSpec HeadSpec[15] = {
    CCreateTexSpec(CreateTex_defaultKey, CreateTex_defaultLabel, 0, DefaultFace, 0, 0, 0),
    CCreateTexSpec(CreateTex_capHelmetKey, CreateTex_helmetAltLabel, 0, &HelmetFace, &HelmetTop, 0,
                   0),
    CCreateTexSpec(CreateTex_capBackwardKey, CreateTex_capBackLabel, 0, &ShadowedFace, CapTop, 0,
                   0),
    CCreateTexSpec(CreateTex_capForwardKey, CreateTex_capForwardLabel, 0, &ShadowedFace, CapTop, 0,
                   0),
    CCreateTexSpec(CreateTex_capBeanieKey, CreateTex_beanieAltLabel, 0, &ShadowedFace, &BeanieTop,
                   0, 0),
    CCreateTexSpec(CreateTex_curlyHairKey, CreateTex_curlyLabel, 0, CurlyHair, 0, 0, 0),
    CCreateTexSpec(CreateTex_afroKey, CreateTex_afroGuyLabel, 0, &AfroFace, 0, 0, 0),
    CCreateTexSpec(CreateTex_dreadsKey, CreateTex_rastaGuyLabel, 0, &RastaFace, 0, 0, 0),
    CCreateTexSpec(CreateTex_skinKey, CreateTex_skinheadLabel, 0, &SkinFace, 0, 0, 0),
    CCreateTexSpec(CreateTex_afroWhiteKey, CreateTex_whiteFroAltLabel, 0, &WhiteAfroFace, 0, 0, 0),
    CCreateTexSpec(CreateTex_gilliganKey, CreateTex_heySkipperLabel, 0, &ShadowedFace, &GilliganTop,
                   0, 0),
    CCreateTexSpec(CreateTex_baldBlackKey, CreateTex_blackBaldLabel, 0, BlackBald, 0, 0, 0),
    CCreateTexSpec(CreateTex_slickKey, CreateTex_slickLabel, 0, &SlickFace, 0, 0, 0),
    CCreateTexSpec(CreateTex_asianKey, CreateTex_asianGuyLabel, 0, &AsianFace, 0, 0, 0),
    CCreateTexSpec(CreateTex_emptyKey, CreateTex_emptyKey, 0, 0, 0, 0, 0),
};

CCreateTexSpec UpperBodySpec[7] = {
    CCreateTexSpec(CreateTex_defaultKey, CreateTex_normalLabel, 0, &DefaultChest, &DefaultBicep,
                   &DefaultForearm, &GenericHand),
    CCreateTexSpec(CreateTex_longSleeveKey, CreateTex_jacketLabel, 0, &LongSleeveChest,
                   &LongSleeveFullArm, 0, &GenericHand),
    CCreateTexSpec(CreateTex_noShirtKey, CreateTex_nudeLabel, 0, &NoShirtChest, &NoShirtFullArm, 0,
                   &GenericHand),
    CCreateTexSpec(CreateTex_hoodyKey, CreateTex_hoodLabel, 0, &HoodyChest, &HoodyFullArm, 0,
                   &GenericHand),
    CCreateTexSpec(CreateTex_tankTopKey, CreateTex_tankLabel, 0, &TanktopChest, &TanktopFullArm, 0,
                   &GenericHand),
    CCreateTexSpec(CreateTex_elbowPadsKey, CreateTex_padsLabel, 120, &ElbowPadsChest,
                   &ElbowPadsBicep, &ElbowPadsForearm, &GenericHand),
    CCreateTexSpec(CreateTex_emptyKey, CreateTex_emptyKey, 0, 0, 0, 0, 0),
};

CCreateTexSpec LowerBodySpec[5] = {
    CCreateTexSpec(CreateTex_defaultKey, CreateTex_standardLabel, 248, DefaultThigh, DefaultShin,
                   &GenericShoe, 0),
    CCreateTexSpec(CreateTex_longPantsKey, CreateTex_slacksLabel, 210, LongPantsFullLeg, 0,
                   &GenericShoe, 0),
    CCreateTexSpec(CreateTex_kneePadKey, CreateTex_padsLabel, 140, &KneepadThigh, KneepadShin,
                   &GenericShoe, 0),
    CCreateTexSpec(CreateTex_baggyPantsKey, CreateTex_baggyLabel, 160, BaggyPantsFullLeg, 0,
                   &GenericShoe, 0),
    CCreateTexSpec(CreateTex_emptyKey, CreateTex_emptyKey, 0, 0, 0, 0, 0),
};
