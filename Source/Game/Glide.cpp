#include "stdafx.h"
#include "Glide.hpp"

#include "Scene.h"

#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include "Player.hpp"

Glide::Glide(Scene* aScene)
	:
	GameObject(aScene)
{
	SetZIndex(500);

	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetSpritePath("Sprites/Objects/GlidePowerup.dds");
	sprite->SetSize(v2f(16.0f, 16.0f));

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize(16.0f, 16.0f);
}

Glide::~Glide()
{

}

void Glide::Init(const v2f& aPosition)
{
	SetPosition(aPosition);

	GameObject::Init();
}

void Glide::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		player->StartGliding();
	}
}