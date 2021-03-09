/*
*	Author: Elia Rönning
*/

#include "stdafx.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "Transform.hpp"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "SpriteComponent.h"

PhysicsComponent::PhysicsComponent(bool aApplyGravity, bool aIsStatic)
	: myApplyGravity(aApplyGravity)
	, myIsStatic(aIsStatic)
	, myVelocity({ 0.0f, 0.0f })
	, myCanCollide(true)
{}

const bool& PhysicsComponent::GetApplyGravity() const
{
	return myApplyGravity;
}
const bool& PhysicsComponent::GetIsStatic() const
{
	return myIsStatic;
}
const bool& PhysicsComponent::GetCanCollide() const
{
	return myCanCollide;
}
const v2f& PhysicsComponent::GetVelocity() const
{
	return myVelocity;
}
const float& PhysicsComponent::GetVelocityX() const
{
	return myVelocity.x;
}
const float& PhysicsComponent::GetVelocityY() const
{
	return myVelocity.y;
}

const v2f& PhysicsComponent::GetDashVelocity() const
{
	return myDashVelocity;
}

const bool PhysicsComponent::HasCollidedAtPoint(GameObject* aGameObject, const v2f aPoint)
{
	ColliderComponent* collider = aGameObject->GetComponent<ColliderComponent>();
	if (aPoint.x >= collider->GetPosition().x + collider->GetWidth() && aPoint.y <= collider->GetPosition().y + collider->GetHeight())
	{
		return true;
	}
	return false;
}

PhysicsComponent& PhysicsComponent::SetApplyGravity(const bool& aApplyGravity)
{
	myApplyGravity = aApplyGravity;

	return *this;
}
PhysicsComponent& PhysicsComponent::SetIsStatic(const bool& aIsStatic)
{
	myIsStatic = aIsStatic;

	return *this;
}
PhysicsComponent& PhysicsComponent::SetCanCollide(const bool& aCanCollide)
{
	myCanCollide = aCanCollide;

	return *this;
}
PhysicsComponent& PhysicsComponent::SetVelocity(const v2f& aVelocity)
{
	myVelocity = aVelocity;

	return *this;
}
PhysicsComponent& PhysicsComponent::SetVelocityX(const float& aVelocity)
{
	myVelocity.x = aVelocity;

	return *this;
}
PhysicsComponent& PhysicsComponent::SetVelocityY(const float& aVelocity)
{
	myVelocity.y = aVelocity;

	return *this;
}

PhysicsComponent& PhysicsComponent::SetDashVelocity(const v2f& aVelocity)
{
	myDashVelocity = aVelocity;

	return *this;
}

ColliderComponent* PhysicsComponent::CreateColliderFromSprite(SpriteComponent* aSprite, GameObject* aGameObject) const
{
	const Transform& transform = aGameObject->GetTransform();

	ColliderComponent* collider = aGameObject->AddComponent<ColliderComponent>();
	collider->SetPosition({ 0.0f, 0.0f });
	collider->SetSize(aSprite->GetBottomRight(transform) - aSprite->GetTopLeft(transform));
	return collider;
}