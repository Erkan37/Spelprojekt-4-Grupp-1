#include "stdafx.h"
#include "OptionsMenu.h"

#include "GameWorld.h"
#include "InputWrapper.h"
#include "Scene.h"
#include "MainMenuScene.h"
#include "Camera.h"
#include "Game.h"

#include "AudioManager.h"
#include "AnimationComponent.hpp"

OptionsMenu::OptionsMenu(Scene* aLevelScene)
	: myCamera(aLevelScene->GetCamera())
{
	myScene = aLevelScene;
	myMovingIndex = {};
	myMenuAcitve = {};
	mySoundMovingIndex = {};
	myVolume = 0;
	myVolumeStep = 2.0f;
}

void OptionsMenu::Init()
{
	v2f referenceSize = Config::ourReferenceSize;
	myVolume = myAudioManager->GetInstance()->GetMusicVolume();
	myInput = CGameWorld::GetInstance()->Input();

	myBackground = std::make_unique<UIObject>(myScene);
	myFireHighlight = std::make_unique<UIObject>(myScene);
	myBar = std::make_unique<UIObject>(myScene);
	mySoundBtn = std::make_unique<UIButton>(myScene);
	myCreditsBtn = std::make_unique<UIButton>(myScene);
	myTutorialsBtn = std::make_unique<UIButton>(myScene);
	myBackBtn = std::make_unique<UIButton>(myScene);
	myResetBtn = std::make_unique<UIButton>(myScene);
	mySoundSettings = std::make_unique<UIObject>(myScene);
	mySoundSettingsHlght = std::make_unique<UIObject>(myScene);
	myBGDot = std::make_unique<UIObject>(myScene);
	mySFXDot = std::make_unique<UIObject>(myScene);

	

	v2f backgroundPos = { 5.f, 5.f };
	v2f barPos = { 30.0f, 75.0f };
	v2f soundPos = { 140.f, 85.f };
	v2f creditsPos = { 140.f, 105.f };
	v2f tutorialPos = { 140.f, 125.f };
	v2f backPos = { 140.f, 145.f };
	v2f resetPos = { 30.f, 170.f };
	v2f soundSettingPos = { 210.f, 85.f };
	v2f bgDot = { 210.f, 90.f };
	v2f SFXDot = { 210.f, 105.f };

	myBackground->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Background.dds", { 520.f, 265.f }, backgroundPos, 201);
	myFireHighlight->InitAnimation("Sprites/UI/pauseMenu/UI_PauseMenu_Flame_16x16px.dds", { 16.0f, 16.0f }, { 200.0f, 70.0f }, 202);
	myBar->Init("Sprites/UI/pauseMenu/UI_PauseMenu_PauseBarScreen_241x3px.dds",{ 275.0f, 5.f }, barPos, 202);
	mySoundBtn->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Sound_36x16px_Unmarked.dds", { 36.0f, 16.0f }, soundPos, "Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Sound_36x16px_Marked.dds", 36);
	myCreditsBtn->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Credits_45x10px_Unmarked.dds", { 45.f, 16.f }, creditsPos, "Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Credits_45x10px_Marked.dds", 45);
	myTutorialsBtn->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Tutorials_48x10px_Unmarked.dds", { 48.f, 16.f }, tutorialPos, "Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Tutorials_48x10px_Marked.dds", 48);
	myBackBtn->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_MainMenu_Unmarked_64x16px.dds", { 64.f,16.f }, backPos, "Sprites/UI/optionsMenu/UI_OptionsMenu_Text_MainMenu_Marked_64x16px.dds", 64);
	mySoundSettings->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Sound_Setting_74x26px_Unmarked.dds", { 72.f, 26.f }, soundSettingPos, 202);
	mySoundSettingsHlght->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Sound_Setting_74x26px_Marked.dds", { 72.f, 26.f }, soundSettingPos, 203);
	myBGDot->Init("Sprites/UI/optionsMenu/tempDot.dds", { 8.f, 8.f }, bgDot, 202);
	mySFXDot->Init("Sprites/UI/optionsMenu/tempDot.dds", { 8.f, 8.f }, SFXDot, 202);

	myButtons.push_back(mySoundBtn.get());
	myButtons.push_back(myCreditsBtn.get());
	myButtons.push_back(myTutorialsBtn.get());
	myButtons.push_back(myBackBtn.get());
	myButtons.push_back(myResetBtn.get());
	mySoundSettingsHlght->SetActive(false);
	InitTexts();
}

void OptionsMenu::Update(const float& aDeltaTime)
{
	if (myMenuAcitve)
	{
		ActivateMenu();
		CheckActiveAnimations();
		CheckIndexPress();
		UpdateUIElements(aDeltaTime);

	}
	else
		DeactivateMenu();
}

