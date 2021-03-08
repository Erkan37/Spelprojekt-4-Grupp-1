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

#include "MovingPlatform.hpp"
#include "UnstablePlatform.hpp"
#include "DestructiblePlatform.hpp"

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

	Platform* staticPlatform;
	MovingPlatform* movingGround;
	UnstablePlatform* unstablePlatform;
	DestructiblePlatform* destructiblePlatform;

	const float ledgeSizeX = preProdPlatforms["LedgeSize"]["X"].GetFloat();
	const float ledgeSizeY = preProdPlatforms["LedgeSize"]["Y"].GetFloat();

	const float destroyTime = preProdPlatforms["DestroyTime"].GetFloat();
	const float respawnTime = preProdPlatforms["RespawnTime"].GetFloat();

	for (rapidjson::Value::ConstValueIterator itr = preProdPlatforms["Ledges"].Begin(); itr != preProdPlatforms["Ledges"].End(); ++itr)
	{
		const float positionX = (*itr)["Position"]["X"].GetFloat();
		const float positionY = (*itr)["Position"]["Y"].GetFloat();

		Ledge* ledge = new Ledge(this);
		ledge->Init(v2f(positionX, positionY), v2f(ledgeSizeX, ledgeSizeY));
	}

	for (rapidjson::Value::ConstValueIterator itr = preProdPlatforms["Platforms"].Begin(); itr != preProdPlatforms["Platforms"].End(); ++itr)
	{
		const float positionX = (*itr)["Position"]["X"].GetFloat();
		const float positionY = (*itr)["Position"]["Y"].GetFloat();

		const float sizeX = (*itr)["Size"]["X"].GetFloat();
		const float sizeY = (*itr)["Size"]["Y"].GetFloat();

		const float spriteSizeX = (*itr)["SpriteSize"]["X"].GetFloat();
		const float spriteSizeY = (*itr)["SpriteSize"]["Y"].GetFloat(); 

		const bool oneway = (*itr)["Oneway"].GetBool();
		const int type = (*itr)["Type"].GetInt();

		float speed = 0;

		switch (type)
		{
			case 0:
				staticPlatform = new Platform(this);
				staticPlatform->Init(v2f(sizeX, sizeY), v2f(spriteSizeX, spriteSizeY), v2f(positionX, positionY), oneway);
				break;
			case 1:
				speed = (*itr)["Speed"].GetFloat();
				movingGround = new MovingPlatform(this);
				movingGround->Init(v2f(sizeX, sizeY), v2f(spriteSizeX, spriteSizeY), v2f(positionX, positionY), oneway);
				movingGround->SetSpeed(speed);

				for (rapidjson::Value::ConstValueIterator waypoint = (*itr)["Waypoints"].Begin(); waypoint != (*itr)["Waypoints"].End(); ++waypoint)
				{
					const float waypointX = (*waypoint)["X"].GetFloat();
					const float waypointY = (*waypoint)["Y"].GetFloat();

					movingGround->AddWaypoint(v2f(waypointX, waypointY));
				}
				break;
			case 2:
				unstablePlatform = new UnstablePlatform(this);
				unstablePlatform->Init(v2f(sizeX, sizeY), v2f(spriteSizeX, spriteSizeY), v2f(positionX, positionY), oneway);
				unstablePlatform->SetTimerProperties(destroyTime, respawnTime);

				break;
			case 3:
				destructiblePlatform = new DestructiblePlatform(this);
				destructiblePlatform->Init(v2f(sizeX, sizeY), v2f(spriteSizeX, spriteSizeY), v2f(positionX, positionY), oneway);
				break;
		}
	}

	preProdPlatformsFile.close();

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
