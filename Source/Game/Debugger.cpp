/*
*	Author: Elia Rönning
*/

#include "stdafx.h"
#ifndef _RETAIL
#include "Debugger.h"

#include "imgui.h"
#include <tga2d/engine.h>
#include <Psapi.h>

#include "GameWorld.h"
#include "../External/Headers/CU/Utilities.h"
#include "InputWrapper.h"
#include <iostream>

uint32_t globalAllocCounter = 0Ui32;

void* operator new(size_t aSize)
{
	++globalAllocCounter;

	return malloc(aSize);
}

Debugger::Debugger()
	: myIsActive(
#ifdef _DEBUG
		true
#else
		false
#endif
	)
{
}

Debugger::~Debugger()
{
	myIsActive = false;
}

void Debugger::Update(const float& aDeltaTime)
{
	if (!myIsActive) return;

	/* FPS */
	int FPS = (int)(1.0f / aDeltaTime);
	char FPSString[32];
	sprintf_s(FPSString, "%i", FPS);

	/* Draw Calls */
	int drawCalls = Tga2D::CEngine::GetInstance()->GetDrawCalls();
	char drawCallsString[32];
	sprintf_s(drawCallsString, "%i", drawCalls);

	/* Memory Usage */
	PROCESS_MEMORY_COUNTERS memCounter;
	BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));

	if (!result)
	{
		return;
	}

	constexpr double inverse1024 = 1.0 / 1024;
	constexpr double inverse1024sqr = inverse1024 * inverse1024;

	int memUsed = static_cast<int>((memCounter.WorkingSetSize) * inverse1024);
	int memUsedMb = static_cast<int>((memCounter.WorkingSetSize) * inverse1024sqr);

	char memUsedStr[32];
	char memUsedMbStr [32];
	sprintf_s(memUsedStr, "%i KB", memUsed);
	sprintf_s(memUsedMbStr, " (%i MB)", memUsedMb);
	strcat_s(memUsedStr, memUsedMbStr);

	/* Heap Allocations */
	char allocsStr[32];
	sprintf_s(allocsStr, "%u", globalAllocCounter);
	globalAllocCounter = 0Ui32;

	/* ImGui */
	ImGui::Begin("Debugger", &myIsActive, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("FPS: ");
	ImGui::SameLine();
	ImGui::Text(FPSString);

	ImGui::SameLine();

	ImGui::Text("Draw Calls: ");
	ImGui::SameLine();
	ImGui::Text(drawCallsString);

	ImGui::Text("Memory: ");
	ImGui::SameLine();
	ImGui::Text(memUsedStr);

	ImGui::Text("Allocs: ");
	ImGui::SameLine();
	ImGui::Text(allocsStr);

	ImGui::End();
}

void Debugger::Activate()
{
	myIsActive = true;
}

void Debugger::Deactivate()
{
	myIsActive = false;
}

void Debugger::Toggle()
{
	myIsActive = !myIsActive;
}

