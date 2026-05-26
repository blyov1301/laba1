cmake_minimum_required(VERSION 3.10)
project(StrategyPattern VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)

# Основная программа
add_executable(strategy_demo main.cpp)

# Тестовая программа
add_executable(test_runner test.cpp)

# Включаем тестирование
enable_testing()
add_test(NAME StrategyTest COMMAND test_runner)

# Настройка DEB пакета
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "strategy-pattern-demo")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "Strategy Pattern Demo - Text Restriction")
include(CPack)
