#include "merge_sort.h"

void MergeSort::merge_ranges(std::vector<int> &a, std::vector<int> &buf, size_t left, size_t mid, size_t right)
{
    size_t i = left, j = mid, k = left;
    while (i < mid && j < right)
    {
        if (a[i] <= a[j])
        {
            buf[k++] = a[i++];
        }
        else
        {
            buf[k++] = a[j++];
        }
    }
    while (i < mid)
    {
        buf[k++] = a[i++];
    }
    while (j < right)
    {
        buf[k++] = a[j++];
    }

    for (size_t t = left; t < right; ++t)
    {
        a[t] = buf[t];
    }
}

void MergeSort::merge_sort_rec(std::vector<int> &a, std::vector<int> &buf, size_t left, size_t right)
{
    const size_t len = right - left;
    if (len <= 1)
        return;
    const size_t mid = left + len / 2;
    merge_sort_rec(a, buf, left, mid);
    merge_sort_rec(a, buf, mid, right);
    merge_ranges(a, buf, left, mid, right);
}

void MergeSort::merge_sort(std::vector<int> &a)
{
    std::vector<int> buf(a.size());
    merge_sort_rec(a, buf, 0, a.size());
}