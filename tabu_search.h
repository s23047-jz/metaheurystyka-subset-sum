#ifndef METAHEURYSTYKA_TABU_SEARCH_H
#define METAHEURYSTYKA_TABU_SEARCH_H

#include "utils.h"


class Neiborhood {
    private:
    std::vector<int> psudoBinarySet;
    int sum;

public:
    Neiborhood(std::vector<int> psudoBinarySet, int sum) {
        this->psudoBinarySet = psudoBinarySet;
        this->sum = sum;
    }

    std::vector<int> getPsudoBinarySet() {
        return psudoBinarySet;
    }

    int getSum() {
        return sum;
    }

    void showNeiborhood() {
        showVector(psudoBinarySet);
        std::cout << " SUM: " << sum << std::endl;
    }
};


class TabuSearch {
private:
    std::vector<std::vector<int>> tabuList;
    std::vector<Neiborhood> tabuListNeiborhood;
    std::vector<int> tabuListSum;
    std::vector<std::vector<int>> neighborList;
    std::vector<int> startPoint;
    std::vector<int> numbersSet;
    int targetSum = 0;
    int tabuLimit = 0;

    int tabuListSize = tabuList.size();

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

                int neighborDistance = std::abs(targetSum - neighborSum);
                int bestNeighborDistance = std::abs(targetSum - bestNeighborSum);

                if (neighborDistance < bestNeighborDistance) {
                    bestNeighbor = neighborList[i];
                    bestNeighborSum = neighborSum;
                }
            }
        }

        std::cout << " SUM: " << bestNeighborSum << " BEST NEIGHBOR: ";
        showVector(bestNeighbor);
        std::cout << std::endl;



        if (bestNeighbor.empty()) {
            --tabuListSize;
            std::cout << "Tabu list size: " << tabuListSize << std::endl;
            bestNeighbor = tabuList[tabuListSize];
            std::cout << "///////////////////////////////////////////////////" << std::endl;

            if (isVectorEqualVector(bestNeighbor, tabuList[0])) {
                std::cout << "Finish program: " << std::endl;
                stopTabuSearch = true;
            }
        }

        if (!bestNeighbor.empty() && !isSubsetInListOfSubsets(bestNeighbor, tabuList)) {
            tabuList.push_back(bestNeighbor);
            tabuListSum.push_back(bestNeighborSum);
            startPoint = bestNeighbor;
            Neiborhood ng = Neiborhood(bestNeighbor, bestNeighborSum);
            tabuListSize = tabuList.size();
            tabuListNeiborhood.push_back(ng);
            neighborList.clear();
        }

        if (tabuLimit != 0 && tabuList.size() == tabuLimit) {
            stopTabuSearch = true;
        }
    }

    void initTabuSearch() {

        tabuList.push_back(startPoint);
        while (!stopTabuSearch) {
            addBestNeighborToTabu();
        }
    }


public :

    TabuSearch(const std::vector<int>& set, const std::vector<int>& startPoint, int target, int tabuLimit=0) {
        this->numbersSet = set;
        this->startPoint = startPoint;
        this->tabuLimit = tabuLimit;
        this->targetSum = target;
    }

    std::vector<std::vector<int>> getTabuList() {
        initTabuSearch();
        std::cout << "Tabu list: ";
        showVectorsInVector(tabuList);
        std::cout << std::endl;
        std::cout << "Tabu list: SUM:";
        showVector(tabuListSum);
        std::cout << std::endl;
        std::cout << " TABU LIST SIZE: " << tabuList.size() << std::endl;

        std::cout << "FINAL Tabu list: ";
        for (auto ng : tabuListNeiborhood) {
            ng.showNeiborhood();
        }
        std::cout<<std::endl;


        return tabuList;
    }
};

#endif //METAHEURYSTYKA_TABU_SEARCH_H
