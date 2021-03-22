#include "stdafx.h"
#include "HiddenArea.hpp"
#include "Player.hpp"

#include "SpriteBatchComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include "Scene.h"

#include "../External/Headers/CU/Utilities.h"

HiddenArea::HiddenArea(Scene* aLevelScene, const v2f& aPosition, const v2f& aSize)
	:
	GameObject(aLevelScene),
	myPlayerCollided(false),
	myHiddenSpriteBatch(nullptr),
	myOpacity(1.0f),
	myOpacityChangeSpeed(3.0f)
{
	SetZIndex(600);
	SetPosition(aPosition);

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize(aSize);
}

HiddenArea::~HiddenArea()
{

}

void HiddenArea::Update(const float& aDeltaTime)
{
	if (myPlayerCollided)
	{
		myOpacity = Utils::Lerp(myOpacity, 0.0f, myOpacityChangeSpeed * aDeltaTime);
	}

	myHiddenSpriteBatch->SetOpacity(myOpacity);

	GameObject::Update(aDeltaTime);
}

void HiddenArea::SetBatch(SpritebatchComponent* aHiddenSpriteBatch)
{
	myHiddenSpriteBatch = aHiddenSpriteBatch;
}

void HiddenArea::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		myPlayerCollided = true;
	}
}