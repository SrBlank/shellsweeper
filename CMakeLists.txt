cmake_minimum_required(VERSION 3.16)

project(shellsweeper VERSION 1.0.0)

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
    src/HighScores.cpp
)

target_include_directories(shellsweeper PRIVATE include)

target_link_libraries(shellsweeper ${CURSES_LIBRARIES})

install(TARGETS shellsweeper DESTINATION bin)

# ---- CPack configuration ----

set(CPACK_PACKAGE_NAME "shellsweeper")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Terminal Minesweeper built with ncurses")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "SrBlank")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libncurses6")

include(CPack)