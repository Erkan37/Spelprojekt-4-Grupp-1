#include "stdafx.h"
#include "LevelScene.h"
#include "SpringObject.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"
#include "Player.hpp"

SpringObject::SpringObject(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	myActiveSpring = {};
}

void SpringObject::Init(const v2f aPosition)
{
	InitSprings(aPosition);
}

void SpringObject::Update(const float& aDeltaTime)
{
	ImGuiUpdate();
}

void SpringObject::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);

	if (player != NULL)
	{
		v2f playerPos = player->GetPosition();
		v2f velo = player->GetComponent<PhysicsComponent>()->GetVelocity();
		v2f colliderPos = GetPosition();
		v2f buttonSize = GetComponent<SpriteComponent>()->GetSize();

		float spriteLeftPosX = (colliderPos.x + GetComponent<ColliderComponent>()->GetSize().x / 2.f) - buttonSize.x / 2.f;
		float spriteRightPosX = (colliderPos.x + GetComponent<ColliderComponent>()->GetSize().x / 2.f) + buttonSize.x / 2.f;

		if (velo.y > 50 && playerPos.x >= spriteLeftPosX - 5.f && playerPos.x <= spriteRightPosX + 5.f && myActiveSpring == false)
		{
			myActiveSpring = true;
			player->ActivateSpringForce(-myVelocityForce, myRetardation);
		}
		else
			myActiveSpring = false;
	}
}


void SpringObject::InitSprings(const v2f aPosition)
{
	myRetardation = 1.0f;
	myVelocityForce = 1000;
	myPosition = aPosition;
	mySize = { 100.f, 100.f };

	SetPosition(aPosition);
	SetPivot(v2f(0.f, 0.f));
	
	CreateGroundSpring();

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(true);
	physics->SetIsStatic(true);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize(mySize);
	collider->SetPosition({ mySize.x * 0.5f, mySize.y * 0.5f });

	GameObject::Init();
}


void SpringObject::CreateGroundSpring()
{
	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetSpritePath("Sprites/Temp/tempTrampoline.dds");
	sprite->SetSize(mySize);
}

void SpringObject::ImGuiUpdate()
{
	ImGui::Begin("Spring", &myIsActive, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::SliderFloat("Spring Velocity Force", &myVelocityForce, 0.0f, 2000.0f);
	ImGui::SliderFloat("Spring Velocity Retardation", &myRetardation, 0.0f, 5.0f);

	ImGui::End();
}
