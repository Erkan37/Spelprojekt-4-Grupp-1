#include "stdafx.h"
#include "WaypointComponent.hpp"
#include "GameObject.h"

WaypointComponent::WaypointComponent()
{
	myWaypointIncrement = 1;
	myLastCheckpointReached = {};
	myReverseBool = {};
}

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
	myDirection = (myWaypoints[myCurrentWayPointIndex] - myOwner->GetPosition()).GetNormalized();
	const float sensitivity = 0.5f;
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
	myCurrentWayPointIndex = myCurrentWayPointIndex + myWaypointIncrement;
	if (myCurrentWayPointIndex >= static_cast<int>(myWaypoints.size()))
	{
		myLastCheckpointReached = true;
		if (!myReverseBool)
			myCurrentWayPointIndex = 0;
	}
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

	if (static_cast<int>(aWaypoints.size()) > 0)
	{
		myCurrentWayPointIndex = 0;
		myOwner->SetPosition(myWaypoints[myCurrentWayPointIndex]);
		myDirection = (myWaypoints[myCurrentWayPointIndex] - myOwner->GetPosition()).GetNormalized();
	}
}

void WaypointComponent::ClearWaypoints()
{
	myWaypoints.clear();
	//myCurrentWayPointIndex = 0;
}

const v2f WaypointComponent::GetVelocity()
{
	return myDirection * mySpeed;
}

void WaypointComponent::SetOwner(GameObject* aGameObject)
{
	myOwner = aGameObject;
}

void WaypointComponent::ReverseWaypoints()
{
	myCurrentWayPointIndex = 0;
	myLastCheckpointReached = false;
}

void WaypointComponent::AddReverseBool()
{
	myReverseBool = true;
}

bool WaypointComponent::IsAtLastCheckPoint()
{
	if (myLastCheckpointReached)
		return true;
	else
		return false;

}
