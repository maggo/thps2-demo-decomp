#ifndef YESNOMENU_INC_H
#define YESNOMENU_INC_H
#include "PSX.h"

struct CMenu;

/* FRONT physically owns the shared confirmation menu in small data. */
#ifdef YESNOMENU_WITHIN_C_LINKAGE
#define YESNOMENU_DECL_LINKAGE extern
#else
#define YESNOMENU_DECL_LINKAGE extern "C"
#endif

#ifdef YESNOMENU_OWNER_DECLARATION
#define YESNOMENU_DECL_ATTR
#else
#define YESNOMENU_DECL_ATTR PSX_SECTION(".data")
#endif

/** Confirmation menu shared by front-end flows. */
YESNOMENU_DECL_LINKAGE CMenu *pYesNoMenu YESNOMENU_DECL_ATTR;

#undef YESNOMENU_DECL_ATTR
#undef YESNOMENU_DECL_LINKAGE
#undef YESNOMENU_OWNER_DECLARATION

#endif // YESNOMENU_INC_H
