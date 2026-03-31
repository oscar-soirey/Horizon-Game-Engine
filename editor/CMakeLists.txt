cmake_minimum_required(VERSION 3.31)
project(editor)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

include_directories(src)
include_directories(third_party)
include_directories(third_party/imgui)

file(GLOB_RECURSE IMGUI_SRC "third_party/imgui/*.cpp")

add_executable(editor ressources/icon.rc
        ${IMGUI_SRC}
        third_party/tinyfiledialogs/tinyfiledialogs.c
        third_party/imgui_textedit/TextEditor.cpp
        third_party/tinyxml2/tinyxml2.cpp

        src/main.cpp

        src/core/history.cpp

        src/ui/window.cpp
        src/ui/style.cpp
        src/ui/common.cpp
        src/ui/menu_bar.cpp
        src/ui/toolbar.cpp
        src/ui/Image.cpp

        src/ui/widgets/TitleIcon.cpp
        src/ui/widgets/FileInput.cpp
        src/ui/widgets/ComboBox.cpp
        src/ui/widgets/IconButton.cpp
        src/ui/widgets/FileButton.cpp
        src/ui/widgets/ActorTitle.cpp
        src/ui/widgets/Details.cpp

        src/ui/windows/open_project.cpp
        src/ui/windows/project_configuration.cpp
        src/ui/windows/script_editor.cpp
        src/ui/windows/content_browser.cpp
        src/ui/windows/texture_editor.cpp
        src/ui/windows/viewport.cpp
        src/ui/windows/place_actors.cpp
        src/ui/windows/outliner.cpp
        src/ui/windows/actor_details.cpp
)


find_package(OpenGL REQUIRED)


add_library(hge STATIC IMPORTED)
set_target_properties(hge PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libhge.dll.a")

add_library(hrl STATIC IMPORTED)
set_target_properties(hrl PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libhrldll.dll.a")

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libglfw3.a")


#link hrl en attendant une version plus stable de hrl (pour ensuite compiler les fichiers hrl dans le projet)
target_link_libraries(editor PRIVATE
        hge
        hrl
        glfw
        OpenGL::GL
)