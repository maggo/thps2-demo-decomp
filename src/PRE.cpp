// PRE.cpp -- PRE archive loading, ownership, and file lookup.
// Original: PRE.CPP
// Functions: 11
// Address range: 0x8005A6E8 - 0x8005AC28
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#include "PSX.h"
#define PRE_POLYMORPHIC_LAYOUT
#include "PRE.h"
#include "PREAPI.h"
#include "MEM.h"

PSX_LAYOUT_CHECK(pre_manager_size_must_be_324, sizeof(PREManager) == 324);

// String literals (absolute addresses in .rodata)
static char PRE_full_msg[]; // 0x800B290C "PRE: All slots full\n" (approx)
static char PRE_open_err[]; // 0x800B2928 "PRE: could not open %s\n" (approx)
#define PREAPI_DECLARE_OWNER_ADDRESS_VIEWS
#include "PREAPI.h"

#define PREMGR_OWNER_DECLARATION
#include "PREMGR.h"

/** PRE archive manager singleton owned by this translation unit. */
PREManager *PREMgr PSX_SECTION(".sdata") = 0;

// Small-data order in this owner is PREMgr, PRE_null_arr, PRE_fmt_s, then
// both vtables, so the recovered definitions follow the string owners.
namespace PreAddressViewOwners
{
extern "C"
{
/** Empty name and filename-copy format stored beside the singleton. */
static char PRE_null_arr[4] PSX_SECTION(".sdata") = { 0, 0, 0, 0 };
static char PRE_fmt_s[4] PSX_SECTION(".sdata") = "%s";
}
}

// Additional external functions

#include "FILEIO.h"
#include <STDIO.H>
#include <STRINGS.H>

// === Function implementations (address order) ===

/** Allocate and publish the global PRE archive manager. */
void PRE_Init(void)
{
    PREMgr = new PREManager;
}

/** Destroy the global PRE archive manager and clear its handle. */
void PRE_Cleanup(void)
{
    delete PREMgr;
    PREMgr = 0;
}

/** Initialize every archive slot and its corresponding filename. */
PREManager::PREManager()
{
    for (int i = 0; i < PREManager::SlotCount; ++i)
    {
        mPre[i] = 0;
        mPreName[i][0] = PRE_null_arr[0];
    }
}

/** Release every loaded archive owned by this manager. */
PREManager::~PREManager()
{
    {
        int i = 0;
        char **slot = mPre;

        do
        {
            char *data = *slot;
            if (data != 0)
            {
                Mem_Delete(data);
            }
            i++;
            slot++;
        } while (i < PREManager::SlotCount);
    }
}

/** Start loading an archive, then wait for the transfer to complete. */
void PREManager::loadPRE(char *pre_name)
{
    spoolPRE(pre_name);
    FileIO_Sync();
}

/** Load an archive into the first free manager slot. */
void PREManager::spoolPRE(char *pre_name)
{
    int slot = 0;
    char **slots;
    char **p;

    slots = mPre;
    p = slots;

    // Find empty slot
loop:
    if (*p == 0) goto check;
    slot++;
    if (slot < PREManager::SlotCount)
    {
        p++;
        goto loop;
    }
check:

    if (slot == PREManager::SlotCount)
    {
        printf(PRE_full_msg);
        return;
    }

    // Open file and allocate buffer
    int fileSize = FileIO_Open(pre_name);
    char *buffer = (char *)Mem_New(fileSize, 0, 1);
    char **selectedSlot = slots + slot;
    *selectedSlot = buffer;
    if (buffer != 0)
    {
        FileIO_Load(buffer);
    }
    else
    {
        printf(PRE_open_err, pre_name);
    }

    // Store filename in names array
    char *nameSlot = mPreName[slot];
    sprintf(nameSlot, PRE_fmt_s, pre_name);
}

/** Register an already-loaded archive in the first free manager slot. */
void PREManager::spoolPREData(char *pDataBuffer, char *pre_name)
{
    int slot = 0;
    char **slots;
    char **p;

    slots = mPre;
    p = slots;

    // Find empty slot
loop2:
    if (*p == 0) goto check2;
    slot++;
    if (slot < PREManager::SlotCount)
    {
        p++;
        goto loop2;
    }
check2:

    if (slot == PREManager::SlotCount)
    {
        printf(PRE_full_msg);
        return;
    }

    // Store the data pointer directly
    char **selectedSlot = slots + slot;
    *selectedSlot = pDataBuffer;

    // Store name in names array
    char *nameSlot = mPreName[slot];
    sprintf(nameSlot, PRE_fmt_s, pre_name);
}

/** Free the named archive and clear its slot. */
void PREManager::unloadPRE(char *pre_name)
{
    int slot = 0;
    // FIXME(match): register pin — $19 forces the loop-invariant `lui PRE_null_arr` to be scheduled before the two field cursors (unpinned: lui comes after, score 4); tried: null_base variable first/last, pointer-copy forms, comma expression, decl orders.
    register char *null_base asm("$19") = PRE_null_arr;
    char **slots = mPre;
    char *names = mPreName[0];

    do
    {
        int result = strcmp(names, pre_name);
        if (result != 0)
        {
            slot++;
            goto unload_continue;
        }

        slot++;

        *names = PRE_null_arr[0];
        {
            char *data = *slots;
            if (data != 0)
            {
                Mem_Delete(data);
            }
        }
        *slots = 0;
        goto unload_done;

    unload_continue:
        slots++;
        names += PREManager::NameLength;
    } while (slot < PREManager::SlotCount);

unload_done:;
}

/** Find a file in any loaded archive and return its data and size. */
char *PREManager::getFile(char *filename, int *size)
{
    char *result = 0;
    int i = 0;
    char **slots = mPre;

    while (i < PREManager::SlotCount)
    {
        char *ptr = *slots;
        if (ptr != 0)
        {
            result = parsePRE(ptr, filename, size);
        }
        i++;
        slots++;
    }
    return result;
}

/**
 * Find a file inside one archive buffer.
 *
 * Each entry contains a padded filename, its byte length, and padded data.
 */
char *PREManager::parsePRE(char *pre, char *filename, int *size)
{
    char *ptr = pre;
    int num_files = *(int *)ptr;
    ptr += 4;
    int i = 0;

    if (num_files > 0)
    {
        int mask = -4;

        do
        {
            int offs = strlen(ptr);
            offs = (offs + 4) & mask;

            char *name = ptr;
            ptr += offs;

            int length = *(int *)ptr;
            ptr += 4;

            if (strcmp(name, filename) == 0)
            {
                *size = length;
                return ptr;
            }

            offs = (length + 3) & mask;
            ptr += offs;
            i++;
        } while (i < num_files);
    }

    return 0;
}

/** Return whether the named archive is currently loaded. */
int PREManager::inPRE(char *pre_name)
{
    int slot = 0;
    char **slots = mPre;
    char *names = mPreName[0];

    do
    {
        if (*slots == 0) goto inpre_not_found;

        if (strcmp(pre_name, names) == 0)
        {
            return 1;
        }

        if (*slots == 0) goto inpre_not_found;
        slots++;
        slot++;
        names += PREManager::NameLength;
    } while (slot < PREManager::SlotCount);

inpre_not_found:
    return 0;
}

/** Diagnostics emitted when no PRE slot or allocation is available. */
static char PRE_full_msg[28] PSX_SECTION(".rdata") = "\nOut of PREManager slots";
static char PRE_open_err[28] PSX_SECTION(".rdata") = "\nMemory error loading %s";
