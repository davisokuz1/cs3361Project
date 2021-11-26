cmake_minimum_required(VERSION 3.20)
project(cs3361Project)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")


add_executable(cs3361Project
        main.cpp)
