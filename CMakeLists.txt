cmake_minimum_required(VERSION 3.5.2)
project(Vigenere)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(Vigenere
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        ${PROJECT_SOURCE_DIR}/src/functions.cpp
        )
