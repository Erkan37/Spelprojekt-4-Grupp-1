#pragma once
#include "Platform.h"

class DeadlyPlatform : public Platform
{
public:
	DeadlyPlatform(Scene* aLevelScene);

	void OnCollision(GameObject* aGameObject) override;

private:

};

