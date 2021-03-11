#include "stdafx.h"
#include "MovingPlatform.hpp"
#include "Player.hpp"
#include "Button.h"

MovingPlatform::MovingPlatform(Scene* aLevelScene)
	:
	Platform(aLevelScene),
	mySpeed(0.0f),
	myCurrentWayPointIndex(0),
	myButton(aLevelScene)
{
}

void MovingPlatform::Update(const float& aDeltaTime)
{
	if (static_cast<int>(myWaypoints.size()) > 0)
	{
		Move(aDeltaTime);
	}
	
	Platform::Update(aDeltaTime);
}

void MovingPlatform::Move(const float& aDeltaTime)
{
	if (myButton.GetActiveButton())
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
}

void MovingPlatform::SetSpeed(const float& aSpeed)
{
	mySpeed = aSpeed;
}

void MovingPlatform::AddWaypoint(const v2f& aWaypoint)
{
	myWaypoints.push_back(aWaypoint);
}

void MovingPlatform::SetWaypoints(const std::vector<v2f>& aWaypoints)
{
	myWaypoints = aWaypoints;
	myCurrentWayPointIndex = 0;
	SetPosition(myWaypoints[myCurrentWayPointIndex]);
	SetButtonPosition();
}

void MovingPlatform::SetButtonPosition()
{
	myButton.Init(GetPosition(), v2f(-450, -100));
}

void MovingPlatform::ClearWaypoints()
{
	myWaypoints.clear();
	myCurrentWayPointIndex = 0;
}

void MovingPlatform::OnCollision(GameObject* aGameObject)
{
	if (myButton.GetActiveButton())
	{
		Player* player = dynamic_cast<Player*>(aGameObject);
		if (player)
		{
			player->SetPlatformVelocity(myDirection * mySpeed);
		}
	}
}