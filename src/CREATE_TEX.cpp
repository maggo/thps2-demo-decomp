// CREATE_TEX.cpp -- Reconstructed translation unit
// Original: CREATE_TEX.CPP
// Functions: 9 reconstructed entries
// Address range: 0x8006D0C0 - 0x8006D86C
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#include "PSX.h"
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

PSX_LAYOUT_CHECK(CreateTex_Spec_size_must_be_72, sizeof(CCreateTexSpec) == 72);
/** Shared declarations for the process-lifetime specification catalogs. */
#include "CREATETEXSPECS.h"

/*
 * CREATE_TEX's complete initialized small-data contribution.  The texture
 * names, menu labels, and two-entry texture lists occupy
 * 0x800DAB50-0x800DB260 in the target.  Keeping the semantic objects in target
 * order preserves every pointer relocation without raw-address initializers.
 */
static char CreateTex_faceSkin2[] PSX_SECTION_ALIGNED(".sdata", 4) = "fceskin2";
static char CreateTex_buzzCut[] PSX_SECTION_ALIGNED(".sdata", 4) = "Buzz cut";
static char CreateTex_faceAsian3[] PSX_SECTION_ALIGNED(".sdata", 4) = "fceAsn_3";
namespace CreateTexAddressViewOwners
{
extern "C"
{
static char CreateTex_asianGuyLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Asian Guy";
}
}
_SCreateTexList DefaultFace[3] PSX_SECTION(".data") = {
    { CreateTex_faceSkin2, CreateTex_buzzCut },
    { CreateTex_faceAsian3, CreateTexAddressViewOwners::CreateTex_asianGuyLabel },
    { 0, 0 },
};

