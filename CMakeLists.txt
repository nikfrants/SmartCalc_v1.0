cmake_minimum_required(VERSION 3.26)
project(SmartCalc_v1_0 C)

set(CMAKE_C_STANDARD 11)

add_executable(SmartCalc_v1_0
        src/s21_smart_calc.c
        src/stack.c
        src/smart_calc.h
        src/parser.c
#        src/get_elem_from_string.c
)

# Определяем исполняемый файл для тестов
add_executable(Test_SmartCalc_v1_0
        src/tests/test.c
        src/tests/test.h
        src/tests/test_stack.c
        src/stack.c
        src/smart_calc.h
        src/parser.c
#        src/get_elem_from_string.c
)

# Создаём тест
add_test(NAME smartcalc_tests COMMAND Test_SmartCalc_v1_0)

# Связываем библиотеку check и libm с исполняемым файлом тестов
target_link_libraries(Test_SmartCalc_v1_0 check subunit m)
