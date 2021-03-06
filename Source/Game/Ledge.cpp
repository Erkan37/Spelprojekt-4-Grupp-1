#include "stdafx.h"
#include "Ledge.h"
#include "Scene.h"

#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

Ledge::Ledge(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{

}

Ledge::~Ledge()
{

}

void Ledge::Init(const v2f& aPosition, const v2f& aSize)
{
	SetPosition(aPosition);
	SetPivot({ 0.5f, 0.0f });

	SpriteComponent* gsprite = AddComponent<SpriteComponent>();
	gsprite->SetSpritePath("Sprites/debugLedge.dds");
	gsprite->SetSize(aSize);

	PhysicsComponent* gphys = AddComponent<PhysicsComponent>();
	gphys->SetCanCollide(false);
	gphys->SetIsStatic(true);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetPosition({ -aSize.x / 2.0f, 0.0f });
	collider->SetSize(aSize);

	SetIsLedge(true);

	GameObject::Init();
}