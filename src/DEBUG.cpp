// DEBUG.cpp -- Debug message sink (the prototype build discards the message).
// Original: DEBUG.CPP
// Functions: 1
// Address range: 0x800484A4 - 0x800484AC
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

/**
 * Receives a source-located debug message.
 *
 * The prototype build intentionally discards the message.
 *
 * @param p Debug message text.
 * @param line Source line that produced the message.
 * @param file Source file that produced the message.
 */
void Debug_String(char *p, int line, char *file)
{
    (void)p;
    (void)line;
    (void)file;
}
