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
	myBatch(AddComponent<SpritebatchComponent>())
{
	
}

TileSetLayer::~TileSetLayer()
{
	
}

void TileSetLayer::LoadTileSetLayer(const TileSetLayerProperties& aTileSetLayerProperties, const GenericArray& aLayerData, const int& aWidth, const int& aHeight, const int& aZIndex)
{
	SetZIndex(aZIndex);

	myBatch->SetSpritePath(aTileSetLayerProperties.mySpritePath);
	myBatch->Init();

	const GenericArray& data = aLayerData;

	const int width = aWidth;
	const int height = aHeight;

	for (int dataIndex = 0; dataIndex < data.Size(); ++dataIndex)
	{
		if (data[dataIndex].GetInt() == 0)
		{
			continue;
		}

		float x = dataIndex % width + .5f;
		float y = dataIndex / width + .5f;

		SpriteComponent* sprite = AddComponent<SpriteComponent>();

		sprite->SetSpritePath(aTileSetLayerProperties.mySpritePath);
		sprite->SetSamplerState(ESamplerFilter_Point);
		sprite->SetSize({ aTileSetLayerProperties.mySpriteSizeX, aTileSetLayerProperties.mySpriteSizeY });
		myBatch->AddSprite(sprite);

		const int realQuad = data[dataIndex].GetInt() - 1.0f;
		float xQ = static_cast<float>(realQuad % aTileSetLayerProperties.myQuadLengthX);
		float yQ = static_cast<float>(realQuad / aTileSetLayerProperties.myQuadLengthX);

		float texelX = 1.0f / aTileSetLayerProperties.myImageSizeX;
		float texelY = 1.0f / aTileSetLayerProperties.myImageSizeY;

		sprite->SetSpriteRect(texelX + xQ * aTileSetLayerProperties.myRectQuadX, texelY + yQ * aTileSetLayerProperties.myRectQuadY, (xQ + 1.0f) * aTileSetLayerProperties.myRectQuadX - texelX, (yQ + 1.0f) * aTileSetLayerProperties.myRectQuadY - texelY);

		sprite->SetRelativePosition({ x * (aTileSetLayerProperties.mySpriteSizeX), y * (aTileSetLayerProperties.mySpriteSizeY) });
	}
}