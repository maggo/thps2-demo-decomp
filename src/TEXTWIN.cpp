// TEXTWIN.cpp -- Reconstructed translation unit
// Original: TEXTWIN.CPP
// Functions: 1 reconstructed entry
// Address range: 0x8006AA00 - 0x8006AAB0
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#include "CCLASS_POLY.h"

/** One linked text window and its line-rendering storage. */
struct CTextWindow : CClass {
    char mPoly[24];
    int mX;
    int mY;
    int mWidth;
    int mHeight;
    void *mpLineData;
    unsigned char *mpLineFlags;
    unsigned char mTextR[4];
    unsigned char mTextG[4];
    unsigned char mTextB[4];
    char *mpTitle;
    CTextWindow *mpNext;
    CTextWindow *mpPrevious;
    int mNumLines;

    /** Unlinks the window and releases its line buffers. */
    virtual ~CTextWindow();
};

static CTextWindow *WinList = 0;

#include "MEM.h"

// === Function implementations (address order) ===

/**
 * CTextWindow::~CTextWindow()
 *
 * Address:   0x8006AA00
 * Mangled:   _._11CTextWindow
 * Demangled: CTextWindow::~CTextWindow()
 *
 */
CTextWindow::~CTextWindow() {
    if (mpNext != 0) {
        mpNext->mpPrevious = mpPrevious;
    }
    if (mpPrevious != 0) {
        mpPrevious->mpNext = mpNext;
    }
    if (WinList == this) {
        WinList = mpNext;
    }
    Mem_Delete(mpLineData);
    Mem_Delete(mpLineFlags);
}

