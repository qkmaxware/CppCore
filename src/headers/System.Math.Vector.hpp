#ifndef _SYSTEM_MATH_VECTOR
#define _SYSTEM_MATH_VECTOR

#include "System.Math.Matrix.hpp"

namespace System {
namespace Math {

template <typename Type, size_t Rows>
using ColumnVector = Matrix<Type, Rows, 1>;

template <typename Type>
using ColumnVector2 = ColumnVector<Type, 2>;

template <typename Type>
using ColumnVector3 = ColumnVector<Type, 3>;

template <typename Type>
using ColumnVector4 = ColumnVector<Type, 4>;


template <typename Type, size_t Columns>
using RowVector = Matrix<Type, 1, Columns>;

template <typename Type>
using RowVector2 = RowVector<Type, 2>;

template <typename Type>
using RowVector3 = RowVector<Type, 3>;

template <typename Type>
using RowVector4 = RowVector<Type, 4>;

}
}

#endif