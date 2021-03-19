#include "stdafx.h"
#include "TileSetLayerProperties.hpp"

#include "../External/Headers/rapidjson/document.h"
#include "../External/Headers/rapidjson/istreamwrapper.h"
#include <fstream>

TileSetLayerProperties::TileSetLayerProperties()
{
	std::ifstream tilesetFile = std::ifstream("JSON/PassOnTileset.json");
	rapidjson::IStreamWrapper tilesetFileStream(tilesetFile);

	rapidjson::Document tileSet;
	tileSet.ParseStream(tilesetFileStream);

	mySpritePath = tileSet["image"].GetString();

	myQuadLengthX = tileSet["columns"].GetInt();
	myQuadLengthY = tileSet["tilecount"].GetInt() / myQuadLengthX;
	mySpriteSizeX = tileSet["tilewidth"].GetFloat();
	mySpriteSizeY = tileSet["tileheight"].GetFloat();
	myImageSizeX = tileSet["imagewidth"].GetInt();
	myImageSizeY = tileSet["imageheight"].GetInt();

	float bufferX = (mySpriteSizeX * myQuadLengthX) / myImageSizeX;
	float bufferY = (mySpriteSizeY * myQuadLengthY) / myImageSizeY;

	myRectQuadX = bufferX / myQuadLengthX;
	myRectQuadY = bufferY / myQuadLengthY;
}