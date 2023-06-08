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

    std::vector<int> getRandomSolutionPseudoBinaryWithNeighbors() {
        std::vector<int> randomSolution = getRandomSolution();
        std::vector<int> randomSolutionPseudoBinary = generatePseudoBinarySet(randomSolution, numbersSet);

        std::cout << "psudo binary for random solution: ";
        showVector(randomSolutionPseudoBinary);
        std::cout<<std::endl;

        int index = 0;
        while (neighborSubsetsSet.size() <= numbersSet.size()) {

            std::vector<int> neighborPseudoBinarySubset = generateNeighborsForSubset(randomSolutionPseudoBinary, index);
            if (index < randomSolutionPseudoBinary.size()) {
                index++;
            } else {
                index = 0;
            }
            if (!isSubsetInListOfSubsets(neighborPseudoBinarySubset, neighborSubsetsSet)) {
                neighborSubsetsSet.push_back(neighborPseudoBinarySubset);
            }
        }
        std::cout << "Neighbor full subsets: ";
        showVectorsInVector(neighborSubsetsSet);
        std::cout<<std::endl;

        return randomSolutionPseudoBinary;
    }

    std::vector<int> getBestNeighbor(std::vector<int> randomPseudoBinarySubset) {
        std::vector<int> bestNeighbor = randomPseudoBinarySubset;
        int sum = calculateSubsetSum(convertFromPseudoBinaryToSubset(randomPseudoBinarySubset, numbersSet));
        int distance = std::abs(targetSum - sum);

        for (auto neighbor : neighborSubsetsSet) {
            int neighborSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(neighbor, numbersSet));
            int neighborDistance = std::abs(targetSum - neighborSum);
            if (neighborDistance < distance) {
                bestNeighbor = neighbor;
                distance = neighborDistance;
            }

           showVector(neighbor);
           std::cout << " SUM: " << neighborSum << " DISTANCE: " << neighborDistance << " " << "targetSum: " << targetSum << std::endl;
        }

        return bestNeighbor;
    }



public:
    HillClimbing(const std::vector<int>& set, int target) {
        this->numbersSet = set;
        this->targetSum = target;
    }

    std::vector<int> getDeterministicBestHillClimb() {
        std::vector<int> randomSolutionPseudoBinary = getRandomSolutionPseudoBinaryWithNeighbors();
        std::vector<int> bestNeighbor = getBestNeighbor(randomSolutionPseudoBinary);

        std::cout << "Best neighbor: ";
        showVector(bestNeighbor);
        std::cout<<std::endl;

        return bestNeighbor;
    }

    std::vector<int> getDeterministicRandomHillClimb() {
        std::vector<int> randomSolutionPseudoBinary = getRandomSolutionPseudoBinaryWithNeighbors();
        return randomSolutionPseudoBinary;
    }
};

#endif //METAHEURYSTYKA_HILL_CLIMBING_H
