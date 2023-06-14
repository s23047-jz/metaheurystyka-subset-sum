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

    int maxIteration=0;

    std::string crosoverMethod = "crosoverOne";

    std::vector<int> fitConvert(std::vector<int> v) {
        return convertFromPseudoBinaryToSubset(v, numbersSet);
    }

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
            int sum = calculateSubsetSum(fitConvert(individual));
            int distance = std::abs(targetSum - sum);

            int repeat = numberSetsDistance - distance;
            for (int i = 0; i < repeat; i++) {
                createdRouletteIndividuals.push_back(individual);
            }
        }
    };

    void checkDistanceForPopulation() {
        std::vector<int> v = population[0];
        int sum = calculateSubsetSum(fitConvert(v));
        int distance = std::abs(targetSum - sum);

        for (auto individual: population) {
            int individualSum = calculateSubsetSum(fitConvert(individual));
            int individualDistance = std::abs(targetSum - individualSum);
            if (individualSum < distance) {
                bestIndividual = individual;
                distance = individualDistance;
            }
        }
    }

        std::vector<int> getBestFromPopulation(std::vector<std::vector<int>> currentPopulation) {
            std::vector<int> bestOne = currentPopulation[0];
            int sum = calculateSubsetSum(fitConvert(bestOne));
            int distance = std::abs(targetSum - sum);

            for (auto individual: currentPopulation) {
                int individualSum = calculateSubsetSum(fitConvert(individual));
                int individualDistance = std::abs(targetSum - individualSum);
                if (individualSum < distance) {
                    bestOne = individual;
                    distance = individualDistance;
                }
            }
            return bestOne;
    }

    std::vector<int> getWeaknestOneFromPopulation(std::vector<std::vector<int>> currentPopulation) {
        std::vector<int> worstOne = currentPopulation[0];
        int sum = calculateSubsetSum(fitConvert(worstOne));
        int distance = std::abs(targetSum - sum);

        for (auto individual: currentPopulation) {
            int individualSum = calculateSubsetSum(fitConvert(individual));
            int individualDistance = std::abs(targetSum - individualSum);
            if (individualSum > distance) {
                worstOne = individual;
                distance = individualDistance;
            }
        }
        return worstOne;
    }

    std::pair<std::vector<int>, std::vector<int>> crosoverIndividuals(
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

    std::pair<std::vector<int>, std::vector<int>> crosoverIndividualsTwo(
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

    int findIndexOfVector(std::vector<int> element, std::vector<std::vector<int>> elemetsList) {
        int index = 0;
        for (int i = index; i < elemetsList.size(); i++) {
            if(isVectorEqualVector(element, elemetsList[i])) {
                index = i;
                break;
            }
        }
        return index;
    }

    std::pair<std::vector<int>, std::vector<int>> getTwoStrongestFromPopulation(std::vector<std::vector<int>> currentPopulation) {
        std::vector<std::vector<int>> p = currentPopulation;

        std::cout << "POPULTION: ";
        showVectorsInVector(p);
        std::cout << std::endl;

        std::vector<int> firstStrongers = getBestFromPopulation(p);
        int indexOfFirstStrongers = findIndexOfVector(firstStrongers, p);

        std::cout << "Erasing index: " << indexOfFirstStrongers << std::endl;

        p.erase(p.begin() + indexOfFirstStrongers);
        std::vector<int> secondStrongers = getBestFromPopulation(p);

        return std::make_pair(firstStrongers, secondStrongers);
    }

    std::vector<std::vector<int>> replaceTwoWeaknestToTwoFromElite(std::vector<std::vector<int>>& currentPopulation,
                                                                                   std::vector<int> strongestFirst, std::vector<int> strongestSecond) {

        std::vector<std::vector<int>> p = currentPopulation;

        std::cout << "POPULTION BEFORE REPLACED WAEKNEST: ";
        showVectorsInVector(p);
        std::cout << std::endl;

        std::vector<int> firstWeaknest = getWeaknestOneFromPopulation(p);
        int indexOfFirstStrongers = findIndexOfVector(firstWeaknest, p);
        std::cout << "Erasing 1st weaknest at  index: " << indexOfFirstStrongers << std::endl;
        p.erase(p.begin() + indexOfFirstStrongers);
        std::vector<int> secondWeaknest = getWeaknestOneFromPopulation(p);
        int indexOfSecondStrongers = findIndexOfVector(secondWeaknest, p);
        std::cout << "Erasing 2nd weaknest at index: " << indexOfSecondStrongers << std::endl;
        p.erase(p.begin() + indexOfSecondStrongers);

        std::cout << "THE STRONGETS: ";
        showVector(strongestFirst);
        showVector(strongestSecond);
        std::cout << std::endl;

        p.push_back(strongestFirst);
        p.push_back(strongestSecond);

        std::cout << "POPULTION AFTER REPLACED WAEKNEST: ";
        showVectorsInVector(p);
        std::cout << std::endl;

        return p;
    }

    void initAG() {
        int iteration = 1;
        int bestSum = calculateSubsetSum(fitConvert(bestIndividual));
        while ((iteration < maxIteration) || (bestSum != targetSum)) {

            std::cout << "bestSum: " << bestSum << std::endl;

            if (bestSum == targetSum) {
                break;
            }

            roulette();
            std::vector<std::vector<int>> newPopulation;

            for (int i=0; i<selectedRouletteIndividuals.size(); i+=2) {

                std::vector<int> individualFirst = selectedRouletteIndividuals[i];
                std::vector<int> individualSecond = selectedRouletteIndividuals[i+1];

                std::pair<std::vector<int>, std::vector<int>> children;
                int c;

                if (crosoverMethod == "crosoverOne") {
                    children = crosoverIndividuals(individualFirst,
                                                      individualSecond);
                } else {
                    children = crosoverIndividualsTwo(individualFirst,
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
            newPopulation.clear();
            checkDistanceForPopulation();
            bestSum = calculateSubsetSum(fitConvert(bestIndividual));

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

    void initAGWithElite() {
        int iteration = 1;
        int bestSum = calculateSubsetSum(fitConvert(bestIndividual));

        std::pair<std::vector<int>, std::vector<int>> elite;
        while ((iteration < maxIteration) || (bestSum != targetSum)) {

            std::cout << "bestSum: " << bestSum << std::endl;

            if (bestSum == targetSum) {
                break;
            }

            roulette();
            std::vector<std::vector<int>> newPopulation;
            elite = getTwoStrongestFromPopulation(population);

            for (int i=0; i<selectedRouletteIndividuals.size(); i+=2) {

                std::vector<int> individualFirst = selectedRouletteIndividuals[i];
                std::vector<int> individualSecond = selectedRouletteIndividuals[i+1];

                std::pair<std::vector<int>, std::vector<int>> children;
                int c;

                if (crosoverMethod == "crosoverOne") {
                    children = crosoverIndividuals(individualFirst,
                                                      individualSecond);
                } else {
                    children = crosoverIndividualsTwo(individualFirst,
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
            newPopulation = replaceTwoWeaknestToTwoFromElite(newPopulation, elite.first, elite.second);
            population = newPopulation;
            newPopulation.clear();
            checkDistanceForPopulation();
            bestSum = calculateSubsetSum(fitConvert(bestIndividual));

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
    AG(int populationSize, int targetSum, std::vector<int> numbersSet, int iteration, std::string crosoverMethod="crosoverOne") {
        this->populationSize = populationSize;
        this->targetSum = targetSum;
        this->numbersSet = numbersSet;
        this->maxIteration = iteration;
        this->crosoverMethod = crosoverMethod;
    }

    void init() {
        initAG();
    }

    void initElite() {
        initAGWithElite();
    }
};

#endif //METAHEURYSTYKA_AG_H
