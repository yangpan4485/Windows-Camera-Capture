#include "video_message_loop.h"

#include "video_capture_ds.h"

VideoMessageLoop::VideoMessageLoop() : ds_capture_(new VideoCaptureDS()){

}

VideoMessageLoop::~VideoMessageLoop() {
    DeinitMessageLoop();
}

VideoMessageLoop& VideoMessageLoop::Instance() {
    static VideoMessageLoop instance;
    return instance;
}

void VideoMessageLoop::SendVideoMessage(VideoMessage message) {
    message_queue_.push(message);
    condition_.notify_one();
}

bool VideoMessageLoop::InitMessageLoop() {
    running_ = true;
    work_ = std::thread(std::bind(&VideoMessageLoop::LoopMessage, this));
    return true;
}

bool VideoMessageLoop::DeinitMessageLoop() {
    running_ = false;
    condition_.notify_all();
    if (work_.joinable()) {
        work_.join();
    }
    return true;
}

void VideoMessageLoop::SetCameraDevice(const VideoDevice& video_device) {
    video_device_ = video_device;
}

void VideoMessageLoop::SetVideoFormat(const VideoDescription& video_description) {
    video_description_ = video_description;
}

void VideoMessageLoop::LoopMessage() {
    while (running_) {
        VideoMessage message = kUnknow;
        {
            std::unique_lock<std::mutex> lk(mutex_);
            // spurious wakeup
            if (message_queue_.size() < 1) {
                condition_.wait(lk, [&] {return message_queue_.size() > 0 || !running_; });
            }
            if (!running_) {
                break;
            }
            message = message_queue_.front();
            message_queue_.pop();
        }
        switch (message) {
        case kOpenCamera:
            ds_capture_->StartCapture(video_device_, video_description_);
            break;
        case kCloseCamera:
            ds_capture_->StopCapture();
            break;
        default:
            break;
        }
    }
}

void VideoMessageLoop::RegisterVideoFrameCallback(VideoFrameCallback callback) {
    ds_capture_->RegisterVideoFrameCallback(callback);
}