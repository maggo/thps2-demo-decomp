// Shared declaration of the non-rendered transient-bit base.
#ifndef CNONRENDEREDBIT_INC_H
#define CNONRENDEREDBIT_INC_H
#ifndef CBIT_VIRTUAL
#define CBIT_VIRTUAL
#endif

/** A transient bit effect with no render payload. */
struct CNonRenderedBit : CBit
{
    /** Construct and attach a non-rendered transient bit. */
    CNonRenderedBit();
    /** Detach and destroy a non-rendered transient bit. */
    CBIT_VIRTUAL ~CNonRenderedBit();
    /** Release non-rendered storage through the CBit allocator. */
};

#endif // CNONRENDEREDBIT_INC_H
