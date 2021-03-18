#pragma once
#include "GameObject.h"
#include "PopUp.h"

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

	void Saved();

	void Reset(const bool aIsTurningIn);

	void SetBonfire(GameObject* aGameObject);

	void TurnIn();

	void ImGuiUpdate();

private:
	v2f mySpawnPosition;
	v2f myTargetPosition;
	GameObject* myTarget;

	float mySpeed;
	float myMinRadiusFromTarget;
	float myIdleMovementSpeed;
	float myIdleMovementDistance;
	float myTimeOffset;

	eCollectibleType myType;
	bool myWasCollected;
	bool myIsSafe;
	bool myWasTurnedIn;

	PopUp* myPopUp;
};

