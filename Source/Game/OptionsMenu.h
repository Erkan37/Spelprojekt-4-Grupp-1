#pragma once
#include "UIButton.h"
#include "UIObject.h"
#include "UIText.h"

#include <vector>

class InputWrapper;
class Scene;
class SpriteComponent;
class AudioManager;

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


private:
	Scene* myScene;
	Camera& myCamera;
	AudioManager* myAudioManager;

	float myVolume;
	float myVolumeStep;

	std::unique_ptr<UIObject> myBackground;
	std::unique_ptr<UIObject> myOptionsTitle;
	std::unique_ptr<UIObject> myFireHighlight;
	std::unique_ptr<UIObject> myBar;
	std::unique_ptr<UIObject> mySoundSettings;
	std::unique_ptr<UIObject> mySoundSettingsHlght;
	std::unique_ptr<UIObject> myBGDot;
	std::unique_ptr<UIObject> mySFXDot;

	std::unique_ptr<UIButton> myTutorialsBtn;
	std::unique_ptr<UIButton> mySoundBtn;
	std::unique_ptr<UIButton> myCreditsBtn;
	std::unique_ptr<UIButton> myBackBtn;
	std::unique_ptr<UIButton> myResetBtn;


	
	std::vector<UIButton*> myButtons;

	std::unique_ptr<UIText> myTitleString;
	std::unique_ptr<UIText> myBGString;
	std::unique_ptr<UIText> myVFXString;

	std::shared_ptr<InputWrapper> myInput;

	int myMovingIndex;
	int mySoundMovingIndex;

	bool myMenuAcitve;
	bool mySoundSettingsActive = false;

	void CheckIndexPress();
	void ActivateMenu();
	void DeactivateMenu();
	void InitTexts();
	void UpdateUIElements(const float& aDeltaTime);
	void CheckActiveAnimations();
	void UpdateSoundSettings();
};

