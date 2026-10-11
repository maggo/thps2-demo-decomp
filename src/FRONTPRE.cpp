// FRONTPRE.cpp -- Front-end PRE archive loading and fade presentation.
// Original: FRONTPRE.CPP
// Functions: 4
// Address range: 0x8006B1E4 - 0x8006B53C
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#define FRONTPRE_POLYMORPHIC_LAYOUT
#include "CCLASS_POLY.h"
#define DB_BUFFER_LAYOUT
#include "DB.h"
#undef DB_BUFFER_LAYOUT
#include "FRONTPRE.h"
#include "PRE.h"
#include <STDIO.H>
#include <STDDEF.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

/** Front-end screen -> PRE archive table (terminated by a null record). */
_FrontPreInfo preInfo[FrontPreInfoCount] = {
    { 1, "player.pre" },
    { 0, 0 },
};

#define SPOOLER_ABSOLUTE_MANAGER_DECLARATION
#include "SPOOLER.h"
#undef SPOOLER_ABSOLUTE_MANAGER_DECLARATION

enum {
    FrontPreInitialTimeout = 3,
    FrontPreFadeStep = 8,
    FrontPreMaximumFade = 255,
    FrontPreRedFadeDivisor = 8,
    FrontPreGreenFadeDivisor = 4,
    FrontPreScreenWidth = 512,
    FrontPreScreenHeight = 240,
};

// DB owns this small-data pointer, but FRONTPRE addresses it absolutely.
#include "PDOUBLEBUFFER.h"

#include "PREMGR.h"

/**
 * Initialize an inactive loader with its short front-end timeout.
 */
FrontPreLoader::FrontPreLoader()
{
    mActive = 0;
    mTimeout = FrontPreInitialTimeout;
    mFade = 0;
}

FrontPreLoader::~FrontPreLoader()
{
}

/**
 * Queue the PRE archive associated with a front-end screen.
 *
 * @param whichScreen Screen identifier stored in the PRE selection table.
 * @return 1 when a request is already active or was queued; 0 when the
 *         selected table record has no filename.
 */
int FrontPreLoader::BeginLoad(int whichScreen)
{
    if (mActive != 0)
    {
        return 1;
    }

    _FrontPreInfo *pInfo = preInfo;
    while (*pInfo->pFileName != '\0')
    {
        if (whichScreen == pInfo->whichScreen)
            break;
        pInfo++;
    }

    if (pInfo->pFileName == 0)
    {
        return 0;
    }

    {
        mActive = 1;
        sprintf(mFileName, "%s", pInfo->pFileName);

        Spooler::SpoolMgr->Reset();
        mSpoolID = Spooler::SpoolMgr->AddFile(mFileName, 0);
        Spooler::SpoolMgr->Spooool();
    }

    return 1;
}

/**
 * Advances the front-end PRE spooler. While a load is active, draws the
 * full-screen fade primitive and installs the PRE data once spooling finishes.
 *
 * @return 1 when the inactive timeout expires or the PRE is installed;
 *         otherwise 0.
 */
int FrontPreLoader::DoneLoading()
{
    POLY_F4 *Poly;
    DR_MODE *dr;

    Spooler::SpoolMgr->Update();

    if (mActive == 0)
    {
        if (mTimeout > 0)
            mTimeout--;
        return mTimeout == 0;
    }

    Poly = reinterpret_cast<POLY_F4 *>(pPoly);
    pPoly = reinterpret_cast<unsigned int *>(Poly + 1);
    setPolyF4(Poly);

    mFade += FrontPreFadeStep;
    if (mFade > FrontPreMaximumFade)
        mFade = FrontPreMaximumFade;

    setRGB0(Poly, mFade / FrontPreRedFadeDivisor,
            mFade / FrontPreGreenFadeDivisor, mFade);
    setXYWH(Poly, 0, 0, FrontPreScreenWidth, FrontPreScreenHeight);

    setSemiTrans(Poly, 1);
    addPrim(pDoubleBuffer->PanelOT, Poly);

    int tpage = GetTPage(2, 2, 0, 0);
    dr = reinterpret_cast<DR_MODE *>(pPoly);
    pPoly = reinterpret_cast<unsigned int *>(dr + 1);
    SetDrawMode(dr, 0, 1, tpage, 0);

    addPrim(pDoubleBuffer->PanelOT, dr);

    if (Spooler::SpoolMgr->IsFileLoaded(mSpoolID))
    {
        PREMgr->spoolPREData(
            reinterpret_cast<char *>(Spooler::SpoolMgr->GetFile(mSpoolID)),
            mFileName);
        return 1;
    }
    return 0;
}
