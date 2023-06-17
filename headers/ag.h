#ifndef METAHEURYSTYKA_AG_H
#define METAHEURYSTYKA_AG_H

#include <string>
#include <random>
#include <utility>

#include "utils.h"


class Individual {
    private:
    std::vector<int> individual;
    int chance = 0;

    public:

    int getChance();
    std::vector<int> getIndividual();
    Individual(std::vector<int> individual, int chance);
};

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

    int maxIteration = 0;

    std::string crossoverMethod = "crosoverOne";

    std::vector<int> fitConvert(std::vector<int> v);

    std::vector<std::vector<int>> getRandomPopulation();

    void createRouletteVector(bool generateFirstPopulation);

    void checkDistanceForPopulation();

    std::vector<int> getBestFromPopulation(std::vector<std::vector<int>> currentPopulation);

    std::vector<int> getWeaknestOneFromPopulation(std::vector<std::vector<int>> currentPopulation);

    std::pair<std::vector<int>, std::vector<int>> crossoverIndividuals(
            std::vector<int> individualParentFirst, std::vector<int> individualParentSecond);

    std::pair<std::vector<int>, std::vector<int>> crossoverIndividualsTwo(
            std::vector<int> individualParentFirst, std::vector<int> individualParentSecond);

    std::vector<int> mutation(std::vector<int> individual);

    void roulette(bool generateFirstPopulation);

    int findIndexOfVector(std::vector<int> element, std::vector<std::vector<int>> elemetsList);

    std::pair<std::vector<int>, std::vector<int>> getTwoStrongestFromPopulation(
            std::vector<std::vector<int>> currentPopulation
    );

    std::vector<std::vector<int>> replaceTwoWeaknestToTwoFromElite(
            std::vector<std::vector<int>> &currentPopulation, std::vector<int> strongestFirst,
            std::vector<int> strongestSecond
    );


    void initAG();

    void initAGWithElite();


public:
    ~AG();

    AG(int populationSize, int targetSum, std::vector<int> numbersSet, int iteration,
       std::string crosoverMethod = "crossoverOne");

    void init();

    void initElite();
};

#endif //METAHEURYSTYKA_AG_H
