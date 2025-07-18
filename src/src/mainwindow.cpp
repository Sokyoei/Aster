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

void MainWindow::onOpenFileButtonClicked() {
    auto file = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("All Files (*)"));
    if (!file.isEmpty()) {
        qDebug() << "Selected file:" << file;

        QFileInfo fileinfo(file);
        if (fileinfo.suffix() == "jpg" || fileinfo.suffix() == "png" || fileinfo.suffix() == "jpeg") {
            QPixmap pixmap(file);
            if (pixmap.isNull()) {
                qDebug() << "Failed to load image from file:" << file;
                ui->showlabel->setText(tr("Failed to load image."));
            } else {
                ui->stackedWidget->setCurrentIndex(0);
                ui->showlabel->setPixmap(
                    pixmap.scaled(ui->showlabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                ui->showlabel->setText("");  // 清除文本
            }
        } else if (fileinfo.suffix() == "mp4" || fileinfo.suffix() == "avi" || fileinfo.suffix() == "mkv") {
            meidaplayer = new QMediaPlayer(this);
            meidaplayer->setVideoOutput(ui->videoWidget);
            meidaplayer->setMedia(QUrl::fromLocalFile(file));
            meidaplayer->play();

            // 检查媒体是否加载成功
            connect(meidaplayer, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
                qDebug() << "Media status:" << status;  // 打印状态：LoadedMedia 表示加载成功
            });
            // 检查播放状态
            connect(meidaplayer, &QMediaPlayer::stateChanged, this, [=](QMediaPlayer::State state) {
                qDebug() << "Player state:" << state;  // PlayingState 表示正在播放
            });

            ui->stackedWidget->setCurrentIndex(1);
            ui->showlabel->setText("");  // 清除文本
        }
    }
}
