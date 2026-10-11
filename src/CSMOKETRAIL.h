// Shared declaration for smoke-trail ribbon effects.
#ifndef CSMOKETRAIL_INC_H
#define CSMOKETRAIL_INC_H

/** Ribbon whose segments fade away before the effect dies. */
struct CSmokeTrail : CRibbon {
    int mFadeAway;

    /** Build a smoke trail and tint its ribbon segments. */
    CSmokeTrail(CVector &pos, int numbits, int r, int g, int b);
    /** Destroy the smoke trail and its inherited ribbon storage. */
    ~CSmokeTrail();
    /** Fade active segments and retire the trail when they are gone. */
    void Move();
    /** Release smoke-trail storage through the CBit allocator. */
};

#endif // CSMOKETRAIL_INC_H