static char CreateTex_faceShadow[] PSX_SECTION_ALIGNED(".sdata", 4) = "fceshdw1";
static char CreateTex_capOn[] PSX_SECTION_ALIGNED(".sdata", 4) = "Cap on";
_SCreateTexList ShadowedFace PSX_SECTION(".sdata") = {
    CreateTex_faceShadow,
    CreateTex_capOn,
};
static _SCreateTexList CreateTex_ShadowedFaceEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_faceBlackBald[] PSX_SECTION_ALIGNED(".sdata", 4) = "fcebkbd1";
static char CreateTex_bald[] PSX_SECTION_ALIGNED(".sdata", 4) = "Bald";
static char CreateTex_faceAfro1[] PSX_SECTION_ALIGNED(".sdata", 4) = "fceafro1";
static char CreateTex_shortHair[] PSX_SECTION_ALIGNED(".sdata", 4) = "Short hair";
static char CreateTex_faceCurly2[] PSX_SECTION_ALIGNED(".sdata", 4) = "fcecrly2";
static char CreateTex_curlyHairLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Curly Hair";
static char CreateTex_faceAfroWig2[] PSX_SECTION_ALIGNED(".sdata", 4) = "fceawig2";
static char CreateTex_bleachedAfro[] PSX_SECTION_ALIGNED(".sdata", 4) = "Bleached Afro";
static char CreateTex_helmetTopTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "helmet_0";
static char CreateTex_helmetLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Helmet";
_SCreateTexList HelmetTop PSX_SECTION(".sdata") = {
    CreateTex_helmetTopTexture,
    CreateTex_helmetLabel,
};
static _SCreateTexList CreateTex_HelmetTopEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_helmetFaceTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "fcehlmt1";
static char CreateTex_chinStrap[] PSX_SECTION_ALIGNED(".sdata", 4) = "Chin Strap";
_SCreateTexList HelmetFace PSX_SECTION(".sdata") = {
    CreateTex_helmetFaceTexture,
    CreateTex_chinStrap,
};
static _SCreateTexList CreateTex_HelmetFaceEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_capBirdTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "capbird0";
static char CreateTex_birdLogo[] PSX_SECTION_ALIGNED(".sdata", 4) = "Bird Logo";
static char CreateTex_capSkullTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "capskul0";
static char CreateTex_skullLogo[] PSX_SECTION_ALIGNED(".sdata", 4) = "Skull Logo";
static char CreateTex_beanieTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "beanie_0";
static char CreateTex_beanieLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Beanie";
_SCreateTexList BeanieTop PSX_SECTION(".sdata") = {
    CreateTex_beanieTexture,
    CreateTex_beanieLabel,
};
static _SCreateTexList CreateTex_BeanieTopEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_afroALabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Afro A";
_SCreateTexList AfroFace PSX_SECTION(".sdata") = {
    CreateTex_faceAfro1,
    CreateTex_afroALabel,
};
static _SCreateTexList CreateTex_AfroFaceEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_rastaTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "fcersta1";
static char CreateTex_rastaLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Rasta";
_SCreateTexList RastaFace PSX_SECTION(".sdata") = {
    CreateTex_rastaTexture,
    CreateTex_rastaLabel,
};
static _SCreateTexList CreateTex_RastaFaceEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_skinTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "fcebald2";
static char CreateTex_baldieLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Baldie";
_SCreateTexList SkinFace PSX_SECTION(".sdata") = {
    CreateTex_skinTexture,
    CreateTex_baldieLabel,
};
static _SCreateTexList CreateTex_SkinFaceEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_whiteFroLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "White Fro";
_SCreateTexList WhiteAfroFace PSX_SECTION(".sdata") = {
    CreateTex_faceAfroWig2,
    CreateTex_whiteFroLabel,
};
static _SCreateTexList CreateTex_WhiteAfroFaceEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_gilliganTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "GlgnHat0";
static char CreateTex_gilliganLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Gilligan";
_SCreateTexList GilliganTop PSX_SECTION(".sdata") = {
    CreateTex_gilliganTexture,
    CreateTex_gilliganLabel,
};
static _SCreateTexList CreateTex_GilliganTopEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_asianFaceTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "fceasn_3";
_SCreateTexList AsianFace PSX_SECTION(".sdata") = {
    CreateTex_asianFaceTexture,
    CreateTexAddressViewOwners::CreateTex_asianGuyLabel,
};
static _SCreateTexList CreateTex_AsianFaceEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_slickFaceTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "fcestrt2";
namespace CreateTexAddressViewOwners
{
extern "C"
{
static char CreateTex_slickLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Slick";
}
}
_SCreateTexList SlickFace PSX_SECTION(".sdata") = {
    CreateTex_slickFaceTexture,
    CreateTexAddressViewOwners::CreateTex_slickLabel,
};
static _SCreateTexList CreateTex_SlickFaceEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_openHandTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "handopn1";
static char CreateTex_openHandLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Open hand";
_SCreateTexList GenericHand PSX_SECTION(".sdata") = {
    CreateTex_openHandTexture,
    CreateTex_openHandLabel,
};
static _SCreateTexList CreateTex_GenericHandEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_genericShoeTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "handopn2";
static char CreateTex_shoeALabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Shoe A";
_SCreateTexList GenericShoe PSX_SECTION(".sdata") = {
    CreateTex_genericShoeTexture,
    CreateTex_shoeALabel,
};
static _SCreateTexList CreateTex_GenericShoeEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_tshirtTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "tshirt_0";
static char CreateTex_tshirtLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "T Shirt";
_SCreateTexList DefaultChest PSX_SECTION(".sdata") = {
    CreateTex_tshirtTexture,
    CreateTex_tshirtLabel,
};
static _SCreateTexList CreateTex_DefaultChestEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_shortSleeveTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "shtslve0";
_SCreateTexList DefaultBicep PSX_SECTION(".sdata") = {
    CreateTex_shortSleeveTexture,
    CreateTex_tshirtLabel,
};
static _SCreateTexList CreateTex_DefaultBicepEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_forearmTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "forearm1";
static char CreateTex_forearmLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Forearm";
_SCreateTexList DefaultForearm PSX_SECTION(".sdata") = {
    CreateTex_forearmTexture,
    CreateTex_forearmLabel,
};
static _SCreateTexList CreateTex_DefaultForearmEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_buttonShirtTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "btnshrt0";
static char CreateTex_buttonShirtLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Button Shirt";
_SCreateTexList LongSleeveChest PSX_SECTION(".sdata") = {
    CreateTex_buttonShirtTexture,
    CreateTex_buttonShirtLabel,
};
static _SCreateTexList CreateTex_LongSleeveChestEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_longSleeveTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "lngslve0";
static char CreateTex_longSleeve2Label[] PSX_SECTION_ALIGNED(".sdata", 4) = "Long Sleeve 2";
_SCreateTexList LongSleeveFullArm PSX_SECTION(".sdata") = {
    CreateTex_longSleeveTexture,
    CreateTex_longSleeve2Label,
};
static _SCreateTexList CreateTex_LongSleeveFullArmEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_noShirtTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "noshirt1";
static char CreateTex_shirtlessLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Shirtless";
_SCreateTexList NoShirtChest PSX_SECTION(".sdata") = {
    CreateTex_noShirtTexture,
    CreateTex_shirtlessLabel,
};
static _SCreateTexList CreateTex_NoShirtChestEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_bareArmTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "barearm1";
static char CreateTex_sleevelessLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Sleeveless";
_SCreateTexList NoShirtFullArm PSX_SECTION(".sdata") = {
    CreateTex_bareArmTexture,
    CreateTex_sleevelessLabel,
};
static _SCreateTexList CreateTex_NoShirtFullArmEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_hoodyTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "hoody__0";
static char CreateTex_hoodyLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Hoody";
_SCreateTexList HoodyChest PSX_SECTION(".sdata") = {
    CreateTex_hoodyTexture,
    CreateTex_hoodyLabel,
};
static _SCreateTexList CreateTex_HoodyChestEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_longSleeveLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Long Sleeve";
_SCreateTexList HoodyFullArm PSX_SECTION(".sdata") = {
    CreateTex_longSleeveTexture,
    CreateTex_longSleeveLabel,
};
static _SCreateTexList CreateTex_HoodyFullArmEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_tankTopTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "tanktop1";
static char CreateTex_johnMcLaneLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "John McLane";
_SCreateTexList TanktopChest PSX_SECTION(".sdata") = {
    CreateTex_tankTopTexture,
    CreateTex_johnMcLaneLabel,
};
static _SCreateTexList CreateTex_TanktopChestEnd PSX_SECTION(".sdata") = { 0, 0 };
_SCreateTexList TanktopFullArm PSX_SECTION(".sdata") = {
    CreateTex_bareArmTexture,
    CreateTex_sleevelessLabel,
};
static _SCreateTexList CreateTex_TanktopFullArmEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_elbowPadsLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Elbow Pads";
_SCreateTexList ElbowPadsChest PSX_SECTION(".sdata") = {
    CreateTex_tshirtTexture,
    CreateTex_elbowPadsLabel,
};
static _SCreateTexList CreateTex_ElbowPadsChestEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_shortSleeveLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Short Sleeve";
_SCreateTexList ElbowPadsBicep PSX_SECTION(".sdata") = {
    CreateTex_shortSleeveTexture,
    CreateTex_shortSleeveLabel,
};
static _SCreateTexList CreateTex_ElbowPadsBicepEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_elbowPadTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "elbwpad1";
_SCreateTexList ElbowPadsForearm PSX_SECTION(".sdata") = {
    CreateTex_elbowPadTexture,
    CreateTex_elbowPadsLabel,
};
static _SCreateTexList CreateTex_ElbowPadsForearmEnd PSX_SECTION(".sdata") = { 0, 0 };

