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

LevelScene::LevelScene()
	: 
	myPlayer(nullptr)
	, Scene()
{}

void LevelScene::Load()
{
	myPlayer = new Player(this);

	HiddenArea* hiddenArea = new HiddenArea(this, myPlayer->GetPosition() + v2f(0.0f, 200.0f), v2f(32.0f, 32.0f));

	//Bonfire* bonfire = new Bonfire(this);
	//bonfire->SetPosition(myPlayer->GetPosition() + v2f(50.0f, 200.0f));

	//EnemyFactory enemyFactory;
	//enemyFactory.ReadEnemies(this, "JSON/AlfaEnemies.json");

	myBackground = std::make_unique<Background>(this);

	myTiledMap = std::make_unique<TiledMap>();
	myTiledMap->Load("Levels/test_level2.json", this);

	//BashableObjectFactory bashableObjectFactory;
	//bashableObjectFactory.ReadBashableObjects(this, "JSON/AlfaBashableObjects.json");

	Scene::Load();
}

void LevelScene::Activate()
{
	Scene::Activate();

	GetCamera().StartFollowing(myPlayer, { 40.0f, 40.0f });
	GetCamera().SetBounds(v2f(-840.0f, -540.0f), v2f(3840.0f, 2160.0f));
	GetCamera().SetZoom(6.0f);
}

void LevelScene::Deactivate()
{
	Scene::Deactivate();

	GetCamera().StopFollowing();
}

void LevelScene::Update(const float& aDeltaTime)
{
	Scene::Update(aDeltaTime);
}

const GameObject* LevelScene::GetPlayer()
{
	return myPlayer;
}
