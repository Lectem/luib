cmake_minimum_required(VERSION 2.8)
project(LUIB C CXX)
SET(BUILD_SHARED_LIBS OFF)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories( include sf2dlib/libsf2d/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/sf2dlib/libsf2d/lib)
set(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH} ${CMAKE_CURRENT_SOURCE_DIR})
FIND_LIBRARY(SF2D_LIBRARY sf2d sf2dlib/libsf2d/lib)

file(GLOB_RECURSE SOURCE_FILES
    source/*
    include/*
)

ADD_EXECUTABLE(hello ${SOURCE_FILES})
target_link_libraries(hello ${SF2D_LIBRARY} ctru)