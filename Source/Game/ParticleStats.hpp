#pragma once
#include "..\tga2dcore\tga2d\math\color.h"
#include <string>

namespace Tga2D
{
	class CColor;
}

class ParticleStats
{
private:
	friend class ParticleEffect;
	friend class ParticleEffectFactory;

	std::string myEffectType = {};
	std::string mySpritePath = {};
	int myEffectTypeIndex = {};
	bool myIsRepeating = {};

	float myEmitTime = {};
	float myPauseTime = {};

	float myStartScale = {};
	float myEndScale = {};

	float myMinBetweenSpawn = {};
	float myMaxBetweenSpawn = {};

	float myMinStartSpeed = {};
	float myMaxStartSpeed = {};

	float myMinAcceleration = {};
	float myMaxAcceleration = {};

	float myParticleAngleInterval = {};
	float myMinParticleAngularVel = {};
	float myMaxParticleAngularVel = {};

	float myEmitterAngle = {};
	float myEmitterWidth = {};

	float myMinEmitterAngularVelocity = {};
	float myMaxEmitterAngularVelocity = {};

	float myMinParticleLifeTime = {};
	float myMaxParticleLifeTime = {};
	float myEmitterLifeTime = {};

	Tga2D::CColor myStartColor = {};
	Tga2D::CColor myEndColor = {};

};