static char CreateTex_shortsTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "shorts_0";
static char CreateTex_shortsLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Shorts";
static char CreateTex_cargoShortsTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "cgshort0";
static char CreateTex_cargoShortsLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Cargo Shorts";
static char CreateTex_bareShinTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "shinnkd1";
static char CreateTex_noSocksLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "No Socks";
static char CreateTex_ankleSocksTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "shinsok1";
static char CreateTex_ankleSocksLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Ankle Socks";
static char CreateTex_highSocksWhiteTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "shinhskw";
static char CreateTex_highSocksLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "High Socks";
static char CreateTex_highSocksTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "shinhsok";
static char CreateTex_mervynsLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Mervyns";
static char CreateTex_longPantsTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "lngpant0";
static char CreateTex_regularPantsLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Regular Pants";
static char CreateTex_cargoPantsTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "cgpants0";
static char CreateTex_cargoPantsLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Cargo Pants";
static char CreateTex_kneepadTexture[] PSX_SECTION_ALIGNED(".sdata", 4) = "kneepad0";
static char CreateTex_kneepadsLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Kneepads";
_SCreateTexList KneepadThigh PSX_SECTION(".sdata") = {
    CreateTex_kneepadTexture,
    CreateTex_kneepadsLabel,
};
static _SCreateTexList CreateTex_KneepadThighEnd PSX_SECTION(".sdata") = { 0, 0 };
static char CreateTex_noSocksLowerLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "No socks";
static char CreateTex_ankleSocksLowerLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Ankle socks";

/*
 * Geometry and front-end labels consumed by the global constructor. Their
 * target identifiers are retained under scoped C linkage so the definitions
 * remain lexically distinct from the address-only views below.
 */
