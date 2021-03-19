#pragma once
#include "GameObject.h"
#include "../External/Headers/rapidjson/document.h"

#include "TileSetLayerProperties.hpp"

typedef rapidjson::GenericArray<true, rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>> GenericArray;

class Scene;
class SpritebatchComponent;
class LoadData;

class TileSetLayer
    : public GameObject
{
public:
    TileSetLayer(Scene* aLevelScene);
    ~TileSetLayer();

    void LoadTileSetLayer(const TileSetLayerProperties& aTileSetLayerProperties, const GenericArray& aLayerData, const int& aWidth, const int& aHeight, const int& aZIndex);

private:
    SpritebatchComponent* myBatch;

};

