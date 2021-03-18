#pragma once
#include "GameObject.h"
#include "UIObject.h"

class Scene;

class PopUp
	: public GameObject
{
public:
	PopUp(Scene* aLevelScene);

	void InitPopUp();
	void Update(const float& aDeltaTime) override;
	bool isEasyActive();
	void SetEasyActive(const bool aBool);

private:
	Scene* myScene;

	std::unique_ptr<UIObject> myFiree;

	bool myEasyActive;


	void ActivateEasy();
	void DeactivateEasy();
};
