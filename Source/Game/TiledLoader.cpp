#include "stdafx.h"
#include "TiledLoader.h"

#include <sstream>
#include <cassert>
#include <vector>

#include "DataManager.h"
#include "rapidjson/document.h"

#include "SpringObject.h"
#include "Bonfire.hpp"
#include "Collectible.hpp"
#include "EnemyFactory.h"
#include "PlatformFactory.hpp"
#include "Ledge.h"
#include "HiddenArea.hpp"
#include "BashableObject.hpp"
#include "MovingPlatform.hpp"


void TiledLoader::Load(Scene* aScene, int aLevelIndex)
{
	//Jag kommer få ett dokumnt med en bana som jag kan använda för att utvinna datan
	//rapidjson::document levelDoc = DataManager::GetInstance().GetLevel(aLevelIndex);
		//levelDoc[json object name].GetFloat();


	rapidjson::Document levelDoc;
	std::vector<LoadData> loadData;

	std::string aLayer = "Springs";

	for (int i = 0; i < levelDoc["layers"].Size(); ++i)
	{
		//Gather Info
		for (int i = 0; i < levelDoc["layers"][i]["objects"].Size(); ++i)
		{
			LoadData data;
			data.myPosition.x = levelDoc["layers"][i]["objects"][i]["x"].GetInt();
			data.myPosition.y = levelDoc["layers"][i]["objects"]["y"].GetInt();

			data.mySize.x = levelDoc["layers"][i]["objects"][i]["width"].GetInt();
			data.mySize.y = levelDoc["layers"][i]["objects"][i]["height"].GetInt();

			data.myType = levelDoc["layers"][i]["objects"][i]["type"].GetInt();

			//if (levelDoc["layers"][i]["objects"][i]["waypoints"])
			//{

			//}
			//Waypoint and speed is optional

			loadData.push_back(data);
		}

		//Call functions
		if (levelDoc["layers"][i]["name"] == "Platforms")
		{
			ParsePlatforms(loadData, aScene);
		}
		else if (levelDoc["layers"][i]["name"] == "Springs")
		{
			ParseSprings(loadData, aScene);
		}
		loadData.clear();
	}
}

void TiledLoader::ParseGraphics(const std::vector<LoadData> someBG1Data, const std::vector<LoadData> someBG2Data, const std::vector<LoadData> someFG1Data, const std::vector<LoadData> someFG2Data, const std::vector<LoadData> someHRData, Scene* aScene)
{
}

void TiledLoader::ParseBonfires(const std::vector<v2f> somePos, Scene* aScene)
{
	for (int i = 0; i < somePos.size(); ++i)
	{
		Bonfire* bonfire = new Bonfire(aScene);
		bonfire->SetPosition(somePos[i]);
	}
}

void TiledLoader::ParseDoors(const std::vector<LoadData> someData, Scene*)
{
}

void TiledLoader::ParseEnemies(const std::vector<LoadData> someData, Scene* aScene)
{
	EnemyFactory enemyFactory;

	for (int i = 0; i < someData.size(); ++i)
	{
		switch (someData[i].myType)
		{
		case 0:
			enemyFactory.CreateNormalEnemy(aScene, GetWaypointPositions(someData[i].myWaypoints, someData[i].myPosition), someData[i].mySpeed);
			break;
		case 1:
			enemyFactory.CreateShootingEnemy(aScene, GetWaypointPositions(someData[i].myWaypoints, someData[i].myPosition), someData[i].mySpeed);
			break;
		}
	}
}

void TiledLoader::ParseLedges(const std::vector<LoadData> someData, Scene* aScene)
{
	for (int i = 0; i < someData.size(); ++i)
	{
		Ledge* ledge = new Ledge(aScene);
		ledge->Init(someData[i].myPosition, someData[i].mySize);
	}
}

void TiledLoader::ParseCollectables(const std::vector<LoadData> someData, Scene* aScene)
{
	for (int i = 0; i < someData.size(); ++i)
	{
		Collectible::eCollectibleType aType = Collectible::eCollectibleType::Easy;

		switch (someData[i].myType)
		{
		case 0:
			aType = Collectible::eCollectibleType::Easy;
			break;
		case 1:
			aType = Collectible::eCollectibleType::Medium;
			break;
		case 2:
			aType = Collectible::eCollectibleType::Hard;
			break;
		}


		Collectible* collectible = new Collectible(aScene);
		collectible->Init(someData[i].myPosition, aType);
	}
}

