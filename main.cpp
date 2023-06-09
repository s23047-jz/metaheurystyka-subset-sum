#include <fstream>
#include <sstream>
#include <filesystem>

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
        TabuSearch tabuSearch(numbersSet, bestSolution, target);
        tabuSearch.getTabuList();
    }

    void getSimulatedAnnealing() {
//        HillClimbing hillClimbing(numbersSet, target);
//        std::vector<int> bestSolution = hillClimbing.getDeterministicBestHillClimb();
        std::vector<int> bestSolution = {1, 1, 1, 1, 1};
        SimulatedAnnealing simulatedAnnealing(numbersSet, [](int k){return 1000/k;}, bestSolution, target);
        simulatedAnnealing.getBestSolution();
    }

    void getGeneticAlgorithm() {
        AG ag = AG(3, numbersSet.size(), target, numbersSet, "mutation");
        ag.init();
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

        // Print the target sum
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
    subsetSum.getDeterministicBestHillClimb();
//    subsetSum.getTabuSearch();
//    subsetSum.getSimulatedAnnealing();
//    subsetSum.getGeneticAlgorithm();
    return 0;
}
