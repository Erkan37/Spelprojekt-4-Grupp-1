#include "stdafx.h"
#include "TiledMap.h"
#include "tileson/tileson_min.hpp"
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

	//Create
	tson::Layer* bonfireLayer = map->getLayer("Bonfire");
	tson::Layer* doorLayer = map->getLayer("Doors");
	tson::Layer* enemyLayer = map->getLayer("Enemies");
	tson::Layer* ledgeLayer = map->getLayer("Ledges");
	tson::Layer* pickupLayer = map->getLayer("Pickups");
	tson::Layer* platformLayer = map->getLayer("Platforms");

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
	if (pickupLayer)
	{
		ParsePickups(pickupLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load pickuplayer");
	}
	if (platformLayer)
	{
		ParsePlatforms(platformLayer, aScene);
	}
	else
	{
		ERROR_PRINT("failed to load platformlayer");
	}

	return true;
}

void TiledMap::ParseBonfires(tson::Layer*, Scene*)
{
}

void TiledMap::ParseDoors(tson::Layer*, Scene*)
{
}

void TiledMap::ParseEnemies(tson::Layer*, Scene*)
{
}

void TiledMap::ParseLedges(tson::Layer*, Scene*)
{
}

void TiledMap::ParsePickups(tson::Layer*, Scene*)
{
}

void TiledMap::ParsePlatforms(tson::Layer* aLayer, Scene* aScene)
{
	auto& tileObj = aLayer->getObjects();

	for (int i = 0; i < tileObj.size(); ++i)
	{
		//Fix this ?
		v2f tileSize;

		//0: Statisk plattform
		//1 : Plattform som rör sig
		//2 : Sån som faller om man står på den instabil plattform
		//3 : Förstörbar plattform
		//4 : MördarPlattform
		//5: OneWay plattformar, kan hoppa igenom underifrån

		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		v2f imageSize;
		imageSize.x = tileObj[i].getSize().x;
		imageSize.y = tileObj[i].getSize().y;

		//GetProperties:
		//tileObj[i].getProp("Properties");

		myPlatformFactory->CreateStaticPlatform(aScene, GetScreenPosition(aPos), GetObjSize(imageSize), GetObjSize(imageSize), true);

		//if (tileObj[i].getType() != "")
		//{
		//	int type = stoi(tileObj[i].getType());

		//	switch (type)
		//	{
		//	case 0:
		//		myPlatformFactory->CreateStaticPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, true); //Change aIsOneWay when it has a variable
		//		break;
		//	case 1:
		//		myPlatformFactory->CreateStaticPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, true);
		//		//myPlatformFactory->CreateMovingPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, );
		//		break;
		//	case 2:
		//		myPlatformFactory->CreateStaticPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, true);
		//		//myPlatformFactory->CreateUnstablePlatform(aScene, GetScreenPosition(aPos));
		//		break;
		//	case 3:
		//		myPlatformFactory->CreateStaticPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize, true);
		//		//myPlatformFactory->CreateDestructiblePlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize);
		//		break;
		//	case 4:
		//		myPlatformFactory->CreateDeadlyPlatform(aScene, GetScreenPosition(aPos), imageSize, imageSize);
		//		break;
		//	}
		//}
	}
}

v2f TiledMap::GetScreenPosition(v2f aTiledPos)
{
	int tiledTileSize = 8;
	v2f screenPos;
	v2f tiledTile;

	tiledTile.x = aTiledPos.x / tiledTileSize;
	tiledTile.y = aTiledPos.y / tiledTileSize;

	v2f tileSizeInPixels;
	tileSizeInPixels.x = Tga2D::CEngine::GetInstance()->GetWindowSize().x / myNumberOfTilesOnScreen.x;
	tileSizeInPixels.y = Tga2D::CEngine::GetInstance()->GetWindowSize().y / myNumberOfTilesOnScreen.y;

	screenPos.x = tiledTile.x * tileSizeInPixels.x;
	screenPos.y = tiledTile.y * tileSizeInPixels.y;

	return screenPos;
}

v2f TiledMap::GetObjSize(v2f aTiledSize)
{
	int tiledTileSize = 8;
	v2f objSize;

	v2f tileSizeInPixels;
	tileSizeInPixels.x = Tga2D::CEngine::GetInstance()->GetWindowSize().x / myNumberOfTilesOnScreen.x;
	tileSizeInPixels.y = Tga2D::CEngine::GetInstance()->GetWindowSize().y / myNumberOfTilesOnScreen.y;

	objSize.x = (aTiledSize.x / tiledTileSize) * tileSizeInPixels.x;
	objSize.y = (aTiledSize.y / tiledTileSize) * tileSizeInPixels.y;

	return objSize;
}
