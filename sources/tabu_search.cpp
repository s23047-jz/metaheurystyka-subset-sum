#include "../headers/tabu_search.h"


Neighbor::~Neighbor() {
    this->psudoBinarySet = std::vector<int>();
    this->sum = 0;

    std::cout <<"Neighbor called destructor" << std::endl;
};

Neighbor::Neighbor(std::vector<int> psudoBinarySet, int sum) {
    this->psudoBinarySet = psudoBinarySet;
    this->sum = sum;
}

std::vector<int> Neighbor::getPsudoBinarySet() {
    return psudoBinarySet;
}

int Neighbor::getSum() {
    return sum;
}

void Neighbor::showNeighbor() {
    showVector(psudoBinarySet);
    std::cout << " SUM: " << sum << std::endl;
}


TabuSearch::~TabuSearch() {
    tabuList.clear();
    tabuListNeiborhood.clear();
    neighborList.clear();
    tabuHistory.clear();
    startPoint.clear();
    numbersSet.clear();
    this->tabuLimit = 1;
    this->targetSum = 0;

    std::cout <<"TabuSearch called destructor" << std::endl;
};

TabuSearch::TabuSearch(const std::vector<int> &set, const std::vector<int> &startPoint, int target, int tabuLimit) {
    this->numbersSet = set;
    this->startPoint = startPoint;
    this->tabuLimit = tabuLimit;
    this->targetSum = target;
}


void TabuSearch::generateNeighborList() {
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

std::vector<int> TabuSearch::fitConvert(std::vector<int> v) {
    return convertFromPseudoBinaryToSubset(v, numbersSet);
}

void TabuSearch::addBestNeighborToTabu() {
    generateNeighborList();
    std::vector<int> bestNeighbor;
    int bestNeighborSum = 0;
    for (int i = 0; i < neighborList.size(); i++) {
        if (!isSubsetInListOfSubsets(neighborList[i], tabuList)) {
            bestNeighbor = neighborList[i];
            bestNeighborSum = calculateSubsetSum(fitConvert(bestNeighbor));
            break;
        }
    }

    for (int i = 0; i < neighborList.size(); i++) {
        if (!isSubsetInListOfSubsets(neighborList[i], tabuList)) {
            int neighborSum = calculateSubsetSum(fitConvert(neighborList[i]));

            int neighborDistance = std::abs(targetSum - neighborSum);
            int bestNeighborDistance = std::abs(targetSum - bestNeighborSum);

            if (neighborDistance < bestNeighborDistance) {
                bestNeighbor = neighborList[i];
                bestNeighborSum = neighborSum;
            }
        }
    }

    if (!bestNeighbor.empty()) {
        std::cout << " SUM: " << bestNeighborSum << " BEST NEIGHBOR: ";
        showVector(bestNeighbor);
        std::cout << std::endl;
    }


    if (bestNeighbor.empty()) {

        std::cout << "No best neighbor found" << std::endl;
        tabuHistory.pop_back();
        if (tabuHistory.size() > 1) {
            showVectorsInVector(tabuHistory);
            startPoint = tabuHistory[tabuHistory.size() - 1];
        }
        else {
            stopTabuSearch = true;
        }
    } else if (!bestNeighbor.empty() && !isSubsetInListOfSubsets(bestNeighbor, tabuList)) {
        tabuList.push_back(bestNeighbor);
        Neighbor ng = Neighbor(bestNeighbor, bestNeighborSum);
        tabuListNeiborhood.push_back(ng);
        neighborList.clear();
        tabuHistory.push_back(bestNeighbor);
        startPoint = tabuHistory[tabuHistory.size() - 1];
    }

    if (tabuLimit != 0 && tabuList.size() == tabuLimit) {
        stopTabuSearch = true;
    }
}

void TabuSearch::initTabuSearch() {

    tabuList.push_back(startPoint);
    tabuHistory.push_back(startPoint);
    std::cout << "=======SSSSSSSSS========" << std::endl;
    showVectorsInVector(tabuHistory);
    while (!stopTabuSearch) {
        addBestNeighborToTabu();
    }
}

std::vector<std::vector<int>> TabuSearch::getTabuList() {
    initTabuSearch();
    std::cout << "Tabu list: ";
    showVectorsInVector(tabuList);
    std::cout << std::endl;
    std::cout << " TABU LIST SIZE: " << tabuList.size() << std::endl;

    std::cout << "FINAL Tabu list: ";
    for (auto ng: tabuListNeiborhood) {
        ng.showNeighbor();
    }
    std::cout << std::endl;


    return tabuList;
}
