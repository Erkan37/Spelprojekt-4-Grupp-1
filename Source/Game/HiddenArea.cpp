#include "stdafx.h"
#include "HiddenArea.hpp"
#include "Player.hpp"

#include "SpriteComponent.h"
#include "PhysicsComponent.h"

#include "Scene.h"

#include "../External/Headers/CU/Utilities.h"

HiddenArea::HiddenArea(Scene* aLevelScene, const v2f& aPosition, const v2f& aSize)
	:
	GameObject(aLevelScene),
	myPlayerCollided(false),
	myHiddenSprite(nullptr),
	myOpacity(1.0f),
	myOpacityChangeSpeed(3.0f)
{
	SetZIndex(130);
	SetPosition(aPosition);

	myHiddenSprite = AddComponent<SpriteComponent>();
	myHiddenSprite->SetSpritePath("Sprites/Temp/HiddenArea.dds");
	myHiddenSprite->SetSize(aSize);

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	physics->CreateColliderFromSprite(myHiddenSprite, this);
}

HiddenArea::~HiddenArea()
{

}

void HiddenArea::Update(const float& aDeltaTime)
{
	if (!myPlayerCollided)
	{
		myOpacity = Utils::Lerp(myOpacity, 1.0f, myOpacityChangeSpeed * aDeltaTime);
	}
	else
	{
		myOpacity = Utils::Lerp(myOpacity, 0.0f, myOpacityChangeSpeed * aDeltaTime);
	}

	myHiddenSprite->SetColor(v4f(1.0f, 1.0f, 1.0f, myOpacity));
	myPlayerCollided = false;

	GameObject::Update(aDeltaTime);
}

void HiddenArea::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		myPlayerCollided = true;
	}
}