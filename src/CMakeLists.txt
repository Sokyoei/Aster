set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

file(
    GLOB_RECURSE
    ASTER_SOURCE_FILES
    "src/*.cpp"
    "src/*.hpp"
    "ui/*.ui"
    "assets/*.qrc"
    "assets/*.rc"
    "assets/*.qml"
)

add_executable(Aster main.cpp ${ASTER_SOURCE_FILES})
target_include_directories(Aster PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(Aster PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

qt_create_translation(QM_FILES i18n/Aster_zh_CN.ts)

target_link_libraries(Aster PRIVATE opencv_core)
target_link_libraries(Aster PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(Aster PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(Aster PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Aster PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)
target_link_libraries(Aster PRIVATE Qt${QT_VERSION_MAJOR}::MultimediaWidgets)
if(USE_QTQML)
    target_link_libraries(Aster PRIVATE Qt${QT_VERSION_MAJOR}::Qml)
    target_link_libraries(Aster PRIVATE Qt${QT_VERSION_MAJOR}::Quick)
endif(USE_QTQML)
target_link_libraries(Aster
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_include_directories(Aster PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(Aster PRIVATE ${FFMPEG_LIBRARY_DIRS})
target_link_libraries(Aster PRIVATE ${FFMPEG_LIBRARIES})
