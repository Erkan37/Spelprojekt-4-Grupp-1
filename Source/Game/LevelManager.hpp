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

	void Update();

#ifdef _DEBUG
	void ImGuiUpdate();
#endif //DEBUG

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

#ifdef _DEBUG
	char myLevelToLoad[1024] = "Levels/test_level2.json";
#endif //DEBUG
};

