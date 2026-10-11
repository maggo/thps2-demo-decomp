// Shared replay-audio lockout physically owned by VIDEO.cpp.
#ifndef REPLAYSOUNDLOCKOUT_INC_H
#define REPLAYSOUNDLOCKOUT_INC_H

#ifdef REPLAYSOUNDLOCKOUT_ABSOLUTE_DECLARATION
#define REPLAYSOUNDLOCKOUT_DECL_ATTR __attribute__((section(".data")))
#else
#define REPLAYSOUNDLOCKOUT_DECL_ATTR
#endif

/** Prevent replay sounds from being emitted recursively during playback. */
extern int ReplaySoundLockout REPLAYSOUNDLOCKOUT_DECL_ATTR;

#undef REPLAYSOUNDLOCKOUT_DECL_ATTR
#undef REPLAYSOUNDLOCKOUT_ABSOLUTE_DECLARATION

#endif // REPLAYSOUNDLOCKOUT_INC_H
