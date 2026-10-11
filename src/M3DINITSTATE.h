/*
 * M3D physically owns these renderer-initialization globals in small data.
 * This header is intentionally re-entrant so the owner and M3DINIT retain
 * their original per-symbol declaration points and addressing views.
 */
struct SRotatedVertex;

#ifdef M3DINITSTATE_ABSOLUTE_DECLARATION
#define M3DINITSTATE_DECL_ATTR __attribute__((section(".data")))
#else
#define M3DINITSTATE_DECL_ATTR
#endif

#ifdef M3DINITSTATE_DECLARE_DEFAULT_LOD_DISTANCE
/** Default far depth assigned to models without an explicit LOD distance. */
extern s16 M3d_DefaultLODDistance M3DINITSTATE_DECL_ATTR;
#endif

#ifdef M3DINITSTATE_DECLARE_ROTATED_VERTICES
/** Rotated-vertex view into the shared transformed-vertex workspace. */
extern SRotatedVertex *RotatedVertices M3DINITSTATE_DECL_ATTR;
#endif

#undef M3DINITSTATE_DECLARE_DEFAULT_LOD_DISTANCE
#undef M3DINITSTATE_DECLARE_ROTATED_VERTICES
#undef M3DINITSTATE_DECL_ATTR
#undef M3DINITSTATE_ABSOLUTE_DECLARATION
