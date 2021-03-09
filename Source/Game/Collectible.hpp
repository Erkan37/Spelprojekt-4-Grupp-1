#pragma once
#include "GameObject.h"

class Scene;

class Collectible : public GameObject
{
public:
	Collectible(Scene* aLevelScene);
	~Collectible();

	void Init(const v2f& aPosition);

	void OnCollision(GameObject* aGameObject) override;

private:
	bool myWasCollected;

};

