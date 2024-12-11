/**
 * @file main.cpp
 * @date 2024/12/04
 * @author Sokyoei
 *
 * Reference: https://www.cnblogs.com/chenglixue/p/16736414.html
 *
 */

#include <Windows.h>

#include <wrl.h>

#include <d3d12.h>

HWND g_hMainWnd = 0;

bool InitMainWindow(HINSTANCE instanceHandle, int show);
int Run();
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/**
 * @brief
 * @param instanceHandle
 * @param show
 * @return
 */
bool InitMainWindow(HINSTANCE instanceHandle, int show) {
    static const TCHAR* appName = TEXT("BasicWndClass");

    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instanceHandle;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = appName;

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, TEXT("RegisterClass FAILED"), appName, MB_ICONERROR);
        return false;
    }

    g_hMainWnd = CreateWindow(appName,              // 采用的前面注册的WNDCLASS
                              TEXT("Win32Basic"),   // 窗口标题
                              WS_OVERLAPPEDWINDOW,  // 窗口的样式标志
                              CW_USEDEFAULT,        // x坐标
                              CW_USEDEFAULT,        // y坐标
                              CW_USEDEFAULT,        // 窗口宽度
                              CW_USEDEFAULT,        // 窗口高度
                              NULL,                 // 父窗口
                              NULL,                 // 菜单句柄
                              instanceHandle,       // 应用程序实例句柄
                              NULL                  // 其他参数
    );

    if (g_hMainWnd == NULL) {
        MessageBox(NULL, TEXT("CreateWindow FALIED"), appName, MB_ICONERROR);
        return false;
    }

    // 展示窗口并更新
    ShowWindow(g_hMainWnd, show);  // show为显示模式
    UpdateWindow(g_hMainWnd);

    return true;
}

int Run() {
    MSG msg = {0};

    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            // 动画或游戏逻辑
        }
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_LBUTTONDOWN:  // 按下鼠标左键
            MessageBox(NULL, TEXT("Hello, World"), TEXT("Hello"), MB_OK);
            return 0;
        case WM_KEYDOWN:  // 键盘键被按下
            if (wParam == VK_ESCAPE) {
                DestroyWindow(g_hMainWnd);
                return 0;
            }
        case WM_DESTROY:  // 窗口被销毁
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd) {
    if (!InitMainWindow(hInstance, nShowCmd)) {
        return 0;
    }

    return Run();
}
