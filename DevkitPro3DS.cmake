set(CMAKE_SYSTEM_NAME Generic)


macro(msys_to_cmake_path MsysPath ResultingPath)
  string(REGEX REPLACE "^/([a-zA-Z])/" "\\1:/" ${ResultingPath} "${MsysPath}")
endmacro()

include(CMakeForceCompiler)
# Prefix detection only works with compiler id "GNU"
# CMake will look for prefixed g++, cpp, ld, etc. automatically
msys_to_cmake_path("$ENV{DEVKITARM}" DEVKITARM)
msys_to_cmake_path("$ENV{DEVKITPRO}" DEVKITPRO)
#set(DEVKITARM "$ENV{DEVKITARM}")

SET(CMAKE_FIND_ROOT_PATH ${DEVKITARM} ${DEVKITPRO}/libctru)

CMAKE_FORCE_C_COMPILER("${DEVKITARM}/bin/arm-none-eabi-gcc.exe" GNU)
CMAKE_FORCE_CXX_COMPILER("${DEVKITARM}/bin/arm-none-eabi-g++.exe" GNU)

include_directories(${DEVKITARM}/include ${DEVKITPRO}/libctru/include)
link_directories(${DEVKITARM}/lib ${DEVKITPRO}/libctru/lib)

set(WITH_PORTLIBS ON CACHE BOOL "use portlibs ?")

if(WITH_PORTLIBS)
  include_directories(${DEVKITPRO}/portlibs/3ds/include)
  link_directories(${DEVKITPRO}/portlibs/3ds/lib)
  set(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH} ${DEVKITPRO}/portlibs)
endif()

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

SET(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Shared libs not available" )
SET(DCMAKE_EXE_LINKER_FLAGS "-static")

set(ARCH "-march=armv6k -mtune=mpcore -mfloat-abi=hard ")
set(CMAKE_C_FLAGS "-DARM11 -D_3DS -fomit-frame-pointer -ffast-math -mword-relocations ${ARCH}" CACHE STRING "C flags" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}  -fno-rtti -fno-exceptions -std=gnu++11" CACHE STRING "CXX flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-specs=3dsx.specs ${ARCH}" CACHE STRING "linker flags" FORCE)
