#include "stdafx.h"
#include "LevelManager.hpp"

#include "Scene.h"
#include "LevelScene.h"
#include "MainMenuScene.h"

#include "TiledLoader.h"

#include "GameObject.h"

#include "DataManager.h"

LevelManager::LevelManager()
{
	myTiledLoader = std::make_shared<TiledLoader>();
#ifndef _RETAIL
	myImGuiIsActive = {};
#endif //RETAIL

	myLoadedLevel = 0;
	myLastDoorType = 1;

	myLevelTransition = false;
	myIsSpeedrunMode = false;

	Subscribe(eMessageType::LoadNext);
	Subscribe(eMessageType::LoadPrevious);
}
LevelManager::~LevelManager()
{

}

void LevelManager::Init(Scene* aMainMenuScene, Scene* aLevelSelect, Scene* aLevelScene/*, Scene* aPauseMenuScene*/, Scene* anIntroLogosScene)
{
	myScenes.insert({ eScenes::MainMenu, aMainMenuScene });
	myScenes.insert({ eScenes::LevelSelect, aLevelSelect });
	myScenes.insert({ eScenes::LevelScene, aLevelScene });
	//myScenes.insert({ eScenes::PauseMenu, aPauseMenuScene });
	myScenes.insert({ eScenes::IntroLogos, anIntroLogosScene });
}

void LevelManager::Update()
{
	if (myLevelTransition)
	{
		LevelScene* levelScene = dynamic_cast<LevelScene*>(myScenes[eScenes::LevelScene]);
		levelScene->Transitioning();
		levelScene->IncreaseBlackScreen(1.0f);

		if (levelScene->GetReachedFullOpacity())
		{
			myLevelTransition = false;
			SingleLoadScene(eScenes::LevelScene);
		}
	}

#ifndef _RETAIL
	ImGuiUpdate();
#endif //RETAIL
}

#ifndef _RETAIL
void LevelManager::ImGuiUpdate()
{
	if (myImGuiIsActive)
	{
		bool levelManager = true;
		ImGui::Begin("Level Manager", &levelManager, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::InputInt("Scene Path", &myLoadedLevel, ImGuiWindowFlags_AlwaysAutoResize);

		if (ImGui::Button("Load Scene"))
		{
			SingleLoadScene(eScenes::LevelScene);
		}

		if (ImGui::Button("MainMenu"))
		{
			SingleLoadScene(eScenes::MainMenu);
		}

		ImGui::End();
	}
}

void LevelManager::ToggleImGui()
{
	myImGuiIsActive = !myImGuiIsActive;
}

#endif //RETAIL

void LevelManager::SingleLoadScene(eScenes aScene)
{
	UnloadAllScenes();

	AdditiveLoadScene(aScene);
}

void LevelManager::AdditiveLoadScene(eScenes aScene)
{
	if (!myScenes[aScene]->IsLoaded())
	{
		myScenes[aScene]->Load();
		myScenes[aScene]->Activate();
	}
}

void LevelManager::UnloadScene(eScenes aScene)
{
	if (myScenes[aScene]->IsLoaded())
	{
		myScenes[aScene]->Unload();
	}
}

void LevelManager::ReloadScene(eScenes aScene)
{
	UnloadScene(aScene);
	AdditiveLoadScene(aScene);
}

void LevelManager::UnloadAllScenes()
{
	for (int scene = 0; scene < static_cast<int>(eScenes::Count); ++scene)
	{
		eScenes currentScene = static_cast<eScenes>(scene);
		UnloadScene(currentScene);
	}
}

const bool LevelManager::GetIsActive(eScenes aScene)
{
	return myScenes[aScene]->IsActive();
}

bool LevelManager::GetIsSpeedrunMode()
{
	return myIsSpeedrunMode;
}

void LevelManager::LoadLevel(LevelScene* aLevelScene, GameObject* aPlayer)
{
	myTiledLoader->Load(aLevelScene, myLoadedLevel, aPlayer);
}

void LevelManager::LoadLevel(LevelScene* aLevelScene, const int& aLevelIndex, GameObject* aPlayer)
{
	myLoadedLevel = aLevelIndex;
	myTiledLoader->Load(aLevelScene, aLevelIndex, aPlayer);
}

void LevelManager::SetLevelIndex(const int& aLevelIndex)
{
	myLoadedLevel = aLevelIndex;
}

void LevelManager::SetIsSpeedrunMode(bool aIsSpeedrunMode)
{
	//myIsSpeedrunMode = aIsSpeedrunMode;
}

void LevelManager::Notify(const Message& aMessage)
{
	if (aMessage.myMessageType == eMessageType::LoadNext)
	{
		++myLoadedLevel;
		if (myLoadedLevel >= DataManager::GetInstance().GetLevelCount())
		{
			myLoadedLevel = DataManager::GetInstance().GetLevelCount() - 1;
		}

		myLastDoorType = std::get<int>(aMessage.myData);

		myLevelTransition = true;
	}
	else if (aMessage.myMessageType == eMessageType::LoadPrevious)
	{
		--myLoadedLevel;
		if (myLoadedLevel < 0)
		{
			myLoadedLevel = 0;
		}

		myLastDoorType = std::get<int>(aMessage.myData);

		myLevelTransition = true;
	}
}

const int LevelManager::GetDoorType()
{
	return myLastDoorType;
}
