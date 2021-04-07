#pragma once
#include "GameObject.h"
#include "ParticleEffect.h"

class Scene;

class ParticleEffectFactory
{
public:
	ParticleEffectFactory();

	void ReadEffects(Scene* aLevelScene);

	void Init();

	void SpawnEffect(v2f aPosition, const eParticleEffects aEffectType);
	void SpawnEffectFollowObject(GameObject* aObject, const eParticleEffects aEffectType);

private:
	Scene* myScene;
	Player* myPlayer;
	std::vector<ParticleStats> myEffects;

	void SetEffect(ParticleEffect& aEffect, const eParticleEffects aEffectType);
	void SpawnCharacterEffects();

};

