#include "stdafx.h"
#include "LevelScene.h"

#include "GameWorld.h"

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"

#include "../External/Headers/CU/Utilities.h"

#include "Player.hpp"

LevelScene::LevelScene()
	: 
	myPlayer(nullptr)
	, myGround(nullptr)
	, myBackground(nullptr)
	, Scene()
{}

void LevelScene::Load()
{
	myPlayer = new Player(this);

	myBackground = new GameObject(this);
	myBackground->SetPosition({1080.0f, 540});

	SpriteComponent* sprite = myBackground->AddComponent<SpriteComponent>();
	sprite->SetSpritePath("Sprites/Background.png");
	sprite->SetSize({ 3840.0f, 2160.0f });

	myGround = new GameObject(this);
	myGround->SetPosition({ 600.0f, 1080.0f });
	myGround->SetPivot({ 0.0f, 1.0f });

	SpriteComponent* gsprite = myGround->AddComponent<SpriteComponent>();
	gsprite->SetSpritePath("Sprites/Platform.dds");
	gsprite->SetSize({ 800.0f, 200.0f });

	PhysicsComponent* gphys = myGround->AddComponent<PhysicsComponent>();
	gphys->SetCanCollide(true);
	gphys->SetIsStatic(true);

	ColliderComponent* collider = myGround->AddComponent<ColliderComponent>();
	collider->SetPosition({ 800.0f / 2.0f, -200.0f / 2.0f });
	collider->SetSize(gsprite->GetSize());

	Scene::Load();
}

void LevelScene::Activate()
{
	Scene::Activate();

	GetCamera().StartFollowing(myPlayer, { 10.0f, 10.0f });
}

void LevelScene::Deactivate()
{
	Scene::Deactivate();

	GetCamera().StopFollowing();
}

void LevelScene::Update(const float& aDeltaTime, const float& aTotalTime)
{
	CGameWorld* world = CGameWorld::GetInstance();
	Utils::Input* input = world->Input();

	Scene::Update(aDeltaTime, aTotalTime);
}