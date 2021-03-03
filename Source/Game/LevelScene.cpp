#include "stdafx.h"
#include "LevelScene.h"

#include "GameWorld.h"

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"

#include "Utilities.h"

#include "Player.hpp"

#include "nlohmann/json.hpp"
#include <fstream>

LevelScene::LevelScene()
	: myPlayer(nullptr)
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

	std::ifstream platformsFile = std::ifstream("JSON/platformsTest.json");
	nlohmann::json platforms = nlohmann::json::parse(platformsFile);

	for (auto platform : platforms["platforms"])
	{
		myGrounds.push_back(new GameObject(this));
		myGrounds[myGrounds.size() - 1]->SetPosition({ platform["position"]["x"].get<float>(), platform["position"]["y"].get<float>() });
		myGrounds[myGrounds.size() - 1]->SetPivot({ 0.0f, 1.0f });

		SpriteComponent* gsprite = myGrounds[myGrounds.size() - 1]->AddComponent<SpriteComponent>();
		gsprite->SetSpritePath("Sprites/Platform.dds");
		gsprite->SetSize({ platform["size"]["x"].get<float>(), platform["size"]["y"].get<float>() });

		PhysicsComponent* gphys = myGrounds[myGrounds.size() - 1]->AddComponent<PhysicsComponent>();
		gphys->SetCanCollide(true);
		gphys->SetIsStatic(true);

		ColliderComponent* collider = myGrounds[myGrounds.size() - 1]->AddComponent<ColliderComponent>();
		collider->SetPosition({ platform["size"]["x"].get<float>() / 2.0f, -platform["size"]["y"].get<float>() / 2.0f });
		collider->SetSize(gsprite->GetSize());
	}

	platformsFile.close();

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