#pragma once
#include "ParticleStats.hpp"
#include "ParticleEffectTypes.hpp"
#include "GameObject.h"
#include "EffectSprite.h"

class SpriteComponent;
class Player;
class LevelScene;

class ParticleEffect : public GameObject
{
public:
	ParticleEffect(Scene* aLevelScene);
	~ParticleEffect() = default;

	void Init(ParticleStats aStats, Player* aPlayer);

	void Update(const float& aDeltaTime) override;

	const void SetIsActive(const bool aActiveState);
	const void SetEffect(ParticleStats aEffect);
	
	const bool GetIsActive();
	const eParticleEffects GetType() const;


private:
	std::vector<std::shared_ptr<EffectSprite>> mySprites;
	ParticleStats myStats;

	float mySpawnInterval;
	float myTimer;
	bool myIsActive;

	Player* myPlayer;

	const void UpdateParticle(const float& aDeltaTime);
	const void UpdatePlayerEffect(const float& aDeltaTime);

};

