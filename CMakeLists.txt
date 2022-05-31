cmake_minimum_required(VERSION 3.22)
project(cgen C)

set(CMAKE_C_STANDARD 11)

add_executable(cgen
        src/main.c
        src/helpers/alloc.c src/helpers/alloc.h
        src/helpers/string_funcs.c src/helpers/string_funcs.h
        src/helpers/colors.h src/helpers/def.h
        src/utils/exec.c src/utils/exec.h
        src/utils/term.c src/utils/term.h
        src/helpers/dir.c src/helpers/dir.h
        src/commands/generate.c src/commands/generate.h
        src/commands/project.c src/commands/project.h
        src/commands/build.c src/commands/build.h
        src/utils/cmake_get.c src/utils/cmake_get.h)
