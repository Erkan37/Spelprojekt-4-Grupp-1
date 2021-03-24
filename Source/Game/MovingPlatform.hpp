#pragma once
#include "Platform.h"
#include "Button.h"

class WaypointComponent;

class MovingPlatform : public Platform
{
public:
	enum class eMovingPlatformType
	{
		RegularPlatform,
		MovingPlatform,
		ReversePlatform,
		PointAtoBPlatform
	};

	MovingPlatform(Scene* aLevelScene);

	~MovingPlatform();

	void Update(const float& aDeltaTime) override;

	void SetWaypoints(const std::vector<v2f>& aWaypoints);

	void AddButton(v2f aPosition, eMovingPlatformType aPlatformType);

	void AdjustXOffset();

	void OnCollision(GameObject* aGameObject) override;

private:
	eMovingPlatformType myType;
	Button* myButton;

	float myPercentageYValue;
	bool myAddedButton;
	bool myRevertOn;

	WaypointComponent* myWaypointComponent;

};

