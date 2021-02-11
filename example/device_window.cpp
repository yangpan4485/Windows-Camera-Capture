#include "device_window.h"

#include "capture/video_device_manager.h"
#include "common/string_utils.h"
#include "common/json.hpp"

#include <iostream>
#include <fstream>

using Json = nlohmann::json;

DeviceWindow::DeviceWindow() {

}

DeviceWindow::~DeviceWindow() {
    DestroyWindow(GetParent(this->GetHWND()));
}

LPCTSTR DeviceWindow::GetWindowClassName() const {
    return _T("DUIDeviceFrame");
}

UINT DeviceWindow::GetClassStyle() const {
    return UI_CLASSSTYLE_DIALOG;
}

void DeviceWindow::Notify(DuiLib::TNotifyUI& msg) {
    auto name = msg.pSender->GetName();
    if (msg.sType == _T("click")) {
        // std::cout << "name:" << name << std::endl;
        if (name == "btnOk") {
            for (size_t i = 0; i < option_vec_.size(); ++i) {
                auto option = dynamic_cast<DuiLib::COptionUI*>(paint_manager_.FindControl(option_vec_[i].c_str()));
                if (option && option->IsSelected()) {
                    if (callback_) {
                        callback_(devices_[i]);
                        UpdateConfig(devices_[i].device_id);
                    }
                    break;
                }
            }
            Close();
        }
        
    }
}

LRESULT DeviceWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT lRes = 0;
    switch (uMsg) {
    case WM_CREATE:
        lRes = OnCreate(uMsg, wParam, lParam);
        break;
    case WM_CLOSE:
        lRes = OnClose(uMsg, wParam, lParam);
        break;
    }
    if (paint_manager_.MessageHandler(uMsg, wParam, lParam, lRes))
    {
        return lRes;
    }
    return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT DeviceWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) {
    return 0;
}

LRESULT DeviceWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    paint_manager_.Init(m_hWnd);
    paint_manager_.AddPreMessageFilter(this);
    DuiLib::CDialogBuilder builder;
    DuiLib::CControlUI* pRoot = builder.Create(_T("device_window.xml"), (UINT)0, NULL, &paint_manager_);
    paint_manager_.AttachDialog(pRoot);
    paint_manager_.AddNotifier(this);
    InitWindow();
    return 0;
}
LRESULT DeviceWindow::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam) {

    return 0;
}

void DeviceWindow::RegisterDeviceCallback(DeviceCallback callback) {
    callback_ = callback;
}

void DeviceWindow::InitWindow() {
    std::string filename = DuiLib::CPaintManagerUI::GetInstancePath() + _T("..\\..\\..\\config.json");
    std::ifstream fin(filename, std::ios::in | std::ios::binary);
    std::string device_id = "";
    if (fin) {
        fin.seekg(0, std::ios_base::end);
        int size = fin.tellg();
        fin.seekg(0);
        char* data = new char[size + 1];
        data[size] = '\0';
        fin.read(data, size);
        fin.close();
        Json config = Json::parse(data);
        device_id = config["camera"];
    }
    else {
        std::cout << "fin open file failed" << std::endl;
    }
    
    auto device_window = dynamic_cast<DuiLib::CVerticalLayoutUI*>(paint_manager_.FindControl(_T("deviceWindow")));
    LONG startX = 10;
    LONG startY = 5;
    LONG width = 150;
    LONG height = 30;
    DuiLib::CLabelUI* inputLabel = new DuiLib::CLabelUI;
    inputLabel->SetText(_T("选择摄像头"));
    inputLabel->SetName(_T("videoSwitch"));
    inputLabel->SetFloat(true);
    inputLabel->SetFont(0);
    SIZE leftTop = { startX,startY };
    inputLabel->SetFixedXY(leftTop);
    inputLabel->SetFixedWidth(width);
    inputLabel->SetFixedHeight(height);
    device_window->Add(inputLabel);

    devices_ = VideoDeviceManager::Instance().GetVideoCaptureDevices();
    if (device_id.empty()) {
        device_id = devices_[0].device_id;
    }
    std::string device_name = "camera";
    option_vec_.swap(std::vector<std::string>());
    for (size_t i = 0; i < devices_.size(); ++i) {
        device_name = "camera_";
        DuiLib::COptionUI* option = new DuiLib::COptionUI;
        DuiLib::CLabelUI* label = new DuiLib::CLabelUI;
        label->SetText(utils::Utf8ToAscii(devices_[i].device_name).c_str());
        device_name = device_name + std::to_string(i);
        option->SetName(device_name.c_str());
        option_vec_.push_back(device_name);
        option->SetFloat(true);
        label->SetFloat(true);
        option->SetFont(0);
        label->SetFont(0);
        startY = startY + 40;
        SIZE leftTop = { startX,startY };
        option->SetFixedXY(leftTop);
        option->SetFixedWidth(20);
        option->SetFixedHeight(20);
        label->SetFixedXY({ startX + 22,startY });
        label->SetFixedWidth(580);
        label->SetFixedHeight(20);
        option->SetNormalImage(_T("common\\radio_un.png"));
        option->SetSelectedImage(_T("common\\radio_sel.png"));
        option->SetGroup(_T("cameraGroup"));
        if (i== 0 || device_id == devices_[i].device_id) {
            option->Selected(true);
        }
        device_window->Add(option);
        device_window->Add(label);
    }
    RECT rect;
    GetWindowRect(m_hWnd, &rect);
    int nwidth = (rect.right - rect.left);
    /*std::cout << "width:" << (rect.right - rect.left) << std::endl;
    std::cout << "height:" << (rect.bottom - rect.top) << std::endl;*/
    startX = nwidth - 180;
    startY = startY + 40;
    DuiLib::CButtonUI* button = new DuiLib::CButtonUI;
    button->SetText(_T("确定"));
    button->SetName(_T("btnOk"));
    button->SetFloat(true);
    button->SetFont(0);
    button->SetPushedImage("common\\button_pushed.png");
    button->SetNormalImage("common\\button_normal.png");
    button->SetFocusedImage("common\\button_hover.png");
    leftTop = { startX,startY };
    button->SetFixedXY(leftTop);
    button->SetFixedWidth(100);
    button->SetFixedHeight(height);
    device_window->Add(button);
}

void DeviceWindow::UpdateConfig(const std::string& device_id) {
    // std::cout << "UpdateConfig" << std::endl;
    Json config;
    config["camera"] = device_id;
    std::string data = config.dump();
    std::string filename = DuiLib::CPaintManagerUI::GetInstancePath() + _T("..\\..\\..\\config.json");
    std::ofstream fout(filename, std::ios::binary | std::ios::out);
    if (!fout) {
        std::cout << "fout open file failed" << std::endl;
        return;
    }
    fout.write((char*)data.c_str(), data.size());
    fout.close();
}