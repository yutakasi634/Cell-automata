cmake_minimum_required(VERSION 2.8)

project(Ising_model)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-D DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
find_library(GLUT_LIBRARY NAMES glut)

add_executable(Ising_model
  Ising_model.cpp)

target_link_libraries(Ising_model ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

add_subdirectory(test)
