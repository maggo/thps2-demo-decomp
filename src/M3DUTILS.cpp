// M3DUTILS.cpp -- Model-animation interpolation and attachment-point helpers.
// Original: M3DUTILS.CPP
// Functions: 8
// Address range: 0x800927EC - 0x8009376C
//
// Compiled with egcs 1.1.1 (GCC 2.91.60). Compiler auto-mangles symbol names.

#include "M3DUTILS.h"
#include <INLINE_C.H>
#include "gte_extensions.h"

#include "globals.h"
#include "PSXREGION.h"

/** Owner-local animation and fixed-point constants recovered from this TU. */
enum M3dUtilsConstants
{
    M3DUTILS_LOOP_WRAP = 1,
    M3DUTILS_ANIM_MIRRORED = 2,
    M3DUTILS_ITEM_USES_POSE_BUFFER = 4,
    M3DUTILS_VECTORS_PER_PART = 4,
    M3DUTILS_ANIM_DIRECTORY_STRIDE = 8,
    M3DUTILS_FIXED_SHIFT = 12,
    M3DUTILS_FIXED_ONE = 1 << M3DUTILS_FIXED_SHIFT,
    M3DUTILS_MAX_TWEEN_PARTS = 30,
    M3DUTILS_GTE_SAFE_COMPONENT = 0x6882,
    M3DUTILS_DIRECT_DIVIDE_LIMIT = 0xFFFFF
};

/** Sliding view of one animation directory row and its following metadata. */
struct M3dUtilsAnimInfo
{
    u8 reserved[4];
    s32 DataOffset;
    u16 NumFrames;
    u16 Interval;
};

/** Hook packet payload; the four-byte packet header precedes the hook array. */
struct M3dUtilsHooksPacket
{
    u8 header[4];
    SHook hooks[1];
};

/** Select the metadata window for an animation directory index. */
static inline M3dUtilsAnimInfo *M3dUtils_GetAnimInfo(unsigned int *pAnimFile, unsigned int Anim)
{
    // Keeping offset + base in this order preserves the target's `addu`
    // operand order; byte-pointer, word-pointer and reversed typed-pointer
    // forms swap the operands in all four callers.
    return reinterpret_cast<M3dUtilsAnimInfo *>(Anim * M3DUTILS_ANIM_DIRECTORY_STRIDE +
                                                reinterpret_cast<int>(pAnimFile));
}

/** CItem layout used by hook positioning and animation lookup. */
struct M3dUtilsCItemOwner
{
    u16 mFlags;
    u16 mInquiry;
    CVector mPos;
    CSVector mAngles;
    u16 mModel;
    u8 mFrame;
    u8 mTintIndex;
    u8 mAnim;
    u8 mRegion;
    M3dUtilsCItemOwner *mpNext;
    u32 mRGB;
    u8 opaque_after_mRGB[40];
};

/** CBody prefix, whose canonical size fixes the following CSuper offsets. */
struct M3dUtilsCBodyOwner
{
    M3dUtilsCItemOwner CItem;
    u8 opaque_after_CItem[188];
};

/** CSuper animation slice used by hook and in-between calculations. */
struct CSuper
{
    union
    {
        M3dUtilsCBodyOwner CBody;
        Item ItemPrefix;
    };
    u32 mAnimFlags;
    u8 opaque_to_mFrame[12];
    s16 mFrame;
    u16 mAnim;
    u8 mLoopMode;
    u8 opaque_to_mTransform[39];
    MATRIX mTransform;
    SMatrix *mpPoseBuffer;
    u8 opaque_after_mpPoseBuffer[40];
};

/** Recover the complete animation-owner view from its ABI-level Item prefix. */
static inline CSuper *M3dUtils_GetSuper(Item *pItem)
{
    return reinterpret_cast<CSuper *>(pItem);
}

#include "M3DASM.h"

/** Return the active decoded animation transforms for an item. */
SMatrix *Decomp_GetAnimTransform(CSuper *pSuper);

