/**
 * @file imgui_utils.hpp
 * @date 2025/08/25
 * @author Sokyoei
 * @details
 * imgui utils
 */

#pragma once
#ifndef AHRI_IMGUI_UTILS_HPP
#define AHRI_IMGUI_UTILS_HPP

#include <glad/glad.h>
// include glad first
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Ahri::IMGUI {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define AHRI_IMGUI_MENUITEM(menu_name, class_instance, class_name, ...)  \
    if (ImGui::MenuItem(menu_name, nullptr, class_instance.is_open())) { \
        if (class_instance.is_open()) {                                  \
            class_instance.close();                                      \
        } else {                                                         \
            class_instance = class_name{};                               \
            __VA_ARGS__                                                  \
        }                                                                \
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void load_chinese_font() {
    ImGuiIO& io = ImGui::GetIO();

#ifdef _WIN32
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/simhei.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
#elif __APPLE__
    io.Fonts->AddFontFromFileTTF("/System/Library/Fonts/PingFang.ttc", 18.0f, NULL,
                                 io.Fonts->GetGlyphRangesChineseFull());
#else
    io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/wqy/wqy-microhei.ttc", 18.0f, NULL,
                                 io.Fonts->GetGlyphRangesChineseFull());
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Classes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief 窗口基类
 * @details 窗口基类，用于实现窗口的创建、显示、关闭等功能
 */
class AbstractImGuiWindow {
public:
    AbstractImGuiWindow(const char* name) : _name(name), _is_open(true) {}
    virtual ~AbstractImGuiWindow() = default;

    // 显示窗口的公共接口
    void show() {
        if (!_is_open) {
            return;
        }

        // 创建窗口
        if (ImGui::Begin(_name, &_is_open, _window_flags)) {
            // 调用子类实现的具体内容
            render();
        }
        ImGui::End();
    }

    // 设置窗口标志
    void set_window_flags(ImGuiWindowFlags flags) { _window_flags = flags; }

    // 检查窗口是否打开
    bool is_open() const { return _is_open; }

    // 关闭窗口
    void close() { _is_open = false; }

protected:
    // 子类需要实现的渲染方法
    virtual void render() = 0;

    const char* _name;
    bool _is_open;
    ImGuiWindowFlags _window_flags = 0;
};

struct ImGuiManager {
    GLFWwindow* glfw_window = nullptr;

    ImGuiManager(GLFWwindow* window) : glfw_window(window) {
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // 启用键盘控制

        // 使用独立的字体加载函数
        load_chinese_font();

        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    ~ImGuiManager() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void start_frame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void end_frame() { ImGui::Render(); }

    void render() {
        int display_w, display_h;
        glfwGetFramebufferSize(glfw_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
};
}  // namespace Ahri::IMGUI

#endif  // !AHRI_IMGUI_UTILS_HPP
