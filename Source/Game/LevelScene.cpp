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

#include "Ledge.h"

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

	std::ifstream preProdPlatformsFile("JSON/PreProdPlatforms.json");
	rapidjson::IStreamWrapper preProdPlatformsStream(preProdPlatformsFile);

	rapidjson::Document preProdPlatforms;
	preProdPlatforms.ParseStream(preProdPlatformsStream);

	for (rapidjson::Value::ConstValueIterator itr = preProdPlatforms["Ledges"].Begin(); itr != preProdPlatforms["Ledges"].End(); ++itr)
	{
		const float positionX = (*itr)["Position"]["X"].GetFloat();
		const float positionY = (*itr)["Position"]["Y"].GetFloat();

		const float sizeX = (*itr)["Size"]["X"].GetFloat();
		const float sizeY = (*itr)["Size"]["Y"].GetFloat();

		Ledge* ledge = new Ledge(this);
		ledge->Init(v2f(positionX, positionY), v2f(sizeX, sizeY));
	}

	for (rapidjson::Value::ConstValueIterator itr = preProdPlatforms["Platforms"].Begin(); itr != preProdPlatforms["Platforms"].End(); ++itr)
	{
		const float positionX = (*itr)["Position"]["X"].GetFloat();
		const float positionY = (*itr)["Position"]["Y"].GetFloat();

		const float sizeX = (*itr)["Size"]["X"].GetFloat();
		const float sizeY = (*itr)["Size"]["Y"].GetFloat();

		const float spriteSizeX = (*itr)["SpriteSize"]["X"].GetFloat();
		const float spriteSizeY = (*itr)["SpriteSize"]["Y"].GetFloat();

		Platform* ground = new Platform(this);
		ground->Init(v2f(sizeX, sizeY), v2f(spriteSizeX, spriteSizeY), v2f(positionX, positionY));
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

void LevelScene::Update(const float& aDeltaTime)
{
	Scene::Update(aDeltaTime);
}
