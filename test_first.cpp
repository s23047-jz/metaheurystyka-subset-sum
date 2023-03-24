#include <iostream>
#include <vector>
#include <string>
#include <array>

using vec3d = std::array<double, 3>;

vec3d operator+(const vec3d a, const vec3d b) {
    return {a[0]+b[0], a[1]+b[1], a[2]+b[2]};
}

std::ostream &operator<<(std::ostream &o, const vec3d v) {
    o << "[";
    for (auto e:v) o << e << " ";
    o << "]";
}

struct person_t {
    /* data */
    int id;
    std::string name;
};

// funkcja edytuje wartosci w tablicy
// void editInVector(std::vector<std::string> &v) {}

int main() {
    // std::vector<std::string> texts = {"ALA", "MILK", "KOT"};
    // ponizej wersja konstruktora
    // std::vector<std::string> texts(3, "Jakis text");

    // for (auto &element: texts) {
        //Dodajac ampersanta '&' edytujemy, nadpisuje, bez tego nie nadpiszemy wartosci!
        // element = "<<" + element + ">>";
    // }

    // for (auto &element: texts) {
    //     std::cout << element;
    // }

    // std::map<std::string, int> numbers = {{"DWA", 2}, {"JEDEN", 1}};
    // numbers["TRZY"] = 3;

    // for (auto [key, val]: numbers) {}

    person_t person;

    return 0;
}