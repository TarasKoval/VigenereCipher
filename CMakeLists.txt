cmake_minimum_required(VERSION 3.5.2)
project(Vigenere)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Vigenere_SOURCE_DIR}/build)

add_executable(Vigenere
        src/main.cpp
        src/functions.cpp
        include/functions.h
        )
