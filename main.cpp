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

    void getHillClimb() {
        HillClimbing hillClimbing(numbersSet, target);
        hillClimbing.getHillClimb();
    }
};

int main() {
    std::vector<int> list_of_numbers = {1, 1, 2, 3, 4, 5};
    SubsetSum subsetSum(list_of_numbers, 5);
    subsetSum.getHillClimb();

    return 0;
}
