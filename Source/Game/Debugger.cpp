/*
*	Author: Elia Rönning
*/

#include "stdafx.h"
#ifndef _RETAIL
#include "Debugger.h"

#include "imgui.h"
#include <tga2d/engine.h>
#include <Psapi.h>

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

		std::cout << "mo------------.........................................``````````````````````````````````..........y\n";
		std::cout << "mo-----------............................................````````````````````````````````..........y\n";
		std::cout << "mo----------...............................-:/+oooooo+/:-..````````````````````````````````........y\n";
		std::cout << "mo--------..............................:+yhhhyyyyyhhhhhyso/-.``````````````````````````````.......y\n";
		std::cout << "mo-------............................-/oyhhhhhyyyyyhhhhyyyyyyo:.`````````````````````````````......y\n";
		std::cout << "mo------...........................-:/+syhhhhhyysyyyyyyyyyso+ooo/.```````````````````````````......y\n";
		std::cout << "mo------..........................:+oossssyyyssoooooooooooo++++/++-``````````````````````````......y\n";
		std::cout << "mo-----.........................-+sooooooo++++++++++++++++++++++++/-``````````````````````````.....y\n";
		std::cout << "mo-----........................:sysoooooo++++++++++++++++++++ooooo+/-`````````````````````````.....y\n";
		std::cout << "mo----........................-syysoooooooo++++++++++++++++++oooosss+.````````````````````````.....y\n";
		std::cout << "mo----......................../yyysooooooo+++++/+++///++++++++ooossys/`````````````````````````....y\n";
		std::cout << "mo--..........................ohyysoooooo++++++++++++++++++++++oosyyy+.````````````````````````....y\n";
		std::cout << "mo--..........................+hyysoooossssyyssssoooosyhhhhhyysoosyyyo.````````````````````...`....y\n";
		std::cout << "mo-.........................../yyysosyhhhddmdhhssoooshdmddhhyyysoosyyo.`````````````````````.......y\n";
		std::cout << "mo--..........................:yyyoosyyhhddmmmdyo+++shdmdmmdhhhsoosyy/``````````````````.```.......y\n";
		std::cout << "mo-............................+yyoosyddhdmdhdyso+++osyhhhhhyyysoosys:..````````````````...........y\n";
		std::cout << "mo-............................-oysossyyyyyyysooo++++ooossssoo+++oosoos/.`````````````.............y\n";
		std::cout << "mo............................:+syooooooooooooooo+/+++o++++++++++++osoyo.```````````...............y\n";
		std::cout << "mo-..........................-yhysoooooooooooooooo++oooo++++o++++oooyyo/.`````````.................y\n";
		std::cout << "mo-...........................oyshooooooooooossyhyyyhdys++ooooooooossyo-...`.......................y\n";
		std::cout << "mo-............................oyhyooooooooooshddhhhhhyo++ooooooooosoo+............................y\n";
		std::cout << "mo-............................-osysoossssoooossyhyyyyso+ooooooosooso+-............................y\n";
		std::cout << "mo--............................-+ssoosssssssssyyyyyyhyyyyhsoooooo+--..............................y\n";
		std::cout << "mo--..............................::/ossssyhdddddhhhyhhhhyyyssoooo/................................y\n";
		std::cout << "mo----...............................+sssssyssyyyyyyyyysooossssooo-................................y\n";
		std::cout << "mo----...............................-ossssyssssyyyhyyssoosssssss/.................................y\n";
		std::cout << "mo------..............................-ossssssssooooooooooooosss:..................................y\n";
		std::cout << "mo--------.............................+osssoooooooooo++++oossso-..................................y\n";
		std::cout << "mo--------.............................+ossssssssssssssssssyysss-..................................y\n";
		std::cout << "mo------------.-.......................osssssyyyyhhhhhhhhyyyysso:..................................y\n";
		std::cout << "mo-----------------....................ossssssssyyyhhhyysssyysso/..................................y\n";
		std::cout << "mo-----------------...................:osssssssssyyyyyysssssssso+..................................y\n";
		std::cout << "mo---------------------............-:+ooossssssssssyyyyyssssssooo:.................................y\n";
		std::cout << "mo----------------------..---/o/::+oooooosssssssssyyyyysssssssooo+/:/:-............................y\n";
		std::cout << "mo-----------------------/oshh+/++ooooooooosssssssyyyysssssssooooo++sdyo:-.........................y\n";
		std::cout << "mo-----------------:/+osshdhmmh++++++ooooosssssssssysssssssssoooo++ymmddhs+/---....................y\n";
		std::cout << "mo---------:/+ossyyhhhddhddddmmho++++ooooosssssssssyyysssssssoooosdmmmmmddhhysoo+/:---.............h\n";
		std::cout << "mo----::/oyhddddddddddmmmmmmddmmdso++++ooooossssssssssssssssoooydmNmmmmmmmmmmmdddhysso+:-----------h\n";
		std::cout << "mo::+syhdddddddddddddddddmmmmmdmmmdyoo++ooooossssyyyyyssssssshmNNNmmmmmmmmmmmddhyyyhdhhhys+:-------h\n";
		std::cout << "myyhdddmmmddmmmmmmmmmmmmmmmmmmmmmmmmmhso+++++oosyyyyyyssyyhdNNNNmmmmmmmmmdddhyyhhddhhhhyhhhhs+:----h\n";
		std::cout << "mddmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmNNmmdhyssssyyhhhddmNNNNNNmmmmmmmmmddddddmmmmmmdddddmmmmddhs/--h\n";
		std::cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmdhhs/h\n";
		std::cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNmmmmmmmmmmmmmmmmmmmmmmmmmmmmmdddddddhm\n";
		std::cout << "mNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNmmmmmmmmNNmNNNmm\n";
		std::cout << "mNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n";
		std::cout << "mNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n";
		std::cout << "mNNNNNNNNNNNNNNNNNmdNmdNdmmhhhNdNNNNNdmNdmmhhdNdNNNmmNdNdhhmNhhdNmhhmNdhdNmhhmNhNNdNNNNNNNNNNNNNNNNN\n";
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

#endif