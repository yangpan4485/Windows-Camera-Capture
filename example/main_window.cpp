#include "main_window.h"

#include <iostream>

#include "capture/video_device_manager.h"
#include "capture/video_capture.h"
#include "device_window.h"
#include "my_window.h"
#include "render/sdl2/video_render_sdl.h"

const uint32_t kDefaultWidth = 640;
const uint32_t kDefaultHeight = 480;

MainWindow::MainWindow() : video_capture_(new VideoCapture()) ,
                           render_(new SDLRender()){

}

MainWindow::~MainWindow() {

}

void MainWindow::Init() {
    SetProcessDPIAware();
    hinstance_ = GetModuleHandle(0);
    DuiLib::CPaintManagerUI::SetInstance(hinstance_);
    DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath() + _T("..\\..\\..\\resources"));
}

void MainWindow::CreateDuiWindow() {
    Create(NULL, _T("MainWindow"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
}

void MainWindow::Show() {
    ShowModal();
}

LPCTSTR MainWindow::GetWindowClassName() const {
    return _T("DUIMainFrame");
}

void MainWindow::Notify(DuiLib::TNotifyUI& msg) {
    auto name = msg.pSender->GetName();
    if (msg.sType == _T("click")) {
        if (name == "btnStart") {
            Start();
        }
        else if (name == "btnStop") {
            Stop();
        }
        else if (name == "btnChoose") {
            Choose();
        }
    }
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT lRes = 0;
    switch (uMsg) {
    case WM_CREATE:
        lRes = OnCreate(uMsg, wParam, lParam);
        break;
    case WM_CLOSE:
        lRes = OnClose(uMsg, wParam, lParam);
        break;
    default:
        break;
    }
    if (paint_manager_.MessageHandler(uMsg, wParam, lParam, lRes))
    {
        return lRes;
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT MainWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    paint_manager_.Init(m_hWnd);
    DuiLib::CDialogBuilder builder;
    DuiLib::CControlUI* pRoot = builder.Create(_T("main_window.xml"), (UINT)0, this, &paint_manager_);
    paint_manager_.AttachDialog(pRoot);
    paint_manager_.AddNotifier(this);
    return 0;
}

LRESULT MainWindow::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Stop();
    return 0;
}

DuiLib::CControlUI* MainWindow::CreateControl(LPCTSTR pstrClass) {
    std::cout << "CreateControl :" << pstrClass << std::endl;
    if (_tcscmp(pstrClass, _T("CWndUI")) == 0) {
        CWndUI* wndui = new CWndUI();
        HWND wnd = CreateWindow(_T("STATIC"), _T(""),
            WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
            0, 0, 900, 480, paint_manager_.GetPaintWindow(), (HMENU)0, NULL, NULL);
        wndui->Attach(wnd);
        return wndui;
    }
    return NULL;
}

void MainWindow::Start() {
    if (running_) {
        return;
    }
    video_capture_->RegisterVideoFrameCallback([&](VideoFrame& video_frame) {
        // std::cout << "frame:" << std::endl;
        Render(video_frame.y_data, video_frame.width, video_frame.height);
    });
    if (video_device_.device_id.empty()) {
        auto devices = VideoDeviceManager::Instance().GetVideoCaptureDevices();
        video_device_ = devices[0];
    }

    auto formats = VideoDeviceManager::Instance().GetVideoDeviceFormats(video_device_.device_id);
    VideoDescription format = formats[0];
    for (size_t i = 0; i < formats.size(); ++i) {
        if (formats[i].width == kDefaultWidth || formats[i].height == kDefaultHeight) {
            format = formats[i];
            break;
        }
    }
    video_capture_->SelectVideoDevice(video_device_);
    video_capture_->SelectVideoFormat(format);
    video_capture_->StartCapture();
    running_ = true;
}

void MainWindow::Stop() {
    if (running_) {
        video_capture_->StopCapture();
        running_ = false;
    }
}

void MainWindow::Choose() {
    if (device_window_ && IsWindow(device_hwnd_)) {

        return;
    }
    device_window_ = std::make_unique<DeviceWindow>();
    // std::cout << "create window:" << std::endl;
    device_hwnd_ = device_window_->Create(m_hWnd, _T("—°‘Ò…Ë±∏"), UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
    auto devices = VideoDeviceManager::Instance().GetVideoCaptureDevices();
    int width = 0;
    int height = devices.size() * 50 + 70;
    for (size_t i = 0; i < devices.size(); ++i) {
        int tmp = devices[i].device_name.length() * 30;
        if (tmp > width) {
            width = tmp;
        }
    }
    device_window_->RegisterDeviceCallback([this](const VideoDevice& video_device) {
        video_device_ = video_device;
        if (running_) {
            Stop();
            Start();
        }
    });
    device_window_->ResizeClient(width, height);
    device_window_->CenterWindow();
    this->ShowWindow(true);
}

void MainWindow::Render(uint8_t* data, int width, int height) {
    if (first_frame_) {
        auto wnd = (CWndUI*)(paint_manager_.FindControl("renderWindow"));
        render_->SetWindow(wnd->GetHwnd());
        first_frame_ = false;
    }
    render_->Render(data, width, height);
}