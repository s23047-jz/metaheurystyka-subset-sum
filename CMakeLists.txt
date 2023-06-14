cmake_minimum_required(VERSION 3.24.2)
project(metaheurystyka)

set(CMAKE_CXX_STANDARD 20)

add_executable(metaheurystyka main.cpp headers/hill_climbing.h headers/tabu_search.h headers/simulated_annealing.h headers/ag.h sources/utils.cpp sources/hill_climbing.cpp sources/tabu_search.cpp sources/simulated_annealing.cpp sources/ag.cpp)
