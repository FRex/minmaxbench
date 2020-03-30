#include "minmaxAvx2.hpp"
#include <immintrin.h>
#include "minmaxes.hpp"

std::pair<int, int> minmaxAvx2(const int * arr, int arrsize)
{
    if(arrsize == 0)
        return std::make_pair(INT_MAX, INT_MIN);

    __m256i minaccu = _mm256_set_epi32(INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX);
    __m256i maxaccu = _mm256_set_epi32(INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN);
    __m256i tmp;

    int only[24];
    int onlysize = 0;

    while(reinterpret_cast<uintptr_t>(arr) % 32 != 0)
    {
        only[onlysize++] = *arr;
        ++arr;
        --arrsize;
    }

    while(arrsize >= 8)
    {
        tmp = _mm256_load_si256((const __m256i *)arr);
        minaccu = _mm256_min_epi32(minaccu, tmp);
        maxaccu = _mm256_max_epi32(maxaccu, tmp);
        arr += 8;
        arrsize -= 8;
    } //while arrsize >= 8

    //leftover part if arrsize was not multiple of 8
    for(int i = 0; i < arrsize; ++i)
        only[onlysize++] = arr[i];

    _mm256_storeu_si256((__m256i*)(only + onlysize), minaccu);
    const int min = minelem(only, onlysize + 8);

    _mm256_storeu_si256((__m256i*)(only + onlysize), maxaccu);
    const int max = maxelem(only, onlysize + 8);

    return std::make_pair(min, max);
}

static int minelemAvx2(const int * arr, int arrsize)
{
    __m256i minaccu = _mm256_set_epi32(INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX);
    __m256i tmp;

    int only[24];
    int onlysize = 0;

    while(reinterpret_cast<uintptr_t>(arr) % 32 != 0)
    {
        only[onlysize++] = *arr;
        ++arr;
        --arrsize;
    }

    while(arrsize >= 8)
    {
        tmp = _mm256_load_si256((const __m256i *)arr);
        minaccu = _mm256_min_epi32(minaccu, tmp);
        arr += 8;
        arrsize -= 8;
    } //while arrsize >= 8

    //leftover part if arrsize was not multiple of 8
    for(int i = 0; i < arrsize; ++i)
        only[onlysize++] = arr[i];

    _mm256_storeu_si256((__m256i*)(only + onlysize), minaccu);
    return minelem(only, onlysize + 8);
}

static int maxelemAvx2(const int * arr, int arrsize)
{
    __m256i maxaccu = _mm256_set_epi32(INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN);
    __m256i tmp;

    int only[24];
    int onlysize = 0;

    while(reinterpret_cast<uintptr_t>(arr) % 32 != 0)
    {
        only[onlysize++] = *arr;
        ++arr;
        --arrsize;
    }

    while(arrsize >= 8)
    {
        tmp = _mm256_load_si256((const __m256i *)arr);
        maxaccu = _mm256_max_epi32(maxaccu, tmp);
        arr += 8;
        arrsize -= 8;
    } //while arrsize >= 8

    //leftover part if arrsize was not multiple of 8
    for(int i = 0; i < arrsize; ++i)
        only[onlysize++] = arr[i];

    _mm256_storeu_si256((__m256i*)(only + onlysize), maxaccu);
    return maxelem(only, onlysize + 8);
}

std::pair<int, int> minmaxAvx2Separate(const int * arr, int arrsize)
{
    return std::make_pair(minelemAvx2(arr, arrsize), maxelemAvx2(arr, arrsize));
}
