#ifndef METAHEURYSTYKA_HILL_CLIMBING_H
#define METAHEURYSTYKA_HILL_CLIMBING_H

#include <numeric>
#include <time.h>

#include "utils.h"


class NeighborSubset {
private:
    std::vector<int> neighborSet;
    std::vector<int> subset;

public:
    NeighborSubset(const std::vector<int>& neighborSet, const std::vector<int>& subset) {
        this->neighborSet = neighborSet;
        this->subset = subset;
    }

    std::vector<int> getSubSet() {
        return subset;
    }

    std::vector<int> getNeighborSet() {
        return neighborSet;
    }
};

class HillClimbing {
private:
    std::vector<int> numbersSet;
    std::vector<std::vector<int>> subsetsSet = {};
    std::vector<NeighborSubset> neighborSubsetsSet = {};
    int targetSum = 0;

    void generateNeighborSubsetsSets(std::vector<int> zeroOneSubset) {

    }

    void hillClimb() {
        std::vector<std::vector<int>> allCombinationsSet = generateCombinations(numbersSet);
        showVectorsInVector(allCombinationsSet);

        for (auto combination : allCombinationsSet) {
            std::vector<int> neighborSubset = generateZeroOneSetForSubset(combination, numbersSet);
            NeighborSubset neighborSubsetObj(neighborSubset, combination);
            neighborSubsetsSet.push_back(neighborSubsetObj);
        }

        srand(time(NULL));
        int randomIndex = rand() % neighborSubsetsSet.size();
        NeighborSubset selectedNeighborSubset = neighborSubsetsSet[randomIndex];

        for (NeighborSubset neighbor : neighborSubsetsSet) {

        }
    }

public:
    HillClimbing(const std::vector<int>& set, int target) {
        this->numbersSet = set;
        this->targetSum = target;
    }

    void getHillClimb() {
        hillClimb();
    }
};

#endif //METAHEURYSTYKA_HILL_CLIMBING_H
