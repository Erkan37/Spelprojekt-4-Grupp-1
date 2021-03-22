#pragma once
#include "GameObject.h"

class Scene;
class Collectible;

class Bonfire : public GameObject
{
public:
	Bonfire(Scene* aScene);
	~Bonfire();

	void OnCollision(GameObject* aGameObject) override;

private:
	float myTurnInSpeed;
	float myTurnInDistance;
	int myCollectibleIndex;

};

