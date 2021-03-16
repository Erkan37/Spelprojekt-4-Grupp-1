#pragma once
#include <map>
#include <memory>

class Scene;

class TiledMap;

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

	void Init(Scene* aLevelScene);

	void SingleLoadScene(eScenes aScene);
	void AdditiveLoadScene(eScenes aScene);
	void UnloadScene(eScenes aScene);
	void ReloadScene(eScenes aScene);

	void UnloadAllScenes();

	const bool GetIsActive(eScenes aScene);

	void LoadLevel(const std::string& aLevelPath);

private:
	std::map<eScenes, Scene*> myScenes;
	std::shared_ptr<TiledMap> myTiledMap;
};

