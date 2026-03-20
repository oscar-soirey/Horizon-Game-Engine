cmake_minimum_required(VERSION 3.31)
project(example)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

include_directories(src)
include_directories(third_party)

add_library(example SHARED
        module.cpp
        src/player.cpp
)


find_package(OpenGL REQUIRED)

add_library(hrl STATIC IMPORTED)
set_target_properties(hrl PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libhrls.dll.a")

add_library(hge STATIC IMPORTED)
set_target_properties(hge PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libhge.dll.a")


target_link_libraries(example PRIVATE
        hge
        hrl
        OpenGL::GL
)