#include <fstream>
#include <sstream>

#include "hill_climbing.h"
#include "tabu_search.h"
#include "simulated_annealing.h"
#include "ag.h"


class SubsetSum {
private:
    std::vector<int> numbersSet;
    int target = 0;

public:
    SubsetSum(const std::vector<int>& numberSet, int num) {
        this->numbersSet = numberSet;
        this->target = num;
    }

    void getDeterministicRandomHillClimb() {
        HillClimbing hillClimbing(numbersSet, target);
        hillClimbing.getDeterministicRandomHillClimb();
    }

    void getDeterministicBestHillClimb() {
        HillClimbing hillClimbing(numbersSet, target);
        hillClimbing.getDeterministicBestHillClimb();
    }

    void getTabuSearch() {
        HillClimbing hillClimbing(numbersSet, target);
        std::vector<int> bestSolution = hillClimbing.getDeterministicBestHillClimb();
        TabuSearch tabuSearch(numbersSet, bestSolution, target, 10);
        tabuSearch.getTabuList();
    }

    void getSimulatedAnnealing() {\
        SimulatedAnnealing simulatedAnnealing(numbersSet, [](int k){return 1000/k;}, target);
        simulatedAnnealing.getBestSolution();
    }

    void getGeneticAlgorithm() {
        std::vector set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        AG ag = AG(10, 10, set);
        ag.init();
    }

    void getGeneticAlgorithmElite() {
        std::vector set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        AG ag = AG(10, 10, set);
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

int main() {

    std::pair<std::vector<int>, int> data = getFileData();

    std::vector<int> list_of_numbers = data.first;
    int targetSum = data.second;

    SubsetSum subsetSum(list_of_numbers, targetSum);
//    subsetSum.getDeterministicRandomHillClimb();
//    subsetSum.getDeterministicBestHillClimb();
//    subsetSum.getTabuSearch();
//    subsetSum.getSimulatedAnnealing();
//    subsetSum.getGeneticAlgorithm();
    subsetSum.getGeneticAlgorithmElite();
    return 0;
}
