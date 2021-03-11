#include "stdafx.h"
#include "Collectible.hpp"
#include "Player.hpp"

#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include "../External/Headers/CU/Utilities.h"

#include "GameWorld.h"

Collectible::Collectible(Scene* aLevelScene)
	:
	GameObject(aLevelScene),
	myTarget(nullptr),
	mySpeed(1.0f),
	myIdleMovementSpeed(5.0f),
	myIdleMovementDistance(25.0f),
	myMinRadiusFromTarget(25.0f),
	myType(eCollectibleType::Easy),
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

	myTimer = CGameWorld::GetInstance()->GetTimer();

	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/Collectible.dds"); //Get correct image depending on type
	spriteIdle->SetSize(v2f(40.0f, 40.0f)); //Get size from data manager instead

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this); //Get collision size from data manager
}

void Collectible::Update(const float& aDeltaTime)
{
	if (myTarget)
	{
		if (myMinRadiusFromTarget * myMinRadiusFromTarget < (myTarget->GetPosition() - myTransform.myPosition).LengthSqr())
		{
			if (Utils::Abs(myTransform.myPosition.x - myTarget->GetPosition().x) > myMinRadiusFromTarget)
			{
				myTargetPosition = myTarget->GetPosition() + v2f(0.0f, -myMinRadiusFromTarget);
			}
		}

		const float offset = sin(myTimer->GetTotalTime() * myIdleMovementSpeed) * myIdleMovementDistance;
		myTransform.myPosition.x = Utils::Lerp(myTransform.myPosition.x, myTargetPosition.x, mySpeed * aDeltaTime);
		myTransform.myPosition.y = Utils::Lerp(myTransform.myPosition.y, myTargetPosition.y + offset, mySpeed * aDeltaTime);
	}

	GameObject::Update(aDeltaTime);
}

void Collectible::OnCollision(GameObject* aGameObject)
{
	if (!myWasCollected)
	{
		Player* player = dynamic_cast<Player*>(aGameObject);
		if (player)
		{
			//GetComponent<SpriteComponent>()->Deactivate(); //SetAnimation;
			myTarget = aGameObject;
			myWasCollected = true;
		}
	}
}