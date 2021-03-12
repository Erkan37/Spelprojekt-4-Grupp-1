#include "stdafx.h"
#include "TiledMap.h"
#include "tileson/tileson_min.hpp"
#include "PlatformFactory.hpp"
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

	//Draw
	auto Bg1 = map->getLayer("BG1");
	map->getLayer("BG2");
	map->getLayer("FG1");
	map->getLayer("FG2");

	//Create
	map->getLayer("");

	tson::Layer* platformLayer = map->getLayer("Platforms");
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

void TiledMap::ParsePlatforms(tson::Layer* aLayer, Scene* aScene)
{
	PlatformFactory aFactory;

	//map with platforms
	const auto& tileObjects = aLayer->getTileObjects();
	auto& tileObj = aLayer->getObjects();
	tileObj[0].getProp("");

	for (int i = 0; i < tileObj.size(); ++i)
	{
		//Fixa denna
		v2f tileSize;
		//0: Statisk plattform
		//1 : Plattform som rör sig
		//2 : Sån som faller om man står på den instabil plattform
		//3 : Förstörbar plattform
		//4 : MördarPlattform
		//5: OneWay plattformar, kan hoppa igenom underifrån

		//Skapa position
		v2f aPos;
		aPos.x = tileObj[i].getPosition().x;
		aPos.y = tileObj[i].getPosition().y;

		v2f imageSize;
		imageSize.x = tileObj[i].getSize().x;
		imageSize.y = tileObj[i].getSize().y;

		//GetProperties
		//tileObj[i].getProp("Properties");

		switch (stoi(tileObj[i].getType())) //Exception
		{
		case 0:
			aFactory.CreateStaticPlatform(aScene, aPos, imageSize, imageSize, true); //Change aIsOneWay when it has a variable
			break;
			//case 1:
			//	aFactory.CreateMovingPlatform(aScene, aPos, imageSize, imageSize, );
			//	break;
			//case 2:
			//	aFactory.CreateUnstablePlatform();
			//	break;
			//case 3:
			aFactory.CreateDestructiblePlatform(aScene, aPos, imageSize, imageSize);
			break;
		case 4:
			aFactory.CreateDeadlyPlatform(aScene, aPos, imageSize, imageSize);
			break;
		}
	}
}
