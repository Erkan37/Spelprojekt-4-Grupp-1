#include "stdafx.h"
#include "Door.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

Door::Door(Scene* aLevelScene)
	:
	GameObject(aLevelScene),
	myButton(new Button(aLevelScene))
{
	myDoorIsOpen = {};
}

void Door::Init(const v2f aPosition)
{
	SetPosition(aPosition);

	myClosedDoorSprite = AddComponent<SpriteComponent>();
	myClosedDoorSprite->SetSpritePath("Sprites/tempDoorClosed.dds");
	myClosedDoorSprite->Activate();

	mySize = myClosedDoorSprite->GetSize();

	myOpenDoorSprite = AddComponent<SpriteComponent>();
	myOpenDoorSprite->SetSpritePath("Sprites/tempDoorOpen.dds");

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(true);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize({ mySize.x, mySize.y });
	collider->SetPosition({ 0.f, -mySize.y * 0.99f });

	GameObject::Init();

	myOpenDoorSprite->Deactivate();
}

void Door::Update(const float& aDeltaTime)
{
	if (myButton->GetActiveButton() && !myDoorIsOpen)
	{
		myDoorIsOpen = true;

		myClosedDoorSprite->Deactivate();
		myOpenDoorSprite->Activate();

		GetComponent<ColliderComponent>()->SetSize(myOpenDoorSprite->GetSize());

	}

	GameObject::Update(aDeltaTime);
}




void Door::AddButton(v2f aPosition)
{
	myButton->Init(GetPosition(), aPosition);
}