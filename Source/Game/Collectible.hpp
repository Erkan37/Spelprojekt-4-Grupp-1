#pragma once
#include "GameObject.h"

class Scene;

class Collectible : public GameObject
{
public:
	enum class eCollectibleType
	{
		Easy,
		Medium,
		Hard
	};

	Collectible(Scene* aLevelScene);
	~Collectible();

	void Init(const v2f& aPosition, eCollectibleType aType);

	void OnCollision(GameObject* aGameObject) override;

private:
	bool myWasCollected;
	eCollectibleType myType;

};

