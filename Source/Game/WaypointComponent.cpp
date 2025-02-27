#include "stdafx.h"
#include "WaypointComponent.hpp"
#include "GameObject.h"

WaypointComponent::WaypointComponent()
{
	myWaypointIncrement = 1;
	myLastCheckpointReached = {};
	myCurrentWayPointIndex = {};
}

void WaypointComponent::Move(const float& aDeltaTime)
{
	if (static_cast<int>(myWaypoints.size()) > 0)
	{
		CheckReachedWayPoint(aDeltaTime);
		myOwner->SetPosition(myOwner->GetPosition() + myDirection * mySpeed * aDeltaTime);
	}
}

void WaypointComponent::CheckReachedWayPoint(const float& aDeltaTime)
{
	myDirection = (myWaypoints[myCurrentWayPointIndex] - myOwner->GetPosition()).GetNormalized();
	const float sensitivity = 0.5f + aDeltaTime * mySpeed;
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
		myCurrentWayPointIndex = 0;
	}
	else if (myCurrentWayPointIndex < 0)
		myCurrentWayPointIndex = myWaypoints.size() - 1;
}

void WaypointComponent::SetSpeed(const float& aSpeed)
{
	mySpeed = aSpeed;
	myOriginalSpeed = mySpeed;
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

void WaypointComponent::ResetVelocity()
{
	myDirection = {};
	mySpeed = {};
}

const float& WaypointComponent::GetSpeed()
{
	return mySpeed;
}

void WaypointComponent::SetOwner(GameObject* aGameObject)
{
	myOwner = aGameObject;
}

void WaypointComponent::ReverseWaypoints()
{
	myWaypointIncrement = -1;

	myCurrentWayPointIndex = myCurrentWayPointIndex - 1;

	if (myCurrentWayPointIndex < 0)
		myCurrentWayPointIndex = myWaypoints.size() - 1;

}

bool WaypointComponent::IsAtLastCheckPoint()
{
	if (myLastCheckpointReached)
		return true;
	else
		return false;

}
