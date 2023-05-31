#include <iostream>
#include <vector>
#include <numeric>

class SubsetSum {
private:
    std::vector<int> listOfNumbers;
    std::vector<std::vector<int>> listOfSubsets = {};
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

    std::vector<int> generateNeighborSubset(const std::vector<int>& subset) {
        // creating a neighbor subset
        // W kontekście problemu „podzbiór sąsiadów” odnosi się do zmodyfikowanej wersji oryginalnego podzbioru w celu znalezienia lepszego rozwiązania.
        // Celem generowania podzbioru sąsiadów jest zbadanie alternatywnych rozwiązań i przejście do lepszego rozwiązania w przestrzeni wyszukiwania.
        std::vector<int> neighborSubset = subset;
        // dzieki module nie przekroczymy zakresu listy
        int randomIndex = std::rand() % subset.size();


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

    bool isSubsetInListOfSums(const std::vector<int>& s) {
        for (const auto& subset : listOfSubsets) {
            if (s.size() == subset.size() && std::equal(s.begin(), s.end(), subset.begin())) {
                return true;
            }
        }
        return false;
    }

    void hillClimb() {
        std::vector<int> currentSet = generateRandomSubset();
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

        if (setSum == targetSum && !isSubsetInListOfSums(currentSet)) {
            listOfSubsets.push_back(currentSet);
        }
    }

public:
    SubsetSum(const std::vector<int>& numberSet, int num) {
        listOfNumbers = numberSet;
        targetSum = num;
    }

    void getHillClimb() {
        // na ten moment zdefiniowalem ze bede szukal 9 rozwiazan, poniewaz jest to maksymalna liczba rozwiazan dla wyniku 8.
        // [ [ 1 2 5 ] [ 2 6 ] [ 1 7 ] [ 8 ] [ 3 5 ] [ 5 1 2 ] [ 1 3 4 ] [ 7 1 ] [ 2 5 1 ] ]
        while (listOfSubsets.size() < 9) {
            hillClimb();
        }
        showVectorsInVector(listOfSubsets);
    }
};

int main() {
    std::vector<int> list_of_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    SubsetSum subsetSum(list_of_numbers, 8);
    subsetSum.getHillClimb();

    return 0;
}
