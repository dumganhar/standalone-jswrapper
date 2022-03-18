/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/base.h>


#include <float.h>
#include <limits>
#include <math.h>
#include <utility>
#include <inttypes.h>

// We have a separate inline define for math functions.
// The performance of these functions is very sensitive to inlining, and some compilers don't deal well with this.
#define AZ_MATH_INLINE AZ_FORCE_INLINE

// We have a separate macro for asserts within the math functions.
// Profile leaves asserts enabled, but in many cases we need highly performant profile builds (editor).
// This allows us to disable math asserts independently of asserts throughout the rest of the engine.
#ifdef AZ_DEBUG_BUILD
#   define AZ_MATH_ASSERT AZ_Assert
#else
#   define AZ_MATH_ASSERT(...)
#endif

namespace AZ
{
    class Quaternion;
    class SimpleLcgRandom;

    //! Important constants.
    namespace Constants
    {
        static constexpr float Pi = 3.14159265358979323846f;
        static constexpr float TwoPi = 6.28318530717958647692f;
        static constexpr float HalfPi = 1.57079632679489661923f;
        static constexpr float QuarterPi = 0.78539816339744830962f;
        static constexpr float TwoOverPi = 0.63661977236758134308f;
        static constexpr float MaxFloatBeforePrecisionLoss = 100000.f;
        static constexpr float Tolerance = 0.001f;
        static constexpr float FloatMax = FLT_MAX;
        static constexpr float FloatEpsilon = FLT_EPSILON;

        enum class Axis : AZ::u8
        {
            XPositive,
            XNegative,
            YPositive,
            YNegative,
            ZPositive,
            ZNegative
        };
    }

    //! Compile-time test for power of two, useful for static asserts
    //! usage: IsPowerOfTwo<(thing you're testing)>::Value
    constexpr bool IsPowerOfTwo(uint32_t testValue)
    {
        return (testValue & (testValue - 1)) == 0;
    }

    //! Calculates at compile-time the integral log base 2 of the input value.
    constexpr uint32_t Log2(uint64_t maxValue)
    {
        uint32_t bits = 0;
        do
        {
            maxValue >>= 1;
            ++bits;
        } while (maxValue > 0);
        return bits;
    }

    //! Calculates at compile-time the number of bytes required to represent the given set of input bits.
    template <uint64_t MAX_VALUE>
    constexpr uint32_t RequiredBytesForBitfield()
    {
        static_assert(MAX_VALUE <= 64, "Invalid value");
        return (MAX_VALUE > 32) ? 8
             : (MAX_VALUE > 16) ? 4
             : (MAX_VALUE >  8) ? 2
             : 1;
    }

    //! Calculates at compile-time the number of bytes required to represent the given max value.
    template <uint64_t MAX_VALUE>
    constexpr uint32_t RequiredBytesForValue()
    {
        static_assert(MAX_VALUE < 0xFFFFFFFFFFFFFFFF, "Invalid value");
        return (MAX_VALUE > 0x00000000FFFFFFFF) ? 8
             : (MAX_VALUE > 0x000000000000FFFF) ? 4
             : (MAX_VALUE > 0x00000000000000FF) ? 2
             : 1;
    }

    //! Compile-time check of address alignment.
    template <uint32_t Alignment>
    AZ_MATH_INLINE bool IsAligned(const void* addr)
    {
        static_assert(IsPowerOfTwo(Alignment), "Alignment must be a power of two");
        return (reinterpret_cast<uintptr_t>(addr) & (Alignment - 1)) == 0;
    }

    template <uint32_t BYTE_COUNT, bool IS_SIGNED = false> struct SizeType { };
    template <> struct SizeType<8, false> { using Type = uint64_t; };
    template <> struct SizeType<7, false> { using Type = uint64_t; };
    template <> struct SizeType<6, false> { using Type = uint64_t; };
    template <> struct SizeType<5, false> { using Type = uint64_t; };
    template <> struct SizeType<4, false> { using Type = uint32_t; };
    template <> struct SizeType<3, false> { using Type = uint32_t; };
    template <> struct SizeType<2, false> { using Type = uint16_t; };
    template <> struct SizeType<1, false> { using Type =  uint8_t; };
    template <> struct SizeType<0, false> { using Type =  uint8_t; };
    template <> struct SizeType<8, true > { using Type =  int64_t; };
    template <> struct SizeType<7, true > { using Type =  int64_t; };
    template <> struct SizeType<6, true > { using Type =  int64_t; };
    template <> struct SizeType<5, true > { using Type =  int64_t; };
    template <> struct SizeType<4, true > { using Type =  int32_t; };
    template <> struct SizeType<3, true > { using Type =  int32_t; };
    template <> struct SizeType<2, true > { using Type =  int16_t; };
    template <> struct SizeType<1, true > { using Type =   int8_t; };
    template <> struct SizeType<0, true > { using Type =   int8_t; };

