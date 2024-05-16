cmake_minimum_required(VERSION 3.20.0)

project(Aster VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# QT moc uic rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_compile_definitions(AHRI_EXPORT)
# add_definitions(-DAHRI_EXPORT)

include(cmake/compiler.cmake)

set(ROOT ${PROJECT_SOURCE_DIR})

# config.h settings
include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include)
configure_file(
    ${PROJECT_SOURCE_DIR}/config.h.cmake
    ${PROJECT_SOURCE_DIR}/config.h
)

# find_package(fmt CONFIG REQUIRED)
# find_package(nlohmann_json CONFIG REQUIRED)
# find_package(tinyxml2 CONFIG REQUIRED)
# find_package(toml11 CONFIG REQUIRED)
# find_package(yaml-cpp CONFIG REQUIRED)

# set(CMAKE_PREFIX_PATH "D:\\Qt\\5.15.2\\msvc2019_64")
# set(CMAKE_PREFIX_PATH "D:\\Anaconda3\\Library\\lib")
# set(Qt5_DIR "D:\\Anaconda3\\Library\\lib\\cmake\\Qt5")
# set(Qt5_DIR "D:\\Qt\\5.15.2\\msvc2019_64\\lib\\cmake\\Qt5")

find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_subdirectory(qt_learn)

# find_package(GTest REQUIRED)
# if (GTest_FOUND)
#     include_directories(${GTEST_ROOT}/include)
#     add_subdirectory(tests)
# endif ()
