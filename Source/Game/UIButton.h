#pragma once
#include "GameObject.h"

class Camera;
class Scene;
class Player;

class UIButton : public GameObject
{
public:
	UIButton(Scene* aLevelScene);

	void Init(const std::string aPathString, const v2f aSize, const v2f aPosition);

	void Update(const float& aDeltaTime) override;


private:
	Scene* myScene;
	Camera& myCamera;

	v2f myPosition;

};

