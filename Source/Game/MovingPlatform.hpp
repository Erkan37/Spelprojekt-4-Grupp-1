#pragma once
#include "Platform.h"
#include "Button.h"

class WaypointComponent;

class MovingPlatform : public Platform
{
public:
	MovingPlatform(Scene* aLevelScene);

	void Update(const float& aDeltaTime) override;

	void SetWaypoints(const std::vector<v2f>& aWaypoints);

	void SetButtonPosition();

	void AddButton(v2f aPosition);

	void OnCollision(GameObject* aGameObject) override;

private:
	Button myButton;
	WaypointComponent* myWaypointComponent;

};

