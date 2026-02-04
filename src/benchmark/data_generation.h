#ifndef DATA_GENERATION_H
#define DATA_GENERATION_H

#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "matrix.h"

class DataGeneration
{
public:
    enum class Type
    {
        Random,
        Zero,
        Identity
    };

    static std::string to_string(Type type);

    // Generate a pair of matrices A,B of size n x n according to "type".
    static std::pair<Matrix, Matrix> generate_data(size_t n, std::mt19937 &rng, Type dgt);

    // Powers of two sizes (including around 32)
    static std::vector<size_t> generate_sizes();

private:
    DataGeneration() = delete;
};

#endif