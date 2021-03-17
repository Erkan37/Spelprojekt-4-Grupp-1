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

	CGameWorld::GetInstance()->GetLevelManager().LoadLevel(this, "Levels/test_level2.json");

	Scene::Load();
}

void LevelScene::Activate()
{
	Scene::Activate();

	GetCamera().StartFollowing(myPlayer, { 40.0f, 40.0f });
	GetCamera().SetBounds(v2f(-840.0f, -540.0f), v2f(3840.0f, 2160.0f));
}

void LevelScene::Deactivate()
{
	Scene::Deactivate();

	GetCamera().StopFollowing();
}

void LevelScene::Update(const float& aDeltaTime)
{
	const float zoomFactorX = Tga2D::CEngine::GetInstance()->GetTargetSize().x / 1920.0f;
	const float zoomFactorY = Tga2D::CEngine::GetInstance()->GetTargetSize().y / 1080.0f;
	const float zoomFactor = zoomFactorX / zoomFactorY;
	const float zoom = 6.0f * zoomFactor;
	GetCamera().SetZoom(zoom);

	Scene::Update(aDeltaTime);
}

const GameObject* LevelScene::GetPlayer()
{
	return myPlayer;
}
