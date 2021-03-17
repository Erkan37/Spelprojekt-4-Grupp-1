#pragma once
#include <fstream>
#include <string>
#include "GameWorld.h"

#ifndef _RETAIL
#include "Debugger.h"
#endif

namespace std
{
	class thread;
}

class Config
{
public:
	Config() = delete;
	Config(const Config& aConfig) = delete;
	~Config() = delete;

	static uint16_t width;
	static uint16_t height;
	static std::wstring appName;
	static v2f ourReferenceSize;
};

class CGame
{
public:
	CGame();
	~CGame();
	bool Init(const std::wstring& aVersion = L"", HWND aHWND = nullptr);

	static void SetResolution(const uint16_t& aWidth, const uint16_t& aHeight);

private:
	void InitCallBack();
	void UpdateCallBack();
	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	CGameWorld myGameWorld;
	std::thread* myThread;
	std::atomic<bool> myActive;

	Utils::Timer* myTimer;

#ifndef _RETAIL
	Debugger myDebugger;
#endif
};