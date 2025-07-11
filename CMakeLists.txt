cmake_minimum_required(VERSION 3.20.0)

project(Aster VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(AHRI_EXPORT)
# add_definitions(-DAHRI_EXPORT)

include(${PROJECT_SOURCE_DIR}/cmake/compiler.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/library.cmake)

set(ROOT ${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include)

########################################################################################################################
# options
########################################################################################################################
option(FFmpeg "build ffmpeg_learn subproject" ON)
option(Qt "build qt_learn subproject" ON)
option(ImGui "build imgui_learn subproject" ON)
option(OpenGL "build opengl_learn subproject" ON)

if(FFmpeg)
    if(FFMPEG_FOUND)
        add_subdirectory(ffmpeg_learn)
    endif(FFMPEG_FOUND)
endif(FFmpeg)

if(Qt)
    if(Qt${QT_VERSION_MAJOR}_FOUND)
        add_subdirectory(qt_learn)
    endif(Qt${QT_VERSION_MAJOR}_FOUND)
endif(Qt)

if(ImGui)
    if(imgui_FOUND)
        add_subdirectory(imgui_learn)
    endif(imgui_FOUND)
endif(ImGui)

if(OpenGL)
    if((glad_FOUND) AND (glfw3_FOUND))
        add_subdirectory(opengl_learn)
    endif((glad_FOUND) AND (glfw3_FOUND))
endif(OpenGL)

if(WIN32)
    add_subdirectory(DirectX_learn)
endif(WIN32)

add_subdirectory(src)

# config.h settings
configure_file(
    ${PROJECT_SOURCE_DIR}/config.h.cmake
    ${PROJECT_SOURCE_DIR}/config.h
)
