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
	myMusicVol = 0;
	myVFXVol = 0;
	myMusicStep = 2.0f;
	myVFXStep = 2.0f;
}

void OptionsMenu::Init()
{
	v2f referenceSize = Config::ourReferenceSize;
	myMusicVol = myAudioManager->GetInstance()->GetMusicVolume();
	myVFXVol = myAudioManager->GetInstance()->GetSFXVolume();
	myInput = CGameWorld::GetInstance()->Input();

	myBackground = std::make_unique<UIObject>(myScene);
	myBar = std::make_unique<UIObject>(myScene);
	
	myFireHighlight = std::make_unique<UIObject>(myScene);
	mySoundBtn = std::make_unique<UIButton>(myScene);
	myCreditsBtn = std::make_unique<UIButton>(myScene);
	myTutorialsBtn = std::make_unique<UIButton>(myScene);
	myBackBtn = std::make_unique<UIButton>(myScene);
	myResetBtn = std::make_unique<UIButton>(myScene);
	myScreenBtn = std::make_unique<UIButton>(myScene);
	
	mySoundSettings = std::make_unique<UIObject>(myScene);
	myBGHighlight = std::make_unique<UIObject>(myScene);
	myVFXHighlight = std::make_unique<UIObject>(myScene);
	myBGDot = std::make_unique<UIObject>(myScene);
	myVFXDot = std::make_unique<UIObject>(myScene);
	
	myResolutions = std::make_unique<UIObject>(myScene);
	my720pHgh = std::make_unique<UIObject>(myScene);
	my1080pHgh = std::make_unique<UIObject>(myScene);
	my4KHgh = std::make_unique<UIObject>(myScene);

	v2f backgroundPos = { 5.f, 5.f };
	v2f barPos = { 30.0f, 60.0f };
	v2f screenPos = { 140.f, 70.f };
	v2f soundPos = { 140.f, 90.f };
	v2f creditsPos = { 140.f, 110.f };
	v2f tutorialPos = { 140.f, 130.f };
	v2f backPos = { 140.f, 150.f };
	v2f resetPos = { 30.f, 160.f };
	v2f soundSettingPos = { 215.f, 90.f };
	v2f bgDot = { 215.f + myMusicVol, 95.f };
	v2f SFXDot = { 215.f + myVFXVol, 110.f };
	v2f resolutionPos = { 215, 73.f };

	//Misc
	myBackground->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Background.dds", { 520.f, 265.f }, backgroundPos, 201);
	myBar->Init("Sprites/UI/pauseMenu/UI_PauseMenu_PauseBarScreen_241x3px.dds",{ 275.0f, 5.f }, barPos, 202);
	
	//Buttons
	myFireHighlight->InitAnimation("Sprites/UI/pauseMenu/UI_PauseMenu_Flame_16x16px.dds", { 16.0f, 16.0f }, { 200.0f, 70.0f }, 202);
	myScreenBtn->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Screensize_66x16px_Unmarked.dds", { 66.f, 16.f }, screenPos, "Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Screensize_66x16px_Marked.dds", 66);
	mySoundBtn->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Sound_36x16px_Unmarked.dds", { 36.0f, 16.0f }, soundPos, "Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Sound_36x16px_Marked.dds", 36);
	myCreditsBtn->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Credits_45x10px_Unmarked.dds", { 45.f, 16.f }, creditsPos, "Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Credits_45x10px_Marked.dds", 45);
	myTutorialsBtn->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Tutorials_48x10px_Unmarked.dds", { 48.f, 16.f }, tutorialPos, "Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Tutorials_48x10px_Marked.dds", 48);
	myBackBtn->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_MainMenu_Unmarked_64x16px.dds", { 64.f,16.f }, backPos, "Sprites/UI/optionsMenu/UI_OptionsMenu_Text_MainMenu_Marked_64x16px.dds", 64);
	myResetBtn->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_ResetSave_65x16px_Unmarked.dds", { 65.f,16.f }, resetPos, "Sprites/UI/optionsMenu/UI_OptionsMenu_Text_ResetSave_65x16px_Marked.dds", 65);

	//Sound
	mySoundSettings->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Sound_Setting_74x26px_Unmarked.dds", { 72.f, 26.f }, soundSettingPos, 202);
	myBGHighlight->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Sound_Setting_74x26px_BG_Marked.dds", { 74.f,26.f }, soundSettingPos, 203);
	myVFXHighlight->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Sound_Setting_74x26px_VFX_Marked.dds", { 74.f,26.f }, soundSettingPos, 203);
	myBGDot->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Sound_SettingsMark_3x3px.dds", { 3.f, 3.f }, bgDot, 202);
	myVFXDot->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Sound_SettingsMark_3x3px.dds", { 3.f, 3.f }, SFXDot, 202);

	//Screen
	myResolutions->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Screensize_Resolutions_All_73x7px_Unmarked.dds", { 73.f, 7.f }, resolutionPos, 202);
	my720pHgh->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Screensize_Resolutions_720p_73x7pxMarked.dds", { 73.f,7.f }, resolutionPos, 203);
	my1080pHgh->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Screensize_Resolutions_1080p_73x7pxMarked.dds", { 73.f,7.f }, resolutionPos, 203);
	my4KHgh->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_Screensize_Resolutions_4k_73x7pxMarked.dds", { 73.f,7.f }, resolutionPos, 203);

	myButtons.push_back(myScreenBtn.get());
	myButtons.push_back(mySoundBtn.get());
	myButtons.push_back(myCreditsBtn.get());
	myButtons.push_back(myTutorialsBtn.get());
	myButtons.push_back(myBackBtn.get());
	myButtons.push_back(myResetBtn.get());
	
	mySoundObjects.push_back(myBGHighlight.get());
	mySoundObjects.push_back(myVFXHighlight.get());

	myResolutionObj.push_back(my720pHgh.get());
	myResolutionObj.push_back(my1080pHgh.get());
	myResolutionObj.push_back(my4KHgh.get());

	InitTexts();
	myTitleString->Deactivate();
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
				mySoundSettingsActive = true;
			}
			else
			{
				mySoundSettingsActive = false;
				myBGHighlight->SetActive(false);
				myVFXHighlight->SetActive(false);
			}
		}
		else if (myMovingIndex == static_cast<int>(eOptionsMenu::ScreenSize))
		{
			if (!myScreenSettingsActive)
			{
				myScreenSettingsActive = true;
			}
			else
				myScreenSettingsActive = false;
		}
	}

	if (mySoundSettingsActive == true)
	{
		if (myInput->GetInput()->GetKeyJustDown(Keys::UPARROWKey))
		{
			mySoundMovingIndex--;
			if (mySoundMovingIndex < 0)
				mySoundMovingIndex = mySoundObjects.size() - 1;
		}
		else if (myInput->GetInput()->GetKeyJustDown(Keys::DOWNARROWKey))
		{
			mySoundMovingIndex++;
			if (mySoundMovingIndex > mySoundObjects.size() - 1)
				mySoundMovingIndex = 0;
		}

		if (myInput->GetInput()->GetKeyJustDown(Keys::RIGHTARROWKey))
		{

			if (mySoundMovingIndex == 0 && myMusicVol < 1.0f)
			{
				myMusicVol += 0.05f;
				myBGDot->SetPositionX(myBGDot->GetPositionX() + myMusicStep);
				UpdateSoundSettings();
			}
			else if (mySoundMovingIndex == 1 && myVFXVol < 1.0f)
			{
				myVFXVol += 0.05f;
				myVFXDot->SetPositionX(myVFXDot->GetPositionX() + myVFXStep);
				//Update VFXVolume
			}
		}
		else if (myInput->GetInput()->GetKeyJustDown(Keys::LEFTARROWKey))
		{
			if (mySoundMovingIndex == 0 && myMusicVol > 0.0f)
			{
				myMusicVol -= 0.05f;
				myBGDot->SetPositionX(myBGDot->GetPositionX() - myMusicStep);
				UpdateSoundSettings();
			}
			else if (mySoundMovingIndex == 1 && myVFXVol > 0.0f)
			{
				myVFXVol -= 0.05f;
				myVFXDot->SetPositionX(myVFXDot->GetPositionX() - myVFXStep);
				//Update VFXVolume
			}
		}
	}
	
	if (myScreenSettingsActive == true)
	{
		if (myInput->GetInput()->GetKeyJustDown(Keys::LEFTARROWKey))
		{
			myScreenMovingIndex--;
			if (myScreenMovingIndex < 0)
				myScreenMovingIndex = myResolutionObj.size() - 1;
		}
		else if (myInput->GetInput()->GetKeyJustDown(Keys::RIGHTARROWKey))
		{
			myScreenMovingIndex++;
			if (myScreenMovingIndex > myResolutionObj.size() - 1)
				myScreenMovingIndex = 0;
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
	myVFXDot->SetActive(true);
	myResolutions->SetActive(true);
}

void OptionsMenu::DeactivateMenu()
{
	for (auto button : myButtons)
		button->SetActive(false);

	for (auto objects : mySoundObjects)
		objects->SetActive(false);

	for (auto res : myResolutionObj)
		res->SetActive(false);

	myBackground->SetActive(false);
	myBackBtn->SetActive(false);
	myBar->SetActive(false);
	myTitleString->Deactivate();
	mySoundSettings->SetActive(false);
	myBGDot->SetActive(false);
	myVFXDot->SetActive(false);
	myResolutions->SetActive(false);
}

void OptionsMenu::InitTexts()
{
	myTitleString = std::make_unique<UIText>(myScene);
	myTitleString->Init("Options Menu", "Text/alagard.ttf", EFontSize::EFontSize_100);
	myTitleString->SetPosition({ 140.f, 50.f });

}

void OptionsMenu::UpdateUIElements(const float& aDeltaTime)
{
	myBackground->UpdateUIObjects(aDeltaTime);
	myBar->UpdateUIObjects(aDeltaTime);
	mySoundSettings->UpdateUIObjects(aDeltaTime);
	myBGDot->UpdateUIObjects(aDeltaTime);
	myVFXDot->UpdateUIObjects(aDeltaTime);
	myResolutions->UpdateUIObjects(aDeltaTime);

	for (auto button : myButtons)
		button->UpdateButton(true);

	for (auto objects : mySoundObjects)
		objects->UpdateUIObjects(true);

	for (auto res : myResolutionObj)
		res->UpdateUIObjects(true);
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
	if (mySoundSettingsActive == true)
	{
		for (int i = 0; i < mySoundObjects.size(); i++)
		{
			if (i == mySoundMovingIndex)
			{
				mySoundObjects[i]->SetActive(true);
			}
			else
				mySoundObjects[i]->SetActive(false);
		}
	}
	if (myScreenSettingsActive == true)
	{
		for (int i = 0; i < myResolutionObj.size(); i++)
		{
			if (i == myScreenMovingIndex)
			{
				myResolutionObj[i]->SetActive(true);
			}
			else
				myResolutionObj[i]->SetActive(false);
		}
	}
}

void OptionsMenu::UpdateSoundSettings()
{
	myAudioManager->GetInstance()->SetMusicVolume(myMusicVol);
}


