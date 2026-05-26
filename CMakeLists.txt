cmake_minimum_required(VERSION 3.10)
project(TextRestricter)

set(CMAKE_CXX_STANDARD 17)

# Основная программа
add_executable(text_restricter main.cpp)

# Тесты
add_executable(run_tests test.cpp)
add_test(NAME TextRestricterTest COMMAND run_tests)

# Включаем тестирование
enable_testing()
