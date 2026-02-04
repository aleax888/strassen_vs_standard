#include "standard_multiplication.h"

namespace StandardMultiplication
{
    Matrix multiply(const Matrix &A, const Matrix &B)
    {
        if (A.n != B.n)
            throw std::runtime_error("Dimension mismatch");
        const size_t n = A.n;
        Matrix C(n);
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t k = 0; k < n; ++k)
            {
                double aik = A(i, k);
                for (size_t j = 0; j < n; ++j)
                {
                    C(i, j) += aik * B(k, j);
                }
            }
        }
        return C;
    }
}
