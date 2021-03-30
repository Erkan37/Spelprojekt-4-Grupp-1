#pragma once
#include "GameObject.h"

class Timer : public GameObject
{
public:
	Timer();

	void Start();
	void Paus();
	void Update(float aDeltatime);
	void Render();

private:
	
	float myTime;
};

