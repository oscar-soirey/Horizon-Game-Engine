cmake_minimum_required(VERSION 3.31)
project(horizon-dialogue)

include_directories(include)

set(CMAKE_CXX_STANDARD 20)

add_library(horizon-dialogue SHARED
        HorizonDialogue.cpp
)

set_target_properties(horizon-dialogue PROPERTIES
        PREFIX ""
        OUTPUT_NAME "horizon-dialogue"
)