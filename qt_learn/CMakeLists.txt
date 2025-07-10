add_executable(main main.cpp)
target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
