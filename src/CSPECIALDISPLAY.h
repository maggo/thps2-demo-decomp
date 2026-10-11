// Shared declaration of the special-display transient-bit base.
#ifndef CSPECIALDISPLAY_INC_H
#define CSPECIALDISPLAY_INC_H
#ifndef CBIT_VIRTUAL
#define CBIT_VIRTUAL
#endif

/** A transient bit whose default display hook emits no geometry. */
struct CSpecialDisplay : CBit {
    /** Construct and attach a special-display bit. */
    CSpecialDisplay();
    /** Detach and destroy a special-display bit. */
    CBIT_VIRTUAL ~CSpecialDisplay();
    /** Default display hook. */
    CBIT_VIRTUAL void Display();
    /** Release special-display storage through the CBit allocator. */
};

#endif // CSPECIALDISPLAY_INC_H
