/*
* Author: Axel Melkersson
*/

#include "stdafx.h"
#include "AnimationComponent.hpp"
#include "GameObject.h"
#include "GameWorld.h"
#include "SpriteComponent.h";
#include "../External/Headers/CU/Utilities.h"

AnimationComponent::AnimationComponent()
	: myTimer(0.0f),
	myDisplayOnce(false),
	myHasBeenDisplayed(false),
	myHasReachedEnd(false),
	myIsBackwards(false),
	myIsBoomerang(false),
	myNextAnimation(nullptr),
	myUpdateTime(0.0f),
	myAnimationFrameCount(0),
	myColumns(0),
	mySpriteIndex(0),
	mySprite(nullptr),
	myBoundsX(0.0f),
	myBoundsY(0.0f)
{}

AnimationComponent::AnimationComponent(SpriteComponent* aSpriteComponent, const int& aAnimationFrameCount, const int& aColumns, const float& aUpdateTime, const int aBoundsX, const int aBoundsY)
{
	myIsBackwards = false;
	myHasReachedEnd = false;
	myIsBoomerang = false;

	myDisplayOnce = false;
	myHasBeenDisplayed = false;

	myNextAnimation = nullptr;

	myBoundsX = aBoundsX;
	myBoundsY = aBoundsY;

	mySprite = aSpriteComponent;

	mySpriteIndex = 0;

	myTimer = aUpdateTime;
	myUpdateTime = aUpdateTime;

	myAnimationFrameCount = aAnimationFrameCount;
	myColumns = aColumns;

	mySprite->SetSpriteRectPixel(0.0f, 0.0f, myBoundsX, myBoundsY);
}

void AnimationComponent::SetSprite(SpriteComponent* aSpriteComponent)
{
	mySprite = aSpriteComponent;
}

void AnimationComponent::SetAnimation(SpriteComponent* aSpriteComponent, const int& aAnimationFrameCount, const int& aColumns, const float& aUpdateTime)
{
	myIsBackwards = false;
	myHasReachedEnd = false;
	myIsBoomerang = false;

	myDisplayOnce = false;
	myHasBeenDisplayed = false;

	myNextAnimation = nullptr;

	mySprite = aSpriteComponent;

	mySpriteIndex = 0;

	myTimer = aUpdateTime;
	myUpdateTime = aUpdateTime;

	myAnimationFrameCount = aAnimationFrameCount;
	myColumns = aColumns;

	mySprite->SetSpriteRectPixel(0.0f, 0.0f, myBoundsX, myBoundsY);
}

void AnimationComponent::SetDisplayOnce(const bool aIsDisplayedOnce)
{
	myDisplayOnce = aIsDisplayedOnce;
}

void AnimationComponent::SetBoomerang(const bool aIsBoomerang)
{
	myIsBoomerang = aIsBoomerang;
}

void AnimationComponent::Update(Transform& aTransform, GameObject& aGameObject)
{
	if (myHasBeenDisplayed && myDisplayOnce)
	{
		return;
	}

	if (myAnimationFrameCount == 0)
	{
		return;
	}

	myTimer -= CGameWorld::GetInstance()->DeltaTime();

	if (myTimer < 0)
	{
		if (myIsBoomerang && myHasReachedEnd)
		{


			--mySpriteIndex;
			if (mySpriteIndex <= 0)
			{
				myHasReachedEnd = false;
			}
		}
		else
		{
			if (myIsBackwards)
			{
				--mySpriteIndex;
			}
			else
			{
				++mySpriteIndex;
			}
		}

		if ((mySpriteIndex >= myAnimationFrameCount && !myIsBackwards) || (mySpriteIndex < 0 && myIsBackwards) || (myIsBoomerang && (mySpriteIndex >= myAnimationFrameCount || mySpriteIndex < 0)))
		{
			
			myHasBeenDisplayed = true;

			if (myIsBackwards)
			{
				mySpriteIndex = myAnimationFrameCount - 1;
			}
			else if (myIsBoomerang)
			{
				--mySpriteIndex;
			}
			else
			{
				mySpriteIndex = 0;
			}

			myHasReachedEnd = true;

			if (myDisplayOnce)
			{
				if (myNextAnimation)
				{
					SetAnimation(myNextAnimation);
				}
				return;
			}
		}

		const float xOffset = static_cast<float>(mySpriteIndex % myColumns) * myBoundsX;
		const float yOffset = static_cast<float>(mySpriteIndex / myColumns) * myBoundsY;

		const v2f imageSize = mySprite->GetImageSize();

		const float xTexel = 1.0f / imageSize.x;
		const float yTexel = 1.0f / imageSize.y;

		myTimer = myUpdateTime;
		mySprite->SetSpriteRectPixel(xTexel + xOffset, yTexel + yOffset, xOffset + myBoundsX - xTexel, yOffset + myBoundsY - yTexel);
	}
}

void AnimationComponent::SetAnimation(Animation* aAnimation)
{
	mySprite->SetSpritePath(aAnimation->mySprite);
	myBoundsX = aAnimation->myBoundsX;
	myBoundsY = aAnimation->myBoundsY;
	SetAnimation(mySprite, aAnimation->myAnimationFrameCount, aAnimation->myColumns, aAnimation->myUpdateTime);
	mySpriteIndex = aAnimation->mySpriteIndex;
	myIsBoomerang = aAnimation->myIsBoomerang;
	myIsBackwards = aAnimation->myIsBackwards;
	myDisplayOnce = aAnimation->myDisplayOnce;

	const float xOffset = static_cast<float>(mySpriteIndex % myColumns) * myBoundsX;
	const float yOffset = static_cast<float>(mySpriteIndex / myColumns) * myBoundsY;

	mySprite->SetSpriteRectPixel(xOffset, yOffset, xOffset + myBoundsX, yOffset + myBoundsY);
}

void AnimationComponent::SetNextAnimation(Animation* aAnimation)
{
	myNextAnimation = aAnimation;
}

void AnimationComponent::ContinueToNextAnimation()
{
	if (myNextAnimation != nullptr)
	{
		SetAnimation(myNextAnimation);
	}
}

bool AnimationComponent::GetIsDisplayedOnce()
{
	return myDisplayOnce;
}

bool AnimationComponent::GetHasBeenDisplayedOnce()
{
	return myHasBeenDisplayed;
}