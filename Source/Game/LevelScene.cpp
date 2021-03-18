#include "stdafx.h"
#include "LevelScene.h"

#include "GameWorld.h"
#include "TiledMap.h"

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"

#include "../External/Headers/CU/Utilities.h"

#include "Player.hpp"

#include "Ledge.h"

#include "MovingPlatform.hpp"
#include "UnstablePlatform.hpp"
#include "DestructiblePlatform.hpp"
#include "DeadlyPlatform.hpp"
#include "PlatformFactory.hpp"

#include "BashableObject.hpp"
#include "BashableObjectFactory.hpp"

#include "Bonfire.hpp"

#include "EnemyFactory.h"
#include "Enemy.h"

#include "Collectible.hpp"

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

	CGameWorld::GetInstance()->GetLevelManager().LoadLevel(this, "Levels/test_level4.json");

	Ledge* ledge = new Ledge(this);
	ledge->Init(v2f(128.0f, 176.0f), v2f(2.0f, 1.0f));
	ledge->Init(v2f(672.0f, 64.0f), v2f(2.0f, 1.0f));

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

	float zoomFactor = 1.0f;
	if (zoomX / 16.0f < zoomY / 9.0f)
	{
		zoomFactor = zoomX / 1920.0f;
	}
	else
	{
		zoomFactor = zoomY / 1080.0f;
	}

	const float zoom = 6.0f * zoomFactor;

	GetCamera().SetZoom(zoom);

	GetCamera().SetBounds(v2f(0.0f, 0.0f), v2f(1920.0f / 4.0f, 1080.0f / 6.0f));

	Scene::Update(aDeltaTime);
}

const GameObject* LevelScene::GetPlayer()
{
	return myPlayer;
}