/** Interpolate packed animation vectors into the owner's tween buffer. */
void M3dUtils_InterpolateVectors(int NumVectors, int Interval, unsigned int *pAnimFile, Item *pItem,
                                 int Part, int NumParts);

#include "M3DMATHS.h"

/** Fixed-point vector operations provided by VECTOR.cpp. */
#include "CVECTOROPS.h"

typedef char M3dUtils_SMatrix_size_must_be_24[(sizeof(SMatrix) == 24) ? 1 : -1];
typedef char M3dUtils_AnimInfo_size_must_be_12[(sizeof(M3dUtilsAnimInfo) == 12) ? 1 : -1];
typedef char M3dUtils_HooksPacket_size_must_be_12[(sizeof(M3dUtilsHooksPacket) == 12) ? 1 : -1];
typedef char M3dUtils_CItem_size_must_be_76[(sizeof(M3dUtilsCItemOwner) == 76) ? 1 : -1];
typedef char M3dUtils_CBody_size_must_be_264[(sizeof(M3dUtilsCBodyOwner) == 264) ? 1 : -1];
typedef char M3dUtils_MATRIX_size_must_be_32[(sizeof(MATRIX) == 32) ? 1 : -1];
typedef char M3dUtils_CSuper_transform_offset_must_be_324
    [((unsigned long)&(((CSuper *)0)->mTransform) == 324) ? 1 : -1];
typedef char M3dUtils_CSuper_pose_buffer_offset_must_be_356
    [((unsigned long)&(((CSuper *)0)->mpPoseBuffer) == 356) ? 1 : -1];
typedef char M3dUtils_CSuper_size_must_be_400[(sizeof(CSuper) == 400) ? 1 : -1];

/** Scratch transforms produced while interpolating up to thirty model parts. */
SMatrix TweenBuffer[M3DUTILS_MAX_TWEEN_PARTS] __attribute__((section(".data"))) = {};

/**
 * Attach the hook array from a model packet to the item's active region.
 *
 * @param pSuper Item whose region owns the hooks.
 * @param pPacket Packet containing its hook-array payload.
 */
void M3dUtils_ReadHooksPacket(CSuper *pSuper, void *pPacket)
{
    // Keeping the packet cursor separate preserves the target load schedule;
    // folding it into the assignment changes seven of eight instructions.
    SHook *pData = static_cast<M3dUtilsHooksPacket *>(pPacket)->hooks;
    PSXRegion[pSuper->CBody.CItem.mRegion].pHooks = pData;
}


/**
 * Resolve a numbered skeletal hook into world space.
 *
 * Mirrored animations temporarily reverse the transform's first matrix
 * column. The selected hook is transformed through its animated part and the
 * item's model matrix, then blended from model space toward the item position.
 *
 * @param pResult Receives the hook position.
 * @param pSuper Animated item that owns the hook.
 * @param Hook Index in the region's hook array.
 */
