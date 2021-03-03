/*
*	Author: Elia Rönning
*/

#pragma once
#include "../External/Headers/CU/Vector2.hpp"

struct Transform
{
public:
	Transform()
		: myPosition({ 0.0f, 0.0f})
		, myRotation(0.0f)
		, myPivot({ .5f, .5f })
	{}
	Transform(const v2f& aPosition)
		: myPosition(aPosition)
		, myRotation(0.0f)
		, myPivot({ .5f, .5f })
	{}
	Transform(const v2f& aPosition, const float& aRotation)
		: myPosition(aPosition)
		, myRotation(aRotation)
		, myPivot({ .5f, .5f })
	{}
	Transform(const v2f& aPosition, const float& aRotation, const v2f& aPivot)
		: myPosition(aPosition)
		, myRotation(aRotation)
		, myPivot(aPivot)
	{}

	v2f myPosition;
	float myRotation;
	v2f myPivot;
	bool myShouldBeDestroyed = false;
};