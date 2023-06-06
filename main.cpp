#include "hill_climbing.h"

class SubsetSum {
private:
    std::vector<int> numbersSet;
    int target = 0;

public:
    SubsetSum(const std::vector<int>& numberSet, int num) {
        this->numbersSet = numberSet;
        this->target = num;
    }

    void getRandomHillClimb() {
        HillClimbing hillClimbing(numbersSet, target);
        hillClimbing.randomHillClimb();
    }

    void getBestHillClimb() {
        HillClimbing hillClimbing(numbersSet, target);
        hillClimbing.bestHillClimb();
    }
};

int main() {
    std::vector<int> list_of_numbers = {1, 2, 3, 4, 5};

    SubsetSum subsetSum(list_of_numbers, 5);
    subsetSum.getRandomHillClimb();
//    subsetSum.getBestHillClimb();

    return 0;
}