    //! Enumerations to describe the sign and size relationship between two integer types.
    enum class IntegralTypeDiff
    {
        //! Left integer is signed, right integer is signed, both are equal in size
        LSignedRSignedEqSize,

        //! Left integer is signed, right integer is unsigned, both are equal in size
        LSignedRUnsignedEqSize,

        //! Left integer is unsigned, right integer is signed, both are equal in size
        LUnsignedRSignedEqSize,

        //! Left integer is unsigned, right integer is unsigned, both are equal in size
        LUnsignedRUnsignedEqSize,

        //! Left integer is signed, right integer is signed, left integer is wider
        LSignedRSignedLWider,

        //! Left integer is signed, right integer is unsigned, left integer is wider
        LSignedRUnsignedLWider,

        //! Left integer is unsigned, right integer is signed, left integer is wider
        LUnsignedRSignedLWider,

        //! Left integer is unsigned, right integer is unsigned, left integer is wider
        LUnsignedRUnsignedLWider,

        //! Left integer is signed, right integer is signed, right integer is wider
        LSignedRSignedRWider,

        //! Left integer is signed, right integer is unsigned, right integer is wider
        LSignedRUnsignedRWider,

        //! Left integer is unsigned, right integer is signed, right integer is wider
        LUnsignedRSignedRWider,

        //! Left integer is unsigned, right integer is unsigned, right integer is wider
        LUnsignedRUnsignedRWider,
    };

    //! Comparison result returned by SafeIntegralCompare.
    enum class IntegralCompare
    {
        LessThan,
        Equal,
        GreaterThan
    };



    //! Converts radians to degrees.
    constexpr float RadToDeg(float rad)
    {
        return rad * 180.0f / Constants::Pi;
    }

    //! Converts degrees to radians.
    constexpr float DegToRad(float deg)
    {
        return deg * Constants::Pi / 180.0f;
    }

    //! Simd optimized math functions.
    //! @{
    float Abs(float value);
    float Mod(float value, float divisor);
    float Wrap(float value, float maxValue);
    float Wrap(float value, float minValue, float maxValue);
    float AngleMod(float value);
    void SinCos(float angle, float& sin, float& cos);
    float Sin(float angle);
    float Cos(float angle);
    float Acos(float value);
    float Atan(float value);
    float Atan2(float y, float x);
    float Sqrt(float value);
    float InvSqrt(float value);
    //! @}

    AZ_MATH_INLINE bool IsClose(float a, float b, float tolerance = Constants::Tolerance)
    {
        return (AZStd::abs(a - b) <= tolerance);
    }

    AZ_MATH_INLINE bool IsClose(double a, double b, double tolerance = Constants::Tolerance)
    {
        return (AZStd::abs(a - b) <= tolerance);
    }

    //! Returns x >= 0.0f ? 1.0f : -1.0f.
    AZ_MATH_INLINE float GetSign(float x)
    {
        union FloatInt
        {
            float           f;
            unsigned int    u;
        } fi;
        fi.f = x;
        fi.u &= 0x80000000; // preserve sign
        fi.u |= 0x3f800000; // 1
        return fi.f;
    }

    //! Returns the clamped value.
    template<typename T>
    constexpr T GetClamp(T value, T min, T max)
    {
        if (value < min)
        {
            return min;
        }
        else if (value > max)
        {
            return max;
        }
        else
        {
            return value;
        }
    }

    //! Return the smaller of the 2 values.
    //! \note we don't use names like clamp, min and max because many implementations define it as a macro.
    template<typename T>
    constexpr T GetMin(T a, T b)
    {
        return a < b ? a : b;
    }

    //! Return the bigger of the 2 values.
    //! \note we don't use names like clamp, min and max because many implementations define it as a macro.
    template<typename T>
    constexpr T GetMax(T a, T b)
    {
        return a > b ? a : b;
    }