void M3dUtils_GetHookPosition(VECTOR *pResult, CSuper *pSuper, int Hook)
{
    u8 regionIdx = pSuper->CBody.CItem.mRegion;
    u16 Anim = pSuper->mAnim;
    SHook *pHook = &PSXRegion[regionIdx].pHooks[Hook];
    u16 Part = pHook->Part;
    unsigned int *pAnimFile = PSXRegion[regionIdx].pAnimFile;

    // Mirroring reverses the model's first basis vector for this transform.
    if ((pSuper->mAnimFlags & M3DUTILS_ANIM_MIRRORED) != 0)
    {
        pSuper->mTransform.m[0][0] = -pSuper->mTransform.m[0][0];
        pSuper->mTransform.m[1][0] = -pSuper->mTransform.m[1][0];
        pSuper->mTransform.m[2][0] = -pSuper->mTransform.m[2][0];
    }

    SMatrix *pAnimTransform;
    u16 superFlags = pSuper->CBody.CItem.mFlags;
    if ((superFlags & M3DUTILS_ITEM_USES_POSE_BUFFER) != 0)
    {
        pAnimTransform = &pSuper->mpPoseBuffer[Part];
    }
    else
    {
        u16 parentBone = M3dUtils_GetAnimInfo(pAnimFile, Anim)->Interval;

        if (parentBone != 0)
        {
            u8 regionIdx2 = pSuper->CBody.CItem.mRegion;
            u16 numParts = PSXRegion[regionIdx2].NumParts;
            M3dUtils_InterpolateVectors(M3DUTILS_VECTORS_PER_PART, parentBone + 1, pAnimFile,
                                        &pSuper->ItemPrefix, Part, numParts);
            pAnimTransform = &TweenBuffer[Part];
        }
        else
        {
            pAnimTransform = &Decomp_GetAnimTransform(pSuper)[Part];
        }
    }

    M3dAsm_TransformTwice(&pHook->Offset, pAnimTransform, &pSuper->mTransform);

    // The transform helper leaves the hook position in MAC1-MAC3.
    gte_stlvnl(pResult);

    // Convert to world fixed point and blend toward the item's position.
    {
        pResult->vx <<= M3DUTILS_FIXED_SHIFT;
        pResult->vy <<= M3DUTILS_FIXED_SHIFT;
        pResult->vz <<= M3DUTILS_FIXED_SHIFT;

        pResult->vx =
            pSuper->CBody.CItem.mPos.vx + ((pResult->vx - pSuper->CBody.CItem.mPos.vx) >> 4);
        pResult->vy =
            pSuper->CBody.CItem.mPos.vy + ((pResult->vy - pSuper->CBody.CItem.mPos.vy) >> 4);
        pResult->vz =
            pSuper->CBody.CItem.mPos.vz + ((pResult->vz - pSuper->CBody.CItem.mPos.vz) >> 4);
    }

    // Restore the model matrix after the temporary mirror operation.
    if ((pSuper->mAnimFlags & M3DUTILS_ANIM_MIRRORED) != 0)
    {
        pSuper->mTransform.m[0][0] = -pSuper->mTransform.m[0][0];
        pSuper->mTransform.m[1][0] = -pSuper->mTransform.m[1][0];
        pSuper->mTransform.m[2][0] = -pSuper->mTransform.m[2][0];
    }
}


/**
 * Resolve an explicit skeletal hook into world space.
 *
 * Unlike the indexed hook path, dynamic hooks do not apply animation
 * mirroring.
 *
 * @param pResult Receives the hook position.
 * @param pSuper Animated item that owns the hook.
 * @param pHook Hook offset and owning part.
 */

void M3dUtils_GetDynamicHookPosition(VECTOR *pResult, CSuper *pSuper, SHook *pHook)
{
    SMatrix *pAnimTransform;
    int Anim;
    int Part;
    int Interval;
    unsigned int *pAnimFile;

    pAnimFile = PSXRegion[pSuper->CBody.CItem.mRegion].pAnimFile;
    Part = pHook->Part;
    Anim = pSuper->mAnim;

    if (pSuper->CBody.CItem.mFlags & M3DUTILS_ITEM_USES_POSE_BUFFER)
    {
        pAnimTransform = &pSuper->mpPoseBuffer[Part];
    }
    else
    {
        // The named interval keeps the metadata load live across this branch;
        // repeating the typed expression reloads it.
        Interval = M3dUtils_GetAnimInfo(pAnimFile, Anim)->Interval;
        if (Interval)
        {
            M3dUtils_InterpolateVectors(M3DUTILS_VECTORS_PER_PART, Interval + 1, pAnimFile,
                                        &pSuper->ItemPrefix, Part,
                                        PSXRegion[pSuper->CBody.CItem.mRegion].NumParts);
            pAnimTransform = &TweenBuffer[Part];
        }
        else
        {
            pAnimTransform = &Decomp_GetAnimTransform(pSuper)[Part];
        }
    }

    M3dAsm_TransformTwice(&pHook->Offset, pAnimTransform, &pSuper->mTransform);

    // Store GTE results: MAC1/MAC2/MAC3 -> pResult vx/vy/vz.
    gte_stlvnl(pResult);

    pResult->vx <<= M3DUTILS_FIXED_SHIFT;
    pResult->vy <<= M3DUTILS_FIXED_SHIFT;
    pResult->vz <<= M3DUTILS_FIXED_SHIFT;

    pResult->vx = pSuper->CBody.CItem.mPos.vx + ((pResult->vx - pSuper->CBody.CItem.mPos.vx) >> 4);
    pResult->vy = pSuper->CBody.CItem.mPos.vy + ((pResult->vy - pSuper->CBody.CItem.mPos.vy) >> 4);
    pResult->vz = pSuper->CBody.CItem.mPos.vz + ((pResult->vz - pSuper->CBody.CItem.mPos.vz) >> 4);
}


