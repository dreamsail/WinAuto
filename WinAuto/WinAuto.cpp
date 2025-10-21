#include "WinAuto.h"

WinAutoApp::WinAutoApp(std::wstring applicationPath)
{

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    ZeroMemory(&processInformation, sizeof(processInformation));
    startupInfo.cb = sizeof(startupInfo);

    success = CreateProcess(
        applicationPath.c_str(),  // 应用程序路径
        NULL,          // 命令行参数
        NULL,             // 进程安全性
        NULL,             // 线程安全性
        FALSE,            // 句柄不继承
        0,                // 无特殊标志
        NULL,             // 环境块
        NULL,             // 当前目录
        &startupInfo,              // 启动信息
        &processInformation               // 进程信息
    );
}

WinAutoApp::~WinAutoApp()
{
    if (success)
    {
        TerminateProcess(processInformation.hProcess, 0);
        CloseHandle(processInformation.hProcess);
        CloseHandle(processInformation.hThread);
    }
}

BOOL WinAutoApp::isRunning()
{
    if (success)
    {
        DWORD exitCode;
        if (GetExitCodeProcess(processInformation.hProcess, &exitCode)) {
            return (exitCode == STILL_ACTIVE);
        }
    }
    return FALSE;
}

WinAutoWindowsList WinAutoApp::windowsList()
{
    WinAutoWindowsList windowsList;
    EnumWindows(WinAutoApp::wndEnumProc, (LPARAM)&windowsList);
    windowsList=windowsList.filterByProcessId(this->processInformation.dwProcessId);
    return windowsList;
}

BOOL WinAutoApp::wndEnumProc(HWND hwnd, LPARAM lparam)
{
    WinAutoWindowsList* lpWindowsList = (WinAutoWindowsList*)lparam;
    WinAutoWindows windows(hwnd);
    lpWindowsList->push_back(windows);
    return TRUE;
}

WinAutoApp WinAuto::start(std::wstring applicationPath)
{
    return WinAutoApp(applicationPath);
}

WinAutoWindows::WinAutoWindows(HWND hwnd)
{
    this->hwnd = hwnd;
    GetWindowThreadProcessId(hwnd, &this->processId);
    // 获取窗口标题
    title.resize(255);
    GetWindowText(hwnd, (TCHAR*)title.data(), 256); 
    //窗口类名
    className.resize(255);
    GetClassName(hwnd, (TCHAR*)className.data(), 255);
    //窗口样式
    style = GetWindowLong(hwnd, GWL_STYLE);
}

WinAutoWindows::~WinAutoWindows()
{
}

void WinAutoWindows::click()
{
    // 计算点击坐标（按钮中心）
    int x =  2;
    int y = 2;
    // 发送鼠标按下和弹起消息
    PostMessage(hwnd, WM_LBUTTONDOWN, 0, MAKELPARAM(x, y));
    PostMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(x, y));
}

void WinAutoWindows::setTitle(std::wstring title)
{
    SetWindowText(this->hwnd, title.c_str());
    SendMessage(this->hwnd, WM_SETTEXT, 0, (LPARAM)title.c_str());
    UpdateWindow(this->hwnd);
}

WinAutoWindowsList WinAutoWindows::windowsList() {
    WinAutoWindowsList windowsList;
    EnumChildWindows(this->hwnd, WinAutoWindows::wndEnumProc, (LPARAM)&windowsList);
    return windowsList;
}

BOOL WinAutoWindows::wndEnumProc(HWND hwnd, LPARAM lparam)
{
    WinAutoWindowsList* lpWindowsList = (WinAutoWindowsList*)lparam;
    WinAutoWindows windows(hwnd);
    lpWindowsList->push_back(windows);
    return TRUE;
}

WinAutoWindowsList::WinAutoWindowsList()
{
}

WinAutoWindowsList::~WinAutoWindowsList()
{
}

WinAutoWindowsList WinAutoWindowsList::filterByProcessId(DWORD processId)
{
    WinAutoWindowsList newList;
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if (it->processId == processId) {
            newList.push_back(*it);
        }
    }
    return newList;
}

WinAutoWindowsList WinAutoWindowsList::filterByTitle(std::wstring title)
{
    WinAutoWindowsList newList;
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if (lstrcmp(it->title.c_str(), title.c_str()) == 0) {
            newList.push_back(*it);
        }
    }
    return newList;
}

WinAutoWindowsList WinAutoWindowsList::filterByClassName(std::wstring className)
{
    WinAutoWindowsList newList;
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if (lstrcmp(it->className.c_str(), className.c_str()) == 0) {
            newList.push_back(*it);
        }
    }
    return newList;
}

WinAutoWindowsList WinAutoWindowsList::filterByStyle(DWORD style)
{
    WinAutoWindowsList newList;
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if (it->style == style) {
            newList.push_back(*it);
        }
    }
    return newList;
}
