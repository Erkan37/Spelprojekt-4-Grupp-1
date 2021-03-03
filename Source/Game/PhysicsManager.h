/*
*	Author: Elia Rönning
*/

#pragma once
#include <vector>

class CGameWorld;
class GameObject;
class ColliderComponent;

class PhysicsManager
{
	friend ColliderComponent;

public:
	PhysicsManager();
	PhysicsManager(const PhysicsManager& aPhysicsManager) = delete;
	~PhysicsManager() = default;

	void PhysicsUpdate(const float& aDeltaTime, std::vector<GameObject*>& gameObjects);
	static constexpr float ourGravity = 800.0f;

private:
	std::vector<ColliderComponent*> myColliders;
};

