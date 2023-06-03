#ifndef METAHEURYSTYKA_UTILS_H
#define METAHEURYSTYKA_UTILS_H

#include <iostream>
#include <vector>


void showVectorNumbers(std::vector<int> v) {
    std::cout << "[ ";
    for (auto number : v) {
        std::cout << number << " ";
    }
    std::cout << "] ";
}

void showVectorsInVector(std::vector<std::vector<int>> v) {
    std::cout << "[ ";
    for (const auto& vec : v) {
        showVectorNumbers(vec);
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

std::vector<int> generateRandomSubset(std::vector<int> currentSet) {
    std::vector<int> subset;
    for (int num : currentSet) {
        if (std::rand() % 2) {
            subset.push_back(num);
        }
    }
    return subset;
}

#endif //METAHEURYSTYKA_UTILS_H
