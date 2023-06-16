#ifndef METAHEURYSTYKA_HILL_CLIMBING_H
#define METAHEURYSTYKA_HILL_CLIMBING_H

#include <numeric>
#include <random>

#include "utils.h"

class HillClimbing {
private:

    std::random_device rd;
    std::mt19937 rgen{rd()};

    std::vector<int> numbersSet;
    std::vector<std::vector<int>> subsetsSet = {};
    std::vector<std::vector<int>> neighborSubsetsSet = {};
    int targetSum = 0;
    int maxIteration = 50;

    std::vector<int> fitConvert(std::vector<int> v);

    std::vector<int> getRandomSolution();

    std::vector<int> getRandomSolutionPseudoBinaryWithNeighbors();

    std::vector<std::vector<int>> generateNeighborsForPseudoSubset(std::vector<int> currentBest);

    std::vector<int> getBestNeighbor(std::vector<int> bestSubset, std::vector<std::vector<int>> neighborSubsets);

    std::vector<int> getRandomBest(std::vector<int> bestSubset, std::vector<std::vector<int>> neighborSubsets);

public:
    ~HillClimbing();
    HillClimbing(const std::vector<int>& set, int target, int iteration);

    std::vector<int> getDeterministicBestHillClimb();

    std::vector<int> getDeterministicRandomHillClimb();
};

#endif //METAHEURYSTYKA_HILL_CLIMBING_H
