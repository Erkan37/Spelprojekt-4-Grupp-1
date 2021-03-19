#pragma once
#include "GameObject.h"
#include "../External/Headers/rapidjson/document.h"

#include "TileSetLayerProperties.hpp"

class Scene;
class SpritebatchComponent;
class LoadData;

class TileSetLayer
    : public GameObject
{
public:
    TileSetLayer(Scene* aLevelScene);
    ~TileSetLayer();

    void LoadTileSetLayer(const TileSetLayerProperties& aTileSetLayerProperties, const rapidjson::GenericArray<true, int>& aLayerData, const int& aWidth, const int& aHeight, const int& aZIndex);

private:
    SpritebatchComponent* myBatch;

};

