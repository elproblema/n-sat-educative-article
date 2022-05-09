cmake_minimum_required(VERSION 3.20)
project(IVR)

set(CMAKE_CXX_STANDARD 14)
include_directories(minisat-master)

add_executable(SAT n-sat.cpp)
add_executable(FORCE bruteforce.cpp)
add_executable(GENETIC genetic.cpp)

add_subdirectory(minisat)

target_link_libraries(SAT MiniSat::libminisat)