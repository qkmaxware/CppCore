#ifndef _SYSTEM_MATH_COMPLEX_HPP
#define _SYSTEM_MATH_COMPLEX_HPP

#include "System.hpp"

namespace System {
namespace Math {

/**
 * Type alias for high precision real valued numbers aka. long double 
 */
using Real = long double;

/**
 * Class representing a complex number of the form (real + imaginary * i) where real and imaginary are both real values. 
 */
class Complex : public System::Object {
    private:
    public:
        /**
         * Real component 
         */
        const Real real;
        /**
         * Imaginary component 
         */
        const Real imaginary;

        /**
         * Complex zero 
         */
        Complex();
        /**
         * Complex value (real + 0i) 
         */
        Complex(Real real);
        /**
         * Complex value with real and imaginary components 
         */
        Complex(Real real, Real imaginary);
        /**
         * Copy an existing complex number  
         */
        Complex(const Complex& other);

        /**
         * Squared magnitude of this complex number 
         */
        Real SqrMagnitude() const;
        /**
         * Magnitude of this complex number 
         */
        Real Magnitude() const;

        /**
         * The complex conjugate of this value 
         */
        Complex Conjugate() const;
        /**
         * Complex number in the same direction but of unit length 
         */
        Complex Normal() const;
        /**
         * The complex argument of this number 
         */
        Real Arg() const;

        /**
         * Determine if this complex number has only a real component 
         */
        bool IsPureReal() const;
        /**
         * Determine if this complex number has only an imaginary component 
         */
        bool IsPureImaginary() const;

        /**
         * String representation of this number 
         */
        virtual std::string ToString() const;

};

/**
 * Add two complex numbers
 */
Complex operator + (const Complex& a, const Complex& b);
/**
 * Add a real and complex number
 */
Complex operator + (Real a, const Complex& b);
/**
 * Add a complex and real number
 */
Complex operator + (const Complex& a, Real b);

/**
 * Subtract two complex numbers
 */
Complex operator - (const Complex& a, const Complex& b);
/**
 * Subtract a real and complex number
 */
Complex operator - (Real a, const Complex& b);
/**
 * Subtract a complex and real number
 */
Complex operator - (const Complex& a, Real b);

/**
 * Multiply two complex numbers
 */
Complex operator * (const Complex& a, const Complex& b);
/**
 * Multiply a real and complex number
 */
Complex operator * (Real a, const Complex& b);
/**
 * Multiply a complex and a real number
 */
Complex operator * (const Complex& a, Real b);

/**
 * Divide two complex numbers
 */
Complex operator / (const Complex& a, const Complex& b);
/**
 * Divide a real and complex number
 */
Complex operator / (Real a, const Complex& b);
/**
 * Divide a complex and real number
 */
Complex operator / (const Complex& a, Real b);

}
}

#endif