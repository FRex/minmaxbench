#pragma once
#include <utility>
#include <vector>
#include <tuple>

typedef std::pair<int, int>(*MinMaxFunc)(const int *, int);

class Tester
{
public:
    void dotest();
    void printResults() const;
    void addFunc(std::string name, MinMaxFunc f);

private:
    int m_rangemin = 1000;
    int m_rangemax = 9999;
    int m_rangecount = 99912345;
    int m_repetitions = 50;
    std::vector<std::tuple<std::string, MinMaxFunc, long long int>> m_funcs;
    std::vector<std::pair<int, int>> m_results;

};
