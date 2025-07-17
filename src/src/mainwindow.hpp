#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QFile>
#include <QMainWindow>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    // 无边框时重写鼠标事件以实现窗口拖动
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    Ui::MainWindow* ui;
    QPoint diff_pos;
    QPoint window_pos;
    QPoint mouse_pos;
};

#endif  // !MAINWINDOW_HPP
