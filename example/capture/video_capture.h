#pragma once
#include <functional>

#include "../common/video_frame.h"

class VideoCapture {
public:
    using VideoFrameCallback = std::function<void(VideoFrame& video_frame)>;
public:
    VideoCapture();
    ~VideoCapture();

    void SelectVideoDevice(const VideoDevice& video_device);
    VideoDevice GetSelectVideoDevice();

    void SelectVideoFormat(const VideoDescription& video_description);
    VideoDescription GetSelectVideoFormat();

    bool StartCapture();
    bool StopCapture();

    void RegisterVideoFrameCallback(VideoFrameCallback callback);

private:
    VideoDevice video_device_{};
    VideoDescription video_description_{};
    
};