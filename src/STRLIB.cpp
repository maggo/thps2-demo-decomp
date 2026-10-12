// STRLIB.cpp -- String helpers used by game-script parsing.
// Original: STRLIB.CPP
// Functions: 3
// Address range: 0x8006C9D0 - 0x8006CAAC
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#include "STRLIB.h"

/**
 * Finds the first occurrence of a substring.
 *
 * @param pHay String to search.
 * @param pNeedle Substring to locate.
 * @return A pointer to the first match, or null when no match exists.
 */
char *strstr(char *pHay, char *pNeedle)
{
    char First = *pNeedle++;
    if (First == '\0') return 0;
    for (;;)
    {
        char hayCharacter = *pHay++;
        if (hayCharacter != First)
        {
            if (hayCharacter == '\0') return 0;
            continue;
        }
        char *pH = pHay;
        char *pN = pNeedle;
        for (;;)
        {
            char needleCharacter = *pN++;
            if (needleCharacter == '\0') return pHay - 1;
            if (needleCharacter != *pH++) break;
        }
    }
}

/**
 * Converts an ASCII string to lower case in place.
 *
 * @param p Null-terminated string to modify.
 */
void LowerCase(char *p)
{
    if (*p == '\0') return;
    do
    {
        char letter = *p;
        if (static_cast<unsigned int>(letter - 'A') < 26)
        {
            letter += 'a' - 'A';
        }
        *p = letter;
        p++;
    } while (*p != '\0');
}

/**
 * Reports whether the current character is horizontal whitespace.
 *
 * @param p Character position to inspect.
 * @return One for a space or tab; otherwise zero.
 */
int WhiteSpace(char *p)
{
    if (*p == ' ' || *p == '\t')
    {
        return 1;
    }
    return 0;
}
