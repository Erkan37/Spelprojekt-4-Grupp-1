#include "stdafx.h"
#include "LevelManager.hpp"

#include "Scene.h"
#include "LevelScene.h"

LevelManager::LevelManager()
{

}

LevelManager::~LevelManager()
{

}

void LevelManager::Init()
{
	//myActiveScenes.insert({ eScenes::MainMenu, new MainMenuScene() });
	myScenes.insert({ eScenes::LevelScene, new LevelScene() });
	//myActiveScenes.insert({ eScenes::PauseMenu, new PauseMenuScene() });
}

void LevelManager::SingleLoadScene(eScenes aScene)
{
	UnloadAllScenes();

	AdditiveLoadScene(aScene);
	myScenes[aScene]->Activate();
}

void LevelManager::AdditiveLoadScene(eScenes aScene)
{
	if (!myScenes[aScene]->IsLoaded())
	{
		myScenes[aScene]->Load();
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
	myScenes[aScene]->Load();
}

void LevelManager::UnloadAllScenes()
{
	for (int scene = 0; scene < static_cast<int>(eScenes::Count); ++scene)
	{
		eScenes currentScene = static_cast<eScenes>(scene);
		UnloadScene(currentScene);
	}
}