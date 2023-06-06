#ifndef METAHEURYSTYKA_HILL_CLIMBING_H
#define METAHEURYSTYKA_HILL_CLIMBING_H

#include <numeric>
#include <random>
#include <time.h>

#include "utils.h"


class HillClimbing {
private:

    std::random_device rd;
    std::mt19937 rgen{rd()};

    std::vector<int> numbersSet;
    std::vector<std::vector<int>> subsetsSet = {};
    std::vector<std::vector<int>> neighborSubsetsSet = {};
    int targetSum = 0;

    std::vector<int> generateNeighborsForSubset(std::vector<int> pseudoBinary, int index) {
        std::vector<int> neighborSubset = pseudoBinary;

        if (neighborSubset[index] == 1) {
            neighborSubset[index] = 0;
        } else {
            neighborSubset[index] = 1;
        }

        if (!isVectorEqualVector(neighborSubset, pseudoBinary)) {
            std::cout << "Neighbor subset: ";
            showVector(neighborSubset);
            std::cout << std::endl << "=====================" << std::endl;

            return neighborSubset;
            }
    }

    std::vector<int> getRandomSolution() {
        std::vector<std::vector<int>> allCombinationsSet = generateCombinations(numbersSet);
        showVectorsInVector(allCombinationsSet);
        std::cout<<std::endl;

        std::uniform_int_distribution<int> dist(0, allCombinationsSet.size() - 1);
        int randomIndex = dist(rgen);

        std::vector<int> randomSolution = allCombinationsSet[randomIndex];
        std::cout << "Selected Index: " << randomIndex << std::endl;
        std::cout << "Selected random solution: ";
        showVector(randomSolution);
        std::cout<<std::endl;

        return randomSolution;
    }

    std::vector<int> getRandomSolutionPseudoBinary() {
        std::vector<int> randomSolution = getRandomSolution();
        std::vector<int> randomSolutionPsuedoBinary = generatePseudoBinarySet(randomSolution, numbersSet);

        std::cout << "psudo binary for random solution: ";
        showVector(randomSolutionPsuedoBinary);
        std::cout<<std::endl;

        int index = 0;
        while (neighborSubsetsSet.size() <= numbersSet.size()) {

            std::vector<int> neighborPseudoBinarySubset = generateNeighborsForSubset(randomSolutionPsuedoBinary, index);
            if (index < randomSolutionPsuedoBinary.size()) {
                index++;
            }
            if (!isSubsetInListOfSubsets(neighborPseudoBinarySubset, neighborSubsetsSet)) {
                neighborSubsetsSet.push_back(neighborPseudoBinarySubset);
            }
        }
        std::cout << "Neighbor full subsets: ";
        showVectorsInVector(neighborSubsetsSet);

        return randomSolutionPsuedoBinary;
    }



public:
    HillClimbing(const std::vector<int>& set, int target) {
        this->numbersSet = set;
        this->targetSum = target;
    }

    std::vector<int> bestHillClimb() {
        std::vector<int> randomSolutionPseudoBinary = getRandomSolutionPseudoBinary();

        return randomSolutionPseudoBinary;
    }

    std::vector<int> randomHillClimb() {
        std::vector<int> randomSolutionPseudoBinary = getRandomSolutionPseudoBinary();
        return randomSolutionPseudoBinary;
    }
};

#endif //METAHEURYSTYKA_HILL_CLIMBING_H
