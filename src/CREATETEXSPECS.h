#ifndef CREATETEXSPECS_INC_H
#define CREATETEXSPECS_INC_H

struct CCreateTexSpec;

#ifdef CREATETEXSPECS_WITHIN_C_LINKAGE
#define CREATETEXSPECS_DECL_LINKAGE extern
#else
#define CREATETEXSPECS_DECL_LINKAGE extern "C"
#endif

/** Head-model and texture specifications owned by CREATE_TEX. */
CREATETEXSPECS_DECL_LINKAGE CCreateTexSpec HeadSpec[];

/** Upper-body model and texture specifications owned by CREATE_TEX. */
CREATETEXSPECS_DECL_LINKAGE CCreateTexSpec UpperBodySpec[];

/** Lower-body model and texture specifications owned by CREATE_TEX. */
CREATETEXSPECS_DECL_LINKAGE CCreateTexSpec LowerBodySpec[];

#undef CREATETEXSPECS_DECL_LINKAGE
#undef CREATETEXSPECS_WITHIN_C_LINKAGE

#endif // CREATETEXSPECS_INC_H