void TiledLoader::ParseCollectableZones(const std::vector<LoadData> someData, Scene*)
{
}

void TiledLoader::ParsePlatforms(const std::vector<LoadData> someData, Scene* aScene)
{
	PlatformFactory platformFactory;

	for (int i = 0; i < someData.size(); ++i)
	{
		switch (someData[i].myType)
		{
		case 0:
			platformFactory.CreateStaticPlatform(aScene, someData[i].myPosition, someData[i].mySize, someData[i].mySize, false);
			break;
		case 1:
			platformFactory.CreateMovingPlatform(aScene, someData[i].myPosition, someData[i].mySize, someData[i].mySize, GetWaypointPositions(someData[i].myWaypoints, someData[i].myPosition), someData[i].mySpeed);
			break;
		case 2:
			platformFactory.CreateUnstablePlatform(aScene, someData[i].myPosition, someData[i].mySize, someData[i].mySize, 0.5f, 2.0f);
			break;
		case 3:
			platformFactory.CreateDestructiblePlatform(aScene, someData[i].myPosition, someData[i].mySize, someData[i].mySize);
			break;
		case 4:
			platformFactory.CreateDeadlyPlatform(aScene, someData[i].myPosition, someData[i].mySize, someData[i].mySize);
			break;
		case 5:
			platformFactory.CreateStaticPlatform(aScene, someData[i].myPosition, someData[i].mySize, someData[i].mySize, true);
		}
	}
}

void TiledLoader::ParseHiddenRooms(const std::vector<LoadData> someData, Scene* aScene)
{
	for (int i = 0; i < someData.size(); ++i)
	{
		HiddenArea* hiddenArea = new HiddenArea(aScene, someData[i].myPosition, someData[i].mySize);
	}
}

void TiledLoader::ParseSprings(const std::vector<LoadData> someData, Scene* aScene)
{
	for (int i = 0; i < someData.size(); ++i)
	{
		SpringObject* aSpring = new SpringObject(aScene);
		aSpring->Init(someData[i].myPosition);
	}
}

void TiledLoader::ParseBashableObjects(const std::vector<LoadData> someData, Scene* aScene)
{
	for (int i = 0; i < someData.size(); ++i)
	{
		BashableObject* bashObj = new BashableObject(aScene);
		bashObj->Init(someData[i].myPosition, 10);
	}
}

void TiledLoader::ParseButtons(const std::vector<LoadData> someData, Scene* aScene)
{
	PlatformFactory platformFactory;

	for (int i = 0; i < someData.size(); ++i)
	{
		if (someData[i].myType == 3)
		{
			//door
		}
		else
		{
			MovingPlatform* platform = platformFactory.CreateMovingPlatform(aScene, someData[i].myPosition, someData[i].mySize, someData[i].mySize, GetWaypointPositions(someData[i].myWaypoints, someData[i].myPosition), someData[i].mySpeed);
			MovingPlatform::eMovingPlatformType aType = MovingPlatform::eMovingPlatformType::MovingPlatform;

			switch (someData[i].myType)
			{
			case 0:
				aType = MovingPlatform::eMovingPlatformType::MovingPlatform;
				break;
			case 1:
				aType = MovingPlatform::eMovingPlatformType::ReversePlatform;
				break;
			case 2:
				aType = MovingPlatform::eMovingPlatformType::PointAtoBPlatform;
				break;
			}
			platform->AddButton(someData[i].myPosition, aType);
		}
	}
}

std::vector<v2f> TiledLoader::GetWaypointPositions(const std::string somePositions, v2f aSpawnPos)
{
	std::vector<v2f> waypoints;
	waypoints.push_back(aSpawnPos);

	std::stringstream sstream;

	sstream << somePositions;
	std::string tempWord;
	int tempNum;
	int tempX;
	bool hasX = false;

	while (!sstream.eof())
	{
		sstream >> tempWord;

		if (std::stringstream(tempWord) >> tempNum)
		{
			if (hasX == false)
			{
				tempX = tempNum;
				hasX = true;
			}
			else
			{
				waypoints.push_back({ static_cast<float>(tempX) * myTileSize.x + aSpawnPos.x, static_cast<float>(tempNum) * myTileSize.y + aSpawnPos.y });
				hasX = false;
			}
		}
	}

	return waypoints;
}