void OptionsMenu::SetActive(const bool aStatement)
{
	myMenuAcitve = aStatement;
}

bool OptionsMenu::IsOptionsActive()
{
	return myMenuAcitve;
}


void OptionsMenu::CheckIndexPress()
{
	if (mySoundSettingsActive == false)
	{
		if (myInput->GetInput()->GetKeyJustDown(Keys::UPARROWKey))
		{
			myMovingIndex--;
			if (myMovingIndex < 0)
				myMovingIndex = myButtons.size() - 1;
		}
		else if (myInput->GetInput()->GetKeyJustDown(Keys::DOWNARROWKey))
		{
			myMovingIndex++;
			if (myMovingIndex > myButtons.size() - 1)
				myMovingIndex = 0;
		}
	}

	if (myInput->GetInput()->GetKeyJustDown(Keys::ENTERKey))
	{
		if (myMovingIndex == static_cast<int>(eOptionsMenu::Back))
		{
			CGameWorld::GetInstance()->GetLevelManager().ReloadScene(LevelManager::eScenes::MainMenu);
		}
		else if (myMovingIndex == static_cast<int>(eOptionsMenu::Sound))
		{
			if (!mySoundSettingsActive)
			{
				mySoundSettingsHlght->SetActive(true);
				mySoundSettingsActive = true;
			}
			else
			{
				mySoundSettingsHlght->SetActive(false);
				mySoundSettingsActive = false;
			}
		}
	}

	if (mySoundSettingsActive == true)
	{
		if (myInput->GetInput()->GetKeyJustDown(Keys::RIGHTARROWKey) && myVolume < 1.0f)
		{
			myVolume += 0.05f;
			myBGDot->SetPositionX(myBGDot->GetPositionX() + myVolumeStep);
			UpdateSoundSettings();
		}
		else if (myInput->GetInput()->GetKeyJustDown(Keys::LEFTARROWKey) && myVolume > 0.0f)
		{
			myVolume -= 0.05f;
			myBGDot->SetPositionX(myBGDot->GetPositionX() - myVolumeStep);
			UpdateSoundSettings();
		}
		if (myInput->GetInput()->GetKeyJustDown(Keys::UPARROWKey))
		{

		}
		else if (myInput->GetInput()->GetKeyJustDown(Keys::DOWNARROWKey))
		{

		}
	}
	
}

void OptionsMenu::ActivateMenu()
{
	for (auto button : myButtons)
		button->SetActive(true);

	myBackground->SetActive(true);
	myFireHighlight->SetActive(true);
	myBar->SetActive(true);
	myTitleString->Activate();
	mySoundSettings->SetActive(true);
	myBGDot->SetActive(true);
	mySFXDot->SetActive(true);
}

void OptionsMenu::DeactivateMenu()
{
	myBackground->SetActive(false);
	myBackBtn->SetActive(false);
	myBar->SetActive(false);
	myTitleString->Deactivate();
	mySoundSettings->SetActive(false);
	myBGDot->SetActive(false);
	mySFXDot->SetActive(false);
}

void OptionsMenu::InitTexts()
{
	myTitleString = std::make_unique<UIText>(myScene);
	myTitleString->Init("Options Menu", "Text/alagard.ttf", EFontSize::EFontSize_100);
	myTitleString->SetPosition({ 140.f, 70.f });

}

void OptionsMenu::UpdateUIElements(const float& aDeltaTime)
{
	myBackground->UpdateUIObjects(aDeltaTime);
	myBar->UpdateUIObjects(aDeltaTime);
	mySoundSettings->UpdateUIObjects(aDeltaTime);
	mySoundSettingsHlght->UpdateUIObjects(aDeltaTime);
	myBGDot->UpdateUIObjects(aDeltaTime);
	mySFXDot->UpdateUIObjects(aDeltaTime);

	for (auto button : myButtons)
		button->UpdateButton(true);
}

void OptionsMenu::CheckActiveAnimations()
{
	for (int i = 0; i < myButtons.size(); i++)
	{
		if (i == myMovingIndex)
		{
			myButtons[i]->SetIsHighlightActive(true);
			myFireHighlight->SetPositionX(myButtons[i]->GetPositionX() - 11.0f);
			myFireHighlight->SetPositionY(myButtons[i]->GetPositionY() + 4.f);
		}
		else
			myButtons[i]->SetIsHighlightActive(false);
	}
}

void OptionsMenu::UpdateSoundSettings()
{
	myAudioManager->GetInstance()->SetMusicVolume(myVolume);
}


