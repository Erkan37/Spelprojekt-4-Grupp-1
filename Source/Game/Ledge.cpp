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
			const float playerBottomY = player->GetPositionY() + player->GetComponent<ColliderComponent>()->GetHeight() / 2.0f;
			const float ledgeBottomY = myTransform.myPosition.y + GetComponent<ColliderComponent>()->GetHeight();
			const float ledgeTopY = myTransform.myPosition.y;

			if (playerBottomY <= ledgeBottomY && playerBottomY >= ledgeTopY && player->GetComponent<PhysicsComponent>()->GetVelocityY() > 0)
			{
				v2f playerSnapPosition = v2f(0.0f, myTransform.myPosition.y - player->GetComponent<ColliderComponent>()->GetHeight() / 2.0f);
				if (player->GetPositionX() > myTransform.myPosition.x)
				{
					playerSnapPosition.x = myTransform.myPosition.x;
				}
				else if (player->GetPositionX() < myTransform.myPosition.x)
				{
					playerSnapPosition.x = myTransform.myPosition.x;
				}

				player->GrabLedge(playerSnapPosition, myTransform.myPosition);
				myPlayerEntered = true;
			}
		}
		myPlayerIsInThisFrame = true;
	}
}