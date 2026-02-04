#include "benchmark_matrix.h"

int BenchMark::get_trials(size_t n)
{
    if (n <= 32)
    {
        return 200;
    }
    if (n <= 64)
    {
        return 80;
    }
    if (n <= 128)
    {
        return 40;
    }
    if (n <= 256)
    {
        return 12;
    }
    if (n <= 512)
    {
        return 4;
    }
    return 2;
}