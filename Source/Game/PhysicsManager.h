/*
*	Author: Elia Rönning
*/

#pragma once
#include <vector>
#include "../External/Headers/CU/Vector2.hpp"

class CGameWorld;
class GameObject;
class ColliderComponent;
class PhysicsComponent;

class PhysicsManager
{
	friend ColliderComponent;

public:
	PhysicsManager();
	PhysicsManager(const PhysicsManager& aPhysicsManager) = delete;
	~PhysicsManager() = default;

	void PhysicsUpdate(const float& aDeltaTime, std::vector<GameObject*>& aGameObjects);
	static constexpr float ourGravity = 1200.0f;

	void UpdateObjectVelocity(const float& aDeltaTime, std::vector<GameObject*>& aGameObjects);

	void CheckOverlap(GameObject* aObj1, GameObject* aObj2, PhysicsComponent* aObj1Physics, PhysicsComponent* aObj2Physics, ColliderComponent* aCollider1, ColliderComponent* aCollider2);
	void OverlapCalculation(GameObject* aObj1, GameObject* aObj2, PhysicsComponent* aObj1Physics, PhysicsComponent* aObj2Physics, const v2f& aObj1Min, const v2f& aObj1Max, const v2f& aObj2Min, const v2f& aObj2Max);

	const void AlmostCollision(GameObject* aObject, const float& aYDistance);

	bool PhysicsManager::OneWayCheck(const float& aInSensitivity, GameObject* aObj1, GameObject* aObj2, const v2f& aObj1Min, const v2f& aObj1Max, const v2f& aObj2Min, const v2f& aObj2Max);

	void CheckBashCollision(GameObject* aObj1, GameObject* aObj2);

private:
	std::vector<ColliderComponent*> myColliders;
};

