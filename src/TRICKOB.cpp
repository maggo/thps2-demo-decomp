// TRICKOB.cpp -- Trick-object triggers, completion state, and environment-item tint updates.
// Original: TRICKOB.CPP
// Functions: 7
// Address range: 0x80050414 - 0x8005086C
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#define TRICKOB_POLYMORPHIC_LAYOUT
#define TRICKOB_OWNER_DECLARATIONS
#include "TRICKOB.h"
#undef TRICKOB_OWNER_DECLARATIONS
#include "MAIN.h"
#include "UTILS.h"

typedef char trickob_owner_size_must_be_24[(sizeof(CTrickOb) == 24) ? 1 : -1];
#include "SPOOL.h"

// === Owner-local $gp-relative globals ===
CTrickOb *TrickObList __attribute__((section(".sdata"))) = 0;
unsigned short DarkenTimer[3] __attribute__((section(".sdata"))) = { 1800, 600, 900 };
static int MapX __attribute__((section(".sdata"))) = 256;
static int MapY __attribute__((section(".sdata"))) = 220;
static int MapScale __attribute__((section(".sdata"))) = 128;
int Missed __attribute__((section(".sdata"))) = 0;

// === Function implementations (address order) ===

/**
 * Destroy every currently linked trick object.
 *
 * Address:   0x80050414
 * Mangled:   TrickOb_Init__Fv
 * Demangled: TrickOb_Init(void)
 */
void TrickOb_Init(void)
{
    while (TrickObList != 0)
    {
        delete TrickObList;
    }
}

/**
 * Delete the complete active trick-object list without relying on head reuse.
 *
 * Address:   0x8005045C
 * Mangled:   TrickOb_DeleteAll__Fv
 * Demangled: TrickOb_DeleteAll(void)
 *
 */
void TrickOb_DeleteAll(void)
{
    CTrickOb *pTrickOb = TrickObList;
    if (pTrickOb != 0)
    {
        do
        {
            CTrickOb *pNext = pTrickOb->mpNext;
            if (pTrickOb != 0)
            {
                delete pTrickOb;
            }
            pTrickOb = pNext;
        } while (pTrickOb != 0);
    }
}

/**
 * Construct and link one trick trigger.
 *
 * Address:   0x800504B0
 * Mangled:   __8CTrickObUsUs
 * Demangled: CTrickOb::(unsigned short, unsigned short)
 *            Link a trick object into the active list and cache its trigger command pointer.
 *
 * @param Node  Rail / graph node identifier.
 * @param DelayLevel  Initial delay tier (unused in this demo build).
 */
CTrickOb::CTrickOb(unsigned short Node, unsigned short DelayLevel)
{
    CTrickOb *oldHead = TrickObList;
    TrickObList = this;
    mState = 0;
    short **offsets = OffsetList;
    mNode = Node;
    mpItem = 0;
    mpNext = oldHead;
    short *pNode = offsets[Node];
    unsigned short count = pNode[1];
    // The command pointer is aligned after skipping the variable short payload.
    pNode += count + 2;
    if (reinterpret_cast<unsigned int>(pNode) & 3) pNode++;
    mChecksum = *reinterpret_cast<unsigned int *>(pNode);
}

/**
 * CTrickOb::~CTrickOb()
 *
 * Address:   0x80050520
 * Mangled:   _._8CTrickOb
 * Demangled: CTrickOb::~CTrickOb()
 *
 */
CTrickOb::~CTrickOb()
{
    CTrickOb *pLast = 0;
    CTrickOb *pTrickOb = TrickObList;
    if (pTrickOb == this) goto found;
    do
    {
        pLast = pTrickOb;
        pTrickOb = pLast->mpNext;
    } while (pTrickOb != this);
found:
    if (pLast != 0)
    {
        pLast->mpNext = mpNext;
    }
    else
    {
        TrickObList = mpNext;
    }
}

