project(Ising_model CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-D DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(Ising_system_test test_for_Ising_system.cpp)
add_executable(spin_test test_for_spin.cpp)
add_executable(system_initializer_func_test test_for_system_initializer_func.cpp)
