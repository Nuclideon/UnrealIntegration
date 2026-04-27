# udMath_Inl

Inline implementations for the math types and functions declared in udMath.h. This file is included automatically at the end of udMath.h and should not be included directly. 

## Functions

### template<typename T>T udHighestBitValue(T i)

### template<typename T>bool udIsPowerOfTwo(T i)

### template<typename T>T udPowerOfTwoAbove(T v)

### template<typename T>T udRoundEven(T t)

### inline float udPow(float f, float n)

### inline double udPow(double d, double n)

### inline float udExp(float f)

### inline double udExp(double d)

### inline float udLogN(float f)

### inline double udLogN(double d)

### inline float udLog10(float f)

### inline double udLog10(double d)

### inline float udLog(float f, float base)

### inline double udLog(double f, double base)

### inline float udLog2(float f)

### inline double udLog2(double d)

### inline float udRSqrt(float f)

### inline double udRSqrt(double d)

### inline float udSqrt(float f)

### inline double udSqrt(double d)

### inline float udSin(float f)

### inline double udSin(double d)

### inline float udCos(float f)

### inline double udCos(double d)

### inline float udTan(float f)

### inline double udTan(double d)

### inline float udSinh(float f)

### inline double udSinh(double d)

### inline float udCosh(float f)

### inline double udCosh(double d)

### inline float udTanh(float f)

### inline double udTanh(double d)

### inline float udASin(float f)

### inline double udASin(double d)

### inline float udACos(float f)

### inline double udACos(double d)

### inline float udATan(float f)

### inline double udATan(double d)

### inline float udATan2(float y, float x)

### inline double udATan2(double y, double x)

### inline float udASinh(float f)

### inline double udASinh(double d)

### inline float udACosh(float f)

### inline double udACosh(double d)

### inline float udATanh(float f)

### inline double udATanh(double d)

### inline float udRound(float f)

### inline double udRound(double d)

### template<typename T>udVector2<T> udRound(const udVector2<T> &v)

### template<typename T>udVector3<T> udRound(const udVector3<T> &v)

### template<typename T>udVector4<T> udRound(const udVector4<T> &v)

### inline float udFloor(float f)

### inline double udFloor(double d)

### template<typename T>udVector2<T> udFloor(const udVector2<T> &v)

### template<typename T>udVector3<T> udFloor(const udVector3<T> &v)

### template<typename T>udVector4<T> udFloor(const udVector4<T> &v)

### inline float udCeil(float f)

### inline double udCeil(double d)

### template<typename T>udVector2<T> udCeil(const udVector2<T> &v)

### template<typename T>udVector3<T> udCeil(const udVector3<T> &v)

### template<typename T>udVector4<T> udCeil(const udVector4<T> &v)

### inline float udMod(float f, float den)

### inline double udMod(double d, double den)

### template<typename T>udVector2<T> udMod(const udVector2<T> &v)

### template<typename T>udVector3<T> udMod(const udVector3<T> &v)

### template<typename T>udVector4<T> udMod(const udVector4<T> &v)

### template<typename T>T udAbs(T v)

### template<typename T>udVector2<T> udAbs(const udVector2<T> &v)

### template<typename T>udVector3<T> udAbs(const udVector3<T> &v)

### template<typename T>udVector4<T> udAbs(const udVector4<T> &v)

### template<typename T>udQuaternion<T> udAbs(const udQuaternion<T> &q)

### template<typename T>udVector2<T> udMin(const udVector2<T> &v1, const udVector2<T> &v2)

### template<typename T>udVector3<T> udMin(const udVector3<T> &v1, const udVector3<T> &v2)

### template<typename T>udVector4<T> udMin(const udVector4<T> &v1, const udVector4<T> &v2)

### template<typename T>T udMinElement(const udVector2<T> &v)

### template<typename T>T udMinElement(const udVector3<T> &v)

### template<typename T>T udMinElement(const udVector4<T> &v)

### template<typename T>udVector2<T> udMax(const udVector2<T> &v1, const udVector2<T> &v2)

### template<typename T>udVector3<T> udMax(const udVector3<T> &v1, const udVector3<T> &v2)

