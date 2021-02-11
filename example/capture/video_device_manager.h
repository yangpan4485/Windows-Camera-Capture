#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

#include "../common/video_frame.h"

class VideoDeviceDS;
class VideoDeviceManager {
public:
    using DeviceStatusCallback = std::function<void(const std::string& device_id, const VideoDeviceStatus& status)>;
public:
    static VideoDeviceManager& Instance();
    std::vector<VideoDevice> GetVideoCaptureDevices();
    std::vector<VideoDescription> GetVideoDeviceFormats(const std::string& device_id);
    void RegisterDeviceStatusCallback(std::shared_ptr<DeviceStatusCallback> callback);

private:
    VideoDeviceManager();
    ~VideoDeviceManager();
    VideoDeviceManager(const VideoDeviceManager&) = delete;
    VideoDeviceManager operator = (const VideoDeviceManager&) = delete;

private:
    std::weak_ptr<DeviceStatusCallback> callback_{};
    std::unique_ptr<VideoDeviceDS> video_device_ds_{};

    // 当有设备插入或者拔出时做删除
    std::vector<VideoDevice> video_devices_{};
    std::unordered_map<std::string, std::vector<VideoDescription>> video_description_{};

};