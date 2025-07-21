#include "Aster.hpp"

#include <QApplication>

#ifndef USE_QTQML
#include <QCamera>
#ifdef USE_QT5
#include <QCameraInfo>
#include <QCameraViewfinder>
#else defined(USE_QT6)
#include <QCameraDevice>
#include <QVideoSink>
#endif
#include <QVBoxLayout>
#include <QWidget>

#include "src/mainwindow.hpp"
#else
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#endif  // USE_QTQML

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

#ifndef USE_QTQML
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

    Ahri::Aster::MainWindow window;
    window.show();

#else   //  Widgets+ui ^^^/vvv QtQuick+QML
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Ahri/Aster/mainwindow.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
#endif  // USE_QTQML

    return app.exec();
}
