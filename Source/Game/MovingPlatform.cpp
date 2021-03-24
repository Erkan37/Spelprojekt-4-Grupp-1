#include "stdafx.h"
#include "MovingPlatform.hpp"
#include "Player.hpp"
#include "Button.h"

#include "WaypointComponent.hpp"
#include "SpriteComponent.h"

MovingPlatform::MovingPlatform(Scene* aLevelScene)
	:
	Platform(aLevelScene),
	myButton(new Button(aLevelScene)),
	myWaypointComponent(nullptr)
{
	SetZIndex(93);

	myWaypointComponent = AddComponent<WaypointComponent>();
	myWaypointComponent->SetOwner(this);
	myAddedButton = false;
	myType = eMovingPlatformType::RegularPlatform;
}

void MovingPlatform::Update(const float& aDeltaTime)
{
	if (myType == eMovingPlatformType::RegularPlatform)
		myWaypointComponent->Move(aDeltaTime);

	if (myAddedButton)
	{
		if (myType == eMovingPlatformType::ReversePlatform)
			if (!myWaypointComponent->IsAtLastCheckPoint())
 				myWaypointComponent->Move(aDeltaTime);

		if (myButton->GetActiveButton())
		{
			if (myType == eMovingPlatformType::ReversePlatform)
			{
				myWaypointComponent->ReverseWaypoints();
			}
			else if (myType == eMovingPlatformType::MovingPlatform)
				myWaypointComponent->Move(aDeltaTime);
			else if (myType == eMovingPlatformType::PointAtoBPlatform)
			{
				if (!myWaypointComponent->IsAtLastCheckPoint())
					myWaypointComponent->Move(aDeltaTime);
				else
					myWaypointComponent->ResetVelocity();
			}
		}
	}

	//Platform::Update(aDeltaTime);
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
	myButton->Init(GetPosition(), aPosition);

	if (myType == eMovingPlatformType::ReversePlatform)
		myWaypointComponent->AddReverseBool();
}

void MovingPlatform::OnCollision(GameObject* aGameObject)
{
	if (!myAddedButton || myButton->GetActiveButton())
	{
		Player* player = dynamic_cast<Player*>(aGameObject);
		if (player)
		{
			player->SetPlatformVelocity(myWaypointComponent->GetVelocity());
		}
	}
}
