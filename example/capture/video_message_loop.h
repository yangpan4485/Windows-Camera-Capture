#pragma once

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "../common/video_frame.h"

class VideoCaptureDS;
class VideoMessageLoop {
public:
    using VideoFrameCallback = std::function<void(VideoFrame& video_frame)>;
public:
    static VideoMessageLoop& Instance();

    void SendVideoMessage(VideoMessage message);
    bool InitMessageLoop();
    bool DeinitMessageLoop();

    void SetCameraDevice(const VideoDevice& video_device);
    void SetVideoFormat(const VideoDescription& video_description);

    void RegisterVideoFrameCallback(VideoFrameCallback callback);

private:
    VideoMessageLoop();
    ~VideoMessageLoop();
    VideoMessageLoop(const VideoMessageLoop&) = delete;
    VideoMessageLoop operator=(const VideoMessageLoop&) = delete;

    void LoopMessage();

private:
    std::thread work_{};
    std::queue<VideoMessage> message_queue_{};
    std::mutex mutex_;
    std::condition_variable condition_;
    bool running_{ false };

    VideoDescription video_description_{};
    VideoDevice video_device_{};

    std::unique_ptr<VideoCaptureDS> ds_capture_{};
};