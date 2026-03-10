cmake_minimum_required(VERSION 3.31)
project(hge)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

include_directories(src)
include_directories(third_party)

find_package(Python REQUIRED)


###Compile static library###
add_library(hge STATIC
        #third-party
        third_party/inih/ini.c
        third_party/tinyxml2/tinyxml2.cpp

        #core
        src/core/actor.cpp
        src/core/object.cpp
        src/core/engine.cpp
        src/core/level.cpp
        src/core/common.cpp
        #private
        src/core/private/material_parser.cpp
        src/core/private/runtime_ressources.cpp

        #filesystem
        src/filesystem/filesystem.cpp
        src/filesystem/ini_parser.cpp

        #module
        src/modules/factory.cpp
        #private
        src/modules/private/system_module.cpp

        #components
        src/components/base_component.cpp
        src/components/scene_component.cpp
        src/components/camera.cpp
        src/components/sprite.cpp
        src/components/light.cpp
)

#link opengl
find_package(OpenGL REQUIRED)


add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libglfw3.a")

add_library(hrl STATIC IMPORTED)
set_target_properties(hrl PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libhrl.a")


#link hrl en attendant une version plus stable de hrl (pour ensuite compiler les fichiers hrl dans le projet)
target_link_libraries(hge PUBLIC
        hrl
        glfw
        OpenGL::GL
)