/**
 * Build interpolated bone transforms when the active animation requires them.
 *
 * @param pSuper Animated item whose pose is being prepared.
 */
void M3dUtils_InBetween(CSuper *pSuper)
{
    u8 regionIdx = pSuper->CBody.CItem.mRegion;
    unsigned int *pAnimFile = PSXRegion[regionIdx].pAnimFile;
    int Interval = M3dUtils_GetAnimInfo(pAnimFile, pSuper->mAnim)->Interval;
    int nextInterval = Interval + 1;

    if (Interval != 0)
    {
        int NumParts = PSXRegion[regionIdx].NumParts;
        M3dUtils_InterpolateVectors(NumParts * M3DUTILS_VECTORS_PER_PART, nextInterval, pAnimFile,
                                    &pSuper->ItemPrefix, 0, NumParts);
    }
}


/**
 * Interpolate animation vectors between the keyframes around the current frame.
 *
 * An exact-keyframe request copies the source vectors directly. Other frames
 * use the GTE to blend each three-component vector into `TweenBuffer`.
 *
 * @param NumVectors Number of vectors to write.
 * @param Interval Frames between animation keys.
 * @param pAnimFile Packed animation directory and transform data.
 * @param pItem Animated item, whose full object is a CSuper.
 * @param Part First model part to interpolate.
 * @param NumParts Number of parts in each animation frame.
 */

void M3dUtils_InterpolateVectors(int NumVectors, int Interval, unsigned int *pAnimFile, Item *pItem,
                                 int Part, int NumParts)
{
    CSVector dAnim; // unused, but MAIN.SYM lists it and it sizes the 0x18 frame
    SMatrix *pAnims;
    int Alpha;
    int Frame0;
    int Frame1;
    int Frame;
    int NumFrames;
    int i;
    int Anim;
    CSVector *pTween;
    CSVector *pAnim0;

    Anim = M3dUtils_GetSuper(pItem)->mAnim;
    NumFrames = M3dUtils_GetAnimInfo(pAnimFile, Anim)->NumFrames;
    pAnims = reinterpret_cast<SMatrix *>(reinterpret_cast<u8 *>(pAnimFile) +
                                         M3dUtils_GetAnimInfo(pAnimFile, Anim)->DataOffset);
    Frame = M3dUtils_GetSuper(pItem)->mFrame;
    Frame0 = Frame - Frame % Interval;
    Frame1 = Frame0 + Interval;

    if (Frame1 >= NumFrames)
    {
        if (M3dUtils_GetSuper(pItem)->mLoopMode == M3DUTILS_LOOP_WRAP)
        {
            // Wrap around: Frame1 becomes zero.
            Frame1 = 0;
            Alpha = ((Frame - Frame0) << M3DUTILS_FIXED_SHIFT) / (NumFrames - Frame0);
        }
        else
        {
            // Clamp back one key interval.
            Frame0 -= Interval;
            if (Frame0 < 0) Frame0 = 0;
            Frame1 -= Interval;
            if (Frame1 == 0)
                Alpha = 0;
            else
                Alpha = ((Frame - Frame0) << M3DUTILS_FIXED_SHIFT) / (Frame1 - Frame0);
        }
    }
    else
    {
        Alpha = ((Frame - Frame0) << M3DUTILS_FIXED_SHIFT) / (Frame1 - Frame0);
    }

    pTween = reinterpret_cast<CSVector *>(TweenBuffer) + Part * M3DUTILS_VECTORS_PER_PART;
    pAnim0 = reinterpret_cast<CSVector *>(&pAnims[(NumParts * Frame0) / Interval]) +
             Part * M3DUTILS_VECTORS_PER_PART;

    if (Alpha == 0)
    {
        // An exact keyframe only needs a direct copy.
        for (i = 0; i < NumVectors; i++)
        {
            *pTween = *pAnim0++;
            pTween++;
        }
    }
    else
    {
        CSVector *pAnim1 = reinterpret_cast<CSVector *>(&pAnims[(NumParts * Frame1) / Interval]) +
                           Part * M3DUTILS_VECTORS_PER_PART;

        gte_lddp(Alpha);

        for (i = 0; i < NumVectors; i++)
        {
            int p0x = pAnim0->vx;
            int p0y = pAnim0->vy;
            int p0z = pAnim0->vz;
            int dx = pAnim1->vx - p0x;
            int dy = pAnim1->vy - p0y;
            int dz = pAnim1->vz - p0z;
            gte_ldmac1(p0x);
            gte_ldmac2(p0y);
            gte_ldmac3(p0z);
            gte_ldir1(dx);
            gte_ldir2(dy);
            gte_ldir3(dz);
            // GPL sf=1: MAC = (MAC << 12) + IR * IR0, result >> 12.
            gte_gpl12();
            pAnim0++;
            pAnim1++;
            // Reads MAC1-3 back through fixed $t0-$t2 (one statement, like
            // Psy-Q's gte_stsv); the clobbers keep every loop pointer out of
            // $t0-$t2 and are what puts i/pTween in $t3/$t8.
            gte_stmac_sv(pTween);
            pTween++;
        }
    }
}


