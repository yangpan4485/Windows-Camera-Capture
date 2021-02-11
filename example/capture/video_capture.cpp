#include "video_capture.h"

#include "video_message_loop.h"
#include "video_device_manager.h"

VideoCapture::VideoCapture() {
    VideoMessageLoop::Instance().InitMessageLoop();
}

VideoCapture::~VideoCapture() {
    VideoMessageLoop::Instance().DeinitMessageLoop();
}

void VideoCapture::SelectVideoDevice(const VideoDevice& video_device) {
    video_device_ = video_device;
    VideoMessageLoop::Instance().SetCameraDevice(video_device_);
}

VideoDevice VideoCapture::GetSelectVideoDevice() {
    return video_device_;
}

void VideoCapture::SelectVideoFormat(const VideoDescription& video_description) {
    video_description_ = video_description;
    VideoMessageLoop::Instance().SetVideoFormat(video_description_);
}

VideoDescription VideoCapture::GetSelectVideoFormat() {
    return video_description_;
}

bool VideoCapture::StartCapture() {
    if (video_device_.device_id.empty() || video_description_.width == 0 || video_description_.height == 0) {
        auto devices = VideoDeviceManager::Instance().GetVideoCaptureDevices();
        if (devices.empty()) {
            return false;
        }
        for (size_t i = 0; i < devices.size(); ++i) {
            auto formats = VideoDeviceManager::Instance().GetVideoDeviceFormats(devices[0].device_id);
            if (formats.size() > 0) {
                video_device_ = devices[i];
                video_description_ = formats[0];
                break;
            }
        }
        
        VideoMessageLoop::Instance().SetCameraDevice(video_device_);
        VideoMessageLoop::Instance().SetVideoFormat(video_description_);
    }
    VideoMessageLoop::Instance().SendVideoMessage(kOpenCamera);
    return true;
}

bool VideoCapture::StopCapture() {
    VideoMessageLoop::Instance().SendVideoMessage(kCloseCamera);
    return true;
}

void VideoCapture::RegisterVideoFrameCallback(VideoFrameCallback callback) {
    VideoMessageLoop::Instance().RegisterVideoFrameCallback(callback);
}