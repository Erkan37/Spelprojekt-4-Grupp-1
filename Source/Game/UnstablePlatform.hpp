#pragma once
#include "Platform.h"

class UnstablePlatform : public Platform
{
public:
	UnstablePlatform(Scene* aLevelScene);

	void Update(const float& aDeltaTime) override;

	void SetTimerProperties(const float& aDestroyTime, const float& aRespawnTime);

	void OnCollision(GameObject* aGameObject) override;

	void ActivatePlatform();
	void DeactivatePlatform();

private:
	float myDestroyTime;
	float myRespawnTime;
	float myTimer;

	bool myCollidedWithPlayer;
	bool myIsDeactivated;

};

