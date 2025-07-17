#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // 设置无边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    // 加载 mainwindow.qss
    QFile* mainwindowStyle = new QFile(":/Ahri/Aster/mainwindow.qss");
    mainwindowStyle->open(QFile::ReadOnly);
    this->setStyleSheet(mainwindowStyle->readAll());
    mainwindowStyle->close();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    mouse_pos = event->globalPos();
    window_pos = this->pos();
    diff_pos = mouse_pos - window_pos;
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        QPoint new_pos = event->globalPos() - diff_pos;
        this->move(new_pos);
    }
}
