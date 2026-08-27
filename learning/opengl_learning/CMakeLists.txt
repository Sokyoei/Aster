add_executable(opengl_main main.cpp)
target_link_libraries(opengl_main PRIVATE glad::glad)
target_link_libraries(opengl_main PRIVATE glfw)
