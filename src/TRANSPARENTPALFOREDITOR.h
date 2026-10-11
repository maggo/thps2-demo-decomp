#ifndef TRANSPARENTPALFOREDITOR_INC_H
#define TRANSPARENTPALFOREDITOR_INC_H

/*
 * PAL owns this editor palette-mode word as target BSS.  LEVELGEN retains its
 * target-proven absolute-address import view.
 */
#ifdef TRANSPARENTPALFOREDITOR_ABSOLUTE_DECLARATION
#define TRANSPARENTPALFOREDITOR_DECL_ATTR __attribute__((section(".data")))
#else
#define TRANSPARENTPALFOREDITOR_DECL_ATTR
#endif

/** Whether palette uploads should retain transparent colours for the editor. */
extern int TransparentPalForEditor TRANSPARENTPALFOREDITOR_DECL_ATTR;

#undef TRANSPARENTPALFOREDITOR_DECL_ATTR
#undef TRANSPARENTPALFOREDITOR_ABSOLUTE_DECLARATION

#endif // TRANSPARENTPALFOREDITOR_INC_H
