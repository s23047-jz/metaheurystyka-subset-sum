#include "../headers/hill_climbing.h"


HillClimbing::~HillClimbing() {
    this->numbersSet = std::vector<int>();
    this->targetSum = 0;
    this->maxIteration = 0;
    std::cout <<"HillClimbing called destructor" << std::endl;
};

HillClimbing::HillClimbing(const std::vector<int> &set, int target, int iteration) {
    this->numbersSet = set;
    this->targetSum = target;
    this->maxIteration = iteration;
}

std::vector<int> HillClimbing::fitConvert(std::vector<int> v) {
    return convertFromPseudoBinaryToSubset(v, numbersSet);
}

std::vector<int> HillClimbing::getRandomSolution() {
    std::vector<std::vector<int>> allCombinationsSet = generateCombinations(numbersSet);
    std::cout << "==========================================" << std::endl;
    showVectorsInVector(allCombinationsSet);
    std::cout << std::endl;
    std::cout << " COMBINATIONS SIZE: " << allCombinationsSet.size() << std::endl;

    std::uniform_int_distribution<int> dist(0, allCombinationsSet.size() - 1);
    int randomIndex = dist(rgen);

    std::vector<int> randomSolution = allCombinationsSet[randomIndex];
    std::cout << "Selected Index: " << randomIndex << std::endl;
    std::cout << "Selected random solution: ";
    showVector(randomSolution);
    std::cout << std::endl;

    return randomSolution;
}

std::vector<int> HillClimbing::getRandomSolutionPseudoBinaryWithNeighbors() {
    std::vector<int> randomSolutionPseudoBinary = getRandomSolution();

    std::cout << "psudo binary for random solution: ";
    showVector(randomSolutionPseudoBinary);
    std::cout << std::endl;

    int index = 0;
    while (neighborSubsetsSet.size() < numbersSet.size()) {

        std::vector<int> neighborPseudoBinarySubset = generateNeighborsForSubset(randomSolutionPseudoBinary, index);
        if (index < randomSolutionPseudoBinary.size()) {
            index++;
        } else {
            index = 0;
        }
        if (!isSubsetInListOfSubsets(neighborPseudoBinarySubset, neighborSubsetsSet)) {
            neighborSubsetsSet.push_back(neighborPseudoBinarySubset);
        }
    }
    std::cout << "Neighbor full subsets: ";
    showVectorsInVector(neighborSubsetsSet);
    std::cout << std::endl;

    return randomSolutionPseudoBinary;
}

std::vector<std::vector<int>> HillClimbing::generateNeighborsForPseudoSubset(std::vector<int> currentBest) {
    std::vector<std::vector<int>> newNeighbors;

    for (int i = 0; i < currentBest.size(); i++) {
        std::vector<int> newNeighbor = generateNeighborsForSubset(currentBest, i);
        newNeighbors.push_back(newNeighbor);
    }

    std::cout << "Neighbor full subsets: ";
    showVectorsInVector(newNeighbors);
    std::cout << std::endl;

    return newNeighbors;
}

std::vector<int> HillClimbing::getBestNeighbor(std::vector<int> bestSubset, std::vector<std::vector<int>> neighborSubsets) {
    std::vector<int> bestNeighbor = bestSubset;
    int sum = calculateSubsetSum(fitConvert(bestNeighbor));
    int distance = std::abs(targetSum - sum);

    for (auto neighbor: neighborSubsets) {
        int neighborSum = calculateSubsetSum(fitConvert(neighbor));
        int neighborDistance = std::abs(targetSum - neighborSum);
        if (neighborDistance < distance) {
            std::cout << "!!! CHANGING !!!!" << std::endl;
            bestNeighbor = neighbor;
            distance = neighborDistance;
        }

        showVector(neighbor);
        std::cout << " SUM: " << neighborSum << " DISTANCE: " << neighborDistance << " " << "targetSum: " << targetSum
                  << std::endl;
    }

    return bestNeighbor;
}

std::vector<int> HillClimbing::getRandomBest(std::vector<int> bestSubset, std::vector<std::vector<int>> neighborSubsets) {
    std::vector<int> bestNeighbor = bestSubset;
    int sum = calculateSubsetSum(fitConvert(bestNeighbor));
    int distance = std::abs(targetSum - sum);

    for (auto neighbor: neighborSubsets) {
        int neighborSum = calculateSubsetSum(fitConvert(neighbor));
        int neighborDistance = std::abs(targetSum - neighborSum);
        if (neighborDistance < distance) {
            std::cout << "!!! CHANGING AND BREAK !!!!" << std::endl;
            bestNeighbor = neighbor;
            distance = neighborDistance;

            showVector(neighbor);
            std::cout << " SUM: " << neighborSum << " DISTANCE: " << neighborDistance << " " << "targetSum: "
                      << targetSum << std::endl;

            break;
        }
    }

    return bestNeighbor;
}

std::vector<int> HillClimbing::getDeterministicBestHillClimb() {
    std::vector<int> randomSolutionPseudoBinary = getRandomSolutionPseudoBinaryWithNeighbors();
    std::vector<std::vector<int>> currentNeighbors = neighborSubsetsSet;
    std::vector<int> bestNeighbor = getBestNeighbor(randomSolutionPseudoBinary, currentNeighbors);

    int iteration = 0;
    while (iteration < maxIteration) {
        currentNeighbors = generateNeighborsForPseudoSubset(bestNeighbor);
        bestNeighbor = getBestNeighbor(bestNeighbor, currentNeighbors);
        iteration++;
    }

    std::cout << "Best neighbor: ";
    showVector(bestNeighbor);
    std::cout << std::endl;

    std::cout << "BEST neighbor SUM: ";
    std::cout << calculateSubsetSum(fitConvert(bestNeighbor)) << std::endl;

    return bestNeighbor;
}

std::vector<int> HillClimbing::getDeterministicRandomHillClimb() {
    std::vector<int> randomSolutionPseudoBinary = getRandomSolutionPseudoBinaryWithNeighbors();
    std::vector<std::vector<int>> currentNeighbors = neighborSubsetsSet;
    std::vector<int> bestNeighbor = getRandomBest(randomSolutionPseudoBinary, currentNeighbors);

    int iteration = 0;
    while (iteration < maxIteration) {
        currentNeighbors = generateNeighborsForPseudoSubset(bestNeighbor);
        bestNeighbor = getRandomBest(bestNeighbor, currentNeighbors);
        iteration++;
    }

    std::cout << "Random neighbor: ";
    showVector(bestNeighbor);
    std::cout << std::endl;

    std::cout << "Random neighbor SUM: ";
    std::cout << calculateSubsetSum(fitConvert(bestNeighbor)) << std::endl;

    return bestNeighbor;
}
