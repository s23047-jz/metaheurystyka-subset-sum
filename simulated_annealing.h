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

    void getRandomSolution() {
        std::vector<std::vector<int>> allCombinationsSet = generateCombinations(numbersSet);
        std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
        showVectorsInVector(allCombinationsSet);
        std::cout << std::endl;
        std::cout << " COMBINATIONS SIZE: " << allCombinationsSet.size() << std::endl;

        std::uniform_int_distribution<int> dist(0, allCombinationsSet.size() - 1);
        int randomIndex = dist(rgen);

        std::vector<int> randomSolution = allCombinationsSet[randomIndex];
        std::cout << "Selected Index: " << randomIndex << std::endl;
        std::cout << "Selected random solution: ";
        showVector(randomSolution);
        std::cout<<std::endl;

        solution = randomSolution;
    }


    std::pair<std::vector<int>, std::vector<int>> getBestNeighbor(std::vector<int> bestGlobal, std::vector<int> bestSubset, std::vector<std::vector<int>> neighborSubsets, int iteration) {

        std::vector<int> bestGlobalSolution = bestGlobal;
        int bestGlobalSolutionSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(bestGlobalSolution, numbersSet));
        int bestGlobalSolutionDistance = std::abs(targetSum - bestGlobalSolutionSum);

        std::vector<int> bestNeighbor = bestSubset;
        int sum = calculateSubsetSum(convertFromPseudoBinaryToSubset(bestNeighbor, numbersSet));
        int distance = std::abs(targetSum - sum);

        for (auto neighbor : neighborSubsets) {
            int neighborSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(neighbor, numbersSet));
            int neighborDistance = std::abs(targetSum - neighborSum);

            if (neighborDistance < distance) {
                bestNeighbor = neighbor;
                sum = neighborSum;
                distance = neighborDistance;

                if (distance < bestGlobalSolutionDistance) {
                    bestGlobalSolution = bestNeighbor;
                    bestGlobalSolutionSum = sum;
                    bestGlobalSolutionDistance = distance;

                    std::cout << "!!!! Updated Best solution for SIM ANNEALING !!!! ";
                    showVector(bestGlobalSolution);
                    std::cout << std::endl;
                }

            } else {
                std::uniform_int_distribution<> u(0.0, 1.0);
                double probability = std::exp(-std::abs(neighborDistance - distance) / temperatureFunction(iteration));
                double rnd = u(rgen);
                std::cout << "Probability: " << probability << " RND " << rnd << std::endl;

                if (rnd < probability) {
                    std::cout << "@@@@@ Accepting worse @@@@@" << std::endl;
                    bestNeighbor = neighbor;
                    sum = neighborSum;
                    distance = neighborDistance;
                }
            }

            showVector(neighbor);
            std::cout << " SUM: " << neighborSum << " DISTANCE: " << neighborDistance << " " << "targetSum: " << targetSum << std::endl;
        }

        return std::pair(bestGlobalSolution, bestNeighbor);
    }

    std::vector<std::vector<int>> generateNeighborsForPseudoSubset(std::vector<int> currentBest) {
        std::vector<std::vector<int>> newNeighbors;

        for (int i=0; i<currentBest.size(); i++) {
            std::vector<int> newNeighbor = generateNeighborsForSubset(currentBest, i);
            newNeighbors.push_back(newNeighbor);
        }

        std::cout << "Neighbor full subsets: ";
        showVectorsInVector(newNeighbors);
        std::cout<<std::endl;

        return newNeighbors;
    }

    std::vector<int> initSimulatedAnnealing() {
        getRandomSolution();
        std::vector<int> bestGlobalSolution = solution; // hill climbing best
        std::vector<int> s = solution; // current solution

        int iteration = 1;
        while (iteration < maxIteration) {

            std::vector<std::vector<int>> currentNeighbors = generateNeighborsForPseudoSubset(s);
            std::pair<std::vector<int>, std::vector<int>> getBest = getBestNeighbor(bestGlobalSolution, s, currentNeighbors, iteration);

            bestGlobalSolution = getBest.first;
            s = getBest.second;

            std::cout << "ITERATION: " << iteration << std::endl;
            iteration++;

        }
        return bestGlobalSolution;
    }

public:
    SimulatedAnnealing(const std::vector<int>& numbersSet, std::function<double(int)> F, int target) {
        this->numbersSet = numbersSet;
        this->temperatureFunction = F;
        this->targetSum = target;
    }

    std::vector<int> getBestSolution() {
        auto bestSolution = initSimulatedAnnealing();
        std::cout << "Best solution for SIM ANNEALING: ";
        showVector(bestSolution);
        std::cout << std::endl;

        return bestSolution;
    }
};


#endif //METAHEURYSTYKA_SIMULATED_ANNEALING_H
