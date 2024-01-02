cmake_minimum_required(VERSION 3.26)
project(SmartCalc_v1_0 C)

set(CMAKE_C_STANDARD 11)

add_executable(SmartCalc_v1_0
        src/s21_smart_calc.c
        src/stack.c
        src/smart_calc.h
        src/parser.c
        src/get_elem_from_string.c
        src/tests/tests.h
        src/tests/test_stack.c
)

target_link_libraries(SmartCalc_v1_0 check m)