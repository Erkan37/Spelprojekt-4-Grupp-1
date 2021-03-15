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

LevelScene::LevelScene()
	: 
	myPlayer(nullptr)
	, Scene()
{}

void LevelScene::Load()
{
	myPlayer = new Player(this);

	Bonfire* bonfire = new Bonfire(this);
	bonfire->SetPosition(myPlayer->GetPosition() + v2f(50.0f, 200.0f));

	EnemyFactory enemyFactory;
	enemyFactory.ReadEnemies(this, "JSON/AlfaEnemies.json");

	Collectible* collectible = new Collectible(this);
	collectible->Init(v2f(500.0f, 500.0f), Collectible::eCollectibleType::Easy);

	Collectible* collectible2 = new Collectible(this);
	collectible2->Init(v2f(900.0f, 500.0f), Collectible::eCollectibleType::Easy);

	myFactory = std::make_unique<ParticleEffectFactory>(this);
	myFactory->ReadEffects(this);
	myFactory->Init();

	myBackground = std::make_unique<Background>(this);

	mySpring = std::make_unique<SpringObject>(this);
	mySpring->Init(v2f(800.f, 865.f));

	//PlatformFactory platformFactory;
	//platformFactory.ReadPlatforms(this, "JSON/PreProdPlatforms.json");

	myTiledMap = std::make_unique<TiledMap>();
	myTiledMap->Load("Levels/test_level.json", this);

	BashableObjectFactory bashableObjectFactory;
	bashableObjectFactory.ReadBashableObjects(this, "JSON/AlfaBashableObjects.json");

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

GameObject* LevelScene::GetPlayer()
{
	return myPlayer;
}
