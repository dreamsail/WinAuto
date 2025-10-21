#pragma once
#include <Windows.h>
#include<iostream>
#include<vector>

class WinAutoWindowsList;

class WinAutoWindows {
public:
	WinAutoWindows(HWND hwnd);
	~WinAutoWindows();
	void click();
	void setTitle(std::wstring title);

	WinAutoWindowsList windowsList();

	static BOOL CALLBACK wndEnumProc(HWND hwnd, LPARAM lparam);
public:
	HWND hwnd;
	DWORD processId;
	std::wstring title;
	std::wstring className;
	DWORD style;
private:
};

class WinAutoWindowsList {
public:
	WinAutoWindowsList();
	~WinAutoWindowsList();
	void clear() {
		this->list.clear();
	}
	size_t size() {
		return this->list.size();
	}
	WinAutoWindows at(size_t pos) {
		return this->list.at(pos);
	}
	void push_back(WinAutoWindows windows) {
		this->list.push_back(windows);
	}
	WinAutoWindowsList filterByProcessId(DWORD processId);
	WinAutoWindowsList filterByTitle(std::wstring title);
	WinAutoWindowsList filterByClassName(std::wstring className);
	WinAutoWindowsList filterByStyle(DWORD style);
private:
	std::vector<WinAutoWindows>list;
};

class WinAutoApp
{
public:
	WinAutoApp(std::wstring applicationPath);
	~WinAutoApp();
	BOOL isRunning();

	WinAutoWindowsList windowsList();
	static BOOL CALLBACK wndEnumProc(HWND hwnd, LPARAM lparam);

public:
	BOOL success;
private:
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInformation;
};


class WinAuto
{
public:
	static WinAutoApp start(std::wstring applicationPath);
};

