#ifndef METAHEURYSTYKA_SIMULATED_ANNEALING_H
#define METAHEURYSTYKA_SIMULATED_ANNEALING_H

#include <functional>
#include <random>

#include "utils.h"


class SimulatedAnnealing {
private:

    std::random_device rd;
    std::mt19937 rgen{rd()};

    std::vector<int> numbersSet;
    std::function<double(int)> temperatureFunction;
    std::vector<int> solution;
    int targetSum = 0;
    int maxIteration = 50;

    std::vector<int> fitConvert(std::vector<int> v);

    void getRandomSolution();

    std::pair<std::vector<int>, std::vector<int>> getBestNeighbor(
            std::vector<int> bestGlobal, std::vector<int> bestSubset, std::vector<std::vector<int>> neighborSubsets,
            int iteration
    );

    std::vector<std::vector<int>> generateNeighborsForPseudoSubset(std::vector<int> currentBest);

    std::vector<int> initSimulatedAnnealing();

public:
    ~SimulatedAnnealing();

    SimulatedAnnealing(const std::vector<int> &numbersSet, std::function<double(int)> F, int target, int iteration);

    std::vector<int> getBestSolution();
};


#endif //METAHEURYSTYKA_SIMULATED_ANNEALING_H
