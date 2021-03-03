#pragma once

namespace Utils
{
	class Timer;
	class Input;
}

class CGame;
class InputWrapper;

#include "LevelScene.h"

class CGameWorld
{
public:
	friend CGame;

	inline static CGameWorld* GetInstance()
	{
		return ourInstance;
	}

	CGameWorld(CGame* aGame); 
	~CGameWorld();

	void Init();
	void Update(); 
	void Render();

	inline const float& DeltaTime() const
	{
		return myDeltaTime;
	}
	inline const float& TotalTime() const
	{
		return myTotalTime;
	}
	inline std::shared_ptr<InputWrapper> Input()
	{
		return myInput;
	}
	inline CGame* Game()
	{
		return myGame;
	}

private:
	/*** System ***/
	Utils::Timer* myTimer;
	//Utils::Input* myInput;
	CGame* myGame;
	std::shared_ptr<InputWrapper> myInput;
	float myDeltaTime;
	float myTotalTime;

	LevelScene myLevelScene;

	static CGameWorld* ourInstance;
};