#pragma once
#include <map>
#include <memory>

class Scene;
class LevelScene;

class TiledLoader;

class GameObject;

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
	void ToggleImGui();
#endif //RETAIL

	void SingleLoadScene(eScenes aScene);
	void AdditiveLoadScene(eScenes aScene);
	void UnloadScene(eScenes aScene);
	void ReloadScene(eScenes aScene);

	void UnloadAllScenes();

	const bool GetIsActive(eScenes aScene);

	void LoadLevel(LevelScene* aLevelScene, const int& aLevelIndex, GameObject* aPlayer);

private:
	std::map<eScenes, Scene*> myScenes;
	std::shared_ptr<TiledLoader> myTiledLoader;

#ifndef _RETAIL
	bool myImGuiIsActive;
	int myLevelToLoad = 0;
#endif //RETAIL
};

