#ifndef STRASSEN_H
#define STRASSEN_H

#include "matrix.h"

namespace Strassen
{
    // threshold: for n <= threshold, use standard multiplication
    Matrix multiply(const Matrix &A, const Matrix &B, size_t threshold = 32);
}

#endif