/**
 * Convert a rotation matrix to the engine's three signed Euler angles.
 *
 * @param pAngles Receives the X, Y, and Z angles.
 * @param pMatrix Rotation matrix to decompose.
 */
void M3dUtils_AnglesFromMatrix(SVECTOR *pAngles, MATRIX *pMatrix)
{
    int r02 = pMatrix->m[0][2];
    int r22 = pMatrix->m[2][2];
    int r10 = pMatrix->m[1][0];
    int r11 = pMatrix->m[1][1];
    int r12 = pMatrix->m[1][2];

    pAngles->vx = ratan2(-r12, M3dMaths_SquareRoot0(r02 * r02 + r22 * r22));
    pAngles->vy = ratan2(r02, r22);
    pAngles->vz = ratan2(r10, r11);
}


/**
 * SQR together with the two GTE pipeline delay slots it needs before its
 * result can be read back.
 *
 * The original emits the delays inside the same asm statement as the opcode:
 * MAIN.SYM attributes all three instructions to a single source line
 * (M3DUTILS.CPP:727 and :845), and the following gte_stlvnl address temp
 * lands in $v1 rather than $v0 only when the compiler sees one statement
 * here instead of three.
 */
#define M3DUTILS_GTE_SQR_DELAYED() __asm__ volatile("nop\nnop\n.word 0x4AA00428")

/**
 * Finds the nearest points on two line segments and returns their separation.
 *
 * Segment parameters use 12-bit fixed point and are clamped to the inclusive
 * range from zero to one. The GTE performs the cross products, projections,
 * interpolation, and final squared-distance calculation.
 *
 * @param L1Start Start of the first segment.
 * @param L1End End of the first segment.
 * @param L2Start Start of the second segment.
 * @param L2End End of the second segment.
 * @param PointL1 Receives the closest point on the first segment.
 * @param t1 Receives the first segment's fixed-point parameter.
 * @param PointL2 Receives the closest point on the second segment.
 * @param t2 Receives the second segment's fixed-point parameter.
 * @return Distance between the two selected points.
 */
