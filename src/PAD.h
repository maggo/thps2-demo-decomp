#ifndef PAD_INC_H
#define PAD_INC_H
#include "PSX.h"


/*
 * PAD-owned input layouts recovered from MAIN_STRUCTS.h.  Keeping this small
 * slice local avoids pulling the unrelated, incomplete gameplay layouts from
 * a monolithic compatibility header into the controller translation unit.
 */
typedef unsigned char u8;
typedef unsigned short u16;


/** One digital button's current state and frame-history counters. */
struct SButton
{
    unsigned char Pressed;
    unsigned char Triggered;
    int PressedTime;
    int ReleasedTime;
    int TriggeredTime;
};

/** Decoded gameplay state, motor state, and remap targets for one pad. */
struct SControl
{
    struct SButton Triangle;
    struct SButton Square;
    struct SButton Circle;
    struct SButton X;
    struct SButton LeftOne;
    struct SButton LeftTwo;
    struct SButton RightOne;
    struct SButton RightTwo;
    struct SButton Left;
    struct SButton Right;
    struct SButton Up;
    struct SButton Down;
    struct SButton AnalogueLeft;
    struct SButton AnalogueRight;
    struct SButton Start;
    struct SButton Select;
    struct SButton Crouch;
    struct SButton Jump;
    struct SButton SmartBomb;
    struct SButton SelectWeapon;
    unsigned char AnaloguePotMapping[4];
    unsigned char RawAnalogueMoveForwardsBackwards;
    unsigned char RawAnalogueMoveLeftRight;
    unsigned char RawAnalogueAimForwardsBackwards;
    unsigned char RawAnalogueAimLeftRight;
    char AnalogueMoveForwardsBackwards;
    char AnalogueMoveLeftRight;
    char AnalogueAimForwardsBackwards;
    char AnalogueAimLeftRight;
    int Type;
    unsigned int ResetCounter;
    unsigned char Motor0;
    unsigned char Motor1;
    unsigned char Lock;
    unsigned char AlignCalled;
    unsigned short Motor0Timer;
    unsigned short Motor1Timer;
    struct SButton *pTriangle;
    struct SButton *pSquare;
    struct SButton *pCircle;
    struct SButton *pX;
};

/** Eight-byte controller packet decoded from a physical port or multitap. */
struct ControllerData
{
    unsigned char status;
    unsigned char type;
    unsigned char button1;
    unsigned char button2;
    unsigned char analog0;
    unsigned char analog1;
    unsigned char analog2;
    unsigned char analog3;
};

/** Raw thirty-four-byte receive buffer filled by the PSY-Q pad library. */
struct ControllerBuffer
{
    unsigned char pad[34];
};

PSX_LAYOUT_CHECK(SButton_size_must_be_16, sizeof(SButton) == 16);
PSX_LAYOUT_CHECK(SControl_size_must_be_364, sizeof(SControl) == 364);
PSX_LAYOUT_CHECK(ControllerData_size_must_be_8, sizeof(ControllerData) == 8);
PSX_LAYOUT_CHECK(ControllerBuffer_size_must_be_34, sizeof(ControllerBuffer) == 34);

/** Shared gameplay input state for the two supported controllers. */
extern struct SControl Pad[2];


void Pad_InitAtStart(void);
void Pad_LockAnalog(void);
void Pad_ClearAllOne(int pad);
void Pad_ClearAll(void);
void Pad_ClearTriggers(SControl *p_pad);
void Pad_ActuatorOn(unsigned char index, unsigned short time, unsigned char motor,
                    unsigned char motor_value);
void Pad_ActuatorOff(unsigned char index, unsigned char motor);
int Pad_Update(void);
void Pad_Restore(void);
void Pad_Remap(void);

#endif // PAD_INC_H
