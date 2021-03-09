#include "stdafx.h"
#include "PlatformFactory.hpp"

#include "Platform.h"
#include "MovingPlatform.hpp"
#include "UnstablePlatform.hpp"
#include "DestructiblePlatform.hpp"
#include "DeadlyPlatform.hpp"

#include "Ledge.h"

#include "../External/Headers/rapidjson/document.h"
#include "../External/Headers/rapidjson/istreamwrapper.h"
#include <fstream>

#include "SpriteComponent.h"

void PlatformFactory::ReadPlatforms(Scene* aLevelScene, const std::string& aFilePath)
{
	std::ifstream platformsFile("JSON/PreProdPlatforms.json");
	rapidjson::IStreamWrapper platformsStream(platformsFile);

	rapidjson::Document platforms;
	platforms.ParseStream(platformsStream);

	const float ledgeSizeX = platforms["LedgeSize"]["X"].GetFloat();
	const float ledgeSizeY = platforms["LedgeSize"]["Y"].GetFloat();

	const float destroyTime = platforms["DestroyTime"].GetFloat();
	const float respawnTime = platforms["RespawnTime"].GetFloat();

	for (rapidjson::Value::ConstValueIterator itr = platforms["Ledges"].Begin(); itr != platforms["Ledges"].End(); ++itr)
	{
		const float positionX = (*itr)["Position"]["X"].GetFloat();
		const float positionY = (*itr)["Position"]["Y"].GetFloat();

		Ledge* ledge = new Ledge(aLevelScene);
		ledge->Init(v2f(positionX, positionY), v2f(ledgeSizeX, ledgeSizeY));
	}

	for (rapidjson::Value::ConstValueIterator itr = platforms["Platforms"].Begin(); itr != platforms["Platforms"].End(); ++itr)
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
		std::vector<v2f> wayPoints;

		switch (type)
		{
		case 0:
			CreateStaticPlatform(aLevelScene, v2f(positionX, positionY), v2f(sizeX, sizeY), v2f(spriteSizeX, spriteSizeY), oneway);
			break;
		case 1:
			for (rapidjson::Value::ConstValueIterator waypoint = (*itr)["Waypoints"].Begin(); waypoint != (*itr)["Waypoints"].End(); ++waypoint)
			{
				wayPoints.push_back(v2f((*waypoint)["X"].GetFloat(), (*waypoint)["Y"].GetFloat()));
			}

			speed = (*itr)["Speed"].GetFloat();

			CreateMovingPlatform(aLevelScene, v2f(positionX, positionY), v2f(sizeX, sizeY), v2f(spriteSizeX, spriteSizeY), wayPoints, speed);
			break;
		case 2:
			CreateUnstablePlatform(aLevelScene, v2f(positionX, positionY), v2f(sizeX, sizeY), v2f(spriteSizeX, spriteSizeY), destroyTime, respawnTime);
			break;
		case 3:
			CreateDestructiblePlatform(aLevelScene, v2f(positionX, positionY), v2f(sizeX, sizeY), v2f(spriteSizeX, spriteSizeY));
			break;
		case 4:
			CreateDeadlyPlatform(aLevelScene, v2f(positionX, positionY), v2f(sizeX, sizeY), v2f(spriteSizeX, spriteSizeY));
			break;
		}
	}

	platformsFile.close();
}

Platform* PlatformFactory::CreateStaticPlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize, const bool aIsOneWay)
{
	Platform* staticPlatform = new Platform(aLevelScene);
	staticPlatform->Init(v2f(aCollisionSize.x, aCollisionSize.y), v2f(aSpriteSize.x, aSpriteSize.y), v2f(aPosition.x, aPosition.y), aIsOneWay);
	staticPlatform->GetComponent<SpriteComponent>()->SetSpritePath("Sprites/platform.dds");
	staticPlatform->GetComponent<SpriteComponent>()->SetSize(aSpriteSize);
	return staticPlatform;
}

MovingPlatform* PlatformFactory::CreateMovingPlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize, const std::vector<v2f>& aWayPoints, const float& aSpeed)
{
	MovingPlatform* movingPlatform = new MovingPlatform(aLevelScene);
	movingPlatform->Init(v2f(aCollisionSize.x, aCollisionSize.y), v2f(aSpriteSize.x, aSpriteSize.y), v2f(aPosition.x, aPosition.y), true);
	movingPlatform->SetWaypoints(aWayPoints);
	movingPlatform->SetSpeed(aSpeed);
	movingPlatform->GetComponent<SpriteComponent>()->SetSpritePath("Sprites/PlattformHype.dds");
	movingPlatform->GetComponent<SpriteComponent>()->SetSize(aSpriteSize);
	return movingPlatform;
}

UnstablePlatform* PlatformFactory::CreateUnstablePlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize, const float& aDestroyTime, const float& aRespawnTime)
{
	UnstablePlatform* unstablePlatform = new UnstablePlatform(aLevelScene);
	unstablePlatform->Init(v2f(aCollisionSize.x, aCollisionSize.y), v2f(aSpriteSize.x, aSpriteSize.y), v2f(aPosition.x, aPosition.y), false);
	unstablePlatform->SetTimerProperties(aDestroyTime, aRespawnTime);
	unstablePlatform->GetComponent<SpriteComponent>()->SetSpritePath("Sprites/PlattformMold.dds");
	unstablePlatform->GetComponent<SpriteComponent>()->SetSize(aSpriteSize);
	return unstablePlatform;
}

DestructiblePlatform* PlatformFactory::CreateDestructiblePlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize)
{
	DestructiblePlatform* destructiblePlatform = new DestructiblePlatform(aLevelScene);
	destructiblePlatform->Init(v2f(aCollisionSize.x, aCollisionSize.y), v2f(aSpriteSize.x, aSpriteSize.y), v2f(aPosition.x, aPosition.y), false);
	destructiblePlatform->GetComponent<SpriteComponent>()->SetSpritePath("Sprites/PlattformCrocs.dds");
	destructiblePlatform->GetComponent<SpriteComponent>()->SetSize(aSpriteSize);
	return destructiblePlatform;
}

DeadlyPlatform* PlatformFactory::CreateDeadlyPlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize)
{
	DeadlyPlatform* deadlyPlatform = new DeadlyPlatform(aLevelScene);
	deadlyPlatform->Init(v2f(aCollisionSize.x, aCollisionSize.y), v2f(aSpriteSize.x, aSpriteSize.y), v2f(aPosition.x, aPosition.y), false);
	deadlyPlatform->GetComponent<SpriteComponent>()->SetSpritePath("Sprites/PlattformKill.dds");
	deadlyPlatform->GetComponent<SpriteComponent>()->SetSize(aSpriteSize);
	return deadlyPlatform;
}