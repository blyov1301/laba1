cmake_minimum_required(VERSION 3.10)
project(TextRestricter VERSION 1.0.0)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Опции для сборки
option(BUILD_TESTS "Build tests" ON)
option(BUILD_DEB_PACKAGE "Build deb package" OFF)

# Включаем директории с заголовками
include_directories(${CMAKE_SOURCE_DIR}/include)

# Основная библиотека
add_library(text_restricter_lib STATIC
    src/text_restricter.cpp
)

# Основная исполняемая программа
add_executable(text_restricter_demo src/text_restricter.cpp)

# Если нужны тесты
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Установка для deb-пакета
install(TARGETS text_restricter_lib text_restricter_demo
    RUNTIME DESTINATION /usr/local/bin
    LIBRARY DESTINATION /usr/local/lib
    ARCHIVE DESTINATION /usr/local/lib
)

install(FILES include/text_restricter.hpp DESTINATION /usr/local/include)
