#!/bin/bash
# Per-TU compiler settings for stock egcs 1.1.1 (gcc 2.91.60), recovered by
# flag sweeps against SLUS_900.86. Read by verify.py (and sourceable from bash).
#
#   thps2_tu_compiler_flags   cc1/cc1plus flags (without -G)
#   thps2_tu_gp_size          assembler -G (maspsx and GNU as)
#   thps2_tu_cc_gp_size       compiler -G; differs from the assembler's for a few
#                             TUs (the original compiler treated some externs as
#                             small data while ASPSX kept them non-gp-relative)
#
# TUs not listed use the defaults at the end of each function.

thps2_tu_compiler_flags() {
    case "$1" in
        BACKGRND) echo "-O2 -fno-strength-reduce -fno-exceptions -fno-rtti -fvtable-thunks" ;;
        BADDY) echo "-O2 -fno-strength-reduce -fno-exceptions -fno-rtti -fvtable-thunks" ;;
        BIT) echo "-O2 -fno-exceptions -fno-rtti -fvtable-thunks" ;;
        BIT2) echo "-O2 -fno-exceptions -fno-rtti -fvtable-thunks -fno-implement-inlines" ;;
        BLOOD) echo "-O2 -fno-strength-reduce -fno-rtti -fno-exceptions -fvtable-thunks" ;;
        CAMERA) echo "-O2 -fno-strength-reduce -fno-exceptions -fno-rtti -fvtable-thunks" ;;
        CAMPT) echo "-O2 -fno-strength-reduce" ;;
        CAR) echo "-O2 -fno-strength-reduce -fno-exceptions -fno-rtti -fvtable-thunks" ;;
        CARD) echo "-O2 -fno-strength-reduce" ;;
        CAREER) echo "-O2" ;;
        COMPETITION) echo "-O2 -fno-rtti -fvtable-thunks -fno-exceptions" ;;
        CREATE) echo "-O2 -fno-exceptions -fno-rtti -fvtable-thunks -fcheck-new" ;;
        CREATE_COLOR) echo "-O2 -fno-strength-reduce" ;;
        CREATE_TEX) echo "-O2 -fno-strength-reduce -fno-exceptions -fno-rtti -fvtable-thunks" ;;
        CREDITS) echo "-O2 -fno-strength-reduce" ;;
        CROWD) echo "-O2" ;;
        DB) echo "-O2" ;;
        DEBUG) echo "-O2 -fno-strength-reduce" ;;
        DECOMP) echo "-O2 -fno-strength-reduce" ;;
        DUST) echo "-O2 -fno-rtti -fvtable-thunks -fno-exceptions" ;;
        EDITORPIECES) echo "-O2" ;;
        EXP) echo "-O2 -fno-strength-reduce -fno-exceptions" ;;
        FACEREMOVAL) echo "-O2 -fno-strength-reduce" ;;
        FILEIO) echo "-O2 -fno-strength-reduce" ;;
        FLASH) echo "-O2 -fno-strength-reduce" ;;
        FONT) echo "-O2" ;;
        FONTTOOLS) echo "-O2 -fno-strength-reduce -fno-exceptions -fno-rtti -fvtable-thunks" ;;
        FRONT) echo "-O2 -fno-exceptions -fno-rtti -fcheck-new -fvtable-thunks" ;;
        FRONTEND2) echo "-O2 -fno-strength-reduce" ;;
        FRONTPRE) echo "-O2 -fno-strength-reduce -fno-rtti -fno-exceptions -fvtable-thunks" ;;
        GAMEFMV) echo "-O2 -fno-strength-reduce" ;;
        GENOBJS) echo "-O2 -fno-rtti -fvtable-thunks -fno-exceptions" ;;
        HIRES) echo "-O2 -fno-strength-reduce" ;;
        IMAGE) echo "-O2 -fno-exceptions -fno-rtti -fvtable-thunks" ;;
        INIT) echo "-O2 -fno-strength-reduce" ;;
        LEVELEDITOR) echo "-O2 -fno-exceptions" ;;
        LEVELGEN) echo "-O2 -fno-rtti -fvtable-thunks -fno-exceptions" ;;
        LEVELSELECT2) echo "-O2 -fno-exceptions -fno-rtti -fvtable-thunks -fcheck-new" ;;
        LIGHT) echo "-O2 -fno-strength-reduce" ;;
        M3D) echo "-O2" ;;
        M3DCOLIJ) echo "-O2" ;;
        M3DELIPS) echo "-O2 -fno-strength-reduce" ;;
        M3DINIT) echo "-O2" ;;
        M3DUTILS) echo "-O2" ;;
        M3DZONE) echo "-O2" ;;
        MAIN) echo "-O2 -fno-strength-reduce" ;;
        MAINMENU) echo "-O2 -fno-strength-reduce -fno-exceptions -fno-rtti -fvtable-thunks -fcheck-new" ;;
        MECH) echo "-O2 -fno-rtti -fvtable-thunks -fno-exceptions" ;;
        MEDALS) echo "-O2 -fno-strength-reduce -fno-rtti -fno-exceptions -fvtable-thunks" ;;
        MEM) echo "-O2" ;;
        MENU) echo "-O2 -fno-rtti -fno-exceptions -fvtable-thunks -fcheck-new" ;;
        MESS) echo "-O2" ;;
        MULTISELECT) echo "-O2 -fno-strength-reduce -fno-exceptions -fno-rtti -fvtable-thunks -fcheck-new" ;;
        OB) echo "-O2 -fno-rtti -fno-exceptions -fvtable-thunks" ;;
        PACK) echo "-O2 -fno-strength-reduce" ;;
        PAD) echo "-O2" ;;
        PAL) echo "-O2 -fno-strength-reduce" ;;
        PANEL) echo "-O2 -fno-exceptions" ;;
        PHYSICS) echo "-O2" ;;
        PLATFORM) echo "-O2 -fno-strength-reduce -fno-exceptions -fno-rtti -fvtable-thunks" ;;
        PLAYERSELECT) echo "-O2 -fno-exceptions -fvtable-thunks -fno-rtti -fcheck-new" ;;
        POWERUP) echo "-O2 -fno-strength-reduce -fno-rtti -fno-exceptions -fvtable-thunks" ;;
        PRE) echo "-O2 -fno-exceptions -fno-rtti -fvtable-thunks -fcheck-new" ;;
        QUAT) echo "-O2 -fno-strength-reduce -fno-exceptions" ;;
        RAIL) echo "-O2 -fno-strength-reduce -fno-exceptions -fno-rtti -fvtable-thunks -fno-implement-inlines" ;;
        REDBOOK) echo "-O2" ;;
        RFRONT) echo "-O2" ;;
        SCREENTOOLS) echo "-O2 -fno-strength-reduce -fno-exceptions -fno-rtti -fvtable-thunks -fcheck-new" ;;
        SFX) echo "-O2" ;;
        SHATTER) echo "-O2 -fno-strength-reduce -fno-exceptions" ;;
        SHELL) echo "-O2 -fno-strength-reduce" ;;
        SHELLUTILS) echo "-O2 -fno-exceptions -fvtable-thunks -fno-rtti -fcheck-new" ;;
        SMOKE) echo "-O2 -fno-exceptions -fno-rtti -fvtable-thunks -fno-implement-inlines" ;;
        SPOOL) echo "-O2 -fno-strength-reduce" ;;
        SPOOLER) echo "-O2 -fno-strength-reduce -fno-rtti -fno-exceptions -fvtable-thunks" ;;
        STRLIB) echo "-O2 -fno-strength-reduce" ;;
        TAPES) echo "-O2 -fno-exceptions -fno-rtti -fvtable-thunks -fno-implement-inlines" ;;
        TEXTEFFECTS) echo "-O2 -fno-strength-reduce -fno-rtti -fno-exceptions -fvtable-thunks" ;;
        TEXTWIN) echo "-O2 -fno-strength-reduce -fno-rtti -fvtable-thunks -fno-exceptions" ;;
        TRICKOB) echo "-O2 -fno-strength-reduce -fno-rtti -fvtable-thunks -fno-exceptions" ;;
        TRICKTIPS) echo "-O2" ;;
        TRIG) echo "-O2 -fno-strength-reduce -fvtable-thunks" ;;
        UTILS) echo "-O2 -fno-strength-reduce" ;;
        VECTOR) echo "-O2 -fno-strength-reduce" ;;
        VIDEO) echo "-O2" ;;
        *) echo "-O2 -fno-strength-reduce" ;;
    esac
}

