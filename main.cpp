#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

class SubsetSum {
private:
    std::vector<int> list_of_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<std::vector<int>> list_of_sums = {};
    int looking_sum_n = 0;

    void hill_climb() {

    }

    void show_vectors_in_vector(std::vector<std::vector<int>> v) {
        std::cout << "[ ";
        for (const auto& vec : v) {
            show_vector_numbers(vec);
        }
        std::cout << "]";
    }

    void show_vector_numbers(std::vector<int> v) {
        std::cout << "[ ";
        for (auto number : v) {
            std::cout << number << " ";
        }
        std::cout << "] ";
    }
public:
    SubsetSum(int looking_sum_number) {
        looking_sum_n = looking_sum_number;
    }

    void get_hill_climb() {
        std::cout << std::accumulate(list_of_numbers.begin(), list_of_numbers.end(), looking_sum_n);
    }

};

int main() {
    SubsetSum subsetSum(6);
    subsetSum.get_hill_climb();

    return 0;
}
