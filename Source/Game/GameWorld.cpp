// Basics
#include "stdafx.h"
#include "GameWorld.h"

// Core
#include "Game.h"
#include "GameObject.h"

// Scene
#include "Scene.h"
#include "LevelScene.h"

// I/O
#include "Keys.h"
#include <math.h>
#include "../External/Headers/CU/Utilities.h"

CGameWorld* CGameWorld::ourInstance = nullptr;

CGameWorld::CGameWorld(CGame* aGame)
	: myGame(aGame)
	, myTimer(new Utils::Timer())
	, myInput(new Utils::Input())
	, myDeltaTime(0.0f)
	, myTotalTime(0.0f)
	, myLevelScene(LevelScene())
{
	if (!ourInstance)
	{
		ourInstance = this;
	}
}

CGameWorld::~CGameWorld() 
{
	if (myTimer)
	{
		delete myTimer;
		myTimer = nullptr;
	}
	if (myInput)
	{
		delete myInput;
		myInput = nullptr;
	}

	myLevelScene.Unload();
}

void CGameWorld::Init()  
{
	myLevelScene.Activate();
}

void CGameWorld::Update()
{
	myInput->Update();

	myTimer->Update();
	myDeltaTime = myTimer->GetDeltaTime();

	Scene::Manager::Update(myDeltaTime);
}

void CGameWorld::Render()
{
	Scene::Manager::Render();
}
