// PSX.h -- PlayStation target specifics used throughout the source.
//
// Data placement and layout checks that the matching build needs are spelled
// through these macros instead of raw GCC attributes. They expand to exactly the
// attribute or declaration the original object code requires.
#ifndef PSX_H
#define PSX_H

/** Place a definition in a specific section, as the original object did. */
#define PSX_SECTION(s) __attribute__((section(s)))
/** Place a definition in a specific section with an explicit alignment. */
#define PSX_SECTION_ALIGNED(s, n) __attribute__((section(s), aligned(n)))
/** Compile-time layout check (e.g. a struct's size or a member's offset). */
#define PSX_LAYOUT_CHECK(name, cond) typedef char name[(cond) ? 1 : -1]

#endif // PSX_H
