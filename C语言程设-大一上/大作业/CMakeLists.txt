cmake_minimum_required(VERSION 3.12)
project(sourcecpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(sourcecpp
        data.db
        dboperation.cpp
        dboperation.h
        includeheaders.cpp
        includeheaders.h
        main.cpp
        softio.cpp
        softio.h
        sqlite3.c
        sqlite3.h)
