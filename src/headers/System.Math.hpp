#ifndef _SYSTEM_MATH_HPP
#define _SYSTEM_MATH_HPP

#include "System.hpp"

//Based on:
//https://docs.microsoft.com/en-us/dotnet/api/system.math?view=netframework-4.7.2

namespace System {
namespace Math {

/**
 * Represents the natural logarithmic base, specified by the constant 'e'
 */
const double E = 2.71828182845904523536;
/**
 * Represents the ratio of the circumference of a circle to its diameter, specified by the constant, 'pi'
 */
const double PI = 3.14159265358979323846;
/**
 * Represents 0
 */
const double ZERO = 0;
/**
 * Represents 1
 */
const double ONE = 1;
/**
 * Degrees to radians conversion constant
 */
const double Deg2Rad = (PI * 2) / 360;
/**
 * Radians to degrees conversion constant
 */
const double Rad2Deg = 360 / (PI * 2);

/**
 * Clamp a value between a given minimum and maximum
 */
double Clamp(double value, double min, double max);
/**
 * Clamp a value between 0 and 1
 */
double Clamp01(double value);
/**
 * Linearly interpolate a value between 'a' and 'b' by the value 't'
 */
double Lerp(double a, double b, double t);
/**
 *  Moves a value current towards target by at most 'maxStep' amount
 */
double MoveTowards(double a, double b, double maxStep);
/** 
 *  Loops the value t, so that it is never larger than length and never smaller than 0.
 */
double Repeat(double t, double length);

/**
 * Types of rounding modes 
 */
enum struct RoundingMode {
    HalfEven, AwayFromZero, TowardsZero
};
/** 
 *  Returns f rounded to the nearest integer.
 */
double Round(double x, RoundingMode mode);
/** 
 *  Returns f rounded to the nearest integer.
 */
long RoundToInt(double x, RoundingMode mode);

/**
 * Returns the absolute value of a double-precision floating-point number.
 */
double Abs(double d);
/**
 * Returns the absolute value of a long integer.
 */
long Abs(long s);

/**
 * Returns the smallest integral value that is greater than or equal to the specified double-precision floating-point number.
 */
long Ceiling(double d);
/**
 * Returns the largest integral value less than or equal to the specified double-precision floating-point number.
 */
long Floor(double d);
/**
 * Raises e to the specified power 
 */
double Exp(double x);
/**
 * Returns a specified number raised to the specified power.
 */
double Pow(double base, double power);
/**
 * Returns an integer that indicates the sign of a double-precision floating-point number.
 */
long Sign(double x);
/**
 * Returns an integer that indicates the sign of a long integer.
 */
long Sign(long x);
/**
 * Returns the square-root of a double-precision floating-point number.
 */
double Sqrt(double x);

/**
 * Returns the natural (base 'e') logarithm of a specified number.
 */
double Log(double x);
/**
 * Returns the base 10 logarithm of a specified number.
 */
double Log10(double x);
/**
 * Returns the logarithm of a specified number in a specified base.
 */
double Log(double x, double base);

/**
 * Return the maximal element in a set 
 */
template<class T>
T Max(T a, T b){
    return (a > b ? a : b);
}
/**
 * Return the maximal element in a set 
 */
template<class T, class... a>
T Max(T x , a... z) {
    T k = Max(z...);
    return (x > k ? x : k);
}
/**
 * Return the minimal element in a set 
 */
template<class T>
T Min(T a, T b){
    return (a < b ? a : b);
}
/**
 * Return the minimal element in a set 
 */
template<class T, class... a>
T Min(T x , a... z) {
    T k = Min(z...);
    return (x < k ? x : k);
}

/**
 * Returns the cosine of the specified angle.
 */
double Cos(double theta);
/**
 * Returns the hyperbolic cosine of the specified angle.
 */
double Cosh(double theta);
/**
 * Returns the sine of the specified angle.
 */
double Sin(double theta);
/**
 * Returns the hyperbolic sine of the specified angle.
 */
double Sinh(double theta);
/**
 * Returns the tangent of the specified angle.
 */
double Tan(double theta);
/**
 * Returns the hyperbolic tangent of the specified angle.
 */
double Tanh(double theta);
/**
 * Returns the angle whose tangent is the specified number.
 */
double Atan(double v);
/**
 * Returns the angle whose cosine is the specified number.
 */
double Acos(double v);
/**
 * Returns the angle whose sine is the specified number.
 */
double Asin(double v);
/**
 * Returns the angle whose tangent is the quotient of two specified numbers.
 */
double Atan2(double y, double x);

}
}

#endif