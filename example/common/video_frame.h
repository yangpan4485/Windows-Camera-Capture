#pragma once

#include <string>

#define RELEASE_AND_CLEAR(p) \
    if (p) {                 \
        (p)->Release();      \
        (p) = NULL;          \
    }

const uint32_t kMaxDeviceLength = 128;

enum VideoMessage {
    kUnknow,
    kOpenCamera,
    kCloseCamera
};

enum VideoType {
    kVideoTypeUnknown,
    kVideoTypeI420,
    kVideoTypeIYUV,
    kVideoTypeRGB24,
    kVideoTypeABGR,
    kVideoTypeARGB,
    kVideoTypeARGB4444,
    kVideoTypeRGB565,
    kVideoTypeARGB1555,
    kVideoTypeYUY2,
    kVideoTypeYV12,
    kVideoTypeUYVY,
    kVideoTypeMJPEG,
    kVideoTypeNV21,
    kVideoTypeNV12,
    kVideoTypeBGRA,
};

enum VideoDeviceStatus {
    kVideoDeviceUnknown = 0,
    kVideoDeviceAdd = 1,
    kVideoDeviceRemove = 2,
};

struct VideoDevice {
    std::string device_id{};
    std::string device_name{};
};

struct VideoDescription {
    uint32_t width{ 0 };
    uint32_t height{ 0 };
    uint32_t fps{ 0 };
    VideoType video_type;
};

struct VideoFrame {
    uint8_t* y_data;
    uint32_t y_stride;
    uint8_t* u_data;
    uint32_t u_stride;
    uint8_t* v_data;
    uint32_t v_stride;
    uint32_t width;
    uint32_t height;
};