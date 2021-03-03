/*
*	Author: Elia Rönning
*/

#include "stdafx.h"
#include "Renderer.h"

#include <algorithm>
#include <tga2d/sprite/sprite.h>
#include <tga2d/sprite/sprite_batch.h>

inline void UpdateSprite(Tga2D::CSprite* aSprite, const v2f& aPos, const v2f& aSize, const v2f& aPivot, const float& aRot, const v4f& aColor)
{
	aSprite->SetPosition(aPos);
	aSprite->SetSizeRelativeToScreen(aSize);
	aSprite->SetPivot(aPivot);
	aSprite->SetRotation(aRot);
	aSprite->SetColor(Tga2D::CColor(aColor.x, aColor.y, aColor.z, aColor.w));
}

Renderer::Renderer()
	: myBuffer1(std::vector<RenderCommand>())
	, myBuffer2(std::vector<RenderCommand>())
	, myCounter(0Ui64)
	, myLogicCounter(0Ui64)
{
	// (mostly) Completely arbitrary magic numbers.
	myBuffer1.reserve(8192Ui64);
	myBuffer2.reserve(8192Ui64);
}

void Renderer::Render()
{
	std::vector<RenderCommand>& buffer = (myCounter % 2 ? myBuffer1 : myBuffer2);

	std::sort(buffer.begin(), buffer.end(), [](RenderCommand& a, RenderCommand& b)
	{
		return a.myZIndex < b.myZIndex;
	});

	for (RenderCommand& com : buffer)
	{
		if (!com.myTarget) continue;

		switch (com.myType)
		{
		case RenderCommand::Type::Sprite:
		{
			Tga2D::CSprite* sprite = (Tga2D::CSprite*)com.myTarget;

			UpdateSprite(sprite, com.myPosition, com.mySize, com.myPivot, com.myRotation, com.myColor);

			sprite->Render();

			break;
		}
		case RenderCommand::Type::Batch:
		{
			Tga2D::CSpriteBatch* batch = (Tga2D::CSpriteBatch*)com.myTarget;

			batch->Render();

			break;
		}
		}
	}

	buffer.clear();
	++myCounter;

	while (myCounter > myLogicCounter);
}

void Renderer::PushRenderCommand(const RenderCommand& aRenderCommand)
{
	(myCounter % 2 ? myBuffer2 : myBuffer1).push_back(aRenderCommand);
}

void Renderer::IncrementLogicCounter()
{
	++myLogicCounter;
}

const std::atomic<uint64_t>& Renderer::GetRenderCounter() const
{
	return myCounter;
}

const std::atomic<uint64_t>& Renderer::GetLogicCounter() const
{
	return myLogicCounter;
}
