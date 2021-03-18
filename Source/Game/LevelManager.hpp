#pragma once
#include <map>
#include <memory>

class Scene;
class LevelScene;

class TiledMap;

class LevelManager
{
public:
	enum class eScenes
	{
		MainMenu,
		LevelScene,
		//PauseMenu,
		Count
	};

	LevelManager();
	~LevelManager();

	void Init(Scene* aMainMenuScene, Scene* aLevelScene);

	void Update();

#ifndef _RETAIL
	void ImGuiUpdate();
#endif //RETAIL

	void SingleLoadScene(eScenes aScene);
	void AdditiveLoadScene(eScenes aScene);
	void UnloadScene(eScenes aScene);
	void ReloadScene(eScenes aScene);

	void UnloadAllScenes();

	const bool GetIsActive(eScenes aScene);

	void LoadLevel(LevelScene* aLevelScene, const std::string& aLevelPath);

private:
	std::map<eScenes, Scene*> myScenes;
	std::shared_ptr<TiledMap> myTiledMap;

#ifndef _RETAIL
	char myLevelToLoad[1024] = "Levels/test_level2.json";
#endif //RETAIL
};

