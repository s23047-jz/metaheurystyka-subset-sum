#include "hill_climbing.h"
#include "tabu_search.h"

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
        TabuSearch tabuSearch(numbersSet, bestSolution);
        tabuSearch.getTabuList();
    }
};

int main() {
    std::vector<int> list_of_numbers = {1, 2, 3, 1, 3, 4, 5};

    SubsetSum subsetSum(list_of_numbers, 5);
//    subsetSum.getDeterministicRandomHillClimb();
    subsetSum.getDeterministicBestHillClimb();
//    subsetSum.getTabuSearch();
    return 0;
}
