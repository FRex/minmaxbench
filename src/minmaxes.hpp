#pragma once
#include <utility>
#include <climits>

std::pair<int, int> minmaxBitHax(const int * arr, int arrsize);
std::pair<int, int> minmaxNormal(const int * arr, int arrsize);
std::pair<int, int> minmaxElseMin(const int * arr, int arrsize);
std::pair<int, int> minmax3Way(const int * arr, int arrsize);
std::pair<int, int> minmaxSeparate(const int * arr, int arrsize);

inline int minelem(const int * arr, int arrsize)
{
    int ret = INT_MAX;
    for(int i = 0; i < arrsize; ++i)
        if(arr[i] < ret)
            ret = arr[i];

    return ret;
}

inline int maxelem(const int * arr, int arrsize)
{
    int ret = INT_MIN;
    for(int i = 0; i < arrsize; ++i)
        if(arr[i] > ret)
            ret = arr[i];

    return ret;
}