### template<typename T>udVector4<T> udMax(const udVector4<T> &v1, const udVector4<T> &v2)

### template<typename T>T udMaxElement(const udVector2<T> &v)

### template<typename T>T udMaxElement(const udVector3<T> &v)

### template<typename T>T udMaxElement(const udVector4<T> &v)

### template<typename T>T udClamp(T v, T \_min, T \_max)

### template<typename T>udVector2<T> udClamp(const udVector2<T> &v, const udVector2<T> &\_min, const udVector2<T> &\_max)

### template<typename T>udVector3<T> udClamp(const udVector3<T> &v, const udVector3<T> &\_min, const udVector3<T> &\_max)

### template<typename T>udVector4<T> udClamp(const udVector4<T> &v, const udVector4<T> &\_min, const udVector4<T> &\_max)

### template<typename T>T udSaturate(const T &v)

### template<typename T>udVector2<T> udSaturate(const udVector2<T> &v)

### template<typename T>udVector3<T> udSaturate(const udVector3<T> &v)

### template<typename T>udVector4<T> udSaturate(const udVector4<T> &v)

### template<typename V, typename T>bool udIsUnitLength(const V &v, T epsilon)

### template<typename T>inline T udDot(const udVector2<T> &v1, const udVector2<T> &v2)

### template<typename T>inline T udDot(const udVector3<T> &v1, const udVector3<T> &v2)

### template<typename T>inline T udDot(const udVector4<T> &v1, const udVector4<T> &v2)

### template<typename T>inline T udDot(const udQuaternion<T> &q1, const udQuaternion<T> &q2)

### template<typename T>T udDot2(const udVector2<T> &v1, const udVector2<T> &v2)

### template<typename T>T udDot2(const udVector3<T> &v1, const udVector3<T> &v2)

### template<typename T>T udDot2(const udVector4<T> &v1, const udVector4<T> &v2)

### template<typename T>T udDot3(const udVector3<T> &v1, const udVector3<T> &v2)

### template<typename T>T udDot3(const udVector4<T> &v1, const udVector4<T> &v2)

### template<typename T>T udDot4(const udVector4<T> &v1, const udVector4<T> &v2)

### template<typename T>T udDoth(const udVector3<T> &v3, const udVector4<T> &v4)

### template<typename T>T udDotQ(const udQuaternion<T> &q1, const udQuaternion<T> &q2)

### template<typename T>inline T udMagSq(const udVector2<T> &v)

### template<typename T>inline T udMagSq(const udVector3<T> &v)

### template<typename T>inline T udMagSq(const udVector4<T> &v)

### template<typename T>inline T udMagSq(const udQuaternion<T> &q)

### template<typename T>T udMagSq2(const udVector2<T> &v)

### template<typename T>T udMagSq2(const udVector3<T> &v)

### template<typename T>T udMagSq2(const udVector4<T> &v)

### template<typename T>T udMagSq3(const udVector3<T> &v)

### template<typename T>T udMagSq3(const udVector4<T> &v)

### template<typename T>T udMagSq4(const udVector4<T> &v)

### template<typename T>T udMagSqQ(const udQuaternion<T> &q)

### template<typename T>inline T udMag(const udVector2<T> &v)

### template<typename T>inline T udMag(const udVector3<T> &v)

### template<typename T>inline T udMag(const udVector4<T> &v)

### template<typename T>inline T udMag(const udQuaternion<T> &v)

### template<typename T>T udMag2(const udVector2<T> &v)

### template<typename T>T udMag2(const udVector3<T> &v)

### template<typename T>T udMag2(const udVector4<T> &v)

### template<typename T>T udMag3(const udVector3<T> &v)

### template<typename T>T udMag3(const udVector4<T> &v)

### template<typename T>T udMag4(const udVector4<T> &v)

### template<typename T>T udMagQ(const udQuaternion<T> &q)

### template<typename T>inline T udCross(const udVector2<T> &v1, const udVector2<T> &v2)

### template<typename T>inline udVector3<T> udCross(const udVector3<T> &v1, const udVector3<T> &v2)

### template<typename T>T udCross2(const udVector2<T> &v1, const udVector2<T> &v2)

### template<typename T>T udCross2(const udVector3<T> &v1, const udVector3<T> &v2)

