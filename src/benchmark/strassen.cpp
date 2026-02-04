#include "strassen.h"
#include "standard_multiplication.h"
#include <algorithm>

using std::min;

namespace Strassen
{
    static Matrix add(const Matrix &A, const Matrix &B)
    {
        Matrix C(A.n);
        for (size_t i = 0; i < A.n * A.n; ++i)
            C.a[i] = A.a[i] + B.a[i];
        return C;
    }

    static Matrix sub(const Matrix &A, const Matrix &B)
    {
        Matrix C(A.n);
        for (size_t i = 0; i < A.n * A.n; ++i)
            C.a[i] = A.a[i] - B.a[i];
        return C;
    }

    static void copy_submatrix(const Matrix &src, Matrix &dst, size_t src_row, size_t src_col, size_t dst_row, size_t dst_col, size_t sz)
    {
        for (size_t i = 0; i < sz; ++i)
            for (size_t j = 0; j < sz; ++j)
                dst(dst_row + i, dst_col + j) = src(src_row + i, src_col + j);
    }

    static Matrix join_quadrants(const Matrix &C11, const Matrix &C12, const Matrix &C21, const Matrix &C22)
    {
        size_t n2 = C11.n;
        Matrix C(n2 * 2);
        for (size_t i = 0; i < n2; ++i)
            for (size_t j = 0; j < n2; ++j)
                C(i, j) = C11(i, j);
        for (size_t i = 0; i < n2; ++i)
            for (size_t j = 0; j < n2; ++j)
                C(i, j + n2) = C12(i, j);
        for (size_t i = 0; i < n2; ++i)
            for (size_t j = 0; j < n2; ++j)
                C(i + n2, j) = C21(i, j);
        for (size_t i = 0; i < n2; ++i)
            for (size_t j = 0; j < n2; ++j)
                C(i + n2, j + n2) = C22(i, j);
        return C;
    }

    Matrix multiply(const Matrix &A, const Matrix &B, size_t threshold)
    {
        if (A.n != B.n)
            throw std::runtime_error("Dimension mismatch");
        size_t n = A.n;
        if (n == 0)
            return Matrix(0);

        if (n <= threshold)
        {
            return StandardMultiplication::multiply(A, B);
        }

        // n must be even (powers of two are used in experiments). For safety, if not even, fall back.
        if (n % 2 != 0)
            return StandardMultiplication::multiply(A, B);

        size_t m = n / 2;

        Matrix A11(m), A12(m), A21(m), A22(m);
        Matrix B11(m), B12(m), B21(m), B22(m);

        // split
        for (size_t i = 0; i < m; ++i)
            for (size_t j = 0; j < m; ++j)
            {
                A11(i, j) = A(i, j);
                A12(i, j) = A(i, j + m);
                A21(i, j) = A(i + m, j);
                A22(i, j) = A(i + m, j + m);

                B11(i, j) = B(i, j);
                B12(i, j) = B(i, j + m);
                B21(i, j) = B(i + m, j);
                B22(i, j) = B(i + m, j + m);
            }

        // 7 multiplications
        Matrix M1 = multiply(add(A11, A22), add(B11, B22), threshold);
        Matrix M2 = multiply(add(A21, A22), B11, threshold);
        Matrix M3 = multiply(A11, sub(B12, B22), threshold);
        Matrix M4 = multiply(A22, sub(B21, B11), threshold);
        Matrix M5 = multiply(add(A11, A12), B22, threshold);
        Matrix M6 = multiply(sub(A21, A11), add(B11, B12), threshold);
        Matrix M7 = multiply(sub(A12, A22), add(B21, B22), threshold);

        Matrix C11 = add(sub(add(M1, M4), M5), M7);
        Matrix C12 = add(M3, M5);
        Matrix C21 = add(M2, M4);
        Matrix C22 = add(sub(add(M1, M3), M2), M6);

        Matrix C = join_quadrants(C11, C12, C21, C22);

        return C;
    }
} // namespace Strassen
