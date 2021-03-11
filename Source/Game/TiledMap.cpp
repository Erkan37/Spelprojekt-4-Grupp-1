#include "stdafx.h"
#include "TiledMap.h"
#include "tileson/tileson_min.hpp"
#include "PlatformFactory.hpp"

#include <cassert>

bool TiledMap::Load(const std::string& aPath)
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

	tson::Layer* foregroundLayer = map->getLayer("Foreground");
	if (foregroundLayer)
	{
		ParseLayer(foregroundLayer);
	}
	else
	{
		ERROR_PRINT("failed to load layer");
	}

	return true;
}

void TiledMap::ParseLayer(tson::Layer*)
{

}
