#include "stdafx.h"
#include "Scene.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d/sprite/sprite_batch.h>
#include "ParticleEffect.h"
#include "LevelScene.h"
#include "Player.hpp"
#include "PhysicsComponent.h"


ParticleEffect::ParticleEffect()
{
	myPlayer = {};
	myPosition = {};
	myIsActive = {};
}

void ParticleEffect::Init(ParticleStats aStats, Player* aPlayer)
{
	assert(aPlayer != NULL);
	myPlayer = aPlayer;
	myStats = aStats;

	if (static_cast<eParticleEffects>(myStats.myEffectTypeIndex) == eParticleEffects::RunEffect)
		myIsActive = true;
}

void ParticleEffect::Update(const float& aDeltaTime)
{
	if (myIsActive)
	{
		if (myStats.myEffectTypeIndex == static_cast<int>(eParticleEffects::RunEffect))
			UpdatePlayerEffect(aDeltaTime);
		else
			UpdateParticle(aDeltaTime);
	}
}

void ParticleEffect::Render()
{
	if (myIsActive)
	{
		mySprites->Render();
	}
}

const void ParticleEffect::SetPosition(const v2f aPosition)
{
	myPosition = aPosition;
}

const void ParticleEffect::SetIsActive(const bool aActiveState)
{
	myIsActive = aActiveState;
}

const bool ParticleEffect::GetIsActive()
{
	return myIsActive;
}

const eParticleEffects ParticleEffect::GetType() const
{
	return static_cast<eParticleEffects>(myStats.myEffectTypeIndex);
}

const void ParticleEffect::UpdateParticle(const float& aDeltaTime)
{
	Tga2D::CSprite* sprite = new Tga2D::CSprite();
	sprite->Init(myStats.mySpritePath.c_str());
	sprite->SetPosition(myPlayer->GetPosition());
	mySprites->AddObject(sprite);

}

const void ParticleEffect::UpdatePlayerEffect(const float& aDeltaTime)
{
	//if (myPlayer->GetComponent<PhysicsComponent>()->GetVelocityX() > 0 || myPlayer->GetComponent<PhysicsComponent>()->GetVelocityX() < 0)
	//{
		UpdateParticle(aDeltaTime);
	//}
}

const void ParticleEffect::SetEffect(ParticleEffect* aEffect)
{
	myIsActive = aEffect->myIsActive;
	myStats = aEffect->myStats;
	myPlayer = aEffect->myPlayer;
	mySprites = new Tga2D::CSpriteBatch(true);
}
