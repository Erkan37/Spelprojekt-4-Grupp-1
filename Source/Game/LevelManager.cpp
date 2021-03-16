#include "stdafx.h"
#include "LevelManager.hpp"

#include "Scene.h"
#include "LevelScene.h"

#include "TiledMap.h"

LevelManager::LevelManager()
{
	myTiledMap = std::make_shared<TiledMap>();
}

LevelManager::~LevelManager()
{

}

void LevelManager::Init(/*Scene* aMainMenuScene, */Scene* aLevelScene/*, Scene* aPauseMenuScene*/)
{
	//myScenes.insert({ eScenes::MainMenu, aMainMenuScene });
	myScenes.insert({ eScenes::LevelScene, aLevelScene });
	//myScenes.insert({ eScenes::PauseMenu, aPauseMenuScene });
}

void LevelManager::Update()
{
#ifdef _DEBUG
	ImGuiUpdate();
#endif //DEBUG
}

#ifdef _DEBUG
void LevelManager::ImGuiUpdate()
{
	if (myScenes[eScenes::LevelScene]->IsLoaded())
	{
		return;
	}

	bool levelManager = true;
	ImGui::Begin("Level Manager", &levelManager, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::InputText("Scene Path", myLevelToLoad, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Load Scene"))
	{
		SingleLoadScene(eScenes::LevelScene);
	}

	ImGui::End();
}
#endif //DEBUG

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

void LevelManager::LoadLevel(const std::string& aLevelPath)
{
#ifdef _DEBUG
	myTiledMap->Load(myLevelToLoad, myScenes[eScenes::LevelScene]);
	return;
#endif //DEBUG

	myTiledMap->Load(aLevelPath, myScenes[eScenes::LevelScene]);
}