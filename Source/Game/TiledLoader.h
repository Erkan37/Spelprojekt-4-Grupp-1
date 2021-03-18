#pragma once
#include "rapidjson/document.h"
#include "Scene.h"

struct LoadData
{
	v2f myPosition;
	v2f mySize;
	int myType;
	std::string myWaypoints;
	float mySpeed;
};

class TiledLoader
{
public:
	void Load(Scene* aScene, int aLevelIndexENUM);
	
private:
	void ParseGraphics(const std::vector<LoadData> someBG1Data, const std::vector<LoadData> someBG2Data, const std::vector<LoadData> someFG1Data, const std::vector<LoadData> someFG2Data, const std::vector<LoadData> someHRData, Scene* aScene);
	void ParseBonfires(const std::vector<v2f> somePos, Scene*);
	void ParseDoors(const std::vector<LoadData> someData, Scene*);
	void ParseEnemies(const std::vector<LoadData> someData, Scene*);
	void ParseLedges(const std::vector<LoadData> someData, Scene*);
	void ParseCollectables(const std::vector<LoadData> someData, Scene*);
	void ParseCollectableZones(const std::vector<LoadData> someData, Scene*);
	void ParsePlatforms(const std::vector<LoadData> someData, Scene*);
	void ParseHiddenRooms(const std::vector<LoadData> someData, Scene*);
	void ParseSprings(const std::vector<LoadData> someData, Scene*);
	void ParseBashableObjects(const std::vector<LoadData> someData, Scene*);
	void ParseButtons(const std::vector<LoadData> someData, Scene*);

	std::vector<v2f> GetWaypointPositions(const std::string somePositions, v2f aSpawnPos);

	v2f myTileSize = { 8, 8 };
};

