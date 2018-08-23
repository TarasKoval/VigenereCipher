cmake_minimum_required(VERSION 3.5.2)
project(Vigenere)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(Vigenere
        src/main.cpp
        src/functions.cpp
        include/functions.h
        )
