#pragma once
#include "GameObject.h"

class Scene;
class Collectible;

class Bonfire : public GameObject
{
public:
	Bonfire(Scene* aScene);
	~Bonfire();

	void Update(const float& aDeltaTime) override;

	void TurnInCollectibles();

	void OnCollision(GameObject* aGameObject) override;

private:
	std::vector<Collectible*> myRetrievedCollectibles;
	float myTurnInSpeed;
	float myTurnInDistance;
	int myCollectibleIndex;

};