/**
 * Handle a trick performed on an environment item.
 *
 * Address:   0x80050598
 * Mangled:   TrickOb_TrickedOnItem__FP4ItemPvi
 * Demangled: TrickOb_TrickedOnItem(Item *, void *, int)
 *
 * @param pItem  Item to operate on.
 * @param pB  Skater/context pointer supplied by the caller.
 * @param Score  Score value.
 * @return Unspecified legacy result; the target body leaves `$v0` untouched.
 */
int TrickOb_TrickedOnItem(Item *pItem, void *pB, int Score)
{
}

/**
 * Mark a matching trick node complete and darken its environment item.
 *
 * Address:   0x800505A0
 * Mangled:   TrickOb_DarkenNode__Fi
 * Demangled: TrickOb_DarkenNode(int)
 *
 * @param NodeIndex  Rail node index.
 */
void TrickOb_DarkenNode(int NodeIndex)
{
    if (GGame == 8)
    {
        CTrickOb *pTrickOb = TrickObList;
        if (pTrickOb != 0)
        {
            int darkColor = 0x00200000;
            int scoreMode = 8;
            darkColor |= 0x2020;

            do
            {
                if (pTrickOb->mNode != NodeIndex) goto next;

                if (pTrickOb->mState != 0)
                {
                    if (GGame != scoreMode) goto done;
                }

                {
                    Item *pItem = Spool_FindEnviroItem(pTrickOb->mChecksum);
                    unsigned short score = static_cast<unsigned short>(TrickScore);
                    pTrickOb->mpItem = pItem;
                    pTrickOb->mScore = score;
                    pTrickOb->mPlayer = static_cast<unsigned char>(TrickPlayer);
                    unsigned short flags = pItem->Flags;
                    pItem->RGB = darkColor;
                    pItem->Flags = flags | 0x400;
                    pTrickOb->mState = 1;
                }
                goto done;

            next:
                pTrickOb = pTrickOb->mpNext;
            } while (pTrickOb != 0);
        }
    }
done:;
}

/**
 * Updates the red color channel of every active trick object.
 *
 * In score mode the channel pulses according to the object's score threshold;
 * otherwise it follows the global frame counter. Player two uses the green
 * channel for the score-mode pulse.
 *
 * Address:   0x8005066C
 * Mangled:   TrickOb_Update__Fv
 * Demangled: TrickOb_Update(void)
 *
 */
void TrickOb_Update(void)
{
    CTrickOb *pTrickOb = TrickObList;
    if (pTrickOb == 0) return;
    int game = GGame;

    do
    {
        Item *pItem;
        if (pTrickOb->mState != 0 && (pItem = pTrickOb->mpItem) != 0)
        {
            if (game == 8)
            {
                int Red;
                unsigned int pulsePhase = static_cast<unsigned int>(Xblanks * 4);
                if (pTrickOb->mScore < 2001)
                {
                    Red = pulsePhase %
                          static_cast<unsigned int>(((pTrickOb->mScore << 6) / 2000 + 1) * 2);
                }
                else
                {
                    Red = pulsePhase % 130;
                }
                if (pTrickOb->mScore < 2001)
                {
                    if ((pTrickOb->mScore << 6) / 2000 + 1 < Red)
                    {
                        goto adjust;
                    }
                }
                else if (65 < Red)
                {
                adjust:
                    if (pTrickOb->mScore < 2001)
                    {
                        Red = ((pTrickOb->mScore << 6) / 2000 + 1) * 2 - Red;
                    }
                    else
                    {
                        Red = 130 - Red;
                    }
                }
                if (pTrickOb->mPlayer == 1)
                {
                    pItem->RGB = (pItem->RGB & 0xff00ffff) | ((Red + 64) * 0x10000);
                    goto next;
                }
                pItem->RGB = (pItem->RGB & 0xffffff00) | (Red + 64);
            }
            else
            {
                int Red = static_cast<unsigned int>(Xblanks) >> 1 & 0x3f;
                if (32 < Red)
                {
                    Red = 64 - Red;
                }
                pItem->RGB = (pItem->RGB & 0xffffff00) | (Red + 32);
            }
        }
    next:
        pTrickOb = pTrickOb->mpNext;
    } while (pTrickOb != 0);
}
