#pragma once
#include <map>
#include <memory>

#include "Subscriber.hpp"

class Scene;
class LevelScene;

class TiledLoader;
class SpeedrunManager;

class GameObject;

class LevelManager : public Subscriber
{
public:
	enum class eScenes
	{
		MainMenu,
		LevelSelect,
		LevelScene,
		IntroLogos,
		WinScene,
		SpeedrunScene,
		//PauseMenu,
		Count
	};

	LevelManager();
	~LevelManager();

	void Init(Scene* aMainMenuScene, Scene* aLevelSelect, Scene* aLevelScene, Scene* anIntroLogosScene, Scene* aWinScene, Scene* aSpeedrunScene);

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
	inline std::shared_ptr<SpeedrunManager> GetSpeedrunManager()
	{
		return mySpeedrunManager;
	}

	void LoadLevel(LevelScene* aLevelScene, GameObject* aPlayer);
	void LoadLevel(LevelScene* aLevelScene, const int& aLevelIndex, GameObject* aPlayer);

	void SetLevelIndex(const int& aLevelIndex);
	void UsedLevelSelect();

	void Notify(const Message& aMessage) override;

	const int& GetDoorType();

private:
	std::map<eScenes, Scene*> myScenes;
	std::shared_ptr<TiledLoader> myTiledLoader;
	std::shared_ptr<SpeedrunManager> mySpeedrunManager;

	int myLastDoorType;

	int myLoadedLevel;

	bool myLoadingHiddenRoom;
	bool myLevelTransition;
	//bool myIsSpeedrunMode;

#ifndef _RETAIL
	bool myImGuiIsActive;
#endif //RETAIL
};

