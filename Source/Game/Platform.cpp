#include "stdafx.h"
#include "Platform.h"

#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

Platform::Platform(Scene* aScene)
	:
	GameObject(aScene)
{

}

Platform::~Platform()
{

}

void Platform::Init(const v2f& aSize, const v2f& aSpriteSize, const v2f& aPosition)
{
	SetPosition(aPosition);
	SetPivot({ 0.0f, 0.0f });

	SpriteComponent* gsprite = AddComponent<SpriteComponent>();
	gsprite->SetSpritePath("Sprites/Platform.dds");
	gsprite->SetSize(aSpriteSize);

	PhysicsComponent* gphys = AddComponent<PhysicsComponent>();
	gphys->SetCanCollide(true);
	gphys->SetIsStatic(true);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetPosition({ aSpriteSize.x / 2.0f, aSpriteSize.y / 2.0f });
	collider->SetSize(aSize);

	GameObject::Init();
}