// Shared animation-tween workspace physically owned by M3DUTILS.cpp.

struct SMatrix;

/*
 * This declaration header is intentionally re-entrant so the owner retains
 * MAIN.SYM's complete thirty-element type while address-only consumers keep
 * the original incomplete array declaration emitted by their object.
 */
#ifdef TWEENBUFFER_OWNER_DECLARATION
#define TWEENBUFFER_DECL_BOUND 30
#else
#define TWEENBUFFER_DECL_BOUND
#endif

/** Scratch transforms produced while interpolating model parts. */
extern SMatrix TweenBuffer[TWEENBUFFER_DECL_BOUND];

#undef TWEENBUFFER_DECL_BOUND
