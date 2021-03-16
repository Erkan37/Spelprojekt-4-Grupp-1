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

void LevelManager::Init(/*Scene* aMainMenuScene, */Scene* aLevelScene/*, Scene* aPauseMenuScene*/)
{
	//myScenes.insert({ eScenes::MainMenu, aMainMenuScene });
	myScenes.insert({ eScenes::LevelScene, aLevelScene });
	//myScenes.insert({ eScenes::PauseMenu, aPauseMenuScene });
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