int M3dUtils_LineLineClosestPoints(CVector *L1Start, CVector *L1End, CVector *L2Start,
                                   CVector *L2End, CVector *PointL1, int *t1, CVector *PointL2,
                                   int *t2)
{
    CVector DL1;
    CVector DL2;
    CVector DStart;
    CVector L1StartInt;
    CVector L2StartInt;
    CVector V;
    CVector SquaredVec;
    CVector CrossProd;
    CVector ApproachVec;
    SVECTOR VShifted;
    int Numerator;
    int Denominator;
    int Shift;
    int ExtraShift;

    DL1 = (*L1End - *L1Start) >> M3DUTILS_FIXED_SHIFT;
    DL2 = (*L2End - *L2Start) >> M3DUTILS_FIXED_SHIFT;
    DStart = (*L1Start - *L2Start) >> M3DUTILS_FIXED_SHIFT;
    L1StartInt = *L1Start >> M3DUTILS_FIXED_SHIFT;
    L2StartInt = *L2Start >> M3DUTILS_FIXED_SHIFT;

    {
        gte_ldopv1(&DL1);
        gte_ldopv2(&DL2);
        gte_op0();
        gte_stlvnl(&V);
    }

    Shift = 0;
    while (V.vx > M3DUTILS_GTE_SAFE_COMPONENT || V.vx < -M3DUTILS_GTE_SAFE_COMPONENT ||
           V.vy > M3DUTILS_GTE_SAFE_COMPONENT || V.vy < -M3DUTILS_GTE_SAFE_COMPONENT ||
           V.vz > M3DUTILS_GTE_SAFE_COMPONENT || V.vz < -M3DUTILS_GTE_SAFE_COMPONENT)
    {
        V >>= 1;
        Shift++;
    }

    {
        gte_ldlvl(&V);
        M3DUTILS_GTE_SQR_DELAYED();
        gte_stlvnl(&SquaredVec);
    }

    {
        gte_ldopv1(&DL2);
        gte_ldopv2(&DStart);
        gte_op0();
        gte_stlvnl(&CrossProd);
    }

    CrossProd >>= Shift;
    ExtraShift = 0;
    while (
        CrossProd.vx > M3DUTILS_GTE_SAFE_COMPONENT || CrossProd.vx < -M3DUTILS_GTE_SAFE_COMPONENT ||
        CrossProd.vy > M3DUTILS_GTE_SAFE_COMPONENT || CrossProd.vy < -M3DUTILS_GTE_SAFE_COMPONENT ||
        CrossProd.vz > M3DUTILS_GTE_SAFE_COMPONENT || CrossProd.vz < -M3DUTILS_GTE_SAFE_COMPONENT)
    {
        CrossProd >>= 1;
        ExtraShift++;
    }

    gte_ldlvl(&CrossProd);
    VShifted.vx = V.vx >> ExtraShift;
    VShifted.vy = V.vy >> ExtraShift;
    VShifted.vz = V.vz >> ExtraShift;
    Denominator = (SquaredVec.vx + SquaredVec.vy + SquaredVec.vz) >> (ExtraShift * 2);
    gte_ldsvrtrow0(&VShifted);
    gte_rtir_sf0();
    gte_stlvnl0(&Numerator);

    if (Numerator < 0)
    {
        *t1 = 0;
        *PointL1 = *L1Start;
    }
    else if (Numerator >= Denominator)
    {
        *t1 = M3DUTILS_FIXED_ONE;
        *PointL1 = *L1End;
    }
    else
    {
        if (Denominator > M3DUTILS_DIRECT_DIVIDE_LIMIT)
        {
            *t1 = Numerator / (Denominator >> M3DUTILS_FIXED_SHIFT);
        }
        else
        {
            *t1 = (Numerator << M3DUTILS_FIXED_SHIFT) / Denominator;
        }

        gte_ldlvnl(&L1StartInt);
        gte_ldlvl(&DL1);
        gte_lddp(*t1);
        gte_gpl12();
        gte_stlvnl(PointL1);
        *PointL1 <<= M3DUTILS_FIXED_SHIFT;
    }

    {
        gte_ldopv1(&DL1);
        gte_ldopv2(&DStart);
        gte_op0();
        gte_stlvnl(&CrossProd);
    }

    CrossProd >>= Shift;
    ExtraShift = 0;
    while (
        CrossProd.vx > M3DUTILS_GTE_SAFE_COMPONENT || CrossProd.vx < -M3DUTILS_GTE_SAFE_COMPONENT ||
        CrossProd.vy > M3DUTILS_GTE_SAFE_COMPONENT || CrossProd.vy < -M3DUTILS_GTE_SAFE_COMPONENT ||
        CrossProd.vz > M3DUTILS_GTE_SAFE_COMPONENT || CrossProd.vz < -M3DUTILS_GTE_SAFE_COMPONENT)
    {
        CrossProd >>= 1;
        ExtraShift++;
    }

    gte_ldlvl(&CrossProd);
    VShifted.vx = V.vx >> ExtraShift;
    VShifted.vy = V.vy >> ExtraShift;
    VShifted.vz = V.vz >> ExtraShift;
    Denominator = (SquaredVec.vx + SquaredVec.vy + SquaredVec.vz) >> (ExtraShift * 2);
    gte_ldsvrtrow0(&VShifted);
    gte_rtir_sf0();
    gte_stlvnl0(&Numerator);

    if (Numerator < 0)
    {
        *t2 = 0;
        *PointL2 = *L2Start;
    }
    else if (Numerator >= Denominator)
    {
        *t2 = M3DUTILS_FIXED_ONE;
        *PointL2 = *L2End;
    }
    else
    {
        if (Denominator > M3DUTILS_DIRECT_DIVIDE_LIMIT)
        {
            *t2 = Numerator / (Denominator >> M3DUTILS_FIXED_SHIFT);
        }
        else
        {
            *t2 = (Numerator << M3DUTILS_FIXED_SHIFT) / Denominator;
        }

        gte_ldlvnl(&L2StartInt);
        gte_ldlvl(&DL2);
        gte_lddp(*t2);
        gte_gpl12();
        gte_stlvnl(PointL2);
        *PointL2 <<= M3DUTILS_FIXED_SHIFT;
    }

    ApproachVec = (*PointL1 - *PointL2) >> M3DUTILS_FIXED_SHIFT;
    {
        gte_ldlvl(&ApproachVec);
        M3DUTILS_GTE_SQR_DELAYED();
        gte_stlvnl(&SquaredVec);
    }

    return M3dMaths_SquareRoot0(SquaredVec.vx + SquaredVec.vy + SquaredVec.vz);
}

