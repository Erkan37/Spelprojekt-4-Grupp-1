#include "stdafx.h"
#include "BashableObject.hpp"

#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "BashComponent.hpp"
#include "WaypointComponent.hpp"

BashableObject::BashableObject(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	WaypointComponent* waypointComponent = AddComponent<WaypointComponent>();
	waypointComponent->SetOwner(this);
}

BashableObject::~BashableObject()
{

}

void BashableObject::Init(const v2f& aPosition, const float& aRadius)
{
	SetPosition(aPosition);
	SetPivot(v2f(0.5f, 0.5f));

	BashComponent* bashComponent = AddComponent<BashComponent>();
	bashComponent->SetRadius(aRadius);

	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/Objects/Bashable.dds");
	spriteIdle->SetSize(v2f(16.0f, 16.0));

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize(v2f(32.0f, 32.0f));

	GameObject::Init();
}

void BashableObject::Update(const float& aDeltaTime)
{
	GetComponent<WaypointComponent>()->Move(aDeltaTime);

	GameObject::Update(aDeltaTime);
}