void Debugger::Init()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, 0, 0, 1920, 1080, TRUE);

	SetActiveWindow(console);

	COORD coordinates;
	coordinates.X = 0;
	coordinates.Y = 0;

	DWORD windowStyle = WS_VISIBLE | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	SetConsoleDisplayMode(console, windowStyle, &coordinates);

	ShowWindow(console, SW_SHOWMAXIMIZED);

	CGameWorld::GetInstance()->Input()->GetInput()->ToggleCaptureCursor(true);

	constexpr int interval = 100;

	std::cout << "mo------------.........................................``````````````````````````````````..........y\n";
	Sleep(interval);
	std::cout << "mo-----------............................................````````````````````````````````..........y\n";
	Sleep(interval);
	std::cout << "mo----------...............................-:/+oooooo+/:-..````````````````````````````````........y\n";
	Sleep(interval);
	std::cout << "mo--------..............................:+yhhhyyyyyhhhhhyso/-.``````````````````````````````.......y\n";
	Sleep(interval);
	std::cout << "mo-------............................-/oyhhhhhyyyyyhhhhyyyyyyo:.`````````````````````````````......y\n";
	Sleep(interval);
	std::cout << "mo------...........................-:/+syhhhhhyysyyyyyyyyyso+ooo/.```````````````````````````......y\n";
	Sleep(interval);
	std::cout << "mo------..........................:+oossssyyyssoooooooooooo++++/++-``````````````````````````......y\n";
	Sleep(interval);
	std::cout << "mo-----.........................-+sooooooo++++++++++++++++++++++++/-``````````````````````````.....y\n";
	Sleep(interval);
	std::cout << "mo-----........................:sysoooooo++++++++++++++++++++ooooo+/-`````````````````````````.....y\n";
	Sleep(interval);
	std::cout << "mo----........................-syysoooooooo++++++++++++++++++oooosss+.````````````````````````.....y\n";
	Sleep(interval);
	std::cout << "mo----......................../yyysooooooo+++++/+++///++++++++ooossys/`````````````````````````....y\n";
	Sleep(interval);
	std::cout << "mo--..........................ohyysoooooo++++++++++++++++++++++oosyyy+.````````````````````````....y\n";
	Sleep(interval);
	std::cout << "mo--..........................+hyysoooossssyyssssoooosyhhhhhyysoosyyyo.````````````````````...`....y\n";
	Sleep(interval);
	std::cout << "mo-.........................../yyysosyhhhddmdhhssoooshdmddhhyyysoosyyo.`````````````````````.......y\n";
	Sleep(interval);
	std::cout << "mo--..........................:yyyoosyyhhddmmmdyo+++shdmdmmdhhhsoosyy/``````````````````.```.......y\n";
	Sleep(interval);
	std::cout << "mo-............................+yyoosyddhdmdhdyso+++osyhhhhhyyysoosys:..````````````````...........y\n";
	Sleep(interval);
	std::cout << "mo-............................-oysossyyyyyyysooo++++ooossssoo+++oosoos/.`````````````.............y\n";
	Sleep(interval);
	std::cout << "mo............................:+syooooooooooooooo+/+++o++++++++++++osoyo.```````````...............y\n";
	Sleep(interval);
	std::cout << "mo-..........................-yhysoooooooooooooooo++oooo++++o++++oooyyo/.`````````.................y\n";
	Sleep(interval);
	std::cout << "mo-...........................oyshooooooooooossyhyyyhdys++ooooooooossyo-...`.......................y\n";
	Sleep(interval);
	std::cout << "mo-............................oyhyooooooooooshddhhhhhyo++ooooooooosoo+............................y\n";
	Sleep(interval);
	std::cout << "mo-............................-osysoossssoooossyhyyyyso+ooooooosooso+-............................y\n";
	Sleep(interval);
	std::cout << "mo--............................-+ssoosssssssssyyyyyyhyyyyhsoooooo+--..............................y\n";
	Sleep(interval);
	std::cout << "mo--..............................::/ossssyhdddddhhhyhhhhyyyssoooo/................................y\n";
	Sleep(interval);
	std::cout << "mo----...............................+sssssyssyyyyyyyyysooossssooo-................................y\n";
	Sleep(interval);
	std::cout << "mo----...............................-ossssyssssyyyhyyssoosssssss/.................................y\n";
	Sleep(interval);
	std::cout << "mo------..............................-ossssssssooooooooooooosss:..................................y\n";
	Sleep(interval);
	std::cout << "mo--------.............................+osssoooooooooo++++oossso-..................................y\n";
	Sleep(interval);
	std::cout << "mo--------.............................+ossssssssssssssssssyysss-..................................y\n";
	Sleep(interval);
	std::cout << "mo------------.-.......................osssssyyyyhhhhhhhhyyyysso:..................................y\n";
	Sleep(interval);
	std::cout << "mo-----------------....................ossssssssyyyhhhyysssyysso/..................................y\n";
	Sleep(interval);
	std::cout << "mo-----------------...................:osssssssssyyyyyysssssssso+..................................y\n";
	Sleep(interval);
	std::cout << "mo---------------------............-:+ooossssssssssyyyyyssssssooo:.................................y\n";
	Sleep(interval);
	std::cout << "mo----------------------..---/o/::+oooooosssssssssyyyyysssssssooo+/:/:-............................y\n";
	Sleep(interval);
	std::cout << "mo-----------------------/oshh+/++ooooooooosssssssyyyysssssssooooo++sdyo:-.........................y\n";
	Sleep(interval);
	std::cout << "mo-----------------:/+osshdhmmh++++++ooooosssssssssysssssssssoooo++ymmddhs+/---....................y\n";
	Sleep(interval);
	std::cout << "mo---------:/+ossyyhhhddhddddmmho++++ooooosssssssssyyysssssssoooosdmmmmmddhhysoo+/:---.............h\n";
	Sleep(interval);
	std::cout << "mo----::/oyhddddddddddmmmmmmddmmdso++++ooooossssssssssssssssoooydmNmmmmmmmmmmmdddhysso+:-----------h\n";
	Sleep(interval);
	std::cout << "mo::+syhdddddddddddddddddmmmmmdmmmdyoo++ooooossssyyyyyssssssshmNNNmmmmmmmmmmmddhyyyhdhhhys+:-------h\n";
	Sleep(interval);
	std::cout << "myyhdddmmmddmmmmmmmmmmmmmmmmmmmmmmmmmhso+++++oosyyyyyyssyyhdNNNNmmmmmmmmmdddhyyhhddhhhhyhhhhs+:----h\n";
	Sleep(interval);
	std::cout << "mddmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmNNmmdhyssssyyhhhddmNNNNNNmmmmmmmmmddddddmmmmmmdddddmmmmddhs/--h\n";
	Sleep(interval);
	std::cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmdhhs/h\n";
	Sleep(interval);
	std::cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNmmmmmmmmmmmmmmmmmmmmmmmmmmmmmdddddddhm\n";
	Sleep(interval);
	std::cout << "mNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNmmmmmmmmNNmNNNmm\n";
	Sleep(interval);
	std::cout << "mNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n";
	Sleep(interval);
	std::cout << "mNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n";
	Sleep(interval);
	std::cout << "mNNNNNNNNNNNNNNNNNmdNmdNdmmhhhNdNNNNNdmNdmmhhdNdNNNmmNdNdhhmNhhdNmhhmNdhdNmhhmNhNNdNNNNNNNNNNNNNNNNN\n";
}

#endif