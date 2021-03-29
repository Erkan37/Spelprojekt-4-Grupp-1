#include "stdafx.h"
#include <iostream>
#include "Scene.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d/sprite/sprite_batch.h>
#include "ParticleEffect.h"
#include "Scene.h"
#include "Player.hpp"
#include "PhysicsComponent.h"
#include "Random.hpp"
#include "SpriteComponent.h"


ParticleEffect::ParticleEffect(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	mySpawnInterval = {};
	myPlayer = {};
	myIsActive = {};
	myTimer = {};
}

void ParticleEffect::Init(ParticleStats aStats, Player* aPlayer)
{
	assert(aPlayer != NULL);
	myPlayer = aPlayer;
	myStats = aStats;

	if (static_cast<eParticleEffects>(myStats.myEffectTypeIndex) == eParticleEffects::RunEffect)
		myIsActive = true;

	SetPosition(myPlayer->GetPosition());
	SetZIndex(100.f);
	SetPivot({ 0.5f, 0.5f });
	Activate();
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
	myTimer += aDeltaTime;

	v2f position = {};

	if (myStats.myEffectTypeIndex == static_cast<int>(eParticleEffects::RunEffect))
	{
		position = myPlayer->GetPosition();
		position.y = position.y + (myPlayer->GetComponent<SpriteComponent>()->GetSizeY() / 2);


	}
	else
		position = GetPosition();
	
	SetPosition(position);

	if (myTimer > mySpawnInterval)
	{
		myTimer = {};

		std::shared_ptr<EffectSprite> sprite = std::make_shared<EffectSprite>();

		sprite->myPathString = myStats.mySpritePath;
		sprite->mySpeedInterval = Utils::RandomFloat(myStats.myMinStartSpeed, myStats.myMaxStartSpeed);
		sprite->myAcceleration = Utils::RandomFloat(myStats.myMinAcceleration, myStats.myMaxAcceleration);
		sprite->myLifeTime = Utils::RandomFloat(myStats.myMinParticleLifeTime, myStats.myMaxParticleLifeTime);
		sprite->myRotation = Utils::RandomFloat(myStats.myMinParticleAngularVel, myStats.myMaxParticleAngularVel);
		sprite->myMinScale = myStats.myStartScale;
		sprite->myMaxScale = myStats.myEndScale;
		sprite->mySpawnAngle = myStats.myParticleAngleInterval;
		sprite->myEmitterAngle = myStats.myEmitterAngle;
		sprite->myEmitterStartAngle = myStats.myMinEmitterAngularVelocity;
		sprite->myEmitterEndAngle = myStats.myMaxEmitterAngularVelocity;
		sprite->myEmitterWidth = myStats.myEmitterWidth;
		sprite->myEmitterHeigth = myStats.myEmitterHeigth;
		sprite->myEmiterLifetime = myStats.myEmitterLifeTime;
		sprite->myStartColor = myStats.myStartColor;
		sprite->myEndColor = myStats.myEndColor;
		sprite->myIsLockedPos = myStats.myLockedPosition;
		sprite->myPosition = GetPosition();

		if (sprite->myIsLockedPos)
			SetPivot({ 0.f, 1.0f });

		sprite->AddSprite(AddComponent<SpriteComponent>());

		mySprites.push_back(sprite);

		mySpawnInterval = Utils::RandomFloat(myStats.myMinBetweenSpawn, myStats.myMaxBetweenSpawn);
	}
	
	for (int x = 0; x < mySprites.size(); x++)
	{
		mySprites[x]->Update(aDeltaTime);
		if (mySprites[x]->IsAlive() == false)
		{
			mySprites.erase(mySprites.begin() + x);
			DeleteInactiveComponents();
			break;
		}
	}


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
