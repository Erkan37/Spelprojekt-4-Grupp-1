#pragma once
#include "GameObject.h"
#include "ParticleEffect.h"

class Scene;

class ParticleEffectFactory : public GameObject
{
public:
	ParticleEffectFactory(Scene* aLevelScene);

	void ReadEffects(Scene* aLevelScene);

	void Init();

	void Update(const float& aDeltaTime) override;
	void Render() override;

	void SpawnEffect(const v2f aPosition, const eParticleEffects aEffectType);


private:
	std::vector<std::shared_ptr<ParticleEffect>> myEffects;


};

