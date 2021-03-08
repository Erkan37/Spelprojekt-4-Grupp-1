#pragma once
#include "Platform.h"

class DestructiblePlatform : public Platform
{
public:
	DestructiblePlatform(Scene* aLevelScene);

	void OnCollision(GameObject* aGameObject) override;

private:

};

