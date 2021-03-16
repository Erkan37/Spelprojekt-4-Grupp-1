// Basics
#include "stdafx.h"
#include "GameWorld.h"

// Core
#include "Game.h"
#include "GameObject.h"
#include "InputWrapper.h"
#include "AudioManager.h"
#include "TiledMap.h"

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
	, myMainMenuScene(MainMenuScene())
{
	myTimer = std::make_unique<Utils::Timer>();
	myInput = std::make_shared<InputWrapper>();
	myInput->Init();
	AudioManager::GetInstance()->Init();

	if (!ourInstance)
	{
		ourInstance = this;
	}
}

CGameWorld::~CGameWorld() 
{
	myLevelManager.UnloadAllScenes();
}

void CGameWorld::Init()
{
	myLevelManager.Init(&myMainMenuScene, &myLevelScene);
	myLevelManager.SingleLoadScene(LevelManager::eScenes::MainMenu);
}

void CGameWorld::Update()
{
	myTimer->Update();
	myDeltaTime = myTimer->GetDeltaTime();
	myInput->Update(myDeltaTime);

	if (myInput->GetInput()->GetKeyJustDown(Keys::NumericKeypad0Key) && !myLevelManager.GetIsActive(LevelManager::eScenes::MainMenu))
	{
		myLevelManager.SingleLoadScene(LevelManager::eScenes::MainMenu);
	}

	myLevelManager.Update();

	Scene::Manager::Update(myDeltaTime);
}

void CGameWorld::Render()
{
	Scene::Manager::Render();
}
