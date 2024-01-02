cmake_minimum_required(VERSION 3.26)
project(SmartCalc_v1_0 C)

set(CMAKE_C_STANDARD 11)

add_executable(SmartCalc_v1_0
        src/s21_smart_calc.c
        src/stack.c
        src/smart_calc.h
        src/parser.c
        src/tests/stack.c
        src/tests/tests.h
        src/get_elem_from_string.c)
