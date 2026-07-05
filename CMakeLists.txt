cmake_minimum_required(VERSION 3.31)
project(hge)

project(hge
        LANGUAGES C CXX
)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options($<$<COMPILE_LANGUAGE:C>:/std:c11>)
endif()

set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

include_directories(src)
include_directories(third_party)
include_directories(third_party/Ogre/include/OGRE-Next)

find_package(Python REQUIRED)


file(GLOB_RECURSE BOX2D_SOURCES "third_party/box2d/*.c")



###Compile static library###
add_library(hge SHARED
        #third-party
        third_party/inih/ini.c
        third_party/tinyxml2/tinyxml2.cpp
        ${BOX2D_SOURCES}

        #core
        src/core/object.cpp
        src/core/actor.cpp
        src/core/character.cpp
        src/core/engine.cpp
        src/core/level.cpp
        src/core/common.cpp
        src/core/gameplay/player_controller.cpp
        src/core/gameplay/input.cpp
        #src/core/gameplay/animation_system.cpp
        #private
        src/core/private/material_parser.cpp
        src/core/private/runtime_ressources.cpp
        src/core/private/input_manager.cpp

        #filesystem
        src/filesystem/filesystem.cpp
        src/filesystem/ini_parser.cpp

        #module
        src/modules/factory.cpp
        #private
        src/modules/private/system_module.cpp

        #plugins
        src/plugins/private/system_plugin.cpp

        #components
        src/components/base_component.cpp
        src/components/scene_component.cpp
        src/components/camera.cpp
        src/components/sprite.cpp
        src/components/light.cpp
        #physics shapes
        src/components/shapes/shape.cpp
        src/components/shapes/capsule.cpp
        src/components/shapes/box.cpp
        src/components/shapes/circle.cpp

        #physics
        src/physics/world.cpp
        src/physics/private/debug_draw.cpp

        #std
        src/std-private/std_module.cpp
        src/std-private/light_actor.cpp
)


target_compile_features(hge PRIVATE c_std_11)

#set_target_properties(hge PROPERTIES
#        OUTPUT_NAME "HorizonNext"
#)


#compile dll declspec export
target_compile_definitions(hge PRIVATE ENGINE_BUILD_DLL)

target_include_directories(hge PUBLIC include/)

target_include_directories(hge PRIVATE third_party)


#link hrl en attendant une version plus stable de hrl (pour ensuite compiler les fichiers hrl dans le projet)


target_link_libraries(hge PRIVATE
        "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/third_party/Ogre/lib/Debug/OgreNextMain_d.lib>"
        "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/third_party/Ogre/lib/Debug/opt/RenderSystem_Vulkan_d.lib>"
        "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/third_party/Ogre/lib/Debug/opt/RenderSystem_Direct3D11_d.lib>"
        "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/third_party/Ogre/lib/Debug/opt/RenderSystem_GL3Plus_d.lib>"

        "$<$<CONFIG:Release>:${CMAKE_CURRENT_SOURCE_DIR}/third_party/Ogre/lib/Release/OgreNextMain.lib>"
        "$<$<CONFIG:Release>:${CMAKE_CURRENT_SOURCE_DIR}/third_party/Ogre/lib/Release/opt/RenderSystem_Vulkan.lib>"
        "$<$<CONFIG:Release>:${CMAKE_CURRENT_SOURCE_DIR}/third_party/Ogre/lib/Release/opt/RenderSystem_Direct3D11.lib>"
        "$<$<CONFIG:Release>:${CMAKE_CURRENT_SOURCE_DIR}/third_party/Ogre/lib/Release/opt/RenderSystem_GL3Plus.lib>"
)