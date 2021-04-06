#pragma once
#include "GameObject.h"
#include "ParticleEffect.h"

class Scene;

class ParticleEffectFactory
{
public:
	ParticleEffectFactory(Scene* aLevelScene);

	void ReadEffects(Scene* aLevelScene);

	void Init();

	void SpawnEffect(v2f aPosition, const eParticleEffects aEffectType);
	void SpawnEffectFollowObject(GameObject* aObject, const eParticleEffects aEffectType);

private:
	Scene* myScene;
	Player* myPlayer;
	std::vector<ParticleStats> myEffects;
	//std::vector<ParticleEffect*> myCreatedEffects;

	void SpawnCharacterEffects();
	void SpawnCharacterEffects2();

};

