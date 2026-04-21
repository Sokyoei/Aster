/**
 * @file opengl_utils.hpp
 * @date 2025/08/25
 * @author Sokyoei
 * @details
 * OpenGL utilities.
 */

#pragma once
#ifndef AHRI_OPENGL_UTILS_HPP
#define AHRI_OPENGL_UTILS_HPP

#include <glad/glad.h>
// include glad first
#include <GLFW/glfw3.h>

#include "Ahri/Ceceilia/utils/logger_utils.hpp"

namespace Ahri::OpenGL {
/**
 * @brief GLFW error callback.
 * @param error Error code.
 * @param description Error description.
 */
void glfw_error_callback(int error, const char* description) {
    AHRI_LOGGER_ERROR("GLFW Error: {} {}", error, description);
}

/**
 * @brief OpenGL context manager.
 */
struct OpenGLContextManager {
    GLFWwindow* window = nullptr;

    OpenGLContextManager() {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit()) {
            AHRI_LOGGER_CRITICAL("Failed to initialize GLFW");
            throw std::runtime_error("Failed to initialize GLFW");
        }
    }

    ~OpenGLContextManager() {
        if (window) {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
    }

    /**
     * @brief 创建窗口
     * @param width 窗口宽度
     * @param height 窗口高度
     * @param title 窗口标题
     * @return GLFWwindow* 窗口指针
     */
    GLFWwindow* create_window(int width, int height, const char* title) {
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (window == nullptr) {
            AHRI_LOGGER_CRITICAL("Failed to create GLFW window");
            throw std::runtime_error("Failed to create GLFW window");
        }
        return window;
    }

    bool initialize_GLAD() {
        if (!window) {
            AHRI_LOGGER_CRITICAL("No window available for GLAD initialization");
            return false;
        }

        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            glfwTerminate();
            AHRI_LOGGER_CRITICAL("Failed to initialize GLAD");
            return false;
        }

        AHRI_LOGGER_INFO("Successfully initialized GLFW({}) and GLAD({}.{}), OpenGL Version: {}",
                         glfwGetVersionString(), gladGLversionStruct().major, gladGLversionStruct().minor,
                         reinterpret_cast<const char*>(glGetString(GL_VERSION)));
        return true;
    }

    /**
     * @brief 是否应该关闭窗口
     * @return
     */
    bool should_close() const { return window && glfwWindowShouldClose(window); }

    /**
     * @brief 交换缓冲区
     */
    void swap_buffers() {
        if (window) {
            glfwSwapBuffers(window);
        }
    }

    /**
     * @brief 轮询事件
     */
    void poll_events() { glfwPollEvents(); }

    /**
     * @brief 设置垂直同步
     * @param interval
     */
    void set_swap_interval(int interval) { glfwSwapInterval(interval); }
};
}  // namespace Ahri::OpenGL

#endif  // !AHRI_OPENGL_UTILS_HPP
