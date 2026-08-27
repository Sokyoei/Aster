cmake_minimum_required(VERSION 3.20.0)

project(Aster VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

# export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(AHRI_EXPORT)
# add_definitions(-DAHRI_EXPORT)

include(${PROJECT_SOURCE_DIR}/cmake/compiler.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/library.cmake)

set(ASTER_ROOT ${PROJECT_SOURCE_DIR})
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/../Ceceilia/include
)

########################################################################################################################
# options
########################################################################################################################
option(AsterQML         "Aster project using QML"               OFF)  # default is using widget
option(Qt               "enable QT"                              ON)
option(ImGui            "enable ImGui"                          OFF)
option(OpenGL           "enable OpenGL"                         OFF)
option(DirectX          "enable DirectX"                        OFF)

########################################################################################################################
# Learning projects
########################################################################################################################
if(Learning)
    add_subdirectory(learning)
endif(Learning)

# flags to use QML
if(AsterQML)
    set(ASTER_USE_QTQML true)
    set(QT_QML_GENERATE_QMLLS_INI ON)
endif(AsterQML)
add_subdirectory(src)

# config.h settings
configure_file(
    ${PROJECT_SOURCE_DIR}/config.h.cmake
    ${PROJECT_SOURCE_DIR}/config.h
)
