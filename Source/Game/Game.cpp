#include "stdafx.h"
#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/text/text.h>
#include "Game.h"

#include <tga2d/error/error_manager.h>

#include <windows.h>
#include <thread>
#include "../External/Headers/CU/Utilities.h"
#include "InputWrapper.h"

using namespace std::placeholders;

uint16_t Config::width = 1920U;
uint16_t Config::height = 1080U;
std::wstring Config::appName = L"epic game lit af";

#ifdef _DEBUG
#pragma comment(lib,"TGA2D_Debug.lib")
std::wstring BUILD_NAME = L"Debug";
#endif // DEBUG
#ifdef _RELEASE
#pragma comment(lib,"TGA2D_Release.lib")
std::wstring BUILD_NAME = L"Release";
#endif // DEBUG
#ifdef _RETAIL
#pragma comment(lib,"TGA2D_Retail.lib")
std::wstring BUILD_NAME = L"Retail";
#endif // DEBUG

CGame::CGame()
	: myGameWorld(this)
	, myThread(nullptr)
	, myActive(true)
	, myTimer(new Utils::Timer())
{}

CGame::~CGame()
{
	myActive = false;
	if (myThread)
	{
		if (myThread->joinable())
		{
			myThread->join();
		}
		delete myThread;
		myThread = nullptr;
	}
	if (myTimer)
	{
		delete myTimer;
		myTimer = nullptr;
	}
}

LRESULT CGame::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (myGameWorld.myInput->GetInput()->UpdateEvents(message, wParam, lParam))
	{
		return 0;
	}

	lParam;
	wParam;
	hWnd;
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	}
	case WM_KILLFOCUS:
	{
	}
	}

	return 0;
}


bool CGame::Init(const std::wstring& aVersion, HWND aHWND)
{
	Tga2D::SEngineCreateParameters createParameters;

	createParameters.myInitFunctionToCall = [this] {InitCallBack(); };
	createParameters.myWinProcCallback = [this](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {return WinProc(hWnd, message, wParam, lParam); };
	createParameters.myUpdateFunctionToCall = [this] {UpdateCallBack(); };
	createParameters.myApplicationName = Config::appName;

	HMONITOR monitor = MonitorFromWindow(aHWND, MONITOR_DEFAULTTONEAREST);
	MONITORINFO info;
	info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &info);
	int monitorWidth = info.rcMonitor.right - info.rcMonitor.left;
	int monitorHeight = info.rcMonitor.bottom - info.rcMonitor.top;

	createParameters.myTargetHeight = Config::height;
	createParameters.myTargetWidth = Config::width;
	createParameters.myWindowHeight = monitorHeight;
	createParameters.myWindowWidth = monitorWidth;
	createParameters.myClearColor = Tga2D::CColor(0.0f, 0.0f, 0.0f, 1.0f);
	createParameters.myWindowSetting = Tga2D::EWindowSetting::EWindowSetting_Borderless;
	//createParameters.myPreferedMultiSamplingQuality = Tga2D::EMultiSamplingQuality_High;
	createParameters.myActivateDebugSystems = 0;

	if (!Tga2D::CEngine::Start(createParameters))
	{
		ERROR_PRINT("Fatal error! Engine could not start!");
		system("pause");
		return false;
	}

	myActive = false;

	// End of program
	return true;
}

void CGame::InitCallBack()
{
	myGameWorld.Init();
	myThread = new std::thread([&]()
	{
		while (myActive)
		{
			myGameWorld.Update();
			myGameWorld.Render();
			myRenderer.IncrementLogicCounter();
			while (myRenderer.GetLogicCounter() > myRenderer.GetRenderCounter() && myActive);
		}
	});
}

void CGame::UpdateCallBack()
{
	myTimer->Update();
	myRenderer.Render();
#ifndef _RETAIL
	if (myGameWorld.myInput->GetInput()->GetKeyJustDown(Keys::F1Key))
	{
		myDebugger.Toggle();
	}

	myDebugger.Update(myTimer->GetDeltaTime());
#endif
}

Renderer& CGame::GetRenderer()
{
	return myRenderer;
}

void CGame::SetResolution(const uint16_t& aWidth, const uint16_t& aHeight)
{
	Config::width = aWidth;
	Config::height = aHeight;

	Tga2D::CEngine::GetInstance()->SetTargetSize({ aWidth, aHeight });
}