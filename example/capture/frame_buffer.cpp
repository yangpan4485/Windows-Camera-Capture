#include "frame_buffer.h"

#include <iostream>

const uint32_t kDefaultNums = 5;

FrameBuffer& FrameBuffer::Instance() {
    static FrameBuffer instance;
    return instance;
}

uint8_t* FrameBuffer::GetBuffer(uint32_t width, uint32_t height, int& index) {
    if (width_ != width || height_ != height) {
        width_ = width;
        height_ = height;
        FreeAllBuffer();
        for (int i = 0; i < kDefaultNums; ++i) {
            buffer_vec_[i] = new uint8_t[width*height * 3 / 2];
            buffer_map_[i] = 0;
        }
    }
    index_ = index_ % kDefaultNums;
    if (buffer_map_[index_] != 0) {
        return nullptr;
    }
    index = index_;
    buffer_map_[index_] = 1;
    return buffer_vec_[index_++];
}

void FrameBuffer::ReleaseBuffer(int index) {
    buffer_map_[index] = 0;
}


FrameBuffer::FrameBuffer() {

}

FrameBuffer::~FrameBuffer() {

}

void FrameBuffer::FreeAllBuffer() {
    for (int i = 0; i < buffer_vec_.size(); ++i) {
        if (buffer_vec_[i]) {
            delete[] buffer_vec_[i];
        }
    }
}