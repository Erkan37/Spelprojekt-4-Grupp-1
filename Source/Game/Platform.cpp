#include "stdafx.h"
#include "Platform.h"

#include "../External/Headers/CU/Utilities.h"

#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include <iostream>

Platform::Platform(Scene* aScene)
	:
	GameObject(aScene),
	myCurrentWayPointIndex(0),
	mySpeed(0)
{

}

Platform::~Platform()
{

}

void Platform::Init(const v2f& aSize, const v2f& aSpriteSize, const v2f& aPosition, const float& aSpeed, const bool& aIsOneway)
{
	SetPosition(aPosition);
	SetPivot({ 0.0f, 0.0f });

	SpriteComponent* gsprite = AddComponent<SpriteComponent>();
	gsprite->SetSpritePath("Sprites/Platform.dds");
	gsprite->SetSize(aSpriteSize);

	PhysicsComponent* gphys = AddComponent<PhysicsComponent>();
	gphys->SetCanCollide(true);
	gphys->SetIsStatic(true);

	if (aIsOneway)
	{
		gphys->SetCollisionType(PhysicsComponent::eCollisionType::OneWay);
	}

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetPosition({ aSpriteSize.x / 2.0f, aSpriteSize.y / 2.0f });
	collider->SetSize(aSize);

	mySpeed = aSpeed;

	GameObject::Init();
}

void Platform::Update(const float& aDeltaTime)
{
	if (static_cast<int>(myWaypoints.size()) > 0)
	{
		Move(aDeltaTime);
	}

	GameObject::Update(aDeltaTime);
}

void Platform::Move(const float& aDeltaTime)
{
	myDirection = (myWaypoints[myCurrentWayPointIndex] - myTransform.myPosition).GetNormalized();
	myTransform.myPosition += myDirection * mySpeed * aDeltaTime;

	const float sensitivity = 5.0f;
	if (myTransform.myPosition.x < myWaypoints[myCurrentWayPointIndex].x + sensitivity &&
		myTransform.myPosition.x > myWaypoints[myCurrentWayPointIndex].x - sensitivity &&
		myTransform.myPosition.y < myWaypoints[myCurrentWayPointIndex].y + sensitivity &&
		myTransform.myPosition.y > myWaypoints[myCurrentWayPointIndex].y - sensitivity)
	{
		++myCurrentWayPointIndex;
		if (myCurrentWayPointIndex >= static_cast<int>(myWaypoints.size()))
		{
			myCurrentWayPointIndex = 0;
		}
	}
}

void Platform::AddWaypoint(const v2f& aWaypoint)
{
	myWaypoints.push_back(aWaypoint);
}

void Platform::SetWaypoints(const std::vector<v2f>& aWaypoints)
{
	myWaypoints = aWaypoints;
	myCurrentWayPointIndex = 0;
}

void Platform::ClearWaypoints()
{
	myWaypoints.clear();
	myCurrentWayPointIndex = 0;
}