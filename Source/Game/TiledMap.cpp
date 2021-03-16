#include "stdafx.h"
#include <sstream>
#include "TiledMap.h"
#include "tileson/tileson_min.hpp"

#include "SpringObject.h"
#include "Bonfire.hpp"
#include "Collectible.hpp"
#include "EnemyFactory.h"
#include "PlatformFactory.hpp"
#include "Ledge.h"
#include "HiddenArea.hpp"
#include "BashableObject.hpp"
#include "MovingPlatform.hpp"

#include "Scene.h"
#include <cassert>

bool TiledMap::Load(const std::string& aPath, Scene* aScene)
{
	tson::Tileson parser;
	std::unique_ptr<tson::Map> map = parser.parse(std::filesystem::path(aPath));

	if (map->getStatus() != tson::ParseStatus::OK)
	{
		ERROR_PRINT("map load failed", map->getStatusMessage().c_str());
		return false;
	}

	assert(map->getSize().x > 0);
	assert(map->getSize().y > 0);

	ParseGraphics(map->getLayer("BG1"), map->getLayer("BG2"), map->getLayer("FG1"), map->getLayer("FG2"), map->getLayer("HR"), aScene);

	//Create
	tson::Layer* bonfireLayer = map->getLayer("Bonfire");
	tson::Layer* doorLayer = map->getLayer("Doors");
	tson::Layer* enemyLayer = map->getLayer("Enemies");
	tson::Layer* ledgeLayer = map->getLayer("Ledges");
	tson::Layer* collectablesLayer = map->getLayer("Collectables");
	tson::Layer* collectableZonesLayer = map->getLayer("CollectableZones");
	tson::Layer* platformLayer = map->getLayer("Platforms");
	tson::Layer* hiddenRoomLayer = map->getLayer("HiddenRooms");
	tson::Layer* springsLayer = map->getLayer("Springs");
	tson::Layer* bashableLayer = map->getLayer("Bashable");
	tson::Layer* buttonLayer = map->getLayer("Buttons");

	if (bonfireLayer)
	{
		ParseBonfires(bonfireLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load bonfirelayer");
	}
	if (doorLayer)
	{
		ParseDoors(doorLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load doorlayer");
	}
	if (enemyLayer)
	{
		ParseEnemies(enemyLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load enemylayer");
	}
	if (ledgeLayer)
	{
		ParseLedges(ledgeLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load ledgelayer");
	}
	if (collectablesLayer)
	{
		ParseCollectables(collectablesLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load collectableslayer");
	}
	if (collectableZonesLayer)
	{
		ParseCollectableZones(collectableZonesLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load collectableZoneslayer");
	}
	if (platformLayer)
	{
		ParsePlatforms(platformLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load platformlayer");
	}
	if (hiddenRoomLayer)
	{
		ParseHiddenRooms(hiddenRoomLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load hiddenRoomlayer");
	}
	if (springsLayer)
	{
		ParseSprings(springsLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load springslayer");
	}
	if (bashableLayer)
	{
		ParseBashableObjects(bashableLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load bashablelayer");
	}
	if (buttonLayer)
	{
		ParseButtons(buttonLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load buttonlayer");
	}

	return true;
}

void TiledMap::ParseGraphics(tson::Layer* aBG1, tson::Layer* aBG2, tson::Layer* aFG1, tson::Layer* aFG2, tson::Layer* aHR, Scene* aScene)
{
}

void TiledMap::ParseBonfires(tson::Layer* aLayer, Scene* aScene)
{
	auto& tileObj = aLayer->getObjects();

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		Bonfire* bonfire = new Bonfire(aScene);
		bonfire->SetPosition(GetScreenPosition(aPos));
	}
}

void TiledMap::ParseDoors(tson::Layer* aLayer, Scene* aScene)
{
	auto& tileObj = aLayer->getObjects();

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		//Add objects here
	}
}

void TiledMap::ParseEnemies(tson::Layer* aLayer, Scene* aScene)
{
	auto& tileObj = aLayer->getObjects();
	EnemyFactory enemyFactory;

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		if (tileObj[i].getType() != "")
		{
			int type = stoi(tileObj[i].getType());

			switch (type)
			{
			case 0:
				enemyFactory.CreateNormalEnemy(aScene, GetWaypointPositions(tileObj[i].getProp("Waypoints")->getValue<std::string>()), tileObj[i].getProp("Speed")->getValue<float>());
				break;
			case 1:
				enemyFactory.CreateShootingEnemy(aScene, GetWaypointPositions(tileObj[i].getProp("Waypoints")->getValue<std::string>()), tileObj[i].getProp("Speed")->getValue<float>());
				break;
			}
		}
	}
}

void TiledMap::ParseLedges(tson::Layer* aLayer, Scene* aScene)
{
	auto& tileObj = aLayer->getObjects();

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		v2f imageSize;
		imageSize.x = tileObj[i].getSize().x;
		imageSize.y = tileObj[i].getSize().y;

		Ledge* ledge = new Ledge(aScene);
		ledge->Init(aPos, imageSize);
	}
}

void TiledMap::ParseCollectables(tson::Layer* aLayer, Scene* aScene)
{
	auto& tileObj = aLayer->getObjects();

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		Collectible::eCollectibleType aType = Collectible::eCollectibleType::Easy;

		if (tileObj[i].getType() != "")
		{
			int type = stoi(tileObj[i].getType());

			switch (type)
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
		}

		Collectible* collectible = new Collectible(aScene);
		collectible->Init(GetScreenPosition(aPos), aType);
	}
}

void TiledMap::ParseCollectableZones(tson::Layer* aLayer, Scene* aScene)
{
	auto& tileObj = aLayer->getObjects();

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		//Add objects here
	}
}

void TiledMap::ParsePlatforms(tson::Layer* aLayer, Scene* aScene)
{
	auto& tileObj = aLayer->getObjects();
	PlatformFactory platformFactory;

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		v2f imageSize;
		imageSize.x = tileObj[i].getSize().x;
		imageSize.y = tileObj[i].getSize().y;

		if (tileObj[i].getType() != "")
		{
			int type = stoi(tileObj[i].getType());

			switch (type)
			{
			case 0:
				platformFactory.CreateStaticPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, false);
				break;
			case 1:
				platformFactory.CreateMovingPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, GetWaypointPositions(tileObj[i].getProp("Waypoints")->getValue<std::string>()), tileObj[i].getProp("Speed")->getValue<float>());
				break;
			case 2:
				platformFactory.CreateUnstablePlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, 0.0f, 0.0f);
				break;
			case 3:
				platformFactory.CreateDestructiblePlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize);
				break;
			case 4:
				platformFactory.CreateDeadlyPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize);
				break;
			case 5:
				platformFactory.CreateStaticPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, true);
			}
		}
	}
}

