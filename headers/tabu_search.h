#ifndef METAHEURYSTYKA_TABU_SEARCH_H
#define METAHEURYSTYKA_TABU_SEARCH_H

#include <numeric>
#include <random>

#include "utils.h"


class Neighbor {
private:
    std::vector<int> psudoBinarySet;
    int sum;

public:
    ~Neighbor();

    Neighbor(std::vector<int> psudoBinarySet, int sum);

    std::vector<int> getPsudoBinarySet();

    int getSum();

    void showNeighbor();
};

class TabuSearch {
private:
    std::vector<std::vector<int>> tabuList;
    std::vector<Neighbor> tabuListNeiborhood;

    std::vector<std::vector<int>> neighborList;
    std::vector<std::vector<int>> tabuHistory;
    std::vector<int> startPoint;
    std::vector<int> numbersSet;
    int targetSum = 0;
    int tabuLimit;

    bool stopTabuSearch = false;

    void generateNeighborList();

    std::vector<int> fitConvert(std::vector<int> v);

    void addBestNeighborToTabu();

    void initTabuSearch();


public:
    ~TabuSearch();

    TabuSearch(const std::vector<int> &set, const std::vector<int> &startPoint, int target, int tabuLimit = 0);

    std::vector<std::vector<int>> getTabuList();
};

#endif //METAHEURYSTYKA_TABU_SEARCH_H
