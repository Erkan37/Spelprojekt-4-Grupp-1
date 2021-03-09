#include "stdafx.h"
#include "TiledMap.h"
#include "tileson/tileson_min.hpp"

#include <cassert>

bool TiledMap::Load(const std::string& aPath)
{
	tson::Tileson parser;
	std::unique_ptr<tson::Map> map = parser.parse(std::filesystem::path(aPath));

	if (map->getStatus() != tson::ParseStatus::OK)
	{
		ERROR_PRINT("map load failed: %s", map->getStatusMessage().c_str());
		return false;
	}

	return false;
}
