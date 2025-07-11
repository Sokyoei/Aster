set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

add_executable(
    qt_main
    main.cpp
    src/mainwindow.hpp
    src/mainwindow.cpp
    ui/mainwindow.ui
    assets/main.qrc
)
target_link_libraries(qt_main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(qt_main PRIVATE src)
