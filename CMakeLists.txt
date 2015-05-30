cmake_minimum_required(VERSION 2.8)
project(LUIB C CXX)
SET(BUILD_SHARED_LIBS OFF)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
include_directories( include )

FIND_LIBRARY(SF2D_LIBRARY sf2d NAMES libsf2d.a PATHS )

file(GLOB_RECURSE SOURCE_FILES
    source/*
    include/*
)

ADD_EXECUTABLE(hello ${SOURCE_FILES})
target_link_libraries(hello sf2d ctru)