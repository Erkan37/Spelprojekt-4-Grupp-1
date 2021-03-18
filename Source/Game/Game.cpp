#include "stdafx.h"
#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/text/text.h>
#include "Game.h"
#include "InputWrapper.h"
#include "DataManager.h"

#include <tga2d/error/error_manager.h>

#include <windows.h>
#include <thread>
#include "../External/Headers/CU/Utilities.h"

using namespace std::placeholders;

v2f Config::ourReferenceSize = { 320.f, 240.f };
uint16_t Config::width = 1920U;
uint16_t Config::height = 1080U;
std::wstring Config::appName = L"Pass On";

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
	case WM_SIZE: 
	{
		SetResolution(LOWORD(lParam), HIWORD(lParam));
		SetZoom(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
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
	aVersion;

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

#ifdef _DEBUG
	createParameters.myWindowSetting = Tga2D::EWindowSetting::EWindowSetting_Overlapped;
#endif // DEBUG
#ifdef _RETAIL
	createParameters.myWindowHeight = static_cast<unsigned short>(monitorHeight);
	createParameters.myWindowWidth = static_cast<unsigned short>(monitorWidth);
	createParameters.myWindowSetting = Tga2D::EWindowSetting::EWindowSetting_Borderless;
#endif // RETAIL

	createParameters.myUseLetterboxAndPillarbox;

	createParameters.myTargetHeight = Config::height;
	createParameters.myTargetWidth = Config::width;
	createParameters.myClearColor = Tga2D::CColor(0.0f, 0.0f, 0.0f, 1.0f);
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
}

void CGame::UpdateCallBack()
{
	myTimer->Update();
	myGameWorld.Update();
	myGameWorld.Render();

	/*if (myGameWorld.myInput->GetInput()->GetKeyJustDown(Keys::ESCKey))
	{
		PostQuitMessage(0);
	}*/

#ifndef _RETAIL
	if (myGameWorld.myInput->GetInput()->GetKeyJustDown(Keys::F1Key))
	{
		myDebugger.Toggle();
	}

	myDebugger.Update(myTimer->GetDeltaTime());
#endif
}

void CGame::SetResolution(const uint16_t& aWidth, const uint16_t& aHeight)
{
	//Config::width = aWidth;
	//Config::height = aHeight;

	//Tga2D::CEngine::GetInstance()->SetTargetSize({ aWidth, aHeight });
}