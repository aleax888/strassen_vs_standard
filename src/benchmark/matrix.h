#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cstddef>
#include <stdexcept>

struct Matrix {
    size_t n;
    std::vector<double> a;

    Matrix() : n(0) {}
    explicit Matrix(size_t n_) : n(n_), a(n_ * n_, 0.0) {}

    double &operator()(size_t i, size_t j)
    {
        return a[i * n + j];
    }

    const double &operator()(size_t i, size_t j) const
    {
        return a[i * n + j];
    }
};

#endif
