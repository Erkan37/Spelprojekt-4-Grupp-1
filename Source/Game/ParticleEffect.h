#pragma once
#include "ParticleStats.hpp"
#include "ParticleEffectTypes.hpp"

class LevelScene;

class ParticleEffect
{
public:
	ParticleEffect();

	void Init(ParticleStats aStats, Scene* aLevelScene);

	void Update(const float& aDeltaTime);

	void SetPosition(const v2f aPosition);
	void SetIsActive(const bool aActiveState);
	
	bool GetIsActive();
	eParticleEffects GetType();


private:
	ParticleStats myStats;
	eParticleEffects myEffectType;
	bool myIsActive;
	const GameObject* myPlayer;
	
	v2f myPosition;

	void CreateParticle();

};

