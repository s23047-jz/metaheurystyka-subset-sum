#ifndef METAHEURYSTYKA_UTILS_H
#define METAHEURYSTYKA_UTILS_H

#include <iostream>
#include <vector>


void showVector(std::vector<int> v);

void showVectorsInVector(std::vector<std::vector<int>> v);

bool isSubsetInListOfSubsets(const std::vector<int>& s, const std::vector<std::vector<int>>& listOfSubsets);

bool isVectorEqualVector(const std::vector<int>& v1, const std::vector<int>& v2);

int calculateSubsetSum(const std::vector<int>& subset);

std::vector<int> convertFromPseudoBinaryToSubset(const std::vector<int>& pseudoBinarySet, const std::vector<int>& numbersSet);

std::vector<std::vector<int>> generateCombinations(const std::vector<int>& numbers);

std::vector<int> generateNeighborsForSubset(std::vector<int> pseudoBinary, int index);

#endif //METAHEURYSTYKA_UTILS_H
