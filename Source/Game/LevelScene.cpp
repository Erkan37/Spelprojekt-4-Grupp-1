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
#include "PlatformFactory.hpp"

LevelScene::LevelScene()
	: 
	myPlayer(nullptr)
	, Scene()
{}

void LevelScene::Load()
{
	myPlayer = new Player(this);

	GameObject* background = new GameObject(this);
	background->SetPosition({1080.0f, 540});

	SpriteComponent* sprite = background->AddComponent<SpriteComponent>();
	sprite->SetSpritePath("Sprites/Background.png");
	sprite->SetSize({ 3840.0f, 2160.0f });

	PlatformFactory platformFactory;
	platformFactory.ReadPlatforms(this, "JSON/PreProdPlatforms.json");

	Scene::Load();
}

void LevelScene::Activate()
{
	Scene::Activate();

	GetCamera().StartFollowing(myPlayer, { 10.0f, 10.0f });
	GetCamera().SetBounds(v2f(-840.0f, -540.0f), v2f(3840.0f, 2160.0f));
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
