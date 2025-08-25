/**
 * @file main.cpp
 * @date 2025/08/25
 * @author Sokyoei
 * @details
 * ImGui example
 */

#include <iostream>
#include <memory>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <opencv2/opencv.hpp>

#include "Ahri/Ceceilia/utils/logger_utils.hpp"
#include "Ahri/imgui_utils.hpp"
#include "Ahri/opengl_utils.hpp"

namespace Ahri::IMGUI {
class SettingsWindow;
class OpenCVSettingsWindow;
class MediaWindow;

/**
 * @brief 设置窗口
 */
class SettingsWindow : public AbstractImGuiWindow {
    friend class MediaWindow;

public:
    SettingsWindow()
        : AbstractImGuiWindow("设置")
    // , f(0.0f), counter(0)
    {}

protected:
    void render() override {
        if (ImGui::Button("选择视频文件")) {
#ifdef _WIN32
            // 使用原生文件对话框选择视频文件
            OPENFILENAMEA ofn;
            char szFile[260] = {0};

            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = "视频文件\0*.mp4;*.avi;*.mkv;*.mov;*.wmv\0所有文件\0*.*\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileNameA(&ofn)) {
                _selected_video_path = std::string(szFile);
                _media_is_open = true;
            }
#endif
        }

        if (!_selected_video_path.empty()) {
            ImGui::Text("已选择: %s", _selected_video_path.c_str());
        }

        if (ImGui::Button(_media_is_open ? "关闭" : "打开")) {
            _media_is_open = !_media_is_open;
            if (!_media_is_open) {
                _selected_video_path.clear();
            }
        }

        // ImGui::Text("这是一个简单的ImGui窗口示例。");  // 显示文本
        // ImGui::SliderFloat("float", &f, 0.0f, 1.0f);   // 滑动条
        // ImGui::ColorEdit3("clear color", color);       // 使用颜色数组而不是指针

        // if (ImGui::Button("按钮")) {  // 按钮
        //     counter++;
        // }
        // ImGui::SameLine();
        // ImGui::Text("counter = %d", counter);

        // ImGuiIO& io = ImGui::GetIO();
        // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    }

public:
    AHRI_NODISCARD auto is_media_open() const -> bool { return _media_is_open; }
    AHRI_NODISCARD auto get_selected_video_path() const -> const std::string& { return _selected_video_path; }

private:
    bool _media_is_open = false;
    std::string _selected_video_path;
    // float f;
    // float color[3] = {0.0f, 0.0f, 0.0f};  // 定义颜色数组
    // int counter;
};

class OpenCVSettingsWindow : public AbstractImGuiWindow {
public:
    OpenCVSettingsWindow() : AbstractImGuiWindow("OpenCV 设置") {}

protected:
    void render() override { ImGui::Text("OpenCV 版本: %s", CV_VERSION); }

private:
};

/**
 * @brief 媒体窗口
 */
class MediaWindow : public AbstractImGuiWindow {
    friend class SettingsWindow;

public:
    MediaWindow() : AbstractImGuiWindow("媒体") {}