thps2_tu_gp_size() {
    case "$1" in
        BACKGRND) echo "4" ;;
        BADDY) echo "4" ;;
        BIT) echo "8" ;;
        BIT2) echo "4" ;;
        BLOOD) echo "8" ;;
        CAMERA) echo "16" ;;
        CAMPT) echo "8" ;;
        CAR) echo "8" ;;
        CARD) echo "8" ;;
        CAREER) echo "4" ;;
        COMPETITION) echo "4" ;;
        CREATE) echo "4" ;;
        CREATE_COLOR) echo "8" ;;
        CREATE_TEX) echo "8" ;;
        CREDITS) echo "8" ;;
        CROWD) echo "4" ;;
        DB) echo "4" ;;
        DEBUG) echo "8" ;;
        DECOMP) echo "8" ;;
        DUST) echo "4" ;;
        EDITORPIECES) echo "4" ;;
        EXP) echo "4" ;;
        FACEREMOVAL) echo "8" ;;
        FILEIO) echo "8" ;;
        FLASH) echo "8" ;;
        FONT) echo "8" ;;
        FONTTOOLS) echo "8" ;;
        FRONT) echo "8" ;;
        FRONTEND2) echo "8" ;;
        FRONTPRE) echo "8" ;;
        GAMEFMV) echo "8" ;;
        GENOBJS) echo "4" ;;
        HIRES) echo "8" ;;
        IMAGE) echo "16" ;;
        INIT) echo "8" ;;
        LEVELEDITOR) echo "4" ;;
        LEVELGEN) echo "8" ;;
        LEVELSELECT2) echo "4" ;;
        LIGHT) echo "8" ;;
        M3D) echo "8" ;;
        M3DCOLIJ) echo "4" ;;
        M3DELIPS) echo "8" ;;
        M3DINIT) echo "8" ;;
        M3DUTILS) echo "8" ;;
        M3DZONE) echo "8" ;;
        MAIN) echo "8" ;;
        MAINMENU) echo "4" ;;
        MECH) echo "10" ;;
        MEDALS) echo "8" ;;
        MEM) echo "16" ;;
        MENU) echo "8" ;;
        MESS) echo "4" ;;
        MULTISELECT) echo "4" ;;
        OB) echo "8" ;;
        PACK) echo "8" ;;
        PAD) echo "8" ;;
        PAL) echo "8" ;;
        PANEL) echo "8" ;;
        PHYSICS) echo "12" ;;
        PLATFORM) echo "4" ;;
        PLAYERSELECT) echo "4" ;;
        POWERUP) echo "8" ;;
        PRE) echo "4" ;;
        QUAT) echo "12" ;;
        RAIL) echo "4" ;;
        REDBOOK) echo "8" ;;
        RFRONT) echo "8" ;;
        SCREENTOOLS) echo "4" ;;
        SFX) echo "4" ;;
        SHATTER) echo "12" ;;
        SHELL) echo "8" ;;
        SHELLUTILS) echo "4" ;;
        SMOKE) echo "0" ;;
        SPOOL) echo "8" ;;
        SPOOLER) echo "8" ;;
        STRLIB) echo "8" ;;
        TAPES) echo "4" ;;
        TEXTEFFECTS) echo "8" ;;
        TEXTWIN) echo "8" ;;
        TRICKOB) echo "8" ;;
        TRICKTIPS) echo "4" ;;
        TRIG) echo "12" ;;
        UTILS) echo "8" ;;
        VECTOR) echo "8" ;;
        VIDEO) echo "4" ;;
        *) echo "8" ;;
    esac
}

thps2_tu_cc_gp_size() {
    case "$1" in
        MAIN) echo "12" ;;
        FRONT) echo "12" ;;
        BIT) echo "16" ;;
        CREATE) echo "16" ;;
        SHELLUTILS) echo "16" ;;
        SMOKE) echo "4" ;;
        COMPETITION) echo "12" ;;
        CREATE_TEX) echo "12" ;;
        FONTTOOLS) echo "16" ;;
        BIT2) echo "16" ;;
        BLOOD) echo "12" ;;
        CREDITS) echo "12" ;;
        DUST) echo "12" ;;
        FRONTPRE) echo "16" ;;
        GENOBJS) echo "12" ;;
        LEVELGEN) echo "12" ;;
        M3DCOLIJ) echo "12" ;;
        MENU) echo "12" ;;
        OB) echo "12" ;;
        PRE) echo "12" ;;
        RAIL) echo "12" ;;
        REDBOOK) echo "12" ;;
        SCREENTOOLS) echo "12" ;;
        SPOOLER) echo "12" ;;
        TEXTEFFECTS) echo "12" ;;
        TEXTWIN) echo "12" ;;
        TRICKOB) echo "12" ;;
        *) thps2_tu_gp_size "$1" ;;
    esac
}
