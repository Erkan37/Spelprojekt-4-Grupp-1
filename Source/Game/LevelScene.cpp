#include "stdafx.h"
#include "LevelScene.h"

#include "GameWorld.h"

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

#include "EnemyFactory.h"
#include "Enemy.h"

#include "Collectible.hpp"

LevelScene::LevelScene()
	: 
	myPlayer(nullptr)
	, Scene()
{}

void LevelScene::Load()
{
	myPlayer = new Player(this);

	EnemyFactory enemyFactory;
	enemyFactory.ReadEnemies(this, "JSON/AlfaEnemies.json");

	Collectible* collectible = new Collectible(this);
	collectible->Init(v2f(500.0f, 500.0f), Collectible::eCollectibleType::Easy);

	myBackground = std::make_unique<Background>(this);
	myBackground->AddPlayerRelation(myPlayer);

	mySpring = std::make_unique<SpringObject>(this);
	mySpring->Init(v2f(500.f, 800.f));

	PlatformFactory platformFactory;
	platformFactory.ReadPlatforms(this, "JSON/PreProdPlatforms.json");

	BashableObjectFactory bashableObjectFactory;
	bashableObjectFactory.ReadBashableObjects(this, "JSON/AlfaBashableObjects.json");

	Scene::Load();
}

void LevelScene::Activate()
{
	Scene::Activate();

	GetCamera().StartFollowing(myPlayer, { 10.0f, 10.0f });
	GetCamera().SetBounds(v2f(-840.0f, -540.0f), v2f(3840.0f, 2160.0f));
	//GetCamera().SetZoom(6.0f);
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
