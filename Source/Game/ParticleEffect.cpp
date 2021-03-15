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
	myPosition = {};
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

	SetPivot({ 0.5f, 0.5f });
	SetPosition(myPlayer->GetPosition());



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
	myTimer += aDeltaTime;

	v2f playerPosition = myPlayer->GetPosition();
	playerPosition.y = playerPosition.y + (myPlayer->GetComponent<SpriteComponent>()->GetSizeY() / 2);

	SetPosition(playerPosition);

	if (myTimer > mySpawnInterval)
	{
		myTimer = {};

		std::shared_ptr<EffectSprite> sprite = std::make_shared<EffectSprite>();

		sprite->myPathString = myStats.mySpritePath;
		sprite->myScale = Utils::RandomFloat(myStats.myStartScale, myStats.myEndScale);
		sprite->mySpeedInterval = Utils::RandomFloat(myStats.myMinStartSpeed, myStats.myMaxStartSpeed);
		sprite->myAcceleration = Utils::RandomFloat(myStats.myMinAcceleration, myStats.myMaxAcceleration);
		sprite->myLifeTime = Utils::RandomFloat(myStats.myMinParticleLifeTime, myStats.myMaxParticleLifeTime);
		sprite->myRotation = Utils::RandomFloat(myStats.myMinParticleAngularVel, myStats.myMaxParticleAngularVel);
		sprite->mySpawnAngle = myStats.myParticleAngleInterval;
		sprite->myEmitterAngle = myStats.myEmitterAngle;
		sprite->myEmitterWidth = myStats.myEmitterWidth;
		sprite->myEmiterLifetime = myStats.myEmitterLifeTime;
		sprite->myStartColor = myStats.myStartColor;
		sprite->myEndColor = myStats.myEndColor;
		sprite->myPosition = GetPosition();

		sprite->AddSprite(AddComponent<SpriteComponent>());

		mySprites.push_back(sprite);

		mySpawnInterval = Utils::RandomFloat(myStats.myMinBetweenSpawn, myStats.myMaxBetweenSpawn);
	}
	
	for (int i = 0; i < mySprites.size(); i++)
	{
		mySprites[i]->Update(aDeltaTime);
		if (mySprites[i]->IsAlive() == false)
		{
			mySprites.erase(mySprites.begin() + i);
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
