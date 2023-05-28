#include <iostream>
#include <vector>
#include <numeric>

class SubsetSum {
private:
    std::vector<int> listOfNumbers;
    std::vector<std::vector<int>> listOfSums = {};
    int targetSum = 0;

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

    std::vector<int> generateRandomSubset() {
        // creating a random subset
        std::vector<int> subset;
        for (int num : listOfNumbers) {
            if (std::rand() % 2) {
                subset.push_back(num);
            }
        }
        return subset;
    }

    std::vector<int> generateNeighborSubset() {
        // creating a neighbor subset
        // W kontekście problemu „podzbiór sąsiadów” odnosi się do zmodyfikowanej wersji oryginalnego podzbioru w celu znalezienia lepszego rozwiązania.
        // Celem generowania podzbioru sąsiadów jest zbadanie alternatywnych rozwiązań i przejście do lepszego rozwiązania w przestrzeni wyszukiwania.
        std::vector<int> neighborSubset = listOfNumbers;
        // dzieki module nie przekroczymy zakresu listy
        int randomIndex = std::rand() % listOfNumbers.size();


        if (std::find(neighborSubset.begin(), neighborSubset.end(), listOfNumbers[randomIndex]) == neighborSubset.end()) {
            neighborSubset.push_back(listOfNumbers[randomIndex]);
        } else {
            neighborSubset.erase(std::remove(neighborSubset.begin(), neighborSubset.end(), listOfNumbers[randomIndex]), neighborSubset.end());
        }

        return neighborSubset;
    }

    int calculateSubsetSum(const std::vector<int>& subset) {
        int sum = 0;
        for (int num : subset) {
            sum += num;
        }
        return sum;
    }

    std::vector<int> hillClimb() {
        std::vector<int> currentSet = listOfNumbers;
        int setSum = calculateSubsetSum(listOfNumbers);

        while (setSum != targetSum) {
            std::vector<int> neighborSubset = generateNeighborSubset();
            int neighborSum = calculateSubsetSum(neighborSubset);

            if (abs(neighborSum - targetSum) < abs(setSum - targetSum)) {
                currentSet = neighborSubset;
                setSum = neighborSum;
            }
        }
        showVectorNumbers(currentSet);
        return currentSet;
    }

public:
    SubsetSum(const std::vector<int>& numberSet, int num) {
        listOfNumbers = numberSet;
        targetSum = num;
    }

    void getHillClimb() {
        showVectorNumbers(hillClimb());
    }

};

int main() {
    std::vector<int> list_of_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    SubsetSum subsetSum(list_of_numbers, 8);
    subsetSum.getHillClimb();

    return 0;
}