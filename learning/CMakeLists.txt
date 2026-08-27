if(ImGui AND imgui_FOUND)
    add_subdirectory(imgui_learning)
endif(ImGui AND imgui_FOUND)

if(OpenGL AND glad_FOUND AND glfw3_FOUND)
    add_subdirectory(opengl_learning)
endif(OpenGL AND glad_FOUND AND glfw3_FOUND)

if(WIN32 AND DirectX)
    add_subdirectory(directx_learning)
endif(WIN32 AND DirectX)
