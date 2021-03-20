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
	myBatch(nullptr)
{
	
}

TileSetLayer::~TileSetLayer()
{
	
}

void TileSetLayer::LoadTileSetLayer(const TileSetLayerProperties& aTileSetLayerProperties, const GenericArray& aLayerData, const int& aWidth, const int& aHeight, const int& aZIndex)
{
	SetZIndex(aZIndex);

	myBatch = AddComponent<SpritebatchComponent>();
	myBatch->SetSpritePath(aTileSetLayerProperties.mySpritePath);
	myBatch->SetSamplerFilter(ESamplerFilter_Point);

	const GenericArray& data = aLayerData;

	const int width = aWidth;
	const int height = aHeight;

	for (int dataIndex = 0; dataIndex < data.Size(); ++dataIndex)
	{
		if (data[dataIndex].GetInt() == 0)
		{
			continue;
		}

		float x = dataIndex % width + 0.5f;
		float y = dataIndex / width + 0.5f;

		SpriteComponent* sprite = AddComponent<SpriteComponent>();

		sprite->SetSpritePath(aTileSetLayerProperties.mySpritePath);
		sprite->SetSamplerState(ESamplerFilter_Point);
		sprite->SetSize({ aTileSetLayerProperties.mySpriteSizeX, aTileSetLayerProperties.mySpriteSizeY });

		const int realQuad = data[dataIndex].GetInt() - 1;
		int xQ = static_cast<int>(realQuad % aTileSetLayerProperties.myQuadLengthX);
		int yQ = static_cast<int>(realQuad / aTileSetLayerProperties.myQuadLengthX);

		int texelX = static_cast<int>(1.0f / aTileSetLayerProperties.myImageSizeX);
		int texelY = static_cast<int>(1.0f / aTileSetLayerProperties.myImageSizeY);

		sprite->SetRelativePosition({ x * (aTileSetLayerProperties.mySpriteSizeX), y * (aTileSetLayerProperties.mySpriteSizeY) });
		sprite->SetSpriteRect(texelX + xQ * aTileSetLayerProperties.myRectQuadX, texelY + yQ * aTileSetLayerProperties.myRectQuadY, (xQ + 1.0f) * aTileSetLayerProperties.myRectQuadX - texelX, (yQ + 1.0f) * aTileSetLayerProperties.myRectQuadY - texelY);
	
		myBatch->AddSprite(sprite);
	}

	myBatch->Init();
}