    void set_settings_window(SettingsWindow& settings) { _settings = std::addressof(settings); }

protected:
    void render() override {
        if (auto settings = _settings; settings && settings->is_media_open()) {
            // 获取视频路径
            std::string video_path = settings->get_selected_video_path();

            // 打开摄像头或视频文件
            if (!_capture.isOpened()) {
                if (!video_path.empty()) {
                    // 打开视频文件
                    _capture.open(video_path);
                } else {
                    // 打开摄像头
                    _capture.open(0);
                }

                if (!_capture.isOpened()) {
                    AHRI_LOGGER_ERROR("无法打开媒体源");
                    ImGui::Text("无法打开媒体源");
                    return;
                }
            }

            // 从媒体源捕获帧
            cv::Mat frame;
            if (_capture.isOpened() && _capture.read(frame)) {
                // 将 BGR 格式转换为 RGB 格式
                cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

                // 如果纹理未创建，则创建纹理
                if (_texture_id == 0) {
                    glGenTextures(1, &_texture_id);
                }

                // 绑定纹理对象，后续的纹理操作都将针对这个纹理 ID
                glBindTexture(GL_TEXTURE_2D, _texture_id);
                // 设置纹理缩小过滤方式为线性过滤，当纹理像素小于显示区域时使用线性插值
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                // 设置纹理放大过滤方式为线性过滤，当纹理像素大于显示区域时使用线性插值
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // 设置像素存储方式，指定内存中像素数据的排列对齐方式
                // GL_UNPACK_ROW_LENGTH为0表示使用紧排列，即每行像素数据紧密排列无填充
                glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
                // 将图像数据上传到GPU纹理内存
                glTexImage2D(GL_TEXTURE_2D,           // - GL_TEXTURE_2D: 指定目标纹理类型
                             0,                       // - 0: 指定纹理级别（0 为基本级别）
                             GL_RGB,                  // - GL_RGB: 指定纹理内部格式
                             frame.cols, frame.rows,  // - frame.cols, frame.rows: 纹理的宽度和高度
                             0,                       // - 0: 边框宽度（必须为 0）
                             GL_RGB,                  // - GL_RGB: 指定像素数据的格式
                             GL_UNSIGNED_BYTE,        // - GL_UNSIGNED_BYTE: 指定像素数据的数据类型
                             frame.data               // - frame.data: 指向图像数据的指针
                );
                // 为当前绑定的纹理生成Mipmap（多级渐进纹理）
                // Mipmap是一系列预计算的纹理图像，用于提高渲染质量和性能
                glGenerateMipmap(GL_TEXTURE_2D);

                // 在ImGui中显示纹理
                ImGui::Text("分辨率: %dx%d", frame.cols, frame.rows);
                if (!video_path.empty()) {
                    ImGui::SameLine();
                    ImGui::Text("文件: %s", video_path.c_str());
                }
                ImVec2 canvas_size = ImGui::GetContentRegionAvail();
                ImVec2 image_size = ImVec2(static_cast<float>(frame.cols), static_cast<float>(frame.rows));

                // 保持宽高比
                float scale = std::min(canvas_size.x / image_size.x, canvas_size.y / image_size.y);
                ImVec2 display_size = ImVec2(image_size.x * scale, image_size.y * scale);

                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - display_size.x) * 0.5f);
                ImGui::Image(static_cast<ImTextureID>(_texture_id), display_size);
            } else {
                ImGui::Text("无法获取媒体画面");
            }
        } else {
            // 关闭媒体源
            if (_capture.isOpened()) {
                _capture.release();
                if (_texture_id != 0) {
                    glDeleteTextures(1, &_texture_id);
                    _texture_id = 0;
                }
            }
            ImGui::Text("媒体源已关闭");
        }
    }

private:
    cv::VideoCapture _capture;
    GLuint _texture_id = 0;
    SettingsWindow* _settings = nullptr;
};
}  // namespace Ahri::IMGUI

int main(AHRI_MAYBE_UNUSED int argc, AHRI_MAYBE_UNUSED char const* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    try {
        // 初始化 OpenGL 上下文管理器
        Ahri::OpenGL::OpenGLContextManager context_manager;
        // 创建窗口
        GLFWwindow* window = context_manager.create_window(1280, 720, "ImGui Example");
        // 初始化GLAD
        if (!context_manager.initialize_GLAD()) {
            return EXIT_FAILURE;
        }
        // 开启垂直同步
        context_manager.set_swap_interval(1);
        // 初始化 ImGui
        Ahri::IMGUI::ImGuiManager imgui_manager{window};
        // 创建窗口实例
        Ahri::IMGUI::SettingsWindow settings;
        Ahri::IMGUI::OpenCVSettingsWindow opencv_settings;
        Ahri::IMGUI::MediaWindow media;

        // 设置关联
        media.set_settings_window(settings);

        // 主循环
        while (!context_manager.should_close()) {
            // 轮询事件
            context_manager.poll_events();
            // 开始ImGui帧
            imgui_manager.start_frame();

            // 创建主菜单栏
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("窗口")) {
                    AHRI_IMGUI_MENUITEM("设置", settings, Ahri::IMGUI::SettingsWindow)
                    AHRI_IMGUI_MENUITEM("OpenCV 设置", opencv_settings, Ahri::IMGUI::OpenCVSettingsWindow)
                    AHRI_IMGUI_MENUITEM("媒体", media, Ahri::IMGUI::MediaWindow, media.set_settings_window(settings);)
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }

            // 显示窗口
            settings.show();
            opencv_settings.show();
            media.show();
            // 结束ImGui帧
            imgui_manager.end_frame();
            // 渲染
            imgui_manager.render();
            // 交换缓冲区
            context_manager.swap_buffers();
        }
    } catch (const std::exception& e) {
        AHRI_LOGGER_CRITICAL("ERROR: {}", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
