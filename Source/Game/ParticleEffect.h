#pragma once
#include "ParticleStats.hpp"
#include "ParticleEffectTypes.hpp"

namespace Tga2D
{
	class CSpriteBatch;
}

class Player;
class LevelScene;

class ParticleEffect
{
public:
	ParticleEffect();
	~ParticleEffect() = default;

	void Init(ParticleStats aStats, Player* aLevelScene);

	void Update(const float& aDeltaTime);
	void Render();

	const void SetPosition(const v2f aPosition);
	const void SetIsActive(const bool aActiveState);
	const void SetEffect(ParticleEffect* aEffect);
	
	const bool GetIsActive();
	const eParticleEffects GetType() const;


private:
	Tga2D::CSpriteBatch* mySprites;
	ParticleStats myStats;

	bool myIsActive;

	Player* myPlayer;
	v2f myPosition;

	const void UpdateParticle(const float& aDeltaTime);
	const void UpdatePlayerEffect(const float& aDeltaTime);

};

