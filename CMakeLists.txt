cmake_minimum_required(VERSION 3.25)
project(metaheurystyka)

set(CMAKE_CXX_STANDARD 20)

add_executable(metaheurystyka main.cpp tabu_search.h simulated_annealing.h)
