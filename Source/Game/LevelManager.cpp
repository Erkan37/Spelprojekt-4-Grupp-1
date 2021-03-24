#include "stdafx.h"
#include "LevelManager.hpp"

#include "Scene.h"
#include "LevelScene.h"
#include "MainMenuScene.h"

#include "TiledLoader.h"

#include "GameObject.h"

LevelManager::LevelManager()
{
	myTiledLoader = std::make_shared<TiledLoader>();
#ifndef _RETAIL
	myImGuiIsActive = {};
#endif //RETAIL
}
LevelManager::~LevelManager()
{

}

void LevelManager::Init(Scene* aMainMenuScene, Scene* aLevelScene/*, Scene* aPauseMenuScene*/, Scene* anIntroLogosScene)
{
	myScenes.insert({ eScenes::MainMenu, aMainMenuScene });
	myScenes.insert({ eScenes::LevelScene, aLevelScene });
	//myScenes.insert({ eScenes::PauseMenu, aPauseMenuScene });
	myScenes.insert({ eScenes::IntroLogos, anIntroLogosScene});
}

void LevelManager::Update()
{
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

		ImGui::InputInt("Scene Path", &myLevelToLoad, ImGuiWindowFlags_AlwaysAutoResize);

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

void LevelManager::LoadLevel(LevelScene* aLevelScene, const int& aLevelIndex, GameObject* aPlayer)
{
#ifndef _RETAIL
	myTiledLoader->Load(aLevelScene, myLevelToLoad, aPlayer);
	return;
#endif //RETAIL

	myTiledLoader->Load(aLevelScene, aLevelIndex, aPlayer);
}
