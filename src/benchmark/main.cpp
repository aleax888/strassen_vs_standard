#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <utility>

#include "data_generation.h"
#include "benchmark_matrix.h"
#include "standard_multiplication.h"
#include "strassen.h"

static bool equal_matrix(const Matrix &A, const Matrix &B, double tol = 1e-6)
{
    if (A.n != B.n)
        return false;
    for (size_t i = 0; i < A.n * A.n; ++i)
        if (std::abs(A.a[i] - B.a[i]) > tol)
            return false;
    return true;
}

int main()
{
    try
    {
        std::ofstream csv("outputs/benchmark/benchmark_results.csv");
        csv << "data_generation_type,n,standard_mean,standard_min,standard_max,strassen_mean,strassen_min,strassen_max,ratio,faster\n";
        const std::vector<size_t> sizes = DataGeneration::generate_sizes();
        std::mt19937 rng(1234567);
        const std::vector<DataGeneration::Type> data_generation_types = {
            DataGeneration::Type::Random,
            DataGeneration::Type::Zero,
            DataGeneration::Type::Identity};

        for (auto type : data_generation_types)
        {
            const int table_width = 170;
            std::string text = " Data Generation Type: " + DataGeneration::to_string(type) + " ";
            int padding_total = table_width - text.length();
            int padding_left = padding_total / 2;
            int padding_right = padding_total - padding_left;
            std::cout << std::string(table_width, '#') << std::endl;
            std::cout << std::string(padding_left, '#') << text << std::string(padding_right, '#') << '\n';
            std::cout << std::string(table_width, '#') << std::endl;

            std::cout << std::left
                      << std::setw(10) << "n"
                      << std::setw(20) << "Mean (ns): Std"
                      << std::setw(20) << "Min (ns): Std"
                      << std::setw(20) << "Max (ns): Std"
                      << std::setw(20) << "Mean (ns): Strassen"
                      << std::setw(20) << "Min (ns): Strassen"
                      << std::setw(20) << "Max (ns): Strassen"
                      << std::setw(20) << "Ratio (std/str)"
                      << std::setw(20) << "Faster"
                      << std::endl;

            for (size_t n : sizes)
            {
                const int trials = BenchMark::get_trials(n);
                auto matrices = DataGeneration::generate_data(n, rng, type);

                // verify correctness on one run
                Matrix Cstd = StandardMultiplication::multiply(matrices.first, matrices.second);
                Matrix Cstr = Strassen::multiply(matrices.first, matrices.second, 32); // default threshold 32

                if (!equal_matrix(Cstd, Cstr))
                {
                    std::cerr << "Error: Results differ at n=" << n << " for type=" << DataGeneration::to_string(type) << std::endl;
                    return 1;
                }

                Stats std_stats = BenchMark::get_execution_time([&](std::pair<Matrix, Matrix> &p)
                                                               {
                                                                   volatile Matrix C = StandardMultiplication::multiply(p.first, p.second);
                                                               }, matrices, trials);

                Stats str_stats = BenchMark::get_execution_time([&](std::pair<Matrix, Matrix> &p)
                                                               {
                                                                   volatile Matrix C = Strassen::multiply(p.first, p.second, 32);
                                                               }, matrices, trials);

                const double ratio = std_stats.mean() / str_stats.mean();
                const std::string faster = (ratio < 1.0) ? "Standard" : "Strassen";

                std::cout << std::left
                          << std::setw(10) << n
                          << std::setw(20) << static_cast<long long>(std_stats.mean())
                          << std::setw(20) << static_cast<long long>(std_stats.min())
                          << std::setw(20) << static_cast<long long>(std_stats.max())
                          << std::setw(20) << static_cast<long long>(str_stats.mean())
                          << std::setw(20) << static_cast<long long>(str_stats.min())
                          << std::setw(20) << static_cast<long long>(str_stats.max())
                          << std::setw(20) << std::fixed << std::setprecision(2) << ratio
                          << std::setw(20) << faster
                          << std::endl;

                csv << DataGeneration::to_string(type) << ","
                    << n << ","
                    << static_cast<long long>(std_stats.mean()) << ","
                    << static_cast<long long>(std_stats.min()) << ","
                    << static_cast<long long>(std_stats.max()) << ","
                    << static_cast<long long>(str_stats.mean()) << ","
                    << static_cast<long long>(str_stats.min()) << ","
                    << static_cast<long long>(str_stats.max()) << ","
                    << ratio << ","
                    << faster
                    << "\n";
            }
            std::cout << std::endl;
        }

        csv.close();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}