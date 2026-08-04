cmake_minimum_required(VERSION 3.16)
project(sudoku LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(sudoku 
    src/main.cpp
    src/board.cpp
    src/solver.cpp
    src/cell.cpp)

target_include_directories(sudoku PRIVATE include)
target_link_libraries(sudoku sfml-graphics sfml-window sfml-system)
