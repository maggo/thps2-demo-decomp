// BADDY.h -- interface of BADDY.cpp
#ifndef BADDY_INC_H
#define BADDY_INC_H

struct CBaddy;
struct CBody;

#ifdef BADDY_OWNER_DECLARATIONS

#include "globals.h"

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

struct CBruce;
struct SVideoInfo;

struct SRainEntry
{
    struct CVector vel;
    struct CGPolyLine *p_line;
};

#endif // BADDY_OWNER_DECLARATIONS

#ifdef BADDY_OWNER_DECLARATIONS
#define BADDY_SHARED_STATE_DECL_ATTR
#else
#define BADDY_SHARED_STATE_DECL_ATTR __attribute__((section(".data")))
#endif

/** Head of the active scripted-baddy object list. */
extern CBody *BaddyList BADDY_SHARED_STATE_DECL_ATTR; // 0x800D9B04

#undef BADDY_SHARED_STATE_DECL_ATTR

#ifdef BADDY_OWNER_DECLARATIONS

// === Variables (absolute in this TU) ===
#define BITSTATE_DECLARE_BIT_COUNT
#include "BITSTATE.h"
#include "CAMERALIST.h"
#define VIDEOINFO_DECLARE_GVINFO1
#include "VIDEOINFO.h"
#define GAMEFMVSTATE_ABSOLUTE_DECLARATION
#define GAMEFMVSTATE_DECLARE_CURRENT_FRAME
#include "GAMEFMVSTATE.h"
#define TRIGSTATE_ABSOLUTE_DECLARATION
#define TRIGSTATE_DECLARE_OFFSET_LIST
#include "TRIGSTATE.h"
#define SOUNDLEVELS_DECLARE_SFXLEVEL
#include "SOUNDLEVELS.h"
#define BITSTATE_DECLARE_USE_CACHE_FOR_BITS
#include "BITSTATE.h"

#endif // BADDY_OWNER_DECLARATIONS

/*
 * Complete gameplay hierarchy shared with BADDY and its proven derived
 * owners. Pointer-only users leave this slice opaque.
 */
#ifdef BADDY_LAYOUT_DECLARATIONS

#ifdef CCLASS_POLY_BADDY_FAMILY
/* Natural hierarchy: CBaddy comes from CCLASS_POLY.h; BADDY.cpp is the owner. */
#include "CCLASS_POLY.h"
struct CSmokeJet;
struct SRainEntry;
#ifdef BADDY_OWNER_DECLARATIONS
/** Script-only actor extension that owns weather and smoke effects. */
struct CScriptOnlyBaddy : CBaddy
{
    unsigned short mWeatherData;
    unsigned short _padToWeather;
    struct SRainEntry *mpWeather;
    struct CSmokeJet *mpSmokeJet;
    unsigned int mLoopingSound;
    int mLoopingSoundUpdate;
    int mLoopingSoundVol;

    /** Initialize a script-only actor from one trigger record. */
    CScriptOnlyBaddy(short *pInfo, int nodeIndex);
    virtual ~CScriptOnlyBaddy();
    virtual void AI();
    virtual int ExecuteCommand(unsigned short command);
    virtual void SetVariable(unsigned short variable);
};

typedef char CScriptOnlyBaddy_size_check[(sizeof(struct CScriptOnlyBaddy) == 556) ? 1 : -1];
#endif
#endif // CCLASS_POLY_BADDY_FAMILY

#endif // BADDY_LAYOUT_DECLARATIONS

#endif // BADDY_INC_H
