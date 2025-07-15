#include <QApplication>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QVBoxLayout>
#include <QWidget>

#include "src/mainwindow.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // // 创建主窗口部件
    // QWidget window;
    // // 创建 QCamera 对象，使用默认摄像头
    // QCamera* camera = new QCamera(QCameraInfo::defaultCamera(), &window);
    // // 创建 QCameraViewfinder 对象
    // QCameraViewfinder* viewfinder = new QCameraViewfinder(&window);
    // // 设置 QCamera 的视图取景器
    // camera->setViewfinder(viewfinder);
    // // 创建垂直布局
    // QVBoxLayout* layout = new QVBoxLayout(&window);
    // layout->addWidget(viewfinder);
    // // 启动摄像头
    // camera->start();
    // // 显示主窗口
    // window.show();

    MainWindow window;
    window.show();

    return app.exec();
}
