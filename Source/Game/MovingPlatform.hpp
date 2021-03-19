#pragma once
#include "Platform.h"
#include "Button.h"

class WaypointComponent;

class MovingPlatform : public Platform
{
public:
	enum class eMovingPlatformType
	{
		MovingPlatform,
		ReversePlatform,
		PointAtoBPlatform
	};

	MovingPlatform(Scene* aLevelScene);

	void Update(const float& aDeltaTime) override;

	void SetWaypoints(const std::vector<v2f>& aWaypoints);

	void AddButton(v2f aPosition, eMovingPlatformType aPlatformType);

	void OnCollision(GameObject* aGameObject) override;

private:
	eMovingPlatformType myType;
	Button* myButton;
	bool myAddedButton;


	WaypointComponent* myWaypointComponent;

};

