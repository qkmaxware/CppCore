#include <cmath>
#include "System.Math.hpp"

double System::Math::Clamp(double value, double min, double max) {
    if(value > max)
        return max;
    return value < min ? min : value;
}
double System::Math::Clamp01(double value) {
    return System::Math::Clamp(value, 0.0, 1.0);
}
double System::Math::Lerp(double a, double b, double t) {
    return (1 - t) * a + t * b;
}
double System::Math::MoveTowards(double a, double b, double maxStep) {
    if (System::Math::Abs(b - a) <= System::Math::Abs(maxStep))
        return b;
    return a + System::Math::Sign(b - a) * System::Math::Abs(maxStep);
}
double System::Math::Repeat(double t, double length){
    return System::Math::Clamp(t - System::Math::Floor(t / length) * length, 0.0f, length);
}


double System::Math::Round(double x, System::Math::RoundingMode mode) {
    switch (mode) {
        case System::Math::RoundingMode::AwayFromZero:
            return x < 0 ? System::Math::Floor(x) : System::Math::Ceiling(x);
        case System::Math::RoundingMode::TowardsZero:
            return x < 0 ? System::Math::Ceiling(x) : System::Math::Floor(x);
        default: //HalfEven
            const double r = std::round(x);
            const double d = r - x;
            if ((d != 0.5f) && (d != -0.5f)) {
                return r;
            }
            if (fmod(r, 2.0f) == 0.0f) {
                return r;
            }
            return x - d;
    }
}
long System::Math::RoundToInt(double x, System::Math::RoundingMode mode) {
    return (long)System::Math::Round(x, mode);
}

double System::Math::Abs(double d) {
    return (d >= 0) ? d : -d;
}
long System::Math::Abs(long s) {
    return (s >= 0) ? s : -s;
}


long System::Math::Ceiling(double d) {
    long i = long(d); 
    if(i < d) i++;
    return i;
}
long System::Math::Floor(double d) {
    long i= long(d); 
    if (i > d) i--; 
    return i;
}
double System::Math::Exp(double x) {
    return std::exp(x);
}
double System::Math::Pow(double base, double power) {
    return std::pow(base, power);
}
long System::Math::Sign(double x) {
    if(x == 0)
        return x;
    else
        return (x > 0) ? 1 : -1;
}
long System::Math::Sign(long x) {
    if(x == 0)
        return x;
    else
        return (x > 0) ? 1 : -1;
}
double System::Math::Sqrt(double x) {
    return std::sqrt(x);
}


double System::Math::Log(double x) {
    return std::log(x);
}
double System::Math::Log10(double x) {
    return std::log10(x);
}
double System::Math::Log(double x, double base) {
    return std::log(x) / std::log(base);
}

double System::Math::Cos(double theta) {
    return std::cos(theta);
}
double System::Math::Cosh(double theta) {
    return std::cosh (theta);
}
double System::Math::Sin(double theta) {
    return std::sin(theta);
}
double System::Math::Sinh(double theta) {
    return std::sinh(theta);
}
double System::Math::Tan(double theta) {
    return std::tan(theta);
}
double System::Math::Tanh(double theta) {
    return std::tanh(theta);
}
double System::Math::Atan(double v) {
    return std::atan(v);
}
double System::Math::Acos(double v) {
    return std::acos(v);
}
double System::Math::Asin(double v) {
    return std::asin(v);
}
double System::Math::Atan2(double y, double x) {
    return std::atan2(y,x);
}