// Basics
#include "stdafx.h"
#include "GameWorld.h"

// Core
#include "Game.h"
#include "GameObject.h"
#include "InputWrapper.h"

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
	, myDeltaTime(0.0f)
	, myTotalTime(0.0f)
	, myLevelScene(LevelScene())
{
	myTimer = std::make_unique<Utils::Timer>();
	myInput = std::make_shared<InputWrapper>();
	myInput->Init();

	if (!ourInstance)
	{
		ourInstance = this;
	}
}

CGameWorld::~CGameWorld() 
{
	myLevelScene.Unload();
}

void CGameWorld::Init()
{
	myLevelScene.Activate();
}

void CGameWorld::Update()
{
	myTimer->Update();
	myDeltaTime = myTimer->GetDeltaTime();
	myInput->Update(myDeltaTime);

	Scene::Manager::Update(myDeltaTime);
}

void CGameWorld::Render()
{
	Scene::Manager::Render();
}
