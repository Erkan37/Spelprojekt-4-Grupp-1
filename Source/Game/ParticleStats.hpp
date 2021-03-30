#pragma once
#include "..\tga2dcore\tga2d\math\color.h"
#include "..\External\Headers\CU\Vector4.hpp"
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
	bool myLockedPosition = {};

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
	float myEmitterHeigth = {};

	float myMinEmitterAngularVelocity = {};
	float myMaxEmitterAngularVelocity = {};

	float myMinParticleLifeTime = {};
	float myMaxParticleLifeTime = {};
	float myEmitterLifeTime = {};

	v4f myEmitterAngular = {};

	Tga2D::CColor myStartColor = {};
	Tga2D::CColor myEndColor = {};

};