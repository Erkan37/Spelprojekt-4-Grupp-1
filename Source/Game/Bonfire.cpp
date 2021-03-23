#include "stdafx.h"
#include "Bonfire.hpp"

#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include "Player.hpp"

#include "Collectible.hpp"

#include "../External/Headers/CU/Utilities.h"

#include "PostMaster.hpp"

Bonfire::Bonfire(Scene* aScene)
	:
	GameObject(aScene)
{
	SetZIndex(91);

	myCollectibleIndex = 0;
	myTurnInDistance = 50.0f;
	myTurnInSpeed = 50.0f;

	myHasBeenActivated = false;

	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/Objects/Bonfire.dds");
	spriteIdle->SetSize(v2f(32.0f, 32.0f));

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(true);
	physics->SetApplyGravity(false);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize(32.0f, 32.0f);

	myAnimations[0] = Animation(false, false, false, 0, 1, 1, 0.1f, spriteIdle, 32, 32);
	myAnimations[1] = Animation(false, true, false, 0, 2, 2, 0.1f, spriteIdle, 32, 32);

	AnimationComponent* animation = AddComponent<AnimationComponent>();
	animation->SetSprite(spriteIdle);
	animation->SetAnimation(&myAnimations[0]);
	spriteIdle->SetSize(v2f(32.0f, 32.0f));
}

Bonfire::~Bonfire()
{

}

void Bonfire::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		if (!myHasBeenActivated)
		{
			GetComponent<AnimationComponent>()->SetAnimation(&myAnimations[1]);
		}
		
		PostMaster::GetInstance().ReceiveMessage(Message(eMessageType::PlayerReachedBonfire, 0));

		myHasBeenActivated = true;
	}
}