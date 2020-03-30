#include "Tester.hpp"
#include <algorithm>
#include <stdio.h>
#include <chrono>
#include <random>

static long long int monotonicMicroSeconds()
{
    const auto now = std::chrono::steady_clock::now();
    const auto usec = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    return usec.time_since_epoch().count();
}

void Tester::dotest()
{
    for(auto& func : m_funcs)
        std::get<long long int>(func) = 0;

    std::vector<int> arr;
    std::random_device dev;
    std::uniform_int_distribution<int> dist(m_rangemin, m_rangemax);
    for(int i = 0; i < m_rangecount; ++i)
        arr.push_back(dist(dev));

    m_results.clear();
    m_results.reserve(m_repetitions * m_funcs.size());

    for(auto& func : m_funcs)
    {
        const auto f = std::get<MinMaxFunc>(func);
        const long long int start = monotonicMicroSeconds();
        for(int i = 0; i < m_repetitions; ++i)
            m_results.push_back(f(arr.data(), static_cast<int>(arr.size())));

        std::get<long long int>(func) = monotonicMicroSeconds() - start;
    } //for

    for(const auto pair : m_results)
        std::fprintf(stderr, "%d, %d\n", pair.first, pair.second);
}

void Tester::printResults() const
{
    std::string name;
    long long int time = 0;

    std::printf("%d ints in range [%d, %d], repetitions = %d, bitness = %d\n",
        m_rangecount, m_rangemin, m_rangemax, m_repetitions, static_cast<int>(sizeof(void*) * 8)
    );

    auto sortedfuncs = m_funcs;
    typedef decltype(m_funcs[0]) elem;
    const auto cmpf = [](elem a, elem b) -> bool { return std::get<long long int>(a) < std::get<long long int>(b); };
    std::sort(sortedfuncs.begin(), sortedfuncs.end(), cmpf);

    for(const auto func : sortedfuncs)
    {
        std::tie(name, std::ignore, time) = func;
        std::printf("%15s: %9lld us, %.3fs\n", name.c_str(), time, time / 1'000'000.0);
    }//for
}

void Tester::addFunc(std::string name, MinMaxFunc f)
{
    m_funcs.emplace_back(name, f, 0);

}
