cmake_minimum_required(VERSION 3.16)

project(shellsweeper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)

add_executable(shellsweeper
    src/main.cpp
    src/Cell.cpp
    src/Board.cpp
    src/Game.cpp
    src/Renderer.cpp
    src/Settings.cpp
)

target_include_directories(shellsweeper PRIVATE include)

target_link_libraries(shellsweeper ${CURSES_LIBRARIES})