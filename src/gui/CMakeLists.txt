
cmake_minimum_required(VERSION 3.5)
project(SmartCalc VERSION 0.1 LANGUAGES C CXX)
#project(SmartCalc VERSION 0.1 LANGUAGES CXX)
#project(calc_polish VERSION 0.1 LANGUAGES C)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -std=c11")
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets PrintSupport REQUIRED)

set (TEST_PART
        ../backend/tests/test.h
        ../backend/tests/test.c
        ../backend/tests/test_parser.c
        ../backend/tests/test_stack.c
        ../backend/tests/test_check_parsed.c
        ../backend/tests/test_calc_polish_n.c
)
set(BACK_LIB
        ../backend/calc_polish_n.c
        ../backend/check_parsed_str.c
        ../backend/parser.c
        ../backend/polish_notation.c
        ../backend/stack.c
        ../backend/stack.h
)

set(PROJECT_SOURCES
        ../main.cpp
        smartcalc.cpp
        smartcalc.h
        smartcalc.ui
        qcustomplot.h
        qcustomplot.cpp

)

add_library(calc_polish STATIC  ${BACK_LIB} )
target_link_libraries(calc_polish subunit m)
#set_source_files_properties(${BACK_LIB} PROPERTIES LANGUAGE C)
#
#set_target_properties(calc_polish PROPERTIES PUBLIC_HEADER backend/stack.h)
#install(TARGETS calc_polish
#        LIBRARY DESTINATION ${backend_lib}
#        PUBLIC_HEADER DESTINATION ${backend/})
#add_executable(Test
#        ${TEST_SOURCES}
#)
#
if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalc
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
else ()
    add_executable(SmartCalc
            ${PROJECT_SOURCES}
    )

endif ()
#set_target_properties(SmartCalc PROPERTIES LANGUAGE CXX) # LINKER_LANGUAGE C)
#set_target_properties(calc_polish PROPERTIES LINKER_LANGUAGE C)
#set_target_properties(calc_polish PROPERTIES LANGUAGE C)
#set_target_properties(Only_Back PROPERTIES LANGUAGE C)

#add_executable(Only_Back
#        ${BACK_LIB} ../backend/s21_smart_calc_back.c
#)
add_executable(Back_test
        ${TEST_PART}  ${BACK_LIB}
)
target_link_libraries(SmartCalc   PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport
        /usr/lib/x86_64-linux-gnu/libQt5PrintSupport.so.5.15.10
        /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.10
        /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.10
        /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.10
        PUBLIC  calc_polish

)
set_target_properties(SmartCalc PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
target_link_libraries(Back_test check subunit m)

#target_link_libraries(Only_Back subunit m)











