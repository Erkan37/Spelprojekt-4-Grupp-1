#pragma once
#include <vector>
#include <map>
#include "Level.hpp"

class LevelManager
{
public:
	enum class eScenes
	{
		//MainMenu,
		LevelScene,
		//PauseMenu,
		Count
	};

	LevelManager();
	~LevelManager();

	void Init();

	void SingleLoadScene(eScenes aScene);
	void AdditiveLoadScene(eScenes aScene);
	void UnloadScene(eScenes aScene);
	void ReloadScene(eScenes aScene);

	void UnloadAllScenes();

private:
	std::map<eScenes, Scene*> myScenes;
	std::vector<Level> myOpenLevels;

};

