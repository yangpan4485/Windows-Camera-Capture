#include "video_device_manager.h"

#include "video_device_ds.h"

VideoDeviceManager::VideoDeviceManager() : video_device_ds_(new VideoDeviceDS()){
    if (!video_device_ds_->Init()) {
        video_device_ds_.reset();
    }
}

VideoDeviceManager::~VideoDeviceManager() {

}

VideoDeviceManager& VideoDeviceManager::Instance() {
    static VideoDeviceManager instance;
    return instance;
}

std::vector<VideoDevice> VideoDeviceManager::GetVideoCaptureDevices() {
    if (!video_device_ds_) {
        return std::vector<VideoDevice>();
    }
    if (video_devices_.empty()) {
        video_devices_ = video_device_ds_->GetVideoCaptureDevices();
    }
    return video_devices_;
}

std::vector<VideoDescription> VideoDeviceManager::GetVideoDeviceFormats(const std::string& device_id) {
    if (!video_device_ds_ || device_id.empty()) {
        return std::vector<VideoDescription>();
    }
    if (video_description_[device_id].empty()) {
        video_description_[device_id] = video_device_ds_->GetVideoDeviceFormats(device_id);
    }
    return video_description_[device_id];
}

void VideoDeviceManager::RegisterDeviceStatusCallback(std::shared_ptr<DeviceStatusCallback> callback) {

}
    