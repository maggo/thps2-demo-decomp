/*
 * M3D physically owns the 800-entry transformed-vertex workspace. M3DINIT
 * retains its target-proven incomplete-array view while splitting that
 * storage into projected and rotated halves.
 */
#ifdef VERTICES_CONSUMER_DECLARATION
#define VERTICES_DECL_EXTENT
#else
#define VERTICES_DECL_EXTENT 800
#endif

/** One entry in M3D's shared transformed-vertex workspace. */
struct SVertex
{
    s16 X;
    s16 Y;
    s16 z;
    u16 Outcode;
};

/** Shared transformed-vertex workspace physically owned by M3D.cpp. */
extern "C" SVertex Vertices[VERTICES_DECL_EXTENT];

#undef VERTICES_DECL_EXTENT
#undef VERTICES_CONSUMER_DECLARATION
