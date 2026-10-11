/*
 * BIT physically owns this six-pointer animation lookup in initialized data.
 * M3D's same-sized declaration naturally retains the target's absolute
 * address formation.
 */
struct SAnimFrame;

/** Fast animation-frame lookup populated by BIT initialization. */
extern SAnimFrame *QuickAnimLookup[6];
