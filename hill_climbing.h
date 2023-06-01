#ifndef METAHEURYSTYKA_HILL_CLIMBING_H
#define METAHEURYSTYKA_HILL_CLIMBING_H

#include <iostream>
#include <vector>
#include <numeric>

#include "utils.h"

class HillClimbing {
private:
    std::vector<int> numbersSet;
    std::vector<std::vector<int>> subsetsSet = {};
    int targetSum = 0;


    std::vector<int> generateNeighborSubset(const std::vector<int>& subset) {
        // creating a neighbor subset
        // W kontekście problemu „podzbiór sąsiadów” odnosi się do zmodyfikowanej wersji oryginalnego podzbioru w celu znalezienia lepszego rozwiązania.
        // Celem generowania podzbioru sąsiadów jest zbadanie alternatywnych rozwiązań i przejście do lepszego rozwiązania w przestrzeni wyszukiwania.
        std::vector<int> neighborSubset = subset;
        // dzieki module nie przekroczymy zakresu listy
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

            if (abs(neighborSum - targetSum) < abs(setSum - targetSum)) {
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

public:
    HillClimbing(const std::vector<int>& set, int targetSum) {
        this->numbersSet = set;
        this->targetSum = targetSum;
    }

    void getHillClimb() {
        // na ten moment zdefiniowalem ze bede szukal 9 rozwiazan, poniewaz jest to maksymalna liczba rozwiazan dla wyniku 8.
        // [ [ 1 2 5 ] [ 2 6 ] [ 1 7 ] [ 8 ] [ 3 5 ] [ 5 1 2 ] [ 1 3 4 ] [ 7 1 ] [ 2 5 1 ] ]
        while (subsetsSet.size() < 9) {
            hillClimb();
        }
        showVectorsInVector(subsetsSet);
    }
};

#endif //METAHEURYSTYKA_HILL_CLIMBING_H
