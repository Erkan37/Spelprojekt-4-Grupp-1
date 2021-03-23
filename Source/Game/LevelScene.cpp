#include "stdafx.h"
#include "LevelScene.h"

#include "GameWorld.h"

#include "../External/Headers/CU/Utilities.h"

#include "Player.hpp"

#include "InputWrapper.h"

#include "Jesus.hpp"
#include "HiddenArea.hpp"

#include "LevelManager.hpp"

#include "Game.h"

#include "PostMaster.hpp"

LevelScene::LevelScene()
	: 
	myPlayer(nullptr),
	myBackground(nullptr),
	Scene()
{}

void LevelScene::Load()
{
	myPlayer = new Player(this);

	myBackground = new Background(this);

	CGameWorld::GetInstance()->GetLevelManager().LoadLevel(this, myPlayer);

	myPauseMenu = new PauseMenu(this);
	myPauseMenu->InitMenu();

	Scene::Load();
}

void LevelScene::Activate()
{
	Scene::Activate();

	GetCamera().StartFollowing(myPlayer, { 40.0f, 40.0f });
}

void LevelScene::Deactivate()
{
	Scene::Deactivate();

	GetCamera().StopFollowing();
}

void LevelScene::Update(const float& aDeltaTime)
{
	const float zoomX = CGameWorld::GetInstance()->Game()->GetZoomX();
	const float zoomY = CGameWorld::GetInstance()->Game()->GetZoomY();

	constexpr float aspectRatioX = 16.0f;
	constexpr float aspectRatioY = 9.0f;
	constexpr float sizeX = 1920.0f;
	constexpr float sizeY = 1080.0f;

	float zoomFactor = 1.0f;
	if (zoomX / aspectRatioX < zoomY / aspectRatioY)
	{
		zoomFactor = zoomX / sizeX;
	}
	else
	{
		zoomFactor = zoomY / sizeY;
	}

	const float zoom = 6.0f * zoomFactor;

	GetCamera().SetZoom(zoom);

	GetCamera().SetBounds(v2f(0.0f, 0.0f), v2f(1920.0f, 1080.0f));

	myPauseMenu->Update(aDeltaTime);

	if (myPauseMenu->IsPauseActive() == false)
		Scene::Update(aDeltaTime);
}

const GameObject* LevelScene::GetPlayer()
{
	return myPlayer;
}
