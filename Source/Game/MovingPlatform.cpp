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
	myAddedButton = {};
}

void MovingPlatform::Update(const float& aDeltaTime)
{
	if (!myAddedButton)
		myWaypointComponent->Move(aDeltaTime);
	else
	{
		if (myButton.GetActiveButton())
			myWaypointComponent->Move(aDeltaTime);
	}
	
	Platform::Update(aDeltaTime);
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

}

void MovingPlatform::AddButton(v2f aPosition, eMovingPlatformType aPlatformType)
{
	myAddedButton = true;
	myType = aPlatformType;
	myButton.Init(GetPosition(), aPosition);
}

void MovingPlatform::OnCollision(GameObject* aGameObject)
{
	if (!myAddedButton || myButton.GetActiveButton())
	{
		Player* player = dynamic_cast<Player*>(aGameObject);
		if (player)
		{
			player->SetPlatformVelocity(myWaypointComponent->GetVelocity());
		}
	}
}