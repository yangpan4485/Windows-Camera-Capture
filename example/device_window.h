#pragma once
#include <functional>

#include "UIlib.h"

#include "common/video_frame.h"

class DeviceWindow : public DuiLib::CWindowWnd, public DuiLib::INotifyUI, public DuiLib::IMessageFilterUI
{
public:
    using DeviceCallback = std::function<void(const VideoDevice& device)>;
public:
    DeviceWindow();
    ~DeviceWindow();

    LPCTSTR GetWindowClassName() const override;
    UINT GetClassStyle() const override;
    void Notify(DuiLib::TNotifyUI& msg) override;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
    LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam);

    void RegisterDeviceCallback(DeviceCallback callback);

private:
    void InitWindow();
    void UpdateConfig(const std::string& device_id);

public:
    DuiLib::CPaintManagerUI paint_manager_{};
    std::vector<VideoDevice> devices_{};

    DeviceCallback callback_{};
    std::vector<std::string> option_vec_{};
};