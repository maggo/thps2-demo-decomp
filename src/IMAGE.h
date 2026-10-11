#ifndef IMAGE_INC_H
#define IMAGE_INC_H

/** Set the active clipping box and relink it into the panel ordering table. */
void SetClippingBox2(int x, int y, int width, int height);

#endif // !IMAGE_INC_H

/*
 * Natural polymorphic image hierarchy (vt4) for TUs that define
 * IMAGE_POLYMORPHIC_LAYOUT (requires CCLASS_POLY.h's CClass first).  Slot order
 * from __vt_12SlicedImage2 / __vt_7Sprite2 / __vt_12RotateSprite:
 *   Image        [0] ~   [1] draw(int,int)
 *   SlicedImage2 [2] setData(void *)  [3] draw(int,int,int)
 * The owner (IMAGE.cpp) defines IMAGE_POLYMORPHIC_LAYOUT_IMPLEMENT and gets the
 * empty in-class bodies of ~Image, Image::draw(int,int) and ~RotateSprite.  GCC
 * emits their out-of-line copies (and the private CClass destructor copy with
 * the two local tables __vt_5Image / _vt.6CClass in .sdata) at the end of the
 * owner's text: that tail is what MAIN.SYM attributes to the file "IMAGE.H"
 * (0x8005e158..0x8005e214 directly after draw__12RotateSpriteiii), so IMAGE.H
 * is not a separate object.
 * Every other TU only declares the three virtuals.
 */
#if defined(IMAGE_POLYMORPHIC_LAYOUT) && !defined(IMAGE_POLYMORPHIC_LAYOUT_EMITTED)
#define IMAGE_POLYMORPHIC_LAYOUT_EMITTED

#ifndef CCLASS_POLY_H
#error "IMAGE_POLYMORPHIC_LAYOUT requires CCLASS_POLY.h first"
#endif

#ifdef IMAGE_POLYMORPHIC_LAYOUT_IMPLEMENT
#define IMAGE_EMPTY_VIRTUAL {}
#else
#define IMAGE_EMPTY_VIRTUAL ;
#endif

struct Slice;

/** Common render state shared by the textured image classes. */
struct Image : CClass {
    void *Transparent;
    void *Shaded;
    int TransType;
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char JustX;
    unsigned char JustY;
    int Scale;

    Image();
    virtual ~Image() IMAGE_EMPTY_VIRTUAL
    /** Draw the image at the requested screen position (empty in Image). */
    virtual void draw(int x, int y) IMAGE_EMPTY_VIRTUAL
};

/** Image split into independently allocated pixel and VRAM slices. */
struct SlicedImage2 : Image {
    Slice *SliceTab;
    short W;
    short H;
    short SliceW;
    short SliceH;
    short SliceCountX;
    short SliceCountY;
    /** True after owned pixel buffers have been allocated for the slices. */
    bool InMemory;
    /** True after the slice rectangles have been allocated in VRAM. */
    bool Packed;
    int BppShift;
    unsigned short Clut;

    SlicedImage2();
    SlicedImage2(void *data, int tileW, int tileH, int maxW, int maxH,
                 unsigned char bpp, unsigned short clut);
    virtual ~SlicedImage2();
    /** Initialize slice dimensions, packing mode, and source data. */
    void newSlicedImage2(void *data, int width, int height, int sliceWidth,
                         int sliceHeight, unsigned char bpp,
                         unsigned short clut);
    /** Replace the copied pixel data for every image slice. */
    virtual void setData(void *data);
    /** Draw every image slice at the requested screen position. */
    virtual void draw(int x, int y, int drawFirst);
    void pack();
    void repack();
    void unpack();
    void removeFromMemory();
    int screenWidth();
    int screenHeight();
};

/** BMP-backed sliced image with no additional storage. */
struct Sprite2 : SlicedImage2 {
    Sprite2(char *filename, int pack, int sliceWidth, int sliceHeight);
    Sprite2(unsigned char *buffer, int pack, int sliceWidth, int sliceHeight);
    virtual ~Sprite2();
    void setData(void *data);
};

/** Rotatable sprite (64 bytes). */
struct RotateSprite : Sprite2 {
    unsigned char AspectType;

    RotateSprite(char *filename, int pack, int slice_w, int slice_h);
    virtual ~RotateSprite() IMAGE_EMPTY_VIRTUAL
    void draw(int x, int y, int rot);
};

typedef char image_poly_Image_size_must_be_28[(sizeof(Image) == 28) ? 1 : -1];
typedef char image_poly_SlicedImage2_size_must_be_60[
    (sizeof(SlicedImage2) == 60) ? 1 : -1];
typedef char image_poly_Sprite2_size_must_be_60[(sizeof(Sprite2) == 60) ? 1 : -1];
typedef char image_poly_RotateSprite_size_must_be_64[
    (sizeof(RotateSprite) == 64) ? 1 : -1];

#endif // IMAGE_POLYMORPHIC_LAYOUT
