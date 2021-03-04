#include "stdafx.h"
#include "LevelScene.h"

#include "GameWorld.h"

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"

#include "../External/Headers/CU/Utilities.h"

#include "../External/Headers/rapidjson/document.h"
#include "../External/Headers/rapidjson/istreamwrapper.h"
#include <fstream>

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

	std::ifstream preProdPlatformsFile("JSON/PreProdPlatforms.json");
	rapidjson::IStreamWrapper preProdPlatformsStream(preProdPlatformsFile);

	rapidjson::Document preProdPlatforms;
	preProdPlatforms.ParseStream(preProdPlatformsStream);

	for (rapidjson::Value::ConstValueIterator itr = preProdPlatforms["Platforms"].Begin(); itr != preProdPlatforms["Platforms"].End(); ++itr)
	{
		const float positionX = (*itr)["Position"]["X"].GetFloat();
		const float positionY = (*itr)["Position"]["Y"].GetFloat();

		const float sizeX = (*itr)["Size"]["X"].GetFloat();
		const float sizeY = (*itr)["Size"]["Y"].GetFloat();

		myGround = new GameObject(this);
		myGround->SetPosition({ positionX, positionY });
		myGround->SetPivot({ 0.0f, 1.0f });

		SpriteComponent* gsprite = myGround->AddComponent<SpriteComponent>();
		gsprite->SetSpritePath("Sprites/Platform.dds");
		gsprite->SetSize({ sizeX, sizeY });

		PhysicsComponent* gphys = myGround->AddComponent<PhysicsComponent>();
		gphys->SetCanCollide(true);
		gphys->SetIsStatic(true);

		ColliderComponent* collider = myGround->AddComponent<ColliderComponent>();
		collider->SetPosition({ sizeX / 2.0f, -sizeY / 2.0f });
		collider->SetSize(gsprite->GetSize());
	}

	preProdPlatformsFile.close();

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

	Scene::Update(aDeltaTime, aTotalTime);
}