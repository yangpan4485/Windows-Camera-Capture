#pragma once

#include <initguid.h> 
#include <vector>
#include <dshow.h>
#include <cguid.h>
#include <dvdmedia.h>

#include "../common/video_frame.h"
#include "sink_filter_ds.h"

class VideoDeviceDS;
class VideoCaptureDS {
public:
    using VideoFrameCallback = std::function<void(VideoFrame& video_frame)>;
public:
    VideoCaptureDS();
    ~VideoCaptureDS();

    bool StartCapture(const VideoDevice& video_device, const VideoDescription& video_description);
    bool StopCapture();

    void RegisterVideoFrameCallback(VideoFrameCallback callback);

private:
    bool Init();
    HRESULT ConnectDVCamera();
    bool SetCameraOutput(const VideoDescription& video_description);
    bool DisconnectGraph();

private:
    bool initialed_{};
    bool running_{ false };

    VideoDevice video_device_{};
    VideoDescription video_description_{};

    std::unique_ptr<VideoDeviceDS> ds_device_{};

    IBaseFilter* capture_filter_{};
    IGraphBuilder* graph_builder_{};

    IMediaControl* media_control_{};
    IPin* input_send_pin_{};
    IPin* output_capture_pin_{};

    IBaseFilter* dv_filter_{};
    IPin* input_dv_pin_{};
    IPin* output_dv_pin_{};

    CaptureSinkFilter* sink_filter_{};
    VideoFrameCallback callback_{};
};