#include "stdafx.h"
#include "TileSetLayer.hpp"

#include "Scene.h"
#include "SpritebatchComponent.h"
#include "SpriteComponent.h"

#include "../External/Headers/rapidjson/istreamwrapper.h"
#include <fstream>

#include "TiledLoader.h"

typedef rapidjson::Value::ConstValueIterator iterator;

TileSetLayer::TileSetLayer(Scene* aLevelScene)
	: GameObject(aLevelScene),
	myBatch(new SpritebatchComponent())
{
	
}

TileSetLayer::~TileSetLayer()
{
	delete myBatch;
}

void TileSetLayer::LoadTileSetLayer(const TileSetLayerProperties& aTileSetLayerProperties, const rapidjson::GenericArray<true, int>& aLayerData, const int& aWidth, const int& aHeight, const int& aZIndex)
{
	myBatch->SetSpritePath(aTileSetLayerProperties.mySpritePath);
	myBatch->Init();

	const rapidjson::GenericArray<true, int>& data = aLayerData;

	const int width = aWidth;
	const int height = aHeight;

	for (int dataIndex = 0; dataIndex < data.Size(); ++dataIndex)
	{
		if (data[dataIndex] == 0)
		{
			continue;
		}

		float x = dataIndex % width + .5f;
		float y = dataIndex / width + .5f;

		SpriteComponent* sprite = AddComponent<SpriteComponent>();

		sprite->SetSpritePath(aTileSetLayerProperties.mySpritePath);
		sprite->SetSamplerState(ESamplerFilter_Point);
		myBatch->AddSprite(sprite);

		const int realQuad = data[dataIndex] - 1.0f;
		float xQ = static_cast<float>(realQuad % aTileSetLayerProperties.myQuadLengthX);
		float yQ = static_cast<float>(realQuad / aTileSetLayerProperties.myQuadLengthX);

		float texelX = 1.0f / aTileSetLayerProperties.myImageSizeX;
		float texelY = 1.0f / aTileSetLayerProperties.myImageSizeY;

		sprite->SetSpriteRect(texelX + xQ * aTileSetLayerProperties.myRectQuadX, texelY + yQ * aTileSetLayerProperties.myRectQuadY, (xQ + 1.0f) * aTileSetLayerProperties.myRectQuadX - texelX, (yQ + 1.0f) * aTileSetLayerProperties.myRectQuadY - texelY);

		sprite->SetRelativePosition({ x * (aTileSetLayerProperties.mySpriteSizeX), y * (aTileSetLayerProperties.mySpriteSizeY) });
	}
}