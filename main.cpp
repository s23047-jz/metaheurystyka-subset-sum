#include <fstream>
#include <sstream>

#include "headers/hill_climbing.h"
#include "headers/tabu_search.h"
#include "headers/simulated_annealing.h"
#include "headers/ag.h"


class SubsetSum {
private:
    std::vector<int> numbersSet;
    int target = 0;
    int capacity = 0;
    int iteration = 0;
    int tabuSize = 0;
    std::string crossoverMethod;

public:
    SubsetSum(const std::vector<int>& numberSet, int num, int capacity, int iteration, int tabuSize, std::string crossoverMethod="crosoverOne") {
        this->numbersSet = numberSet;
        this->target = num;
        this->capacity = capacity;
        this->iteration = iteration;
        this->tabuSize = tabuSize;
        this->crossoverMethod = crossoverMethod;
    }

    void getDeterministicRandomHillClimb() {
        HillClimbing hillClimbing(numbersSet, target, iteration);
        hillClimbing.getDeterministicRandomHillClimb();
    }

    void getDeterministicBestHillClimb() {
        HillClimbing hillClimbing(numbersSet, target, iteration);
        hillClimbing.getDeterministicBestHillClimb();
    }

    void getTabuSearch() {
        HillClimbing hillClimbing(numbersSet, target, iteration);
        std::vector<int> bestSolution = hillClimbing.getDeterministicBestHillClimb();
        TabuSearch tabuSearch(numbersSet, bestSolution, target, tabuSize);
        tabuSearch.getTabuList();
    }

    void getSimulatedAnnealing() {\
        SimulatedAnnealing simulatedAnnealing(numbersSet, [](int k){return 1000/k;}, target, iteration);
        simulatedAnnealing.getBestSolution();
    }

    void getGeneticAlgorithm() {
        AG ag = AG(capacity, target, numbersSet, iteration, crossoverMethod);
        ag.init();
    }

    void getGeneticAlgorithmElite() {
        AG ag = AG(capacity, target, numbersSet, iteration, crossoverMethod);
        ag.initElite();
    }
};

std::pair<std::vector<int>, int> getFileData() {

    std::ifstream file("../data.txt");
    if (file.is_open()) {
        std::string line;
        std::getline(file, line);

        std::vector<int> numbersSet;
        std::istringstream iss(line);
        int number;

        while (iss >> number) {
            numbersSet.push_back(number);
        }

        std::getline(file, line);

        // convert string to int std::stoi()
        int targetSum = std::stoi(line);

        file.close();

        std::cout << "Numbers Set: [ ";
        for (int num : numbersSet) {
            std::cout << num << " ";
        }
        std::cout << " ] " << std::endl;

        std::cout << "Target Sum: " << targetSum << std::endl;

        return std::make_pair(numbersSet, targetSum);
    } else {
        std::cout << "Unable to open file" << std::endl;
        return std::make_pair(std::vector<int>(), 0);
    }
};

int main(int argc, char* argv[]) {

    std::pair<std::vector<int>, int> data = getFileData();

    std::vector<int> list_of_numbers = data.first;
    int targetSum = data.second;

    int iteration, capacity, tabuSize;
    std::string crossoverMethod;

    if (argc == 5) {
        capacity = std::stoi(argv[1]);
        iteration = std::stoi(argv[2]);
        tabuSize = std::stoi(argv[3]);
        crossoverMethod = argv[4];
    } else {
        std::cout << "Nieprawidlowe dane werjsciowe! nalezy podac 4, capacity, iteration, tabuSize, wszystko jako liczba calkowita oraz crossoverMethod jako string" << std::endl;
        return 1;
    }

    SubsetSum subsetSum(list_of_numbers, targetSum, capacity, iteration, tabuSize, crossoverMethod);
//    subsetSum.getDeterministicRandomHillClimb();
//    subsetSum.getDeterministicBestHillClimb();
    subsetSum.getTabuSearch();
//    subsetSum.getSimulatedAnnealing();
//    subsetSum.getGeneticAlgorithm();
//    subsetSum.getGeneticAlgorithmElite();
    return 0;
}
