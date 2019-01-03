#include "System.Math.Complex.hpp"
#include <math.h> 
#include <string>

namespace System {
namespace Math {

Complex::Complex() : real(0), imaginary(0) {}

Complex::Complex(Real a) : real(a), imaginary(0) {}

Complex::Complex(Real a, Real b) : real(a), imaginary(b) {}

Real Complex::SqrMagnitude() const {
    Complex b = this->Conjugate();
    return this->real * b.real - this->imaginary * b.imaginary;
}

Real Complex::Magnitude() const {
    return sqrt(abs(this->SqrMagnitude()));
}

Complex Complex::Conjugate() const {
    return Complex(this->real, -1 * this->imaginary);
}

Complex Complex::Normal() const {
    Real mag = this->Magnitude();
    return Complex(this->real / mag, this->imaginary / mag);
}

Real Complex::Arg() const {
    return atan2(this->imaginary, this->real);
}

bool Complex::IsPureReal() const {
    return this->imaginary == 0;
}

bool Complex::IsPureImaginary() const {
    return this->real == 0;
}

std::string Complex::ToString() const {
    std::string str;
    str += std::to_string(this->real);
    
    if(this->imaginary != 0) {
        if(this->imaginary > 0) {
            str += "+";
        } else {
            str += "-";
        }
        str += std::to_string(this->imaginary);
        str += "i";
    }

    return str;
}

Complex operator + (const Complex& a, const Complex& b) {
    return Complex(a.real + b.real, a.imaginary + b.imaginary);
}
Complex operator + (Real a, const Complex& b) {
    return Complex(a + b.real, b.imaginary);
}
Complex operator + (const Complex& a, Real b) {
    return Complex(a.real, a.imaginary + b);
}

Complex operator - (const Complex& a, const Complex& b) {
    return Complex(a.real - b.real, a.imaginary - b.imaginary);
}
Complex operator - (Real a, const Complex& b) {
    return Complex(a - b.real, b.imaginary);
}
Complex operator - (const Complex& a, Real b) {
    return Complex(a.real, a.imaginary - b);
}

Complex operator * (const Complex& a, const Complex& b) {
    return Complex(a.real * b.real - a.imaginary * b.imaginary, a.real * b.imaginary + a.imaginary * b.real);
}
Complex operator * (Real a, const Complex& b) {
    return Complex(a * b.real, a * b.imaginary);
}
Complex operator * (const Complex& a, Real b) {
    return Complex(b * a.real, b * a.imaginary);
}

Complex operator / (const Complex& a, const Complex& b) {
    Real d = b.real * b.real + b.imaginary * b.imaginary;
    Real r = (a.real * b.real + a.imaginary * b.imaginary) / d;
    Real i = (a.imaginary * b.real - a.real * b.imaginary) / d;
    return Complex(r, i);
}
Complex operator / (Real a, const Complex& b) {
    return Complex(a) / b;
}
Complex operator / (const Complex& a, Real b) {
    return Complex(a.real / b, a.imaginary / b);
}

}
}