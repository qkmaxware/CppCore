#ifndef _SYSTEM_MATH_MATRIX_HPP
#define _SYSTEM_MATH_MATRIX_HPP

#include "System.hpp"
#include "System.Math.Complex.hpp"
#include <array>
#include <vector>

namespace System {
namespace Math {

template <typename T, size_t Rows, size_t Columns>
class Matrix : public System::Object {
    private:
        std::array<T, Rows * Columns> array;

    public:
        /**
        * Create an empty matrix
        */
        Matrix(): array() {}
        /**
        * Create a matrix with values 
        */
        Matrix(const std::vector<T> values) : array(values) {}
        /**
        * Create a matrix as a clone of anther
        */
        Matrix(const Matrix<T, Rows, Columns>& other) : array(other.array) {}

        size_t Count() const {
            return Rows * Columns;
        }

        size_t CountRows() const {
            return Rows;
        }

        size_t CountColumns() const {
            return Columns;
        }

        bool IsSquare() const {
            return Rows == Columns;
        }

        bool IsColumn() const {
            return Columns == 1;
        }

        bool IsRow() const {
            return Rows == 1;
        }

        T Get(size_t ind) const {
            return array[ind];
        }

        T Get(size_t x, size_t y) const {
            return array[x + Columns * y];
        }

        void Set(size_t x, size_t y, T& val) {
            array[x + Columns * y] = val;
        }

        void Set(size_t ind, T& val) {
            array[ind] = val;
        }
};

// ----------------------------------------------
// Operators
// ----------------------------------------------

/**
* Add two same sized matrices
*/
template <typename T, size_t R, size_t C>
Matrix<T, R, C> operator + (Matrix<T, R, C> &a, Matrix<T, R, C> &b){
    std::vector<T> ts(a.Count());
    for (size_t t = 0; t < ts.Count(); t++) {
        ts[t] = a.Get(t) + b.Get(t);
    }
    return Matrix<T, R, C>(ts);
}


/**
* Subtract two same sized matrices
*/
template <typename T, size_t R, size_t C>
Matrix<T, R, C> operator - (Matrix<T, R, C> &a, Matrix<T, R, C> &b){
    std::vector<T> ts(a.Count());
    for (size_t t = 0; t < ts.Count(); t++) {
        ts[t] = a.Get(t) - b.Get(t);
    }
    return Matrix<T, R, C>(ts);
}

/**
* Multiply matrix by scalar
*/
template <typename T, size_t R, size_t C>
Matrix<T, R, C> operator * (T &a, Matrix<T, R, C> &b){
    std::vector<T> ts(a.Count());
    for (size_t t = 0; t < ts.Count(); t++){
        ts[t] = a * b.Get(t);
    }
    return Matrix<T, R, C>(ts);
}

/**
* Multiply matrix by scalar
*/
template <typename T, size_t R, size_t C>
Matrix<T, R, C> operator * (Matrix<T, R, C> &b, T &a){
    std::vector<T> ts(a.Count());
    for (size_t t = 0; t < ts.Count(); t++){
        ts[t] = a * b.Get(t);
    }
    return Matrix<T, R, C>(ts);
}


/**
* Divide matrix by scalar
*/
template <typename T, size_t R, size_t C>
Matrix<T, R, C> operator / (Matrix<T, R, C> &b, T &a){
    std::vector<T> ts(a.Count());
    for (size_t t = 0; t < ts.Count(); t++){
        ts[t] = b.Get(t) / a;
    }
    return Matrix<T, R, C>(ts);
}

/**
* Multiply two matrices. Dimensions must match as enforced via templated parameters.
*/
template <typename T, size_t R1, size_t C1, size_t C2>
Matrix<T, R1, C2> operator * (Matrix<T, R1, C1> &a, Matrix<T, C1, C2> &b){
    std::vector<T> ts(R1 * C2);
    T sum;
    for (size_t i = 0; i < R1; i++){
        for (size_t j = 0; j < C2; j++){
            sum = T();
            for (size_t k = 0; k < C1; k++){
                sum = sum + a.Get(i, k) * b.Get(k, j);
            }

            ts[i * C2 + j] = sum;
        }
    }

    return Matrix<T, R1, C2>(ts);
}

// ----------------------------------------------
// Convenience Aliases
// ----------------------------------------------

template <size_t R, size_t C>
using Matrixf = Matrix<float, R, C>;

template <size_t R, size_t C>
using Matrixd = Matrix<double, R, C>;

template <size_t R, size_t C>
using Matrixi = Matrix<int, R, C>;

template <size_t R, size_t C>
using Matrixl = Matrix<long, R, C>;

template <size_t R, size_t C>
using Matrixc = Matrix<Complex, R, C>;

}
}

#endif