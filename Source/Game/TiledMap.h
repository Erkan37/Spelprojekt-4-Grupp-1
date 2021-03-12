#pragma once
#include "Scene.h"
#include "PlatformFactory.hpp"

namespace tson
{
	class Layer;
}

class Scene; 

class TiledMap
{
public:
	bool Load(const std::string& aPath, Scene*);

private:
	void ParseBonfires(tson::Layer*, Scene*);
	void ParseDoors(tson::Layer*, Scene*);
	void ParseEnemies(tson::Layer*, Scene*);
	void ParseLedges(tson::Layer*, Scene*);
	void ParsePickups(tson::Layer*, Scene*);
	void ParsePlatforms(tson::Layer*, Scene*);

	v2f GetScreenPosition(v2f aTiledPos);
	v2f GetObjSize(v2f aTiledSize);
	v2f myNumberOfTilesOnScreen;

	std::unique_ptr<PlatformFactory> myPlatformFactory;
};

