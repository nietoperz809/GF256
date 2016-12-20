cmake_minimum_required(VERSION 3.6)
project(GF256)

set(SOURCE_FILES
        galois.c
        main.c)

add_executable(GF256 ${SOURCE_FILES})
