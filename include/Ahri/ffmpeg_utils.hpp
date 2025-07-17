/**
 * @file ffmpeg_utils.hpp
 * @date 2025/01/13
 * @author Sokyoei
 * FFmpeg Utils
 *
 */

#pragma once
#ifndef AHRI_FFMPEG_UTILS_HPP
#define AHRI_FFMPEG_UTILS_HPP

#include <iostream>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <libavformat/avformat.h>
#include <libavutil/log.h>
#include <libavutil/opt.h>
#include <libavutil/version.h>
#include <libpostproc/postprocess.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
}

namespace Ahri::FFmpeg {
void init_ffmpeg() {
#if LIBAVCODEC_VERSION_MAJOR < 59
    av_register_all();
    avcodec_register_all();
    avformat_register_all();
#else  // FFmpeg 4.x ^^^ / vvv FFmpeg 5.x later
    avformat_network_init();
#endif
}

void deinit_ffmpeg() {
#if LIBAVCODEC_VERSION_MAJOR < 59

#else  // FFmpeg 4.x ^^^ / vvv FFmpeg 5.x later
    avformat_network_deinit();
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Log
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Macro
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
static char av_error[AV_ERROR_MAX_STRING_SIZE] = {0};
#ifdef av_err2str
#undef av_err2str
#endif
#define av_err2str(errnum) av_make_error_string(av_error, AV_ERROR_MAX_STRING_SIZE, errnum)
#endif

#define AV_CHECK(retcode, message)                                       \
    do {                                                                 \
        if (retcode != 0)                                                \
            av_log(nullptr, AV_LOG_ERROR, message, av_err2str(retcode)); \
        return EXIT_FAILURE                                              \
    } while (0)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Media
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Media {
public:
    Media(const char* url) {
        _context = avformat_alloc_context();
        avformat_open_input(&_context, url, nullptr, nullptr);
    }
    ~Media() { avformat_close_input(&_context); }

private:
    AVFormatContext* _context;
};
}  // namespace Ahri::FFmpeg

#endif  // !AHRI_FFMPEG_UTILS_HPP
