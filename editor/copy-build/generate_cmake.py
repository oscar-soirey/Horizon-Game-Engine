import json
from pathlib import Path

def generate_cmake(project)-> str:
    proj_name = ""
    cpp_files = []
    
    with open(project, 'r') as f:
        data = json.load(f)
        
        proj_name = data["name"]
        src_dir = data["src-dir"]

        project_path = Path(project).parent
        src_path = project_path / src_dir
        
        #.c and .cpp
        files = list(src_path.rglob("*.c")) + list(src_path.rglob("*.cpp"))
        for fls in files:
            cpp_files.append(str(fls.relative_to(project_path)))

    #formatage cmake
    cpp_files_str = "\n        ".join(cpp_files)
        
    content = f"""
cmake_minimum_required(VERSION 3.31)
project({proj_name})

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

include_directories(src)
include_directories(third_party)

add_library({proj_name} SHARED
        {cpp_files_str}
)


find_package(OpenGL REQUIRED)

add_library(hrl STATIC IMPORTED)
set_target_properties(hrl PROPERTIES IMPORTED_LOCATION "${{CMAKE_SOURCE_DIR}}/lib/libhrldll.dll.a")

add_library(hge STATIC IMPORTED)
set_target_properties(hge PROPERTIES IMPORTED_LOCATION "${{CMAKE_SOURCE_DIR}}/lib/libhge.dll.a")


target_link_libraries({proj_name} PRIVATE
        hge
        hrl
        OpenGL::GL
)
"""

    return content
    
