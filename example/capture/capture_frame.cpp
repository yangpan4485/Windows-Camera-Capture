#include "capture_frame.h"

CaptureFrame::CaptureFrame(const VideoDescription& description) {
    width_ = description.width;
    height_ = description.height;
    data_ = new uint8_t[width_ * height_ * 3 / 2];
}

CaptureFrame::~CaptureFrame() {
    if (data_) {
        delete[] data_;
    }
}

uint8_t* CaptureFrame::Data() {
    return data_;
}

uint32_t CaptureFrame::Width() {
    return width_;
}

uint32_t CaptureFrame::Height() {
    return height_;
}