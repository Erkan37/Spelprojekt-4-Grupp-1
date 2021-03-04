/*
*	Author: Elia Rönning
*/

#pragma once
#include <vector>

struct Transform;
class GameObject;

class Component
{
public:
	Component() = default;
	Component(const Component& aComponent) = default;
	virtual ~Component() = default;

	virtual void Init(Transform& aTransform, GameObject& aGameObject) { aTransform; aGameObject; };
	virtual void Update(Transform& aTransform, GameObject& aGameObject) { aTransform; aGameObject; };
	virtual void Render(Transform& aTransform, GameObject& aGameObject) { aTransform; aGameObject; };
};