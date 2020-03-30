#include "minmaxes.hpp"
#include <algorithm>

std::pair<int, int> minmaxBitHax(const int * arr, int arrsize)
{
    long long int min = INT_MAX, max = INT_MIN;
    for(int i = 0U; i < arrsize; ++i)
    {
        const int v = arr[i];
        min = v + ((min - (long long int)v) & ((min - (long long int)v) >> (sizeof(long long int) * CHAR_BIT - 1U)));
        max = v - (((long long int)v - max) & (((long long int)v - max) >> (sizeof(long long int) * CHAR_BIT - 1U)));
    }

    return std::make_pair(static_cast<int>(min), static_cast<int>(max));
}

std::pair<int, int> minmaxNormal(const int * arr, int arrsize)
{
    int min = INT_MAX, max = INT_MIN;
    for(int i = 0; i < arrsize; ++i)
    {
        min = std::min(min, arr[i]);
        max = std::max(max, arr[i]);
    }

    return std::make_pair(min, max);
}

std::pair<int, int> minmaxElseMin(const int * arr, int arrsize)
{
    if(arrsize == 0)
        return std::make_pair(INT_MAX, INT_MIN);

    int min = arr[0], max = arr[0];
    for(int i = 0; i < arrsize; ++i)
    {
        const int v = arr[i];
        if(v > max)
            max = v;
        else if(v < min)
            min = v;
    }

    return std::make_pair(min, max);
}

std::pair<int, int> minmax3Way(const int * arr, int arrsize)
{
    if(arrsize == 0)
        return std::make_pair(INT_MAX, INT_MIN);

    int min = arr[0], max = arr[0];
    if(arrsize % 2 == 1)
    {
        ++arr;
        --arrsize;
    }

    for(int i = 0; i < arrsize; i += 2)
    {
        int a = arr[i + 0];
        int b = arr[i + 1];

        if(a > b)
            std::swap(a, b);

        min = std::min(min, a);
        max = std::max(max, b);
    }

    return std::make_pair(min, max);
}

std::pair<int, int> minmaxSeparate(const int * arr, int arrsize)
{
    return std::make_pair(minelem(arr, arrsize), maxelem(arr, arrsize));
}
