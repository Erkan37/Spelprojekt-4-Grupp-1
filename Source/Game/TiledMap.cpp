#include "stdafx.h"
#include <sstream>
#include "TiledMap.h"
#include "tileson/tileson_min.hpp"

#include "SpringObject.h"
#include "Bonfire.hpp"
#include "Collectible.hpp"

#include "Scene.h"
#include <cassert>

bool TiledMap::Load(const std::string& aPath, Scene* aScene)
{
	myNumberOfTilesOnScreen.x = 40;
	myNumberOfTilesOnScreen.y = 22.5;

	tson::Tileson parser;
	std::unique_ptr<tson::Map> map = parser.parse(std::filesystem::path(aPath));

	if (map->getStatus() != tson::ParseStatus::OK)
	{
		ERROR_PRINT("map load failed", map->getStatusMessage().c_str());
		return false;
	}

	assert(map->getSize().x > 0);
	assert(map->getSize().y > 0);

	//Draw (not sure if we can do this yet)
	tson::Layer* Bg1 = map->getLayer("BG1");
	tson::Layer* Bg2 = map->getLayer("BG2");
	tson::Layer* Fg1 = map->getLayer("FG1");
	tson::Layer* Fg2 = map->getLayer("FG2");
	tson::Layer* Hr = map->getLayer("HR");

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

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		//Add objects here
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

		//Add objects here
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

		Collectible::eCollectibleType aType;

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

	for (int i = 0; i < tileObj.size(); ++i)
	{
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		v2f imageSize;
		imageSize.x = tileObj[i].getSize().x;
		imageSize.y = tileObj[i].getSize().y;

		//Delete this when the switch case is fixed
		myPlatformFactory->CreateStaticPlatform(aScene, GetScreenPosition(aPos), GetObjSize(imageSize), GetObjSize(imageSize), true);

		//float speed = 0;
		//std::string stringWaypoints = "";
		//std::vector<v2f> waypoints;

		//if (tileObj[i].getType() != "")
		//{
		//	int type = stoi(tileObj[i].getType());

		//	switch (type)
		//	{
		//	case 0:
		//		myPlatformFactory->CreateStaticPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, false);
		//		break;
		//	case 1:
		//		speed = tileObj[i].getProp("Speed")->getValue<float>();
		//		stringWaypoints = tileObj[i].getProp("Waypoints")->getValue<std::string>();
		//		
		//		// translate stringWaypoints to actual waypoints
		//		waypoints.push_back({0, 0});

		//		myPlatformFactory->CreateMovingPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, waypoints, speed);
		//		break;
		//	case 2:
		//		myPlatformFactory->CreateUnstablePlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize);
		//		break;
		//	case 3:
		//		myPlatformFactory->CreateDestructiblePlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize);
		//		break;
		//	case 4:
		//		myPlatformFactory->CreateDeadlyPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize);
		//		break;
		//	case 5:
		//		myPlatformFactory->CreateStaticPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, true);
		//	}
		//}
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

		//Add objects here
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

		//Add objects here
	}
}

void TiledMap::ParseButtons(tson::Layer* aLayer, Scene* aScene)
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

v2f TiledMap::GetScreenPosition(v2f aTiledPos)
{
	//int tiledTileSize = 8;
	//v2f screenPos;
	//v2f tiledTile;

	//tiledTile.x = aTiledPos.x / tiledTileSize;
	//tiledTile.y = aTiledPos.y / tiledTileSize;

	//v2f tileSizeInPixels;
	//tileSizeInPixels.x = Tga2D::CEngine::GetInstance()->GetWindowSize().x / myNumberOfTilesOnScreen.x;
	//tileSizeInPixels.y = Tga2D::CEngine::GetInstance()->GetWindowSize().y / myNumberOfTilesOnScreen.y;

	//screenPos.x = tiledTile.x * tileSizeInPixels.x;
	//screenPos.y = tiledTile.y * tileSizeInPixels.y;

	//return screenPos;
	return aTiledPos;
}

v2f TiledMap::GetObjSize(v2f aTiledSize)
{
	//int tiledTileSize = 8;
	//v2f objSize;

	//v2f tileSizeInPixels;
	//tileSizeInPixels.x = Tga2D::CEngine::GetInstance()->GetWindowSize().x / myNumberOfTilesOnScreen.x;
	//tileSizeInPixels.y = Tga2D::CEngine::GetInstance()->GetWindowSize().y / myNumberOfTilesOnScreen.y;

	//objSize.x = (aTiledSize.x / tiledTileSize) * tileSizeInPixels.x;
	//objSize.y = (aTiledSize.y / tiledTileSize) * tileSizeInPixels.y;

	//return objSize;
	return aTiledSize;
}
