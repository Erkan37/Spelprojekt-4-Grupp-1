#pragma once
#include "ParticleStats.hpp"
#include "ParticleEffectTypes.hpp"

class Player;
class LevelScene;

class ParticleEffect
{
public:
	ParticleEffect();

	void Init(ParticleStats aStats, Scene* aLevelScene);

	void Update(const float& aDeltaTime);
	void Render();

	void SetPosition(const v2f aPosition);
	void SetIsActive(const bool aActiveState);
	
	bool GetIsActive();
	eParticleEffects GetType();


private:
	ParticleStats myStats;

	bool myIsActive;

	Player* myPlayer;
	v2f myPosition;

	void UpdateParticle(const float& aDeltaTime);

};

