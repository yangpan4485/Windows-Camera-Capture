#pragma once

#include <vector>

#include "capture_frame.h"
class CaptureFrameFactory {
public:
    static CaptureFrameFactory& Instance();

    // I420
    void CreateFrame(int nums, const VideoDescription& description);
    void DestroyFrame();

    std::shared_ptr<CaptureFrame> GetCaptureFrame();
private:
    CaptureFrameFactory();
    ~CaptureFrameFactory();
    CaptureFrameFactory(const CaptureFrameFactory&) = delete;
    CaptureFrameFactory operator=(const CaptureFrameFactory&) = delete;

private:
    std::vector <std::shared_ptr<CaptureFrame>> frame_vec_;
    int index_ = 0;
};