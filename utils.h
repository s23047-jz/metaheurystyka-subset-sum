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

int calculateSubsetSum(const std::vector<int>& subset) {
    return std::accumulate(subset.begin(), subset.end(), 0);

}

std::vector<int> generateZeroOneSetForSubset(const std::vector<int>& subset, const std::vector<int>& numbersSet) {
    std::vector<int> neighborSubset(numbersSet.size(), 0);;

    for (int num : subset) {
        auto isIn = std::find(numbersSet.begin(), numbersSet.end(), num);
        if (isIn != numbersSet.end()) {
            // std::distance  Jesli element zostal znaleziony szukamy indexu
            int index = std::distance(numbersSet.begin(), isIn);
            neighborSubset[index] = 1;
        }
    }

    return neighborSubset;
}

std::vector<std::vector<int>> generateCombinations(const std::vector<int>& numbers) {
    std::vector<std::vector<int>> result;
    int size = numbers.size();
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            std::vector<int> combination;
            for (int k = i; k <= j; k++) {
                combination.push_back(numbers[k]);
            }
            if (!isSubsetInListOfSubsets(combination, result)) {
                result.push_back(combination);
            }
        }
    }
    return result;
}

#endif //METAHEURYSTYKA_UTILS_H