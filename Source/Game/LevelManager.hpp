#pragma once
#include <map>
#include <memory>

#include "Subscriber.hpp"

class Scene;
class LevelScene;

class TiledLoader;

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
		//PauseMenu,
		Count
	};

	LevelManager();
	~LevelManager();

	void Init(Scene* aMainMenuScene, Scene* aLevelSelect, Scene* aLevelScene, Scene* anIntroLogosScene, Scene* aWinScene);

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
	bool GetIsSpeedrunMode();

	void LoadLevel(LevelScene* aLevelScene, GameObject* aPlayer);
	void LoadLevel(LevelScene* aLevelScene, const int& aLevelIndex, GameObject* aPlayer);

	void SetLevelIndex(const int& aLevelIndex);
	void SetIsSpeedrunMode(bool aIsSpeedrunMode);

	void Notify(const Message& aMessage) override;

	const int GetDoorType();

private:
	std::map<eScenes, Scene*> myScenes;
	std::shared_ptr<TiledLoader> myTiledLoader;

	int myLoadedLevel;
	int myLastDoorType;

	bool myLevelTransition;
	bool myIsSpeedrunMode;

#ifndef _RETAIL
	bool myImGuiIsActive;
#endif //RETAIL
};

