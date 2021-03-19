#include "stdafx.h"
#include "TiledLoader.h"

#include <vector>

#include "DataManager.h"

#include "SpringObject.h"
#include "Bonfire.hpp"
#include "Collectible.hpp"
#include "EnemyFactory.h"
#include "PlatformFactory.hpp"
#include "Ledge.h"
#include "HiddenArea.hpp"
#include "BashableObject.hpp"
#include "MovingPlatform.hpp"

typedef rapidjson::Value::ConstValueIterator iterator;

void TiledLoader::Load(Scene* aScene, int aLevelIndex)
{
	const rapidjson::Document& levelDoc = DataManager::GetInstance().GetLevel(aLevelIndex);
	std::vector<LoadData> loadData;

	if (levelDoc.IsObject())
	{
		for (iterator layer = levelDoc["layers"].Begin(); layer != levelDoc["layers"].End(); ++layer)
		{
			if ((*layer).HasMember("objects"))
			{
				//Gather Info
				for (iterator object = (*layer)["objects"].Begin(); object != (*layer)["objects"].End(); ++object)
				{
					LoadData data;
					data.myPosition.x = (*object)["x"].GetInt();
					data.myPosition.y = (*object)["y"].GetInt();

					data.mySize.x = (*object)["width"].GetInt();
					data.mySize.y = (*object)["height"].GetInt();

					std::string type = (*object)["type"].GetString();
					std::stringstream degree(type);
					degree >> data.myType;


					if ((*object).HasMember("properties"))
					{
						for (iterator property = (*object)["properties"].Begin(); property != (*object)["properties"].End(); ++property)
						{
							if (std::string((*property)["name"].GetString()).compare("Waypoints") == 0)
							{
								data.myWaypoints = (*property)["value"].GetString();
							}
							
							if (std::string((*property)["name"].GetString()).compare("Speed") == 0)
							{
								data.mySpeed = (*property)["value"].GetFloat();
							}
						}
					}

					loadData.push_back(data);
				}

				std::string name = (*layer)["name"].GetString();

				//Call functions
				if (name == "Bonfire")
				{
					ParseBonfires(loadData, aScene);
				}
				else if (name == "Doors")
				{
					ParseDoors(loadData, aScene);
				}
				else if (name == "Enemies")
				{
					ParseEnemies(loadData, aScene);
				}
				else if (name == "Ledges")
				{
					ParseLedges(loadData, aScene);
				}
				else if (name == "Collectables")
				{
					ParseCollectables(loadData, aScene);
				}
				else if (name == "CollectableZones")
				{
					ParseCollectableZones(loadData, aScene);
				}
				else if (name == "Platforms")
				{
					ParsePlatforms(loadData, aScene);
				}
				else if (name == "HiddenRooms")
				{
					ParseHiddenRooms(loadData, aScene);
				}
				else if (name == "Springs")
				{
					ParseSprings(loadData, aScene);
				}
				else if (name == "Bashable")
				{
					ParseBashableObjects(loadData, aScene);
				}
				else if (name == "Buttons")
				{
					ParseButtons(loadData, aScene);
				}

				loadData.clear();
			}
		}
	}
}

void TiledLoader::ParseGraphics(const std::vector<LoadData> someBG1Data, const std::vector<LoadData> someBG2Data, const std::vector<LoadData> someFG1Data, const std::vector<LoadData> someFG2Data, const std::vector<LoadData> someHRData, Scene* aScene)
{

}

void TiledLoader::ParseBonfires(const std::vector<LoadData> someData, Scene* aScene)
{
	for (int i = 0; i < someData.size(); ++i)
	{
		Bonfire* bonfire = new Bonfire(aScene);
		bonfire->SetPosition(someData[i].myPosition);
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
	const v2f ledgeSize = v2f(2.0f, 1.0f);
	for (int i = 0; i < someData.size(); ++i)
	{
		Ledge* ledge = new Ledge(aScene);
		ledge->Init(someData[i].myPosition, ledgeSize);
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
	constexpr float radius = 20.0f;
	for (int i = 0; i < someData.size(); ++i)
	{
		BashableObject* bashObj = new BashableObject(aScene);
		bashObj->Init(someData[i].myPosition, radius);
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