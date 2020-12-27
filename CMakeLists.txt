cmake_minimum_required(VERSION 3.17)
project(practice-tsp)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-std=c++20 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -fopenmp")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3 -fopenmp")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

add_subdirectory(random)
add_subdirectory(utility)
add_subdirectory(simple_solver)
add_subdirectory(preprocessing)

add_executable(route_builder simple_tsp.cpp)
target_link_libraries(route_builder xor_shift utility simple_solver simple_preprocessing)

#[[
set_target_properties( route_builder
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../"
)
]]
