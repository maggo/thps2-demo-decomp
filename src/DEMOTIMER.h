#ifndef DEMOTIMER_INC_H
#define DEMOTIMER_INC_H

/*
 * FRONT physically owns the demo countdown word in small data. Consumers
 * address it absolutely, so each inclusion must select the proven view.
 */
#ifdef DEMOTIMER_ABSOLUTE_DECLARATION
#define DEMOTIMER_DECL_ATTR __attribute__((section(".data")))
#else
#define DEMOTIMER_DECL_ATTR
#endif

/** Countdown used while demo playback is active. */
extern int DemoTimer DEMOTIMER_DECL_ATTR;

#undef DEMOTIMER_DECL_ATTR
#undef DEMOTIMER_ABSOLUTE_DECLARATION

#endif // DEMOTIMER_INC_H
