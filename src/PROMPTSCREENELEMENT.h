#ifndef PROMPTSCREENELEMENT_INC_H
#define PROMPTSCREENELEMENT_INC_H

#if defined(SCREENTOOLS_POLYMORPHIC_LAYOUT_EMITTED)

/** Prompt row containing an icon and its explanatory text (natural class;
 *  PLAYERSELECT.cpp owns the members and the compiler-emitted table:
 *  [1] update__17ScreenElementList [2] draw__17ScreenElementListii
 *  [3] width__19PromptScreenElement [4] refresh__13ScreenElement). */
struct PromptScreenElement : ScreenElementList
{
    PromptScreenElement(char *pFileName, char *pString, Font *pFont, int homeX, int homeY,
                        int screenX, int screenY);
    virtual ~PromptScreenElement();
    int width();
};

#else

#ifndef SCREENTOOLS_AGGREGATE_LAYOUT_EMITTED
#error "PromptScreenElement requires the SCREENTOOLS aggregate layout first"
#endif

/** Prompt row containing an icon and its explanatory text. */
struct PromptScreenElement
{
    struct ScreenElementList ScreenElementList;

    /** Allocate prompt storage through the shared CClass arena. */
    static void *operator new(unsigned int size) throw() { return ::CClass::operator new(size); }
    PromptScreenElement(char *pFileName, char *pString, Font *pFont, int homeX, int homeY,
                        int screenX, int screenY);
    ~PromptScreenElement();
    int width();
};

#endif

#endif // PROMPTSCREENELEMENT_INC_H
