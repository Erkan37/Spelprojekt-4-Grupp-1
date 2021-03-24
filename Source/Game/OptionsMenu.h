#pragma once
#include "UIButton.h"
#include "UIObject.h"
#include "UIText.h"

#include <vector>

class InputWrapper;
class Scene;
class SpriteComponent;

class OptionsMenu
{
public:
	enum class eOptionsMenu
	{
		Sound,
		Credits,
		ResetGame,
		Back
	};

	OptionsMenu(Scene* aLevelScene);
		
	void Init();

	void Update(const float& aDeltaTime);

	void SetActive(const bool aStatement);
	bool IsOptionsActive();
	void SelectButton();

private:
	Scene* myScene;
	Camera& myCamera;

	std::unique_ptr<UIObject> myBackground;
	std::unique_ptr<UIObject> myFireHighlight;
	std::unique_ptr<UIObject> myBar;

	std::unique_ptr<UIButton> myResetBtn;
	std::unique_ptr<UIButton> mySoundBtn;
	std::unique_ptr<UIButton> myCreditsBtn;
	std::unique_ptr<UIButton> myBackBtn;

	std::vector<UIButton*> myButtons;

	std::unique_ptr<UIText> myTitleString;
	std::unique_ptr<UIText> myBGString;
	std::unique_ptr<UIText> myVFXString;

	std::shared_ptr<InputWrapper> myInput;

	int myMovingIndex;

	bool myMenuAcitve;

	void CheckIndexPress();
	void ActivateMenu();
	void DeactivateMenu();
	void InitTexts();
	void UpdateUIElements(const float& aDeltaTime);
	void CheckActiveAnimations();
};

