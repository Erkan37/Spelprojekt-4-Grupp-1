#pragma once
#include "GameObject.h"
#include "ParticleEffect.h"

class Scene;

class ParticleEffectFactory : public GameObject
{
public:
	ParticleEffectFactory(Scene* aLevelScene);

	void ReadEffects(Scene* aLevelScene);

	void Init() override;

	void Update(const float& aDeltaTime) override;
	void Render() override;

	void SpawnEffect(GameObject* aObject, const eParticleEffects aEffectType);


private:
	std::vector<std::shared_ptr<ParticleEffect>> myEffects;
	std::vector<std::shared_ptr<ParticleEffect>> myCreatedEffects;

	void SpawnCharacterEffects();
	void Spawn(const eParticleEffects aEffectType);

};

