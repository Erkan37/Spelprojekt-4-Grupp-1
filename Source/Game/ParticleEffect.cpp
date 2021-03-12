#include "stdafx.h"
#include "Scene.h"
#include "ParticleEffect.h"
#include "LevelScene.h"
#include "Player.hpp"

ParticleEffect::ParticleEffect()
{
	myPlayer = {};
	myPosition = {};
	myIsActive = {};
}

void ParticleEffect::Init(ParticleStats aStats, Scene* aLevelScene)
{
	myStats = aStats;
	LevelScene* myScene = dynamic_cast<LevelScene*>(aLevelScene);
	myPlayer = dynamic_cast<Player*>(myScene->GetPlayer());

	if (static_cast<eParticleEffects>(myStats.myEffectTypeIndex) == eParticleEffects::RunEffect)
		myIsActive = true;
}

void ParticleEffect::Update(const float& aDeltaTime)
{
	if (myIsActive)
	{
		UpdateParticle(aDeltaTime);
	}
}

void ParticleEffect::Render()
{
	if (myIsActive)
	{

	}
}

void ParticleEffect::SetPosition(const v2f aPosition)
{
	myPosition = aPosition;
}

void ParticleEffect::SetIsActive(const bool aActiveState)
{
	myIsActive = aActiveState;
}

bool ParticleEffect::GetIsActive()
{
	return myIsActive;
}

eParticleEffects ParticleEffect::GetType()
{
	return static_cast<eParticleEffects>(myStats.myEffectTypeIndex);
}

void ParticleEffect::UpdateParticle(const float& aDeltaTime)
{





}
