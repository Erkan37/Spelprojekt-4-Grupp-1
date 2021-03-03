/*
*	Author: Elia Rönning
*/

#include "stdafx.h"
#include "SpritebatchComponent.h"
#include "SpriteComponent.h"
#include <tga2d/sprite/sprite_batch.h>
#include "Game.h"
#include "GameWorld.h"
#include "RenderCommand.hpp"

SpritebatchComponent::SpritebatchComponent()
	: myBatch(nullptr)
	, mySprites(std::vector<SpriteComponent*>())
	, mySpritePath(std::string())
	, myBlendState(EBlendState_Alphablend)
	, mySamplerFilter(ESamplerFilter_Bilinear)
{}

SpritebatchComponent::~SpritebatchComponent()
{
	for (SpriteComponent*& sprite : mySprites)
	{
		sprite->myIsPartOfBatch = false;
	}
	mySprites.clear();

	Reset();
}

void SpritebatchComponent::Init()
{
	myBatch->Init(mySpritePath.c_str());
}

void SpritebatchComponent::Render(Transform& aTransform, GameObject& aGameObject)
{
	CGameWorld::GetInstance()->Game()->GetRenderer().PushRenderCommand(
	{
		RenderCommand::Type::Batch,
		myBatch,
		0,
		myBlendState,
		mySamplerFilter
	});
}

SpritebatchComponent& SpritebatchComponent::SetSpritePath(const std::string& aSpritePath)
{
	if (myBatch)
	{
		Reset();
	}

	myBatch = new Tga2D::CSpriteBatch(false);
	mySpritePath = aSpritePath;

	return *this;
}
const std::string SpritebatchComponent::GetSpritePath() const
{
	return myBatch->GetImagePath();
}
SpritebatchComponent& SpritebatchComponent::AddSprite(SpriteComponent* aSprite)
{
	myBatch->AddObject(aSprite->mySprite);
	mySprites.push_back(aSprite);
	aSprite->myIsPartOfBatch = true;

	return *this;
}

void SpritebatchComponent::Reset()
{
	delete myBatch;
	myBatch = nullptr;
}

void SpritebatchComponent::SetBlendState(const EBlendState aBlendState)
{
	myBlendState = aBlendState;
}

const EBlendState& SpritebatchComponent::GetBlendState() const
{
	return myBlendState;
}

void SpritebatchComponent::SetSamplerFilter(const ESamplerFilter& aSamplerFilter)
{
	mySamplerFilter = aSamplerFilter;
}

const ESamplerFilter& SpritebatchComponent::GetSamplerFilter() const
{
	return mySamplerFilter;
}
