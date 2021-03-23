#include "stdafx.h"
#include "LevelDoor.hpp"

#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include "Player.hpp"

#include "PostMaster.hpp"

LevelDoor::LevelDoor(Scene* aScene)
	:
	GameObject(aScene)
{
	myType = eDoorType::Entry;
	myWasActivated = false;
}

LevelDoor::~LevelDoor()
{

}

void LevelDoor::Init(const eDoorType aDoorType, const v2f& aSize)
{
	myType = aDoorType;

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(true);
	physics->SetApplyGravity(false);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize(aSize);
}

void LevelDoor::OnCollision(GameObject* aGameObject)
{
	if (myWasActivated)
	{
		return;
	}

	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		myWasActivated = true;

		if (myType == eDoorType::Exit)
		{
			PostMaster::GetInstance().ReceiveMessage(Message(eMessageType::LoadNext, 0), true);
		}
		else if (myType == eDoorType::Entry)
		{
			PostMaster::GetInstance().ReceiveMessage(Message(eMessageType::LoadPrevious, 0), true);
		}
	}
}