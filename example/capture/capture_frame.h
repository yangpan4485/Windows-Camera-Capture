#pragma once

#include "../common/video_frame.h"

class CaptureFrame {
public:
    CaptureFrame(const VideoDescription& description);
    ~CaptureFrame();

    uint8_t* Data();
    uint32_t Width();
    uint32_t Height();

private:
    uint8_t* data_{};
    uint32_t width_{};
    uint32_t height_{};
};