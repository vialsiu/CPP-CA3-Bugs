cmake_minimum_required(VERSION 3.30)
project(BugsLife)

set(CMAKE_CXX_STANDARD 20)

add_executable(BugsLife
        main.cpp
        Crawler.cpp
        Crawler.h
        Board.cpp
        Board.h
        Bug.h
        Hopper.h
        Hopper.cpp
        Position.h
        KnightBug.cpp
        KnightBug.h
        BugLifeGUI.cpp
        BugLifeGUI.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics network REQUIRED)
include_directories("C:/SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.2/include")
target_link_libraries(BugsLife sfml-system sfml-window sfml-graphics)
