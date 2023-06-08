#ifndef METAHEURYSTYKA_SIMULATED_ANNEALING_H
#define METAHEURYSTYKA_SIMULATED_ANNEALING_H

#include "utils.h"


class SimulatedAnnealing {
private:
    std::vector<int> numbersSet;
    std::vector<int> startPoint;



public:
    SimulatedAnnealing(const std::vector<int>& numbersSet, const std::vector<int>& startPoint) {
        this->numbersSet = numbersSet;
        this->startPoint = startPoint;
    }
};


#endif //METAHEURYSTYKA_SIMULATED_ANNEALING_H
