#pragma once
#include "GameObject.h"
#include "UIObject.h"

class Scene;


class PopUp
	: public GameObject
{
public:
	enum class ePopUpTypes
	{
		Easy,
		Medium,
		Hard
	};

	PopUp(Scene* aLevelScene);

	void InitPopUp();
	void Update(const float& aDeltaTime) override;
	bool isEasyActive();
	bool isMediumActive();
	bool isHardActive();
	void SetEasyActive(const bool aBool);
	void SetMediumActive(const bool aBool);
	void SetHardActive(const bool aBool);

private:
	Scene* myScene;

	std::unique_ptr<UIObject> myBackground;
	std::unique_ptr<UIObject> myFireEasy;
	std::unique_ptr<UIObject> myFireMedium;
	std::unique_ptr<UIObject> myFireHard;



	float myCurrentTime;
	float myMaxTime;


	bool myEasyActive;
	bool myMediumActive;
	bool myHardActive;

	void Activate(ePopUpTypes aType);
	void Deactivate(ePopUpTypes aType);
};
