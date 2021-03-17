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
#include "WaypointComponent.hpp"

void PlatformFactory::ReadPlatforms(Scene* aLevelScene, const std::string& aFilePath)
{
	std::ifstream platformsFile(aFilePath);
	rapidjson::IStreamWrapper platformsStream(platformsFile);

	rapidjson::Document platforms;
	platforms.ParseStream(platformsStream);

	const float ledgeSizeX = platforms["LedgeSize"]["X"].GetFloat();
	const float ledgeSizeY = platforms["LedgeSize"]["Y"].GetFloat();

	const float destroyTime = platforms["DestroyTime"].GetFloat();
	const float respawnTime = platforms["RespawnTime"].GetFloat();

	for (rapidjson::Value::ConstValueIterator ledges = platforms["Ledges"].Begin(); ledges != platforms["Ledges"].End(); ++ledges)
	{
		const float positionX = (*ledges)["Position"]["X"].GetFloat();
		const float positionY = (*ledges)["Position"]["Y"].GetFloat();

		Ledge* ledge = new Ledge(aLevelScene);
		ledge->Init(v2f(positionX, positionY), v2f(ledgeSizeX, ledgeSizeY));
	}

	for (rapidjson::Value::ConstValueIterator platform = platforms["Platforms"].Begin(); platform != platforms["Platforms"].End(); ++platform)
	{
		const float positionX = (*platform)["Position"]["X"].GetFloat();
		const float positionY = (*platform)["Position"]["Y"].GetFloat();

		const float sizeX = (*platform)["Size"]["X"].GetFloat();
		const float sizeY = (*platform)["Size"]["Y"].GetFloat();

		const float spriteSizeX = (*platform)["SpriteSize"]["X"].GetFloat();
		const float spriteSizeY = (*platform)["SpriteSize"]["Y"].GetFloat();

		const int type = (*platform)["Type"].GetInt();

		float speed = 0;
		std::vector<v2f> wayPoints;

		switch (type)
		{
		case 0:
			CreateStaticPlatform(aLevelScene, v2f(positionX, positionY), v2f(sizeX, sizeY), v2f(spriteSizeX, spriteSizeY), false);
			break;
		case 1:
			for (rapidjson::Value::ConstValueIterator waypoint = (*platform)["Waypoints"].Begin(); waypoint != (*platform)["Waypoints"].End(); ++waypoint)
			{
				wayPoints.push_back(v2f((*waypoint)["X"].GetFloat(), (*waypoint)["Y"].GetFloat()));
			}

			speed = (*platform)["Speed"].GetFloat();

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
		case 5:
			CreateStaticPlatform(aLevelScene, v2f(positionX, positionY), v2f(sizeX, sizeY), v2f(spriteSizeX, spriteSizeY), true);
		}
	}

	platformsFile.close();
}

Platform* PlatformFactory::CreateStaticPlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize, const bool aIsOneWay)
{
	Platform* staticPlatform = new Platform(aLevelScene);
	staticPlatform->Init(aCollisionSize, aSpriteSize, aPosition, aIsOneWay);
	staticPlatform->GetComponent<SpriteComponent>()->SetSpritePath("Sprites/Platforms/BreakableFloor.dds");
	staticPlatform->GetComponent<SpriteComponent>()->SetSize(aSpriteSize);
	return staticPlatform;
}

MovingPlatform* PlatformFactory::CreateMovingPlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize, const std::vector<v2f>& aWayPoints, const float& aSpeed)
{
	MovingPlatform* movingPlatform = new MovingPlatform(aLevelScene);

	std::string spritePath = "Sprites/Platforms/Moving6.dds";

	v2f adjustedSize = v2f(0.0f, 8.0f);
	if (aCollisionSize.x >= 40.0f)
	{
		adjustedSize.x = 48.0f;
		spritePath = "Sprites/Platforms/Moving6.dds";
	}
	else if (aCollisionSize.x >= 24.0f)
	{
		adjustedSize.x = 32.0f;
		spritePath = "Sprites/Platforms/Moving4.dds";
	}
	else
	{
		adjustedSize.x = 16.0f;
		spritePath = "Sprites/Platforms/Moving2.dds";
	}

	movingPlatform->Init(adjustedSize, adjustedSize, aPosition, true);
	movingPlatform->SetWaypoints(aWayPoints);
	movingPlatform->GetComponent<WaypointComponent>()->SetSpeed(aSpeed);
	movingPlatform->GetComponent<SpriteComponent>()->SetSpritePath(spritePath);
	movingPlatform->GetComponent<SpriteComponent>()->SetSize(adjustedSize);
	return movingPlatform;
}

UnstablePlatform* PlatformFactory::CreateUnstablePlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize, const float& aDestroyTime, const float& aRespawnTime)
{
	UnstablePlatform* unstablePlatform = new UnstablePlatform(aLevelScene);

	std::string spritePath = "Sprites/Platforms/Unstable5.dds";

	v2f adjustedSize = v2f(0.0f, 8.0f);
	if (aCollisionSize.x >= 40.0f)
	{
		adjustedSize.x = 40.0f;
		spritePath = "Sprites/Platforms/Unstable5.dds";
	}
	else if (aCollisionSize.x >= 24.0f)
	{
		adjustedSize.x = 24.0f;
		spritePath = "Sprites/Platforms/Unstable3.dds";
	}
	else
	{
		adjustedSize.x = 8.0f;
		spritePath = "Sprites/Platforms/Unstable1.dds";
	}

	unstablePlatform->Init(adjustedSize, adjustedSize, aPosition, false);
	unstablePlatform->SetTimerProperties(aDestroyTime, aRespawnTime);
	unstablePlatform->GetComponent<SpriteComponent>()->SetSpritePath(spritePath);
	unstablePlatform->GetComponent<SpriteComponent>()->SetSize(aSpriteSize);
	return unstablePlatform;
}

DestructiblePlatform* PlatformFactory::CreateDestructiblePlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize)
{
	DestructiblePlatform* destructiblePlatform = new DestructiblePlatform(aLevelScene);

	std::string spritePath = "Sprites/Platforms/BreakableWall.dds";

	v2f adjustedSize = v2f(0.0f, 0.0f);
	if (aCollisionSize.x >= 32.0f)
	{
		adjustedSize.x = 32.0f;
		adjustedSize.y = 24.0f;
		spritePath = "Sprites/Platforms/BreakableFloor.dds";
	}
	else
	{
		adjustedSize.x = 24.0f;
		adjustedSize.y = 32.0f;
		spritePath = "Sprites/Platforms/BreakableWall.dds";
	}


	destructiblePlatform->Init(adjustedSize, adjustedSize, aPosition, false);
	destructiblePlatform->GetComponent<SpriteComponent>()->SetSpritePath(spritePath);
	destructiblePlatform->GetComponent<SpriteComponent>()->SetSize(aSpriteSize);
	return destructiblePlatform;
}

DeadlyPlatform* PlatformFactory::CreateDeadlyPlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize)
{
	DeadlyPlatform* deadlyPlatform = new DeadlyPlatform(aLevelScene);
	deadlyPlatform->Init(aCollisionSize, aSpriteSize, aPosition, false);
	deadlyPlatform->GetComponent<SpriteComponent>()->SetSpritePath("Sprites/Platforms/BreakableFloor.dds");
	deadlyPlatform->GetComponent<SpriteComponent>()->SetSize(aSpriteSize);
	return deadlyPlatform;
}