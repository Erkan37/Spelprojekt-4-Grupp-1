/*
*	Author: Elia Rönning
*/

#pragma once
#include "Vector2.hpp"
#include "Vector4.hpp"

enum EBlendState : int;
enum ESamplerFilter : int;

struct RenderCommand
{
	enum class Type : uint8_t
	{
		Sprite,
		Batch
	};

	Type myType;
	void* myTarget;
	int32_t myZIndex;
	EBlendState myBlendState;
	ESamplerFilter mySamplerFilter;
	v2f myPosition;
	v2f mySize;
	v2f myPivot;
	float myRotation;
	v4f myColor;
	v4f myRect;
};