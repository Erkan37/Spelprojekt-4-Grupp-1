#include "stdafx.h"
#include "LevelScene.h"
#include "SpringObject.h"
#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"
#include "Player.hpp"
#include "Game.h"

SpringObject::SpringObject(Scene* aLevelScene) : GameObject(aLevelScene)
{
	myRetardation = {};
	myVelocityForce = {};
	myActiveSpring = {};
}

void SpringObject::Init(const v2f aPosition)
{
	InitSprings(aPosition);

	GameObject::Init();
}
void SpringObject::Update(const float& aDeltaTime)
{
	myTimer += aDeltaTime;

#ifdef _DEBUG
	ImGuiUpdate();
#endif // _DEBUG
}

void SpringObject::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);

	if (player != NULL)
	{
		v2f playerPos = player->GetPosition();
		v2f velo = player->GetComponent<PhysicsComponent>()->GetVelocity();
		v2f colliderPos = GetPosition();

		float spriteLeftPosX = (colliderPos.x - GetComponent<ColliderComponent>()->GetSize().x / 2.f);
		float spriteRightPosX = (colliderPos.x + GetComponent<ColliderComponent>()->GetSize().x / 2.f);

		if (playerPos.x >= spriteLeftPosX && playerPos.x <= spriteRightPosX && velo.y > 50.f && myTimer > mySpringTimerCooldown)
		{
			myTimer = {};
			player->ActivateSpringForce(-myVelocityForce, myRetardation);
			GetComponent<AnimationComponent>()->SetAnimation(&myAnimations[1]);
			GetComponent<AnimationComponent>()->SetNextAnimation(&myAnimations[2]);
		}
	}
}

void SpringObject::InitSprings(const v2f aPosition)
{
	mySpringTimerCooldown = 0.1f;
	myRetardation = 1.0f;
	myVelocityForce = 1000;
	myPosition = aPosition;
	mySize = { 16.0f, 16.0f };

	SetPosition(myPosition);
	SetPivot(v2f(0.5f, 1.0f));

	CreateGroundSpring();

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(true);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize({ mySize.x, mySize.y * 0.05f });
	collider->SetPosition({ 0.f, -mySize.y * 0.95f });

}

void SpringObject::CreateGroundSpring()
{
	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetSpritePath("Sprites/Objects/Mushroom.dds");
	sprite->SetSize(mySize);

	myAnimations[0] = Animation(false, true, false, 0, 1, 1, 0.08f, sprite, 16, 16);
	myAnimations[1] = Animation(false, true, false, 0, 4, 4, 0.08f, sprite, 16, 16);
	myAnimations[2] = Animation(true, true, false, 3, 4, 4, 0.08f, sprite, 16, 16);

	AnimationComponent* animation = AddComponent<AnimationComponent>();
	animation->SetSprite(sprite);
	animation->SetAnimation(&myAnimations[0]);
	sprite->SetSize(mySize);

}

#ifdef _DEBUG
void SpringObject::ImGuiUpdate()
{
	ImGui::Begin("Spring", &myIsActive, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::SliderFloat("Spring Velocity Force", &myVelocityForce, 0.0f, 2000.0f);
	ImGui::SliderFloat("Spring Velocity Retardation", &myRetardation, 0.0f, 5.0f);

	ImGui::End();
}
#endif // _DEBUG
