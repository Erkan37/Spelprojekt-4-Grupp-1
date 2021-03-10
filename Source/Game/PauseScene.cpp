#include "stdafx.h"
#include "PauseScene.h"
#include "UIManager.h"
#include "InputWrapper.h"
#include "GameWorld.h"


PauseScene::PauseScene()
	: myUIManager(nullptr)
	, myInputHandler(nullptr)
{}

PauseScene::~PauseScene()
{
	Unload();
}

void PauseScene::Load()
{
	CGameWorld* world = CGameWorld::GetInstance();
	myInputHandler = world->Input();

	myUIManager = new UIManager(this);
	GameObject* myResumeButton = new GameObject(this);
	GameObject* myMainMenuButton = new GameObject(this);

	//Load in data from DataManager?
}

void PauseScene::Unload()
{
	myUIManager->Destroy();

	myInputHandler = nullptr;
	myUIManager = nullptr;

	Scene::Unload();
}

void PauseScene::Activate()
{
	if (IsActive()) return;
	if (!IsLoaded()) Load();
	myUIManager->Activate();

	Scene::Activate();
}

void PauseScene::Deactivate()
{
	if (!IsActive()) return;

	myUIManager->Deactivate();

	Scene::Deactivate();
}

void PauseScene::Update(const float& aDeltaTime, const float& aTotalTime)
{
}
