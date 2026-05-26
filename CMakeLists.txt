cmake_minimum_required(VERSION 3.10)
project(TextRestricter)

set(CMAKE_CXX_STANDARD 17)

add_executable(text_restricter main.cpp)
add_executable(run_tests test.cpp)

enable_testing()
add_test(NAME test COMMAND run_tests)
