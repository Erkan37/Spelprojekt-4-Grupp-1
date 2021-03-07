#include "stdafx.h"
#include "Ledge.h"
#include "Scene.h"

#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include "Player.hpp"

Ledge::Ledge(Scene* aLevelScene)
	:
	GameObject(aLevelScene),
	myPlayerEntered(false),
	myPlayerIsInThisFrame(false),
	myPlayer(nullptr)
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

	GameObject::Init();
}

void Ledge::Update(const float& aDeltaTime)
{
	if (!myPlayerIsInThisFrame)
	{
		if (myPlayerEntered)
		{
			myPlayer->LeaveLedge();
		}
		myPlayerEntered = false;
	}
	
	myPlayerIsInThisFrame = false;
	GameObject::Update(aDeltaTime);
}

void Ledge::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		myPlayer = player;
		if (!myPlayerEntered)
		{
			player->EnterLedge();
			myPlayerEntered = true;
		}
		myPlayerIsInThisFrame = true;
	}
}

const bool Ledge::GetPlayerEntered()
{
	return myPlayerEntered;
}