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

	void Update(const float& aDeltaTime);
	void Render();

	void SpawnEffect(v2f aPosition, const eParticleEffects aEffectType);


private:
	Scene* myScene;
	Player* myPlayer;
	std::vector<ParticleStats> myEffects;
	std::vector<std::shared_ptr<ParticleEffect>> myCreatedEffects;

	void SpawnCharacterEffects();
	void SpawnCharacterEffects2();

};

