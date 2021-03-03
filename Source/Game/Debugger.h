/*
*	Author: Elia Rönning
*/

#ifndef _RETAIL
#pragma once

class Debugger
{
public:
	Debugger();
	Debugger(const Debugger& aDebugger) = delete;
	~Debugger();

	void Update(const float& aDeltaTime);

	void Activate();
	void Deactivate();
	void Toggle();

private:
	bool myIsActive;
};
#endif

