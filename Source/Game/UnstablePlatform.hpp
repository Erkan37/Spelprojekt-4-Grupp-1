#pragma once
#include "Platform.h"

class SpriteComponent;

class UnstablePlatform : public Platform
{
public:
	UnstablePlatform(Scene* aLevelScene);

	void Update(const float& aDeltaTime) override;

	void SetTimerProperties(const float& aDestroyTime, const float& aRespawnTime);

	void OnCollision(GameObject* aGameObject) override;

	void Landed(const int& aOverlapY) override;

	void SetSpriteToDisable(SpriteComponent* aSprite);

	void ActivatePlatform();
	void DeactivatePlatform();

private:
	SpriteComponent* mySpriteToDisable;

	float myDestroyTime;
	float myRespawnTime;
	float myTimer;

	bool myCollidedWithPlayer;
	bool myCollidedLastFrame;
	bool myIsDeactivated;

	bool myPlayerIsOnTop;

};

