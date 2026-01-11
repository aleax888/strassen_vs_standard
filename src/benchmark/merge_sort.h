#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>

class MergeSort
{
public:
    static void merge_sort(std::vector<int> &a);

private:
    static void merge_sort_rec(std::vector<int> &a,
                               std::vector<int> &buf,
                               size_t left,
                               size_t right);

    static void merge_ranges(std::vector<int> &a,
                             std::vector<int> &buf,
                             size_t left,
                             size_t mid,
                             size_t right);

    MergeSort() = delete;
};

#endif
