#include "benchmark_sorts.h"

int BenchMark::get_trials(size_t n)
{
    if (n <= 128)
    {
        return 2000;
    }
    if (n <= 512)
    {
        return 800;
    }
    if (n <= 2048)
    {
        return 200;
    }
    if (n <= 8192)
    {
        return 60;
    }
    return 30;
}