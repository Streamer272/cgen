cmake_minimum_required(VERSION 3.22)
project(cgen C)

set(CMAKE_C_STANDARD 11)

add_executable(cgen
        src/main.c
        src/string_funcs.c src/string_funcs.h
        src/alloc.c src/alloc.h)
