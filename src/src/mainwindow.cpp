#include "mainwindow.hpp"
#include "ui_mainwindow.h"

namespace Ahri::Aster {
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

void MainWindow::onMinButtonClicked() {
    this->showMinimized();
}

void MainWindow::onMaxButtonClicked() {
    if (this->isMaximized()) {
        this->showNormal();
    } else {
        this->showMaximized();
    }
}

void MainWindow::onCloseButtonClicked() {
    this->close();
}

void MainWindow::onOpenFileButtonClicked() {
    auto file = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("All Files (*)"));
    if (!file.isEmpty()) {
        qDebug() << "Selected file:" << file;

        QFileInfo fileinfo(file);
        if (picture_extensions.contains(fileinfo.suffix(), Qt::CaseInsensitive)) {
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
        } else if (video_extensions.contains(fileinfo.suffix(), Qt::CaseInsensitive)) {
            meidaplayer = new QMediaPlayer(this);
            meidaplayer->setVideoOutput(ui->videoWidget);
            ui->videoWidget->show();

            QUrl mediaurl = QUrl::fromLocalFile(file);
            if (!mediaurl.isValid()) {
                qDebug() << "Invalid media url:" << file;
            }

#ifdef USE_QT6
            meidaplayer->setSource(mediaurl);
#else defined(USE_QT5)
            QMediaContent content(mediaurl);
            meidaplayer->setMedia(content);
#endif
            meidaplayer->play();

            // 检查媒体是否加载成功
            connect(meidaplayer, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
                qDebug() << "Media status:" << status;
                if (status == QMediaPlayer::InvalidMedia) {
                    qDebug() << "invalid media file:" << file;
                } else if (status == QMediaPlayer::LoadedMedia) {
                    qDebug() << "success load" << file;
                }
            });

            // 检查播放状态
#ifdef USE_QT6
            connect(meidaplayer, &QMediaPlayer::playbackStateChanged, this, [=](QMediaPlayer::PlaybackState state) {
#else defined(USE_QT5)
            connect(meidaplayer, &QMediaPlayer::stateChanged, this, [=](QMediaPlayer::State state) {
#endif
                qDebug() << "Player state:" << state;
            });

            ui->stackedWidget->setCurrentIndex(1);
            ui->showlabel->setText("");  // 清除文本
        }
    }
}
}  // namespace Ahri::Aster