### template<typename T>T udCross2(const udVector4<T> &v1, const udVector4<T> &v2)

### template<typename T>udVector3<T> udCross3(const udVector3<T> &v1, const udVector3<T> &v2)

### template<typename T>udVector3<T> udCross3(const udVector4<T> &v1, const udVector4<T> &v2)

### template<typename T>inline udVector2<T> udNormalize(const udVector2<T> &v)

### template<typename T>inline udVector3<T> udNormalize(const udVector3<T> &v)

### template<typename T>inline udVector4<T> udNormalize(const udVector4<T> &v)

### template<typename T>inline udQuaternion<T> udNormalize(const udQuaternion<T> &q)

### template<typename T>udVector2<T> udNormalize2(const udVector2<T> &v)

### template<typename T>udVector3<T> udNormalize2(const udVector3<T> &v)

### template<typename T>udVector4<T> udNormalize2(const udVector4<T> &v)

### template<typename T>udVector3<T> udNormalize3(const udVector3<T> &v)

### template<typename T>udVector4<T> udNormalize3(const udVector4<T> &v)

### template<typename T>udVector4<T> udNormalize4(const udVector4<T> &v)

### template<typename T>udQuaternion<T> udNormalizeQ(const udQuaternion<T> &v)

### template<typename V>inline bool udEqualApprox(const V &a, const V &b, typename V::ElementType epsilon)

### template<typename T>inline bool udMatrixEqualApprox(const udMatrix4x4<T> &a, const udMatrix4x4<T> &b, T epsilon)

### template<typename T>inline T udNormaliseRotation(T rad, T absRange)

### template<typename T>udVector3<T> udDirectionFromYPR(const udVector3<T> &ypr)

### template<typename T>udVector3<T> udDirectionToYPR(const udVector3<T> &direction)

### template<typename T, typename U>udMatrix4x4<T> udMul(const udMatrix4x4<T> &m, U f)

### template<typename T>udVector2<T> udMul(const udMatrix4x4<T> &m, const udVector2<T> &v)

### template<typename T>udVector3<T> udMul(const udMatrix4x4<T> &m, const udVector3<T> &v)

### template<typename T>udVector4<T> udMul(const udMatrix4x4<T> &m, const udVector4<T> &v)

### template<typename T>udMatrix4x4<T> udMul(const udMatrix4x4<T> &m1, const udMatrix4x4<T> &m2)

### template<typename T>udMatrix4x4<T> udAdd(const udMatrix4x4<T> &m1, const udMatrix4x4<T> &m2)

### template<typename T>udMatrix4x4<T> udSub(const udMatrix4x4<T> &m1, const udMatrix4x4<T> &m2)

### template<typename T>udQuaternion<T> udMul(const udQuaternion<T> &q1, const udQuaternion<T> &q2)

### template<typename T>T udLerp(T a, T b, double t)

### template<typename T>T udBiLerp(T a, T b, T c, T d, double t1, double t2)

### template<typename T>udVector2<T> udLerp(const udVector2<T> &v1, const udVector2<T> &v2, double t)

### template<typename T>udVector3<T> udLerp(const udVector3<T> &v1, const udVector3<T> &v2, double t)

### template<typename T>udVector4<T> udLerp(const udVector4<T> &v1, const udVector4<T> &v2, double t)

### template<typename T>udMatrix4x4<T> udLerp(const udMatrix4x4<T> &m1, const udMatrix4x4<T> &m2, double t)

### template<typename T>udQuaternion<T> udLerp(const udQuaternion<T> &q1, const udQuaternion<T> &q2, double t)

### template<typename T>udQuaternion<T> udSlerp(const udQuaternion<T> &q1, const udQuaternion<T> &\_q2, double t)

### template<typename T>udMatrix4x4<T> udTranspose(const udMatrix4x4<T> &m)

### template<typename T>T udDeterminant(const udMatrix4x4<T> &m)

### template<typename T>udMatrix4x4<T> udInverse(const udMatrix4x4<T> &m)

### template<typename T>udQuaternion<T> udInverse(const udQuaternion<T> &q)

### template<typename T>udQuaternion<T> udConjugate(const udQuaternion<T> &q)
