cmake_minimum_required(VERSION 3.31)
project(hge)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

include_directories(src)
include_directories(third_party)

find_package(Python REQUIRED)


file(GLOB_RECURSE BOX2D_SOURCES "third_party/box2d/*.c")



###Compile static library###
add_library(hge SHARED
        #third-party
        third_party/inih/ini.c
        third_party/tinyxml2/tinyxml2.cpp
        ${BOX2D_SOURCES}

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

        #physics
        src/physics/world.cpp

        #std
        src/std-private/std_module.cpp
        src/std-private/light_actor.cpp
)


#compile dll declspec export
target_compile_definitions(hge PRIVATE ENGINE_BUILD_DLL)

target_include_directories(hge PUBLIC include/)

target_include_directories(hge PRIVATE third_party)

#link opengl
find_package(OpenGL REQUIRED)


add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libglfw3.a")

add_library(hrl STATIC IMPORTED)
set_target_properties(hrl PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libhrldll.dll.a")


#link hrl en attendant une version plus stable de hrl (pour ensuite compiler les fichiers hrl dans le projet)
target_link_libraries(hge PUBLIC
        hrl
        glfw
        OpenGL::GL
)