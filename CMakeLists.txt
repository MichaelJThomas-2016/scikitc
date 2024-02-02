cmake_minimum_required(VERSION 3.27)
project(scikitc C)

set(CMAKE_C_STANDARD 99)

add_library(scikitc STATIC library.c
        matrix.c
        stats.c
        utils.c
        matrix.h
        utils.h
        stats.h
)
