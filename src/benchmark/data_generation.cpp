#include "data_generation.h"

std::string DataGeneration::to_string(Type type)
{
    switch (type)
    {
    case Type::Random:
        return "Random";
    case Type::Zero:
        return "Zero";
    case Type::Identity:
        return "Identity";
    default:
        return "Unknown";
    }
}

std::pair<Matrix, Matrix> DataGeneration::generate_data(size_t n, std::mt19937 &rng, Type dgt)
{
    Matrix A(n), B(n);
    if (n == 0)
        return {A, B};

    std::uniform_real_distribution<double> distribution(-10.0, 10.0);

    if (dgt == Type::Random)
    {
        for (size_t i = 0; i < n * n; ++i)
        {
            A.a[i] = distribution(rng);
            B.a[i] = distribution(rng);
        }
    }
    else if (dgt == Type::Zero)
    {
        // already zero-initialized
    }
    else if (dgt == Type::Identity)
    {
        for (size_t i = 0; i < n; ++i)
        {
            A(i, i) = 1.0;
            B(i, i) = 1.0;
        }
    }

    return {A, B};
}

std::vector<size_t> DataGeneration::generate_sizes()
{
    std::vector<size_t> sizes;

    // powers of two from 8 up to 4096 (nearest power >= 4000)
    // for (size_t n = 8; n <= 256; n *= 2)
    for (size_t n = 8; n <= 1024; n *= 2)
    {
        sizes.push_back(n);
    }

    return sizes;
}