#include "stdafx.h"
#include "MovingPlatform.hpp"
#include "Player.hpp"
#include "Button.h"

#include "WaypointComponent.hpp"

MovingPlatform::MovingPlatform(Scene* aLevelScene)
	:
	Platform(aLevelScene),
	myButton(aLevelScene),
	myWaypointComponent(nullptr)
{
	myWaypointComponent = AddComponent<WaypointComponent>();
	myWaypointComponent->SetOwner(this);
}

void MovingPlatform::Update(const float& aDeltaTime)
{
	myWaypointComponent->Move(aDeltaTime);
	
	Platform::Update(aDeltaTime);
}

void MovingPlatform::SetSpeed(const float& aSpeed)
{
	myWaypointComponent->SetSpeed(aSpeed);
}

void MovingPlatform::AddWaypoint(const v2f& aWaypoint)
{
	myWaypointComponent->AddWaypoint(aWaypoint);
}

void MovingPlatform::SetWaypoints(const std::vector<v2f>& aWaypoints)
{
	constexpr float xOffset = 4.0f; //To offset platform to middle of line

	std::vector<v2f> adjustedWaypoints;

	for (const v2f& waypoint : aWaypoints)
	{
		adjustedWaypoints.push_back(waypoint - v2f(4.0f, 0.0f));
	}

	myWaypointComponent->SetWaypoints(aWaypoints);

	SetButtonPosition();
}

void MovingPlatform::SetButtonPosition()
{
	myButton.Init(GetPosition(), v2f(-450, -100));
}

void MovingPlatform::OnCollision(GameObject* aGameObject)
{
	if (myButton.GetActiveButton())
	{
		Player* player = dynamic_cast<Player*>(aGameObject);
		if (player)
		{
			player->SetPlatformVelocity(myWaypointComponent->GetVelocity());
		}
	}
}