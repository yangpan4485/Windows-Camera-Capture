#pragma once

#include <initguid.h> 
#include <vector>
#include <dshow.h>
#include <cguid.h>
#include <dvdmedia.h>

#include "../common/video_frame.h"

class VideoDeviceDS {
public:
    VideoDeviceDS();
    ~VideoDeviceDS();

    std::vector<VideoDevice> GetVideoCaptureDevices();
    std::vector<VideoDescription> GetVideoDeviceFormats(const std::string& device_id);

    bool Init();

    IBaseFilter* GetDeviceFilter(const std::string& device_id);
    

private:
    ICreateDevEnum* ds_dev_enum_{};
    IEnumMoniker* ds_enum_moniker_{};
    bool initialed_{ false };
};