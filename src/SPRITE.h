// Shared declaration for captured screen sprites.
#ifndef SPRITE_INC_H
#define SPRITE_INC_H

struct SlicedImage;

/** Screen rectangle stored as a sliced image. */
#ifdef CCLASS_POLY_H
struct Sprite : CClass
{
#else
struct Sprite
{
    struct CClass CClass;
#endif
    int m_w;
    int m_h;
    int m_packed;
    int m_bpp;
    struct SlicedImage *m_image;

#ifndef CCLASS_POLY_H
    /** Allocate through the original CClass arena. */
    static void *operator new(unsigned int size) throw() { return ::CClass::operator new(size); }
#endif

    /** Load an image-backed sprite. */
    Sprite(char *file, int pack, int slicew, int sliceh);

    /** Capture a rectangular screen area into a sprite. */
    Sprite(int x, int y, int w, int h, int pack = 0, int slicew = 0, int sliceh = 0);

    /** Destroy the image owned by this sprite. */
#ifdef CCLASS_POLY_H
    virtual ~Sprite();
#else
    ~Sprite();
#endif
#ifndef CCLASS_POLY_H
    /** Release sprite storage through the original CClass allocator. */
    static void operator delete(void *storage) { ::CClass::operator delete(storage); }
#endif

    /** Draw this sprite with optional RGB modulation. */
    void draw(int x, int y, int UsePanelOT, int r = 0, int g = 0, int b = 0);
};

#endif // SPRITE_INC_H

#if defined(SPRITE_DECLARE_SLICED_IMAGE_UNPACK_ABI)

namespace SlicedImageMethodABI
{
/** Release every packed VRAM slice owned by an image. */
extern "C" void unpack__11SlicedImage(SlicedImage *image);
}

#endif // SPRITE_DECLARE_SLICED_IMAGE_UNPACK_ABI