namespace CreateTexAddressViewOwners
{
extern "C"
{
static char CreateTex_defaultKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "default";
static char CreateTex_defaultLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "Default";
static char CreateTex_capHelmetKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "caphelmet";
static char CreateTex_helmetAltLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "helmet";
static char CreateTex_capBackwardKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "capbackward";
static char CreateTex_capBackLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "cap back";
static char CreateTex_capForwardKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "capforward";
static char CreateTex_capForwardLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "cap forward";
static char CreateTex_capBeanieKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "capbeanie";
static char CreateTex_beanieAltLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "beanie";
static char CreateTex_curlyHairKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "curlyhair";
static char CreateTex_curlyLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "curly";
static char CreateTex_afroKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "afro";
static char CreateTex_afroGuyLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "afro guy";
static char CreateTex_dreadsKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "dreads";
static char CreateTex_rastaGuyLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "rasta guy";
static char CreateTex_skinKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "skin";
static char CreateTex_skinheadLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "skinhead";
static char CreateTex_afroWhiteKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "afrowhite";
static char CreateTex_whiteFroAltLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "whitefro";
static char CreateTex_gilliganKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "gilligan";
static char CreateTex_heySkipperLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "hey skipper";
static char CreateTex_baldBlackKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "baldblack";
static char CreateTex_blackBaldLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "black bald";
static char CreateTex_slickKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "slick";
static char CreateTex_asianKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "asian";
static char CreateTex_emptyKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "";
static char CreateTex_normalLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "normal";
static char CreateTex_longSleeveKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "longsleve";
static char CreateTex_jacketLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "jacket";
static char CreateTex_noShirtKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "noshirt";
static char CreateTex_nudeLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "nude";
static char CreateTex_hoodyKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "hoody";
static char CreateTex_hoodLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "hood";
static char CreateTex_tankTopKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "tanktop";
static char CreateTex_tankLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "tank";
static char CreateTex_elbowPadsKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "elbowpads";
static char CreateTex_padsLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "pads";
static char CreateTex_standardLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "standard";
static char CreateTex_longPantsKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "longpants";
static char CreateTex_slacksLabel[] PSX_SECTION_ALIGNED(".sdata", 4) = "slacks";
static char CreateTex_kneePadKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "kneepad";
static char CreateTex_baggyPantsKey[] PSX_SECTION_ALIGNED(".sdata", 4) = "baggypants";
static char CreateTex_baggyLabel[8] PSX_SECTION_ALIGNED(".sdata", 4) = "baggy";
}
}

/*
 * The initialized texture-list catalogs precede the three mutable
 * CCreateTexSpec tables at 0x800C44A0-0x800C4588.
 */

_SCreateTexList BlackBald[3] PSX_SECTION(".data") = {
    { CreateTex_faceBlackBald, CreateTex_bald },
    { CreateTex_faceAfro1, CreateTex_shortHair },
    { 0, 0 },
};
_SCreateTexList CurlyHair[3] PSX_SECTION(".data") = {
    { CreateTex_faceCurly2, CreateTex_curlyHairLabel },
    { CreateTex_faceAfroWig2, CreateTex_bleachedAfro },
    { 0, 0 },
};
_SCreateTexList CapTop[3] PSX_SECTION(".data") = {
    { CreateTex_capBirdTexture, CreateTex_birdLogo },
    { CreateTex_capSkullTexture, CreateTex_skullLogo },
    { 0, 0 },
};
_SCreateTexList DefaultThigh[3] PSX_SECTION(".data") = {
    { CreateTex_shortsTexture, CreateTex_shortsLabel },
    { CreateTex_cargoShortsTexture, CreateTex_cargoShortsLabel },
    { 0, 0 },
};
_SCreateTexList DefaultShin[5] PSX_SECTION(".data") = {
    { CreateTex_bareShinTexture, CreateTex_noSocksLabel },
    { CreateTex_ankleSocksTexture, CreateTex_ankleSocksLabel },
    { CreateTex_highSocksWhiteTexture, CreateTex_highSocksLabel },
    { CreateTex_highSocksTexture, CreateTex_mervynsLabel },
    { 0, 0 },
};
_SCreateTexList LongPantsFullLeg[3] PSX_SECTION(".data") = {
    { CreateTex_longPantsTexture, CreateTex_regularPantsLabel },
    { CreateTex_cargoPantsTexture, CreateTex_cargoPantsLabel },
    { 0, 0 },
};
_SCreateTexList KneepadShin[3] PSX_SECTION(".data") = {
    { CreateTex_bareShinTexture, CreateTex_noSocksLowerLabel },
    { CreateTex_ankleSocksTexture, CreateTex_ankleSocksLowerLabel },
    { 0, 0 },
};
_SCreateTexList BaggyPantsFullLeg[3] PSX_SECTION(".data") = {
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
