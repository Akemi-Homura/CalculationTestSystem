cmake_minimum_required(VERSION 2.8)
project(CalculationTestSystem C)

add_executable(main main.c)

target_link_libraries(main curses)
