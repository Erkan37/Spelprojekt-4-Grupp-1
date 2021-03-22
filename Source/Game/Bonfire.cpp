#include "stdafx.h"
#include "Bonfire.hpp"

#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include "Player.hpp"

#include "Collectible.hpp"

#include "../External/Headers/CU/Utilities.h"

Bonfire::Bonfire(Scene* aScene)
	:
	GameObject(aScene)
{
	SetZIndex(91);

	myCollectibleIndex = 0;
	myTurnInDistance = 50.0f;
	myTurnInSpeed = 50.0f;

	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/Objects/Bonfire.dds");
	spriteIdle->SetSize(v2f(64.0f, 64.0f));

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(true);
	physics->SetApplyGravity(false);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize(64.0f, 64.0f);
}

Bonfire::~Bonfire()
{

}

void Bonfire::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		//Activate;
	}
}