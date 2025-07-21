#pragma once
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <QStringList>

namespace Ahri::Aster {
const QStringList picture_extensions = {
    "jpg",  "jpeg", "jfif",  // JPEG
    "png",                   // PNG
    "gif",                   //
    "bmp",                   // BMP
    "tiff",                  // TIFF
};

const QStringList video_extensions = {
    "mp4",                 // MP4
    "avi",                 // AVI
    "mov",  "flv", "wmv",  //
    "mkv",                 // MKV
    "webm", "m4v"          //
};
}  // namespace Ahri::Aster

#endif  // !CONSTANTS_HPP
