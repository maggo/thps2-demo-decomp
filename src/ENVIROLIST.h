// Shared environment-item list physically owned by SPOOL.cpp.
#ifndef ENVIROLIST_INC_H
#define ENVIROLIST_INC_H

struct Item;

#ifdef ENVIROLIST_WITHIN_C_LINKAGE
#define ENVIROLIST_DECL_LINKAGE extern
#else
#define ENVIROLIST_DECL_LINKAGE extern "C"
#endif

#ifdef ENVIROLIST_OWNER_DECLARATION
#define ENVIROLIST_DECL_ATTR
#else
#define ENVIROLIST_DECL_ATTR __attribute__((section(".data")))
#endif

/** Head of the loaded environment-item chain. */
ENVIROLIST_DECL_LINKAGE Item *EnviroList ENVIROLIST_DECL_ATTR;

#undef ENVIROLIST_DECL_ATTR
#undef ENVIROLIST_DECL_LINKAGE
#undef ENVIROLIST_OWNER_DECLARATION
#undef ENVIROLIST_WITHIN_C_LINKAGE

#endif // ENVIROLIST_INC_H
