#include "hill_climbing.h"

class SubsetSum {
private:
    std::vector<int> listOfNumbers;
    int targetSum = 0;

public:
    SubsetSum(const std::vector<int>& numberSet, int num) {
        listOfNumbers = numberSet;
        targetSum = num;
    }

    void getHillClimb() {
        HillClimbing hillClimbing(listOfNumbers, targetSum);
        hillClimbing.getHillClimb();
    }
};

int main() {
    std::vector<int> list_of_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    SubsetSum subsetSum(list_of_numbers, 8);
    subsetSum.getHillClimb();

    return 0;
}
