/*
* Author: Axel Melkersson
*/

#pragma once

class SpriteComponent;
class AnimationComponent;

class Animation
{
public:
	Animation();
	Animation(const bool aIsBackwards, const bool aIsDisplayedOnce, const bool aIsBoomerang, const int aSpriteIndex, const int aAnimationFrames, const int aColumns, const float& aUpdateTime, const std::string& aSpritePath, const int aBoundsX, const int aBoundsY);

	bool myIsBackwards;
	bool myDisplayOnce;

	bool myIsBoomerang;

	int myBoundsX;
	int myBoundsY;

	int mySpriteIndex;
	int myAnimationFrameCount;
	int myColumns;

	float myUpdateTime;

	std::string mySprite;
};

