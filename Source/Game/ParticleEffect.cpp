#include "stdafx.h"
#include <iostream>
#include "Scene.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d/sprite/sprite_batch.h>
#include "ParticleEffect.h"
#include "Scene.h"
#include "Player.hpp"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "SpritebatchComponent.h"


ParticleEffect::ParticleEffect(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
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

	SetPivot({ 0.f, 0.f });
	SetPosition(myPlayer->GetPosition());

	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetSpritePath(myStats.mySpritePath);
	sprite->SetSize({ 32.f, 32.f });

	GameObject::Init();
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

//const void ParticleEffect::SetPosition(const v2f aPosition)
//{
//	myPosition = aPosition;
//}

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
	//SpriteComponent* sprite = new SpriteComponent();
	//sprite->SetSpritePath(myStats.mySpritePath);
	//sprite->SetRelativePosition(myPlayer->GetPosition());
	////mySprites.push_back(sprite);
	//myObject->GetComponent<SpritebatchComponent>()->AddSprite(sprite);
	SetPosition(myPlayer->GetPosition());
	std::cout << myPlayer->GetPosition().x << std::endl;


	
}

const void ParticleEffect::UpdatePlayerEffect(const float& aDeltaTime)
{
	//if (myPlayer->GetComponent<PhysicsComponent>()->GetVelocityX() > 0 || myPlayer->GetComponent<PhysicsComponent>()->GetVelocityX() < 0)
	//{
		UpdateParticle(aDeltaTime);
	//}
}

const void ParticleEffect::SetEffect(ParticleStats aEffect)
{
	myStats = aEffect;

	//myObject->AddComponent<SpritebatchComponent>();
	//myObject->GetComponent<SpritebatchComponent>()->SetSpritePath(myStats.mySpritePath);
	//myObject->GetComponent<SpritebatchComponent>()->Init();
}
