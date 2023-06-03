#ifndef METAHEURYSTYKA_HILL_CLIMBING_H
#define METAHEURYSTYKA_HILL_CLIMBING_H

#include <numeric>
#include <time.h>

#include "utils.h"

class HillClimbing {
private:
    std::vector<int> numbersSet;
    std::vector<std::vector<int>> subsetsSet = {};
    int targetSum = 0;


    std::vector<int> generateNeighborSubset(const std::vector<int>& subset) {
        std::vector<int> neighborSubset = subset;
        // randomowa liczba z zakresu [0, subset.size()-1]
        int randomIndex = std::rand() % subset.size();


        if (std::find(neighborSubset.begin(), neighborSubset.end(), numbersSet[randomIndex]) == neighborSubset.end()) {
            neighborSubset.push_back(numbersSet[randomIndex]);
        } else {
            neighborSubset.erase(std::remove(neighborSubset.begin(), neighborSubset.end(), numbersSet[randomIndex]), neighborSubset.end());
        }

        return neighborSubset;
    }

    void hillClimb() {
        std::vector<int> currentSet = generateRandomSubset(numbersSet);
        int setSum = calculateSubsetSum(currentSet);

        while (setSum != targetSum) {
            std::vector<int> neighborSubset = generateNeighborSubset(currentSet);
            int neighborSum = calculateSubsetSum(neighborSubset);

            if ((neighborSum - targetSum) <= (setSum - targetSum)) {
                currentSet = neighborSubset;
                setSum = neighborSum;
            } else {
                break;
            }
        }

        if (setSum == targetSum && !isSubsetInListOfSubsets(currentSet, subsetsSet)) {
            subsetsSet.push_back(currentSet);
        }
    }

    // TODO Do weryfickaji najlepszy siasiad i losowy
    void hillClimbDeterministic() {
        std::cout << "\n NAJLEPSZE ROZWIAZANIE: ";
        showVectorNumbers(subsetsSet[0]);
    }

    void hillClimbRandom() {
        srand(time(NULL));
        int index = std::rand() % (subsetsSet.size()-1);

        std::cout << "\n LOSOWE ROZWIAZANIE: ";
        showVectorNumbers(subsetsSet[index]);
    }

public:
    HillClimbing(const std::vector<int>& set, int target) {
        this->numbersSet = set;
        this->targetSum = target;
    }

    void getHillClimb() {
        while (subsetsSet.size() < 9) {
            hillClimb();
        }
        showVectorsInVector(subsetsSet);

        hillClimbDeterministic();
        hillClimbRandom();
    }
};

#endif //METAHEURYSTYKA_HILL_CLIMBING_H
