#include "stdafx.h"
#include "Collectible.hpp"
#include "Player.hpp"

#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include "../External/Headers/CU/Utilities.h"

#include "GameWorld.h"

#include "Random.hpp"

#include "Bonfire.hpp"

Collectible::Collectible(Scene* aLevelScene)
	:
	GameObject(aLevelScene),
	myPopUp(new PopUp(aLevelScene)),
	myTarget(nullptr),
	mySpeed(1.0f),
	myIdleMovementSpeed(5.0f),
	myIdleMovementDistance(25.0f),
	myMinRadiusFromTarget(25.0f),
	myTimeOffset(0.0f),
	myType(eCollectibleType::Easy),
	myWasCollected(false),
	myIsSafe(false),
	myWasTurnedIn(false)
{
	
}

Collectible::~Collectible()
{

}

void Collectible::Init(const v2f& aPosition, eCollectibleType aType)
{
	SetZIndex(400);
	SetPosition(aPosition);
	mySpawnPosition = aPosition;

	myTargetPosition = aPosition;

	myTimeOffset = Utils::RandomFloat(0.0f, 6.0f);

	myType = aType;

	std::string spritePath;

	switch (aType)
	{
		case eCollectibleType::Easy:
			spritePath = "Sprites/Objects/Collectible1.dds";
			break;
		case eCollectibleType::Medium:
			spritePath = "Sprites/Objects/Collectible2.dds";
			break;
		case eCollectibleType::Hard:
			spritePath = "Sprites/Objects/Collectible3.dds";
			break;
	}

	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath(spritePath); //Get correct image depending on type
	spriteIdle->SetSize(v2f(16.0f, 16.0f)); //Get size from data manager instead

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this); //Get collision size from data manager

	myPopUp->InitPopUp();

	GameObject::Init();
}

void Collectible::Update(const float& aDeltaTime)
{
	constexpr float tau = 6.283185307f;

	myTimeOffset += aDeltaTime;
	if (myTimeOffset > tau)
	{
		myTimeOffset -= tau;
	}

	if (myTarget)
	{
		if (myMinRadiusFromTarget * myMinRadiusFromTarget < (myTarget->GetPosition() - myTransform.myPosition).LengthSqr())
		{
			myTargetPosition = myTarget->GetPosition() + v2f(0.0f, -myMinRadiusFromTarget);
		}
	}

	const float offset = sin(myTimeOffset * myIdleMovementSpeed) * myIdleMovementDistance;
	myTransform.myPosition.x = Utils::Lerp(myTransform.myPosition.x, myTargetPosition.x, mySpeed * aDeltaTime);
	myTransform.myPosition.y = Utils::Lerp(myTransform.myPosition.y, myTargetPosition.y + offset, mySpeed * aDeltaTime);

#ifdef _DEBUG
	ImGuiUpdate();
#endif // DEBUG

	GameObject::Update(aDeltaTime);
}

void Collectible::OnCollision(GameObject* aGameObject)
{
	if (!myWasCollected && !myWasTurnedIn)
	{
		Player* player = dynamic_cast<Player*>(aGameObject);
		if (player)
		{
			player->AddCollectible(this);
			//SetAnimation;
			myTarget = aGameObject;
			myWasCollected = true;
		}
	}
}

void Collectible::Saved()
{
	myIsSafe = true;
}

void Collectible::Reset(const bool aIsTurningIn)
{
	if (aIsTurningIn)
	{
		myWasCollected = false;
	}
	else
	{
		if (!myIsSafe)
		{
			myTarget = nullptr;
			myWasCollected = false;
			SetPosition(mySpawnPosition);
			myTargetPosition = v2f();
		}
	}
}

void Collectible::SetBonfire(GameObject* aGameObject)
{
	myTarget = aGameObject;
	myTargetPosition = aGameObject->GetPosition();
	myWasTurnedIn = true;
}

void Collectible::TurnIn()
{
	//Add To Score or whatever
	if (myType == eCollectibleType::Easy)
	{
		myPopUp->SetEasyActive(true);
	}
	Destroy();
}

void Collectible::ImGuiUpdate()
{
	ImGui::Begin("Collectible", &myIsActive, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::InputFloat("Speed", &mySpeed, 0.0f, 200.0f);
	ImGui::InputFloat("Radius From Target", &myMinRadiusFromTarget, 0.0f, 200.0f);
	ImGui::InputFloat("Idle Movement Speed", &myIdleMovementSpeed, 0.0f, 100.0f);
	ImGui::InputFloat("Idle Movement Distance", &myIdleMovementDistance, 0.0f, 200.0f);

	ImGui::End();
}