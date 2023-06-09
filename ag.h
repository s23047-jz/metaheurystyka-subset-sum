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

    int populationSize = 0;
    int targetSum = 0;
    std::vector<int> numbersSet;
    std::vector<std::vector<int>> population;
    std::vector<std::vector<int>> createdRouletteIndividuals;
    std::vector<std::vector<int>> selectedRouletteIndividuals;
    std::vector<std::vector<int>> elitePopulation;
    std::vector<int> bestIndividual;

    std::string method = "crucifixion";


    std::vector<int> generateRandomIndividual() {
        std::vector<int> individualSet;
        std::uniform_int_distribution<int> dist(0, 1);
        for (int i = 0; i < numbersSet.size(); i++) {
            if (dist(rgen) == 1) {
                individualSet.push_back(1);
            } else {
                individualSet.push_back(0);
            }
        }
        return individualSet;
    }

    void generatePopulation() {
        for (int i = 0; i < populationSize; i++) {
            std::vector<int> individualSet = generateRandomIndividual();
            if (!isSubsetInListOfSubsets(individualSet, population)) {
                population.push_back(individualSet);
            } else {
                i--;
            }
        }
    }

    void createRouletteVector() {
        generatePopulation();
        int numberSetsSum = calculateSubsetSum(numbersSet);
        int numberSetsDistance = std::abs(targetSum - numberSetsSum);

        for (auto individual: population) {
            int sum = calculateSubsetSum(convertFromPseudoBinaryToSubset(individual, numbersSet));
            int distance = std::abs(targetSum - sum);

            int repeat = numberSetsDistance - distance;
            for (int i = 0; i < repeat; i++) {
                createdRouletteIndividuals.push_back(individual);
            }
        }
    };

    bool isIndividualLastOne(std::vector<int> individual) {
        return std::find(selectedRouletteIndividuals.begin(), selectedRouletteIndividuals.end(), individual) != selectedRouletteIndividuals.end();
    }

    std::vector<int> getHigherDistance() {
        std::vector<int> higherDistanceIndividual = population[0];
        int sum = calculateSubsetSum(convertFromPseudoBinaryToSubset(higherDistanceIndividual, numbersSet));
        int distance = std::abs(targetSum - sum);

        for (auto individual: population) {
            int individualSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(individual, numbersSet));
            int individualDistance = std::abs(targetSum - individualSum);
            if (individualSum > distance) {
                higherDistanceIndividual = individual;
                distance = individualDistance;
            }
        }
        return higherDistanceIndividual;
    }

    void checkDistanceForPopulation() {
        std::vector<int> v = population[0];
        int sum = calculateSubsetSum(convertFromPseudoBinaryToSubset(v, numbersSet));
        int distance = std::abs(targetSum - sum);

        for (auto individual: population) {
            int individualSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(individual, numbersSet));
            int individualDistance = std::abs(targetSum - individualSum);
            if (individualSum < distance) {
                bestIndividual = individual;
                distance = individualDistance;
            }
        }

        std::cout << "Best individual after iteration: ";
        showVector(bestIndividual);
        std::cout << std::endl;
    }

    void createElitePopulation() {
        std::vector<int> bestIndividual = getHigherDistance();
        int sum = calculateSubsetSum(convertFromPseudoBinaryToSubset(bestIndividual, numbersSet));
        int distance = std::abs(targetSum - sum);

        while (elitePopulation.size() < populationSize / 2) {
            for (auto individual: population) {
                int individualSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(individual, numbersSet));
                int individualDistance = std::abs(targetSum - individualSum);
                if (individualSum < distance) {
                    bestIndividual = individual;
                    distance = individualDistance;
                }
            }

            if (!isSubsetInListOfSubsets(bestIndividual, elitePopulation)) {
                elitePopulation.push_back(bestIndividual);
            }
        }
    }

    std::pair<std::vector<int>, std::vector<int>> crucifixionIndividuals(
            std::vector<int> individualParentFirst, std::vector<int> individualParentSecond) {

        std::uniform_int_distribution<int> divisionPoints(1, numbersSet.size() - 1);
        int divisionPoint = divisionPoints(rgen);

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

    std::pair<std::vector<int>, std::vector<int>> crucifixionIndividualsTwo(
            std::vector<int> individualParentFirst, std::vector<int> individualParentSecond) {

        std::uniform_int_distribution<int> divisionPoints(1, numbersSet.size() - 1);
        int divisionPoint1 = divisionPoints(rgen);
        int divisionPoint2 = divisionPoints(rgen);

        // Ensure divisionPoint1 is smaller than divisionPoint2
        if (divisionPoint1 > divisionPoint2) {
            std::swap(divisionPoint1, divisionPoint2);
        }


        std::vector<int> childFirst, childSecond;

        childFirst.insert(childFirst.end(), individualParentFirst.begin(),
                          individualParentFirst.begin() + divisionPoint1);

        childFirst.insert(childFirst.end(), individualParentSecond.begin() + divisionPoint1,
                          individualParentSecond.begin() + divisionPoint2);

        childFirst.insert(childFirst.end(), individualParentFirst.begin() + divisionPoint2,
                          individualParentFirst.end());

        childSecond.insert(childSecond.end(), individualParentSecond.begin(),
                           individualParentSecond.begin() + divisionPoint1);

        childSecond.insert(childSecond.end(), individualParentFirst.begin() + divisionPoint1,
                           individualParentFirst.begin() + divisionPoint2);

        childSecond.insert(childSecond.end(), individualParentSecond.begin() + divisionPoint2,
                           individualParentSecond.end());


        return std::make_pair(childFirst, childSecond);
    }

    std::vector<int> mutation(std::vector<int> individual) {
        std::uniform_int_distribution<int> dist(0, 1);

        for (int i = 0; i < individual.size(); i++) {
            int random = dist(rgen);
            if (random == 1) {
                if (individual[i] == 1) {
                    individual[i] = 0;
                } else {
                    individual[i] = 1;
                }
                break;
            }
        }
        std::cout << " mutated individual: ";
        showVector(individual);
        std::cout << std::endl;

        return individual;
    }

    void roulette() {
        createRouletteVector();
        for (int i = 0; i < populationSize; i++) {
            std::uniform_int_distribution<int> dist(0, createdRouletteIndividuals.size() - 1);
            int random = dist(rgen);

            std::vector<int> individual = createdRouletteIndividuals[random];
            selectedRouletteIndividuals.push_back(individual);
        }
    }

    void initAG() {
        int iteration = 1;
        int bestSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(
                bestIndividual, numbersSet));
        while ((iteration < 1000) || (bestSum != targetSum)) {

            std::cout << "bestSum: " << bestSum << std::endl;

            if (bestSum == targetSum) {
                break;
            }

            roulette();
            std::vector<std::vector<int>> newPopulation;

            for (int i=0; i<selectedRouletteIndividuals.size() / 2; i+=2) {

                std::vector<int> individualFirst = selectedRouletteIndividuals[i];
                std::vector<int> individualSecond = selectedRouletteIndividuals[i+1];

                std::pair<std::vector<int>, std::vector<int>> children;
                std::uniform_int_distribution<int> crucifixioMethod(0, 1);
                int c = crucifixioMethod(rgen);

                if (c == 0) {
                    children = crucifixionIndividuals(individualFirst,
                                                      individualSecond);
                } else {
                    children = crucifixionIndividualsTwo(individualFirst,
                                                         individualSecond);
                }

                std::uniform_int_distribution<int> mutationMethod(0, 100);
                c = mutationMethod(rgen);

                std::vector<int> childFirst = children.first;
                std::vector<int> childSecond = children.second;

                if (c == 1) {
                    childFirst = mutation(childFirst);
                }

                c = mutationMethod(rgen);
                if (c == 1) {
                    childSecond = mutation(childSecond);
                }

                newPopulation.push_back(childFirst);
                newPopulation.push_back(childSecond);
            }
            population = newPopulation;
            checkDistanceForPopulation();
            bestSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(
                    bestIndividual, numbersSet));

            std::cout << "New population after iteration " << iteration << ": ";
            showVectorsInVector(population);
            std::cout << std::endl;

            selectedRouletteIndividuals.clear();
            createdRouletteIndividuals.clear();

            iteration++;
        }

        std::cout << "Last population: ";
        showVectorsInVector(population);
        std::cout << std::endl;

        std::cout << "Last Best Individualist: ";
        showVector(bestIndividual);
        std::cout << std::endl;
    }


public:
    AG(int populationSize, int targetSum, std::vector<int> numbersSet) {
        this->populationSize = populationSize;
        this->targetSum = targetSum;
        this->numbersSet = numbersSet;
    }

    void init() {
        initAG();
    }
};

#endif //METAHEURYSTYKA_AG_H
