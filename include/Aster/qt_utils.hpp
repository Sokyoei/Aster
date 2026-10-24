#pragma once
#ifndef ASTER_QT_UTILS_HPP
#define ASTER_QT_UTILS_HPP

#include <QImage>
#include <opencv2/opencv.hpp>

namespace Asuka::Qt {
inline cv::Mat QImage2cvMat(QImage& qimage) {
    cv::Mat mat;
    switch (qimage.format()) {
        case QImage::Format_RGB888:
            mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC3, (void*)qimage.bits(), qimage.bytesPerLine());
            cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
            break;
        default:
            break;
    }
    return mat;
}

inline QImage cvMat2QImage(cv::Mat& mat) {
    cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
    return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_BGR888);
}
}  // namespace Asuka::Qt

#endif  // !ASTER_QT_UTILS_HPP
