#include "data_generation.h"

std::string DataGeneration::to_string(Type type)
{
    switch (type)
    {
    case Type::Random:
        return "Random";
    case Type::Sorted:
        return "Sorted";
    case Type::ReverseSorted:
        return "Reverse Sorted";
    case Type::NearlySorted:
        return "Nearly Sorted";
    default:
        return "Unknown";
    }
}

std::vector<int> DataGeneration::generate_data(size_t n, std::mt19937 &rng, Type dgt)
{
    std::vector<int> generated_data(n);
    if (n == 0)
    {
        return generated_data;
    }

    std::uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);
    for (size_t i = 0; i < n; ++i)
    {
        generated_data[i] = distribution(rng);
    }

    if (dgt == Type::Sorted)
    {
        std::sort(generated_data.begin(), generated_data.end());
    }
    else if (dgt == Type::ReverseSorted)
    {
        std::sort(generated_data.begin(), generated_data.end(), std::greater<>());
    }
    else if (dgt == Type::NearlySorted)
    {
        std::sort(generated_data.begin(), generated_data.end());
        if (n >= 2)
        {
            const size_t swaps = std::max<size_t>(1, n / 100);
            std::uniform_int_distribution<size_t> idx(0, n - 1);
            for (size_t s = 0; s < swaps; ++s)
            {
                size_t i = idx(rng), j = idx(rng);
                std::swap(generated_data[i], generated_data[j]);
            }
        }
    }

    return generated_data;
}

std::vector<size_t> DataGeneration::generate_sizes()
{
    std::vector<size_t> sizes;

    // 5 → 10 (paso 1)
    for (size_t n = 5; n < 10; ++n)
    {
        sizes.push_back(n);
    }

    // 10 → 100 (paso 10)
    for (size_t n = 10; n < 100; n += 10)
    {
        sizes.push_back(n);
    }

    // 100 → 1'000 (paso 100)
    for (size_t n = 100; n < 1'000; n += 100)
    {
        sizes.push_back(n);
    }

    // 1'000 → 10'000 (paso 1'000)
    for (size_t n = 1'000; n <= 10'000; n += 1'000)
    {
        sizes.push_back(n);
    }

    return sizes;
}