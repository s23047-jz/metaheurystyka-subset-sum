#ifndef METAHEURYSTYKA_UTILS_H
#define METAHEURYSTYKA_UTILS_H

#include <iostream>
#include <vector>


void showVector(std::vector<int> v) {
    std::cout << "[ ";
    for (auto number : v) {
        std::cout << number << " ";
    }
    std::cout << "] ";
}

void showVectorsInVector(std::vector<std::vector<int>> v) {
    std::cout << "[ ";
    for (const auto& vec : v) {
        showVector(vec);
    }
    std::cout << "]";
}

bool isSubsetInListOfSubsets(const std::vector<int>& s, const std::vector<std::vector<int>>& listOfSubsets) {
    for (const auto& subset : listOfSubsets) {
        if (s.size() == subset.size() && std::equal(s.begin(), s.end(), subset.begin())) {
            return true;
        }
    }
    return false;
}

bool isVectorEqualVector(const std::vector<int>& v1, const std::vector<int>& v2) {
    return v1.size() == v2.size() && std::equal(v1.begin(), v1.end(), v2.begin());
}

int calculateSubsetSum(const std::vector<int>& subset) {
    return std::accumulate(subset.begin(), subset.end(), 0);
}

std::vector<int> convertFromPseudoBinaryToSubset(const std::vector<int>& pseudoBinarySet, const std::vector<int>& numbersSet) {
    std::vector<int> convertedSet;

    for (int i=0; i<pseudoBinarySet.size(); i++) {
        if (pseudoBinarySet[i] == 1) {
            convertedSet.push_back(numbersSet[i]);
        }
    }
    return convertedSet;
}

std::vector<std::vector<int>> generateCombinations(const std::vector<int>& numbers) {
    std::vector<std::vector<int>> result;

    // definiujemy dlugosc binarna
    int maxCombinations = 1 << numbers.size();

    for (int i = 0; i < maxCombinations; ++i) {
        std::vector<int> combination;

        for (int j = 0; j < numbers.size(); ++j) {
            if ((i >> j) & 1) {
                combination.push_back(1);
            } else {
                combination.push_back(0);
            }
        }

        result.push_back(combination);
    }

    return result;
}

std::vector<int> generateNeighborsForSubset(std::vector<int> pseudoBinary, int index) {
    std::vector<int> neighborSubset = pseudoBinary;

    if (neighborSubset[index] == 1) {
        neighborSubset[index] = 0;
    } else {
        neighborSubset[index] = 1;
    }

    if (!isVectorEqualVector(neighborSubset, pseudoBinary)) {
        std::cout << "Neighbor subset: ";
        showVector(neighborSubset);
        std::cout << std::endl << "=====================" << std::endl;

        return neighborSubset;
    }
}

#endif //METAHEURYSTYKA_UTILS_H