void TiledMap::ParseHiddenRooms(tson::Layer* aLayer, Scene* aScene)
{
	auto& tileObj = aLayer->getObjects();

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		v2f imageSize;
		imageSize.x = tileObj[i].getSize().x;
		imageSize.y = tileObj[i].getSize().y;

		HiddenArea* hiddenArea = new HiddenArea(aScene, aPos, imageSize);
	}
}

void TiledMap::ParseSprings(tson::Layer* aLayer, Scene* aScene)
{
	auto& tileObj = aLayer->getObjects();

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		SpringObject* aSpring = new SpringObject(aScene);
		aSpring->Init(GetScreenPosition(aPos));
	}
}

void TiledMap::ParseBashableObjects(tson::Layer* aLayer, Scene* aScene)
{
	auto& tileObj = aLayer->getObjects();

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		BashableObject* bashObj = new BashableObject(aScene);
		bashObj->Init(aPos, 10);
	}
}

void TiledMap::ParseButtons(tson::Layer* aLayer, Scene* aScene)
{
	auto& tileObj = aLayer->getObjects();
	PlatformFactory platformFactory;

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		v2f imageSize;
		imageSize.x = tileObj[i].getSize().x;
		imageSize.y = tileObj[i].getSize().y;

		if (tileObj[i].getType() != "")
		{
			int type = stoi(tileObj[i].getType());

			if (type == 3)
			{
				//door
			}
			else
			{
				MovingPlatform* platform = platformFactory.CreateMovingPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, GetWaypointPositions(tileObj[i].getProp("Waypoints")->getValue<std::string>()), tileObj[i].getProp("Speed")->getValue<float>());
				MovingPlatform::eMovingPlatformType aType = MovingPlatform::eMovingPlatformType::MovingPlatform;
				
				switch (type)
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
				platform->AddButton(aPos, aType);
			}

		}
	}
}

std::vector<v2f> TiledMap::GetWaypointPositions(const std::string somePositions)
{
	std::vector<v2f> waypoints;
	waypoints.push_back({ -100, -10 }); //temp
	return waypoints;
}

v2f TiledMap::GetScreenPosition(v2f aTiledPos)
{
	return aTiledPos;
}
