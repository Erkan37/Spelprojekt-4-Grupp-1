#include "stdafx.h"
#include "WaypointComponent.hpp"
#include "GameObject.h"

void WaypointComponent::Move(const float& aDeltaTime)
{
	if (static_cast<int>(myWaypoints.size()) > 0)
	{
		CheckReachedWayPoint();
		myOwner->SetPosition(myOwner->GetPosition() + myDirection * mySpeed * aDeltaTime);
	}
}

void WaypointComponent::CheckReachedWayPoint()
{
	const float sensitivity = 5.0f;
	if (myOwner->GetPosition().x < myWaypoints[myCurrentWayPointIndex].x + sensitivity &&
		myOwner->GetPosition().x > myWaypoints[myCurrentWayPointIndex].x - sensitivity &&
		myOwner->GetPosition().y < myWaypoints[myCurrentWayPointIndex].y + sensitivity &&
		myOwner->GetPosition().y > myWaypoints[myCurrentWayPointIndex].y - sensitivity)
	{
		SetNextWayPoint();
	}
}

void WaypointComponent::SetNextWayPoint()
{
	++myCurrentWayPointIndex;
	if (myCurrentWayPointIndex >= static_cast<int>(myWaypoints.size()))
	{
		myCurrentWayPointIndex = 0;
	}

	myDirection = (myWaypoints[myCurrentWayPointIndex] - myOwner->GetPosition()).GetNormalized();
}

void WaypointComponent::SetSpeed(const float& aSpeed)
{
	mySpeed = aSpeed;
}

void WaypointComponent::AddWaypoint(const v2f& aWaypoint)
{
	myWaypoints.push_back(aWaypoint);
}

void WaypointComponent::SetWaypoints(const std::vector<v2f>& aWaypoints)
{
	myWaypoints = aWaypoints;

	myCurrentWayPointIndex = 0;
	myOwner->SetPosition(myWaypoints[myCurrentWayPointIndex]);
	myDirection = (myWaypoints[myCurrentWayPointIndex] - myOwner->GetPosition()).GetNormalized();
}

void WaypointComponent::ClearWaypoints()
{
	myWaypoints.clear();
	myCurrentWayPointIndex = 0;
}

const v2f WaypointComponent::GetVelocity()
{
	return myDirection * mySpeed;
}

void WaypointComponent::SetOwner(GameObject* aGameObject)
{
	myOwner = aGameObject;
}