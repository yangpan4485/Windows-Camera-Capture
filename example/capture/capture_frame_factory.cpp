#include "capture_frame_factory.h"

CaptureFrameFactory& CaptureFrameFactory::Instance() {
    static CaptureFrameFactory instance;
    return instance;
}

// I420
void CaptureFrameFactory::CreateFrame(int nums, const VideoDescription& description) {
    for (int i = 0; i < nums; ++i) {
        std::shared_ptr<CaptureFrame> frame = std::make_shared<CaptureFrame>(description);
        frame_vec_.push_back(frame);
    }
}

void CaptureFrameFactory::DestroyFrame() {
    for (size_t i = 0; i < frame_vec_.size(); ++i) {
        frame_vec_[i].reset();
    }
}

std::shared_ptr<CaptureFrame> CaptureFrameFactory::GetCaptureFrame() {
    index_ = index_ % frame_vec_.size();
    return frame_vec_[index_++];
    
}

CaptureFrameFactory::CaptureFrameFactory() {

}

CaptureFrameFactory::~CaptureFrameFactory() {

}