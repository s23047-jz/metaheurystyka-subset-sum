#ifndef METAHEURYSTYKA_AG_H
#define METAHEURYSTYKA_AG_H

#include <string>
#include <random>
#include <utility>

#include "utils.h"


class AG {
private:
    std::random_device rd;
    std::mt19937 rgen{rd()};

    int populationSize=0;
    int individualSize=0;
    int targetSum=0;
    std::vector<int> numbersSet;
    std::vector<std::vector<int>> population;
    std::vector<std::vector<int>> elitePopulation;


    std::vector<int> generateRandomIndividual() {
        std::vector<int> individualSet;
        std::uniform_int_distribution<int> dist(0, 1);
        for (int i=0; i<individualSize; i++) {
            if (dist(rgen) == 1) {
                individualSet.push_back(1);
            } else {
                individualSet.push_back(0);
            }
        }
        return individualSet;
    }

    void generatePopulation() {
        for (int i=0; i<populationSize; i++) {
            std::vector<int> individualSet = generateRandomIndividual();
            if (!isSubsetInListOfSubsets(individualSet, population)) {
                population.push_back(individualSet);
            } else {
                i--;
            }
        }
    }

    bool isIndividualLastOne(std::vector<int> individual) {
        return std::find(population.begin(), population.end(), individual) != population.end();
    }

    std::vector<int> getHigherDistance() {
        std::vector<int> higherDistanceIndividual = population[0];
        int sum = calculateSubsetSum(convertFromPseudoBinaryToSubset(higherDistanceIndividual, numbersSet));
        int distance = std::abs(targetSum - sum);

        for (auto individual : population) {
            int individualSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(individual, numbersSet));
            int individualDistance = std::abs(targetSum - individualSum);
            if (individualSum > distance) {
                higherDistanceIndividual = individual;
                distance = individualDistance;
            }
        }
        return higherDistanceIndividual;
    }

    void createElitePopulation() {
        std::vector<int> bestIndividual = getHigherDistance();
        int sum = calculateSubsetSum(convertFromPseudoBinaryToSubset(bestIndividual, numbersSet));
        int distance = std::abs(targetSum - sum);

        while (elitePopulation.size() < populationSize/2) {
            for (auto individual : population) {
                int individualSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(individual, numbersSet));
                int individualDistance = std::abs(targetSum - individualSum);
                if (individualSum < distance) {
                    bestIndividual = individual;
                    distance = individualDistance;
                }
            }

            if(!isSubsetInListOfSubsets(bestIndividual, elitePopulation)) {
                elitePopulation.push_back(bestIndividual);
            }
        }
    }

    std::pair<std::vector<int>, std::vector<int>> crucifixionIndividuals(
            std::vector<int> individualParentFirst, std::vector<int> individualParentSecond) {

        std::uniform_int_distribution<int> divisionPoints(1, 8-1);
        int divisionPoint = divisionPoints(rgen);

        std::cout << "divisionPoint: " << divisionPoint << std::endl;

        std::cout << " Parent First : ";
        showVector(individualParentFirst);
        std::cout << std::endl;

        std::cout << " Parent Second: ";
        showVector(individualParentSecond);
        std::cout << std::endl;

        std::vector<int> childFirst, childSecond;

        childFirst.insert(childFirst.end(), individualParentFirst.begin(),
                          individualParentFirst.begin() + divisionPoint);


        childFirst.insert(childFirst.end(), individualParentSecond.begin() + divisionPoint,
                          individualParentSecond.end());


        childSecond.insert(childSecond.end(), individualParentSecond.begin(),
                           individualParentSecond.begin() + divisionPoint);


        childSecond.insert(childSecond.end(), individualParentFirst.begin() + divisionPoint,
                           individualParentFirst.end());


        return std::make_pair(childFirst, childSecond);
    }

    std::vector<int> mutationIndividual(std::vector<int> individual) {
        std::uniform_int_distribution<int> dist(0, 100);

        for (int i=0; i<individual.size(); i++) {
            int random = dist(rgen);
            std::cout<< "random: " << random << std::endl;
            if (dist(rgen) == 1) {
                if (individual[i] == 1) {
                    individual[i] = 0;
                } else {
                    individual[i] = 1;
                }
            }
        }
        std::cout << " mutated individual: ";
        showVector(individual);
        std::cout << std::endl;

        return individual;
    }

    void initAG() {
        std::vector<int> individualSet1 = {1, 0, 1, 0, 1, 0, 1, 0};
        std::vector<int> individualSet2 = {1, 1, 0, 0, 1, 1, 1, 0};

//        std::pair<std::vector<int>, std::vector<int>> children = crucifixionIndividuals(individualSet1, individualSet2);
//
//        std::cout << " childFirst: ";
//        showVector(children.first);
//        std::cout << std::endl;
//
//        std::cout << " childSecond: ";
//        showVector(children.second);
//        std::cout << std::endl;

        individualSet1 = mutationIndividual(individualSet1);
    }


public:
    AG(int populationSize, int individualSize, int targetSum, std::vector<int> numbersSet) {
        this->populationSize = populationSize;
        this->individualSize = individualSize;
        this->targetSum = targetSum;
        this->numbersSet = numbersSet;
    }

    void init() {
        initAG();
    }
};

#endif //METAHEURYSTYKA_AG_H
