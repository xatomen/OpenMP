cmake_minimum_required(VERSION 3.28)
project(OpenMP)

#Buscar libreria
find_package(OpenMP REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(OpenMP main.cpp)

#Si la encuentra, linkear
if(OpenMP_CXX_FOUND)
    target_link_libraries(OpenMP PUBLIC OpenMP::OpenMP_CXX)
endif()