    //! Returns a linear interpolation between 2 values.
    constexpr float Lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    }

    constexpr double Lerp(double a, double b, double t)
    {
        return a + (b - a) * t;
    }

    //! Returns a value t where Lerp(a, b, t) == value (or 0 if a == b).
    inline float LerpInverse(float a, float b, float value)
    {
        return IsClose(a, b, AZStd::numeric_limits<float>::epsilon()) ? 0.0f : (value - a) / (b - a);
    }

    inline double LerpInverse(double a, double b, double value)
    {
        return IsClose(a, b, AZStd::numeric_limits<double>::epsilon()) ? 0.0 : (value - a) / (b - a);
    }

    //! Returns true if the number provided is even.
    template<typename T>
    constexpr AZStd::enable_if_t<AZStd::is_integral<T>::value, bool> IsEven(T a)
    {
        return a % 2 == 0;
    }

    //! Returns true if the number provided is odd.
    template<typename T>
    constexpr AZStd::enable_if_t<AZStd::is_integral<T>::value, bool> IsOdd(T a)
    {
        return a % 2 != 0;
    }

    AZ_MATH_INLINE float GetAbs(float a)
    {
        return AZStd::abs(a);
    }

    AZ_MATH_INLINE double GetAbs(double a)
    {
        return AZStd::abs(a);
    }

    AZ_MATH_INLINE float GetMod(float a, float b)
    {
        return Mod(a, b);
    }

    AZ_MATH_INLINE double GetMod(double a, double b)
    {
        return fmod(a, b);
    }

    //! Wraps [0, maxValue].
    AZ_MATH_INLINE int Wrap(int value, int maxValue)
    {
        return (value % maxValue) + ((value < 0) ? maxValue : 0);
    }

    //! Wraps [minValue, maxValue].
    AZ_MATH_INLINE int Wrap(int value, int minValue, int maxValue)
    {
        return Wrap(value - minValue, maxValue - minValue) + minValue;
    }

    AZ_MATH_INLINE float GetFloatQNaN()
    {
        return AZStd::numeric_limits<float>::quiet_NaN();
    }

    //! IsCloseMag(x, y, epsilon) returns true if y and x are sufficiently close, taking magnitude of x and y into account in the epsilon
    template<typename T>
    AZ_MATH_INLINE bool IsCloseMag(T x, T y, T epsilonValue = AZStd::numeric_limits<T>::epsilon())
    {
        return (AZStd::abs(x - y) <= epsilonValue * GetMax<T>(GetMax<T>(T(1.0), AZStd::abs(x)), AZStd::abs(y)));
    }

    //! ClampIfCloseMag(x, y, epsilon) returns y when x and y are within epsilon of each other (taking magnitude into account).  Otherwise returns x.
    template<typename T>
    AZ_MATH_INLINE T ClampIfCloseMag(T x, T y, T epsilonValue = AZStd::numeric_limits<T>::epsilon())
    {
        return IsCloseMag<T>(x, y, epsilonValue) ? y : x;
    }

    // This wrapper function exists here to ensure the correct version of isnormal is used on certain platforms (namely Android) because of the
    // math.h and cmath include order can be somewhat dangerous.  For example, cmath undefines isnormal (and a number of other C99 math macros 
    // defined in math.h) in favor of their std:: variants.
//cjh    AZ_MATH_INLINE bool IsNormalDouble(double x)
//    {
//        return std::isnormal(x);
//    }

    AZ_MATH_INLINE bool IsFiniteFloat(float x)
    {
        return (azisfinite(x) != 0);
    }

    //! Returns the value divided by alignment, where the result is rounded up if the remainder is non-zero.
    //! Example: alignment: 4
    //! Value:  0 1 2 3 4 5 6 7 8
    //! Result: 0 1 1 1 1 2 2 2 2
    //! @param value The numerator.
    //! @param alignment The denominator. The result will be rounded up to the nearest multiple of alignment. Must be non-zero or it will lead to undefined behavior
    template<typename T>
    constexpr T DivideAndRoundUp(T value, T alignment)
    {
        AZ_MATH_ASSERT(alignment != 0, "0 is an invalid multiple to round to.");
        AZ_MATH_ASSERT(
            AZStd::numeric_limits<T>::max() - value >= alignment,
            "value and alignment will overflow when added together during DivideAndRoundUp.");
        return (value + alignment - 1) / alignment;
    }
    
    //! Returns the value rounded up to a multiple of alignment.
    //! This function will work for non power of two alignments.
    //! If your alignment is guaranteed to be a power of two, SizeAlignUp in base.h is a more efficient implementation.
    //! Example: roundTo: 4
    //! Value:  0 1 2 3 4 5 6 7 8
    //! Result: 0 4 4 4 4 8 8 8 8
    //! @param value The number to round up.
    //! @param alignment Round up to the nearest multiple of alignment. Must be non-zero or it will lead to undefined behavior
    template<typename T>
    constexpr T RoundUpToMultiple(T value, T alignment)
    {
        return DivideAndRoundUp(value, alignment) * alignment;
    }



    //! Creates a unit quaternion uniformly sampled from the space of all possible rotations.
    //! See Graphics Gems III, chapter 6.
//cjh    Quaternion CreateRandomQuaternion(SimpleLcgRandom& rng);
}
