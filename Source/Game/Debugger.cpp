/*
*	Author: Elia Rönning
*/

#include "stdafx.h"
#ifndef _RETAIL
#include "Debugger.h"

#include "imgui.h"
#include <tga2d/engine.h>
#include <Psapi.h>

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
	sprintf(FPSString, "%i", FPS);

	/* Draw Calls */
	int drawCalls = Tga2D::CEngine::GetInstance()->GetDrawCalls();
	char drawCallsString[32];
	sprintf(drawCallsString, "%i", drawCalls);

	/* Memory Usage */
	PROCESS_MEMORY_COUNTERS memCounter;
	BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));

	if (!result)
	{
		return;
	}

	constexpr double inverse1024 = 1.0 / 1024;
	constexpr double inverse1024sqr = inverse1024 * inverse1024;

	int memUsed = (int)(memCounter.WorkingSetSize) * inverse1024;
	int memUsedMb = (int)(memCounter.WorkingSetSize) * inverse1024sqr;

	char memUsedStr[32];
	char memUsedMbStr [32];
	sprintf(memUsedStr, "%i KB", memUsed);
	sprintf(memUsedMbStr, " (%i MB)", memUsedMb);
	strcat(memUsedStr, memUsedMbStr);

	/* Heap Allocations */
	char allocsStr[32];
	sprintf(allocsStr, "%u", globalAllocCounter);
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