#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QCamera>
#include <QImage>
#include <opencv2/opencv.hpp>

namespace Ahri::Aster {
class QtCamera : public QCamera {
private:
public:
    QtCamera();
    ~QtCamera();
};

class IntelRealSenseCamera {};
}  // namespace Ahri::Aster

#endif  // !CAMERA_HPP
