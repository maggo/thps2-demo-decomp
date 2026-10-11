/*
 * M3D physically owns the active depth-cue parameters in small data.
 * Consumers retain their target-recorded absolute-address declaration view.
 */
#include "PSX.h"
#ifdef DPQGLOBALS_C_LINKAGE
#define DPQGLOBALS_DECL_LINKAGE extern "C"
#else
#define DPQGLOBALS_DECL_LINKAGE extern
#endif

#ifdef DPQGLOBALS_DECLARE_HISTORY
/** Previous maximum depth-cue distance retained during camera interpolation. */
DPQGLOBALS_DECL_LINKAGE int LastDpqMax PSX_SECTION(".data");

/** Previous minimum depth-cue distance retained during camera interpolation. */
DPQGLOBALS_DECL_LINKAGE int LastDpqMin PSX_SECTION(".data");
#endif

/** Maximum depth-cue distance used by the renderer. */
DPQGLOBALS_DECL_LINKAGE int DpqMax PSX_SECTION(".data");

/** Minimum depth-cue distance used by the renderer. */
DPQGLOBALS_DECL_LINKAGE int DpqMin PSX_SECTION(".data");

#ifdef DPQGLOBALS_DECLARE_SHIFT
/** Scale shift applied to the active depth-cue range. */
DPQGLOBALS_DECL_LINKAGE int DpqShift PSX_SECTION(".data");
#endif

#undef DPQGLOBALS_DECLARE_HISTORY
#undef DPQGLOBALS_DECLARE_SHIFT
#undef DPQGLOBALS_DECL_LINKAGE
