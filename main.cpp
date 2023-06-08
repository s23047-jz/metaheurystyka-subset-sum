#include "hill_climbing.h"
#include "tabu_search.h"
#include "simulated_annealing.h"

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
        std::vector<int> bestSolution = {0, 1, 1, 0, 1};
        SimulatedAnnealing simulatedAnnealing(numbersSet, [](int k){return 1000/k;}, bestSolution, target);
        simulatedAnnealing.getBestSolution();
    }
};

int main() {
    std::vector<int> list_of_numbers = {1, 2, 3, 4, 5};

    SubsetSum subsetSum(list_of_numbers, 5);
//    subsetSum.getDeterministicRandomHillClimb();
//    subsetSum.getDeterministicBestHillClimb();
//    subsetSum.getTabuSearch();
    subsetSum.getSimulatedAnnealing();

    return 0;
}
