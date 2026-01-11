#ifndef DATA_GENERATION_H
#define DATA_GENERATION_H

#include <string>
#include <vector>
#include <random>
#include <climits>
#include <algorithm>

class DataGeneration
{
public:
    enum class Type
    {
        Random,
        Sorted,
        ReverseSorted,
        NearlySorted
    };

    static std::string to_string(Type type);

    static std::vector<int> generate_data(size_t n, std::mt19937 &rng, Type dgt);

    static std::vector<size_t> generate_sizes();

private:
    DataGeneration() = delete;
};

#endif