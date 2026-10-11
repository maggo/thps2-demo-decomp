// PRE.h -- interface of PRE.cpp
#ifndef PRE_INC_H
#define PRE_INC_H

#ifdef PRE_POLYMORPHIC_LAYOUT
#include "CCLASS_POLY.h"
#else
#include "globals.h"
#endif

// No classified variables for this TU.

/** Owns up to sixteen loaded PRE archives and their lookup names. */
#ifdef PRE_POLYMORPHIC_LAYOUT
struct PREManager : CClass
{
#else
struct PREManager
{
#endif
    enum
    {
        SlotCount = 16,
        NameLength = 16
    };

#ifndef PRE_POLYMORPHIC_LAYOUT
    struct CClass CClass;
#endif
    char *mPre[SlotCount];
    char mPreName[SlotCount][NameLength];

#ifdef PRE_POLYMORPHIC_LAYOUT
    PREManager();
    virtual ~PREManager();
#else
    ~PREManager();
#endif
    void loadPRE(char *pre_name);
    void spoolPRE(char *pre_name);
    void spoolPREData(char *data, char *pre_name);
    void unloadPRE(char *pre_name);
    char *getFile(char *filename, int *size);
    char *parsePRE(char *pre, char *filename, int *size);
    int inPRE(char *pre_name);
#ifndef PRE_POLYMORPHIC_LAYOUT
    /** Allocate manager storage through the original CClass allocator. */
    static void *operator new(unsigned int size) throw() { return ::CClass::operator new(size); }
#endif
#ifndef PRE_POLYMORPHIC_LAYOUT
    /** Release manager storage through the original CClass allocator. */
    static void operator delete(void *p) { ::CClass::operator delete(p); }
#endif
};

#endif // PRE_INC_H
