#include "stdafx.h"
#include "BashableObjectFactory.hpp"

#include "BashableObject.hpp"

#include "WaypointComponent.hpp"

BashableObject* BashableObjectFactory::CreateBashableObject(Scene* aLevelScene, const v2f& aPosition, const float& aRadius, const float& aSpeed, const std::vector<v2f>& aWaypoints)
{
	BashableObject* bashableObject = new BashableObject(aLevelScene);
	bashableObject->Init(aPosition, aRadius);
	bashableObject->GetComponent<WaypointComponent>()->SetSpeed(aSpeed);
	bashableObject->GetComponent<WaypointComponent>()->SetWaypoints(aWaypoints);
	return bashableObject;
}