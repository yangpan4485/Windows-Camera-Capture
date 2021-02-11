#pragma once

#include <memory>

#include "UIlib.h"
#include "common/video_frame.h"

class VideoCapture;
class DeviceWindow;
class SDLRender;
class MainWindow : public DuiLib::CWindowWnd, public DuiLib::INotifyUI, DuiLib::IDialogBuilderCallback {
public:
    MainWindow();
    ~MainWindow();

    void Init();
    void CreateDuiWindow();
    void Show();

private:
    LPCTSTR GetWindowClassName() const override;
    void Notify(DuiLib::TNotifyUI& msg) override;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam);
    DuiLib::CControlUI* CreateControl(LPCTSTR pstrClass) override;

    void Start();
    void Stop();
    void Choose();

    void Render(uint8_t* data, int width, int height);

private:
    DuiLib::CPaintManagerUI paint_manager_{};
    HINSTANCE hinstance_{};

    std::unique_ptr<VideoCapture> video_capture_{};
    std::unique_ptr<DeviceWindow> device_window_{};
    std::unique_ptr<SDLRender> render_{};

    VideoDevice video_device_{};

    HWND device_hwnd_{};
    bool running_{ false };
    bool first_frame_{ true };
};