/**
 * Normalizes a fixed-point vector after reducing it to the GTE input range.
 *
 * @param pV Vector to normalize in place.
 */
void M3dUtils_NormaliseVector(CVector *pV)
{
    CVector VSqd;
    int Magnitude;

    while (pV->vx > M3DUTILS_GTE_SAFE_COMPONENT || pV->vx < -M3DUTILS_GTE_SAFE_COMPONENT ||
           pV->vy > M3DUTILS_GTE_SAFE_COMPONENT || pV->vy < -M3DUTILS_GTE_SAFE_COMPONENT ||
           pV->vz > M3DUTILS_GTE_SAFE_COMPONENT || pV->vz < -M3DUTILS_GTE_SAFE_COMPONENT)
    {
        *pV >>= 1;
    }

    gte_ldlvl(pV);
    gte_sqr0();
    gte_stlvnl(&VSqd);

    Magnitude = M3dMaths_SquareRoot0(VSqd.vx + VSqd.vy + VSqd.vz);

    if (Magnitude != 0)
    {
        pV->vx = (pV->vx << M3DUTILS_FIXED_SHIFT) / Magnitude;
        pV->vy = (pV->vy << M3DUTILS_FIXED_SHIFT) / Magnitude;
        pV->vz = (pV->vz << M3DUTILS_FIXED_SHIFT) / Magnitude;
    }
    else
    {
        pV->vx = M3DUTILS_FIXED_ONE;
        pV->vy = 0;
        pV->vz = 0;
    }
}
