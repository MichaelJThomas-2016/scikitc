cmake_minimum_required(VERSION 3.27)
project(scikitc C)

set(CMAKE_C_STANDARD 99)

add_library(scikitc STATIC
        src/matrix.c
        src/stats.c
        src/stats.h
        src/utils.c
        src/utils.h
)
