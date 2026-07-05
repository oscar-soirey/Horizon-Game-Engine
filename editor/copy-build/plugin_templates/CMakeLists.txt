cmake_minimum_required(VERSION 3.31)
project(new_plugin)

include_directories(include)

set(CMAKE_CXX_STANDARD 20)

add_library(new_plugin SHARED
        new_plugin.cpp
)

set_target_properties(new_plugin PROPERTIES
        PREFIX ""
        OUTPUT_NAME "new_plugin"
)