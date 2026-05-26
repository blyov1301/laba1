cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0.0)

# Устанавливаем C++ стандарт
set(CMAKE_CXX_STANDARD 11)

# Создаём исполняемый файл для теста
add_executable(test_runner test.cpp)

# Подключаем Google Test (автоматически скачается)
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(test_runner PRIVATE gtest_main)

# Включаем тесты
enable_testing()
add_test(NAME MyTest COMMAND test_runner)

# Настройка CPack для DEB пакета
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
include(CPack)
