cmake_minimum_required(VERSION 2.8)
project(LUIB CXX)
SET(BUILD_SHARED_LIBS OFF)

include_directories( include)



file(GLOB_RECURSE SOURCE_FILES
    source/*
    include/*
)

ADD_EXECUTABLE(hello ${SOURCE_FILES})
target_link_libraries(hello sf2d ctru)