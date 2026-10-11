// BLOOD.cpp -- Reconstructed translation unit
// Original: BLOOD.CPP
// Functions: 4 reconstructed entries
// Address range: 0x8006B56C - 0x8006B680
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#include "PSX.h"
#include "CCLASS_POLY.h"
#include "BIT.h"

struct BloodBit;
struct CBruce;

/** Virtual prefix used when retiring a blood particle. */
struct BloodBitVtable
{
    void (*reserved0)(void *object);
    void (*reserved1)(void *object);
    void (*destroy)(BloodBit *object, int flags);
};

/** Minimal named CBit layout needed for virtual destruction. */
struct BloodBit
{
    unsigned char state[68];
    BloodBitVtable *vtable;
};

/** Blood particle stack and lifetime state. */
struct Blood : CClass
{
    enum
    {
        Capacity = 20,
        InitialAge = 128
    };

    /** Initialize an empty blood-particle manager. */
    Blood();
    virtual ~Blood();
    /** Destroy all live blood particles and reset the manager state. */
    void Reset();
    /** Update blood particles for the active skater. */
    void Update(CBruce *bruce);

    struct BloodBit *mBloodStack[Capacity];
    int mBloodCount;
    int mAge;
};

PSX_LAYOUT_CHECK(blood_owner_size_must_be_92, sizeof(Blood) == 92);
PSX_LAYOUT_CHECK(blood_bit_size_must_be_72, sizeof(BloodBit) == 72);

// === Function implementations (address order) ===

/**
 * Initialize an empty blood-particle manager.
 *
 * Address:   0x8006B56C
 * Mangled:   __5Blood
 * Demangled: Blood::Blood(void)
 *
 */
Blood::Blood()
{
    int i = 0;
    BloodBit **ptr = mBloodStack;
    do
    {
        *ptr = 0;
        i++;
        ptr++;
    } while (i < Blood::Capacity);
    mBloodCount = 0;
    mAge = Blood::InitialAge;
}


/**
 * Blood::~Blood()
 *
 * Address:   0x8006B5A4
 * Mangled:   _._5Blood
 * Demangled: Blood::~Blood()
 *            Destructor: sets Blood vtable, calls Reset, sets base CClass vtable, conditionally deletes
 *
 */
Blood::~Blood()
{
    Reset();
}


/**
 * Destroy all live blood particles and reset the manager state.
 *
 * Address:   0x8006B5F4
 * Mangled:   Reset__5Blood
 * Demangled: Blood::Reset(void)
 *            Clears active blood bits and resets Blood's counters.
 *
 */
void Blood::Reset()
{
    int i = 0;
    if (0 < mBloodCount)
    {
        BloodBit **p = mBloodStack;
        do
        {
            BloodBit *bit = *p;
            if (bit != 0)
            {
                bit->vtable->destroy(bit, 3);
            }
            *p++ = 0;
            i++;
        } while (i < mBloodCount);
    }
    mBloodCount = 0;
    mAge = 0;
}


/**
 * Preserve the blood-update working set used by the full game implementation.
 *
 * Address:   0x8006B680
 * Mangled:   Update__5BloodP6CBruce
 * Demangled: Blood::Update(CBruce *)
 *            Reserves the original update scratch frame, but performs no per-frame blood
 *            simulation work in this build.
 *
 * @param pBruce  Active skater (CBruce) being processed.
 */
void Blood::Update(CBruce *pBruce)
{
    CSVector traj;
    CSVector cone;
    CVector SparkPos;
    CVector tempVector;
    SHook hook;
    char reservedScratch[16];
    (void)traj;
    (void)cone;
    (void)SparkPos;
    (void)tempVector;
    (void)hook;
    (void)reservedScratch;
    return;
}
