#ifndef METAHEURYSTYKA_TABU_SEARCH_H
#define METAHEURYSTYKA_TABU_SEARCH_H

#include "utils.h"

class TabuSearch {
private:
    std::vector<std::vector<int>> tabuList;
    std::vector<int> tabuListSum;
    std::vector<std::vector<int>> neighborList;
    std::vector<int> startPoint;
    std::vector<int> numbersSet;

    bool stopTabuSearch = false;

    void generateNeighborList() {
        int i = 0;
        while (i < numbersSet.size()) {
            std::vector<int> neighbor = generateNeighborsForSubset(startPoint, i);
            neighborList.push_back(neighbor);
            i++;
        }

        std::cout << "Neighbor full subsets: ";
        showVectorsInVector(neighborList);
        std::cout << std::endl;
    }

    void addBestNeighborToTabu() {
        generateNeighborList();
        std::vector<int> bestNeighbor;
        int bestNeighborSum = 0;
        for (int i = 0; i < neighborList.size(); i++) {
            if (!isSubsetInListOfSubsets(neighborList[i], tabuList)) {
                bestNeighbor = neighborList[i];
                bestNeighborSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(bestNeighbor, numbersSet));
                break;
            }
        }

        for (int i = 0; i < neighborList.size(); i++) {
            if (!isSubsetInListOfSubsets(neighborList[i], tabuList)) {
                int neighborSum = calculateSubsetSum(convertFromPseudoBinaryToSubset(neighborList[i], numbersSet));
                if (neighborSum > bestNeighborSum) {
                    bestNeighbor = neighborList[i];
                    bestNeighborSum = neighborSum;
                }
            }
        }

        std::cout << " SUM: " << bestNeighborSum << " BEST NEIGHBOR: ";
        showVector(bestNeighbor);
        std::cout << std::endl;

        if (bestNeighbor.empty()) {
            stopTabuSearch = true;
        }

        if (!bestNeighbor.empty()) {
            tabuList.push_back(bestNeighbor);
            tabuListSum.push_back(bestNeighborSum);
            startPoint = bestNeighbor;
            neighborList.clear();
        }
    }

    void initTabuSearch() {
        tabuList.push_back(startPoint);
        while (!stopTabuSearch) {
            generateNeighborList();
            addBestNeighborToTabu();
        }
    }


public :

    TabuSearch(const std::vector<int>& set, const std::vector<int>& startPoint) {
        this->numbersSet = set;
        this->startPoint = startPoint;
    }

    std::vector<std::vector<int>> getTabuList() {
        initTabuSearch();
        std::cout << "Tabu list: ";
        showVectorsInVector(tabuList);
        std::cout << std::endl;
        std::cout << "Tabu list: SUM:";
        showVector(tabuListSum);
        std::cout << std::endl;


        return tabuList;
    }
};

#endif //METAHEURYSTYKA_TABU_SEARCH_H
