#include "capture_frame.h"

#include <iostream>
#include "frame_buffer.h"

CaptureFrame::CaptureFrame(const VideoDescription& description) {
    width_ = description.width;
    height_ = description.height;
    data_ = FrameBuffer::Instance().GetBuffer(width_, height_, index_);
}

CaptureFrame::~CaptureFrame() {
    if (index_ != -1) {
        FrameBuffer::Instance().ReleaseBuffer(index_);
    }
    index_ = -1;
    /*if (data_) {
        delete[] data_;
    }*/
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