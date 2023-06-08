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

    std::vector<int> initSimulatedAnnealing() {
        std::vector<int> bestGlobalSolution = solution; // hill climbing best
        std::vector<int> s = solution; // current solution

        int sSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(s, numbersSet));
        int sDistance = std::abs(targetSum - sSum);

        int bestGlobalSolutionSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(bestGlobalSolution, numbersSet));
        int bestGlobalSolutionDistance = std::abs(targetSum - bestGlobalSolutionSum);

        int index = 0;
        for (int i=1; i<25; i++) {
            std::vector<int> neighbor = generateNeighborsForSubset(s, index);
            if (index == numbersSet.size() - 1) {
                index = 0;
            } else {
                index++;
            }

            int neighborSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(neighbor, numbersSet));
            int neighborDistance = std::abs(targetSum - neighborSum);

            std::cout << "Neighbor Distance: " << neighborDistance << " S Distance: " << sDistance;
            std::cout << " BEST DISTANCE: " << bestGlobalSolutionDistance << std::endl;

            if (neighborDistance < sDistance) {
                s = neighbor;
                sSum = neighborSum;
                sDistance = neighborDistance;

                if (sDistance < bestGlobalSolutionDistance) {
                    bestGlobalSolution = s;
                    bestGlobalSolutionSum = sSum;
                    bestGlobalSolutionDistance = sDistance;

                    std::cout << "!!!! Updated Best solution for SIM ANNEALING !!!! ";
                    showVector(bestGlobalSolution);
                    std::cout << std::endl;
                }

            } else {
                std::uniform_int_distribution<int> u(0, 1);
                int rnd = u(rgen);
                double probability = std::exp(-std::abs(neighborDistance - sDistance) / temperatureFunction(i));
                int p = (int)probability;

                std::cout << "Probability: " << p << " RND " << rnd << std::endl;

                if (rnd < p) {
                    std::cout << "@@@@@ Accepting worse @@@@@" << std::endl;
                    s = neighbor;
                    sSum = neighborSum;
                    sDistance = neighborDistance;
                }
            }

        }
        return bestGlobalSolution;
    }

public:
    SimulatedAnnealing(const std::vector<int>& numbersSet, std::function<double(int)> F,
                       std::vector<int> best_solution, int target
                       ) {
        this->numbersSet = numbersSet;
        this->temperatureFunction = F;
        this->targetSum = target;
        this->solution = best_solution;
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
