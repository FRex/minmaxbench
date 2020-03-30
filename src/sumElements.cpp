#include "sumElements.hpp"

static std::pair<int, int> sumElementsX(const int * arr, int arrsize, int x)
{
    unsigned ret = 0u;
    for(int i = 0; i < arrsize; i += x)
        ret += static_cast<unsigned>(arr[i]);

    const int reti = static_cast<int>(ret);
    return std::make_pair(reti, reti);
}

std::pair<int, int> sumElements1(const int * arr, int arrsize)
{
    return sumElementsX(arr, arrsize, 1);
}

std::pair<int, int> sumElements4(const int * arr, int arrsize)
{
    return sumElementsX(arr, arrsize, 4);
}

std::pair<int, int> sumElements8(const int * arr, int arrsize)
{
    return sumElementsX(arr, arrsize, 8);
}
