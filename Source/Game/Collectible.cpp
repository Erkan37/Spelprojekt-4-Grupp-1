#include "stdafx.h"
#include "Collectible.hpp"
#include "Player.hpp"

#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

Collectible::Collectible(Scene* aLevelScene)
	:
	GameObject(aLevelScene),
	myWasCollected(false)
{

}

Collectible::~Collectible()
{

}

void Collectible::Init(const v2f& aPosition, eCollectibleType aType)
{
	SetZIndex(400);
	SetPosition(aPosition);

	myType = aType;

	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/Collectible.dds"); //Get correct image depending on type
	spriteIdle->SetSize(v2f(100.0f, 100.0f)); //Get size from data manager instead

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this); //Get collision size from data manager
}

void Collectible::OnCollision(GameObject* aGameObject)
{
	if (!myWasCollected)
	{
		Player* player = dynamic_cast<Player*>(aGameObject);
		if (player)
		{
			GetComponent<SpriteComponent>()->Deactivate(); //SetAnimation;
			myWasCollected = true;
		}
	}
}