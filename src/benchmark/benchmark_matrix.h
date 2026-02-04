#ifndef BENCHMARK_MATRIX_H
#define BENCHMARK_MATRIX_H

#include <vector>
#include <string>
#include <chrono>
#include <cfloat>

#include "stats.h"

class BenchMark
{
public:
    using Clock = std::chrono::steady_clock;
    using ns = std::chrono::nanoseconds;

    template <class F, class T>
    static Stats get_execution_time(F &&fn, const T &input, int trials)
    {
        double sum = 0.0;
        double best = DBL_MAX;
        double worst = DBL_MIN;

        int t = trials;
        while (t--)
        {
            T input_copy = input; // requires T to be copyable (matrices/pairs)

            auto start = Clock::now();
            fn(input_copy);
            auto end = Clock::now();

            double elapsed_time = std::chrono::duration_cast<ns>(end - start).count();
            sum += elapsed_time;
            if (elapsed_time < best)
            {
                best = elapsed_time;
            }
            if (elapsed_time > worst)
            {
                worst = elapsed_time;
            }
        }

        Stats s(sum / trials, best, worst);
        return s;
    }

    static int get_trials(size_t n);

private:
    BenchMark() = delete;
};

#endif