#pragma once
#include "GameObject.h"

class Camera;


class UIBackground : public GameObject
{
public:
	UIBackground(Scene* aLevelScene);
	
	void Init(const std::string aPathString, const v2f aSize, const v2f aPosition);


	void Update(const float& aDeltaTime) override;



private:
	Camera* myCamera;

	v2f myPosition;

};

