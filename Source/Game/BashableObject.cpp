#include "stdafx.h"
#include "BashableObject.hpp"

#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "BashComponent.hpp"

BashableObject::BashableObject(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{

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
	spriteIdle->SetSpritePath("Sprites/TommyIdle.dds");
	spriteIdle->SetSize(v2f(100.0f, 100.0f));

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this);
}
