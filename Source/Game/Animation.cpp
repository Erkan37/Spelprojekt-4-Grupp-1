/*
* Author: Axel Melkersson
*/

#include "stdafx.h"
#include "Animation.hpp"
#include "SpriteComponent.h"
#include "AnimationComponent.hpp"

Animation::Animation()
	:
	myIsBackwards(false),
	myDisplayOnce(false),
	myIsBoomerang(false),
	mySpriteIndex(0),
	myAnimationFrameCount(1),
	myColumns(1),
	myUpdateTime(0.15f),
	mySpriteComponent(nullptr),
	myBoundsX(0),
	myBoundsY(0)
{}

Animation::Animation(const bool aIsBackwards, const bool aIsDisplayedOnce, const bool aIsBoomerang, const int aSpriteIndex, const int aAnimationFrames, const int aColumns, const float& aUpdateTime, SpriteComponent* aSprite, const int aBoundsX, const int aBoundsY)
	:
	myIsBackwards(aIsBackwards),
	myDisplayOnce(aIsDisplayedOnce),
	myIsBoomerang(aIsBoomerang),
	mySpriteIndex(aSpriteIndex),
	myAnimationFrameCount(aAnimationFrames),
	myColumns(aColumns),
	myUpdateTime(aUpdateTime),
	mySpriteComponent(aSprite),
	myBoundsX(aBoundsX),
	myBoundsY(aBoundsY)
{}