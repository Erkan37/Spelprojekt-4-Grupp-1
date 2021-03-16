#pragma once
#include "../External/Headers/CU/Vector2.hpp"

class SpriteComponent;

class EffectSprite
{
public:
	EffectSprite();
	~EffectSprite();

	void Update(const float& aDeltatime);

	void AddSprite(SpriteComponent* aSprite);
	bool IsAlive();


	SpriteComponent* mySprite;

	std::string myPathString = {};
	v2f myPosition = {};
	v2f myScale = {};
	v2f myMaxVectorScale = {};

	float myTotalTimer = {};

	float myMinScale = {};
	float myMaxScale = {};
	float mySpeedInterval = {};
	float myAcceleration = {};
	float myLifeTime = {};
	float myRotation = {};
	float myEmitterWidth = {};
	float myEmiterLifetime = {};
	float mySpawnAngle = {};
	float myEmitterAngle = {};

	bool myIsAlive = true;

	Tga2D::CColor myStartColor = {};
	Tga2D::CColor myEndColor = {};

};