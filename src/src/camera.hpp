#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QCamera>
#include <QImage>
#include <opencv2/opencv.hpp>

namespace Ahri {
class QtCamera : public QCamera {
private:
public:
    QtCamera();
    ~QtCamera();
    cv::Mat QImage_to_Mat(QImage& qimage);
    QImage Mat_to_QImage(cv::Mat& mat);
};

class IntelRealSenseCamera {};
}  // namespace Ahri

#endif  // !CAMERA_HPP
