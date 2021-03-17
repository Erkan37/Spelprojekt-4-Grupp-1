#pragma once
#include "Scene.h"

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
	void ParseGraphics(tson::Layer* aBG1, tson::Layer* aBG2, tson::Layer* aFG1, tson::Layer* aFG2, tson::Layer* aHR, Scene* aScene);
	void ParseBonfires(tson::Layer*, Scene*);
	void ParseDoors(tson::Layer*, Scene*);
	void ParseEnemies(tson::Layer*, Scene*);
	void ParseLedges(tson::Layer*, Scene*);
	void ParseCollectables(tson::Layer*, Scene*);
	void ParseCollectableZones(tson::Layer*, Scene*);
	void ParsePlatforms(tson::Layer*, Scene*);
	void ParseHiddenRooms(tson::Layer*, Scene*);
	void ParseSprings(tson::Layer*, Scene*);
	void ParseBashableObjects(tson::Layer*, Scene*);
	void ParseButtons(tson::Layer*, Scene*);


	std::vector<v2f> GetWaypointPositions(const std::string somePositions);
	v2f GetScreenPosition(v2f aTiledPos);
};

