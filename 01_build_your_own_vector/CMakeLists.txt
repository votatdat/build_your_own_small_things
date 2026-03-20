cmake_minimum_required(VERSION 3.16)
project(build_your_own_vector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(vector_tests
    # tests/test_int_vector.cpp
    # src/int_vector.cpp    
    tests/test_vector.cpp
)

target_include_directories(vector_tests PRIVATE
    include
    tests
)