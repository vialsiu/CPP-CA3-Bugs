cmake_minimum_required(VERSION 3.30)
project(BugsLife)

set(CMAKE_CXX_STANDARD 20)

add_executable(BugsLife main.cpp
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
)
