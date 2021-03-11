#pragma once
#include "GameObject.h"

class Scene;

namespace Utils
{
	class Timer;
}

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

	void Update(const float& aDeltaTime) override;

	void OnCollision(GameObject* aGameObject) override;

	void ImGuiUpdate();

private:
	v2f myTargetPosition;
	GameObject* myTarget;

	float mySpeed;
	float myMinRadiusFromTarget;
	float myIdleMovementSpeed;
	float myIdleMovementDistance;

	Utils::Timer* myTimer;

	eCollectibleType myType;
	bool myWasCollected;
};

