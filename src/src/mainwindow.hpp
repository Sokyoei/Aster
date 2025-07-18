#pragma once
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QPixmap>
#include <QVideoWidget>

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

private slots:
    void onOpenFileButtonClicked();

private:
    Ui::MainWindow* ui;
    QPoint diff_pos;
    QPoint window_pos;
    QPoint mouse_pos;
    QMediaPlayer* meidaplayer;
};

#endif  // !MAINWINDOW_HPP
