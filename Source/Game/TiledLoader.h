#pragma once
#include "rapidjson/document.h"
#include "Scene.h"

#include "TileSetLayerProperties.hpp"


struct LoadData
{
	v2f myPosition;
	v2f mySize;
	int myType;
	std::string myWaypoints;
	float mySpeed;
};

struct TileLayerData
{
	std::vector<int> myTiles;
	v2f mySize;
	int myZ;
};

class TiledLoader
{
public:
	void Load(Scene* aScene, int aLevelIndex);

private:
	void ParseGraphics(const std::vector<LoadData> someBG1Data, const std::vector<LoadData> someBG2Data, const std::vector<LoadData> someFG1Data, const std::vector<LoadData> someFG2Data, const std::vector<LoadData> someHRData, Scene* aScene);
	void ParseBonfires(const std::vector<LoadData> someData, Scene*);
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

	std::vector<TileLayerData> myTileLayerData;
	v2f myTileSize = { 8, 8 };

	TileSetLayerProperties myTileSetLayerProperties;
	
	int myBG1z = 80;
	int myBG2z = 90;
	int myFG1z = 110;
	int myFG2z = 120;
	int myHRz = 130;
};