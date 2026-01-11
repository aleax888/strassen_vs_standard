#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <fstream>

#include "merge_sort.h"
#include "insertion_sort.h"
#include "data_generation.h"
#include "benchmark_sorts.h"

int main()
{
    try
    {
        std::ofstream csv("outputs/benchmark/benchmark_results.csv");
        csv << "data_generation_type,n,insertion_sort_mean,insertion_sort_min,insertion_sort_max,merge_sort_mean,merge_sort_min,merge_sort_max,ratio,faster\n";
        const std::vector<size_t> sizes = DataGeneration::generate_sizes();
        std::mt19937 rng(1234567);
        const std::vector<DataGeneration::Type> data_generation_types = {
            DataGeneration::Type::Random,
            DataGeneration::Type::Sorted,
            DataGeneration::Type::ReverseSorted,
            DataGeneration::Type::NearlySorted};

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
                      << std::setw(20) << "Mean (ns): I. S."
                      << std::setw(20) << "Min (ns): I. S."
                      << std::setw(20) << "Max (ns): I, S."
                      << std::setw(20) << "Mean (ns): M. S."
                      << std::setw(20) << "Min (ns): M. S."
                      << std::setw(20) << "Max (ns): M. S."
                      << std::setw(20) << "Ratio (i/m)"
                      << std::setw(20) << "Faster"
                      << std::endl;

            for (size_t n : sizes)
            {
                const int trials = BenchMark::get_trials(n);
                const std::vector<int> input = DataGeneration::generate_data(n, rng, type);

                // Time insertion sort
                Stats insertion_sort = BenchMark::get_execution_time([](std::vector<int> &a)
                                                                     { InsertionSort::insertion_sort(a); }, input, trials);

                // Time merge sort
                Stats merge_sort = BenchMark::get_execution_time([](std::vector<int> &a)
                                                                 { MergeSort::merge_sort(a); }, input, trials);

                const double ratio = insertion_sort.mean() / merge_sort.mean();
                const std::string faster = (ratio < 1.0) ? "Insertion Sort" : "Merge Sort";

                std::cout << std::left
                          << std::setw(10) << n
                          << std::setw(20) << static_cast<long long>(insertion_sort.mean())
                          << std::setw(20) << static_cast<long long>(insertion_sort.min())
                          << std::setw(20) << static_cast<long long>(insertion_sort.max())
                          << std::setw(20) << static_cast<long long>(merge_sort.mean())
                          << std::setw(20) << static_cast<long long>(merge_sort.min())
                          << std::setw(20) << static_cast<long long>(merge_sort.max())
                          << std::setw(20) << std::fixed << std::setprecision(2) << ratio
                          << std::setw(20) << faster
                          << std::endl;
                csv << DataGeneration::to_string(type) << ","
                    << n << ","
                    << static_cast<long long>(insertion_sort.mean()) << ","
                    << static_cast<long long>(insertion_sort.min()) << ","
                    << static_cast<long long>(insertion_sort.max()) << ","
                    << static_cast<long long>(merge_sort.mean()) << ","
                    << static_cast<long long>(merge_sort.min()) << ","
                    << static_cast<long long>(merge_sort.max()) << ","
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