// Owner-local layout overlay for SMOKE.cpp.
#ifndef SMOKE_INC_H
#define SMOKE_INC_H

#ifdef SMOKE_OWNER_DECLARATIONS
#define CCLASS_POLY_ITEM_FAMILY
#define CCLASS_POLY_BIT_FAMILY
#include "CCLASS_POLY.h"
#endif
#include "globals.h"

/** Target-proven storage size of one smoke jet. */
enum
{
    SMOKE_JET_STORAGE_SIZE = 364
};

enum
{
    SMOKE_POINT_COUNT = 10,
    SMOKE_LAST_POINT = SMOKE_POINT_COUNT - 1,
};

#ifdef SMOKE_OWNER_DECLARATIONS

struct Texture;
#include "CSPECIALDISPLAY.h"

#include "SRIBBONPOINT.h"

#include "CTEXTUREDRIBBON.h"

#include "CSMOKEJET.h"

/** Composition-only item view used for smoke-jet range and damage checks. */
typedef char smoke_CBit_size_must_be_72[(sizeof(CBit) == 72) ? 1 : -1];
typedef char smoke_SRibbonPoint_size_must_be_36[(sizeof(SRibbonPoint) == 36) ? 1 : -1];
typedef char smoke_CTexturedRibbon_size_must_be_108[(sizeof(CTexturedRibbon) == 108) ? 1 : -1];
typedef char smoke_SWidthWobble_size_must_be_8[(sizeof(SWidthWobble) == 8) ? 1 : -1];
typedef char smoke_CSmokeJet_size_must_be_364[(sizeof(CSmokeJet) == 364) ? 1 : -1];

#endif // SMOKE_OWNER_DECLARATIONS

#endif // SMOKE_INC_H
