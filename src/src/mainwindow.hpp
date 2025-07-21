#pragma once
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <algorithm>

#include "Aster.hpp"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QPixmap>
#include <QVideoWidget>

#ifdef USE_QT6
#include <QMediaFormat>
#else defined(USE_QT5)
#include <QMediaContent>
#endif

#include "constants.hpp"

namespace Ui {
class MainWindow;
}

namespace Ahri::Aster {
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    // 无边框时重写鼠标事件以实现窗口拖动
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
    void onOpenFileButtonClicked();

    // 最小化最大化和关闭按钮的槽函数
    void onMinButtonClicked();
    void onMaxButtonClicked();
    void onCloseButtonClicked();

private:
    Ui::MainWindow* ui;
    QPoint diff_pos;
    QPoint window_pos;
    QPoint mouse_pos;
    QMediaPlayer* meidaplayer{nullptr};
};
}  // namespace Ahri::Aster

#endif  // !MAINWINDOW_HPP
