#pragma once
#include "GameObject.h"

class Camera;
class SpriteComponent;
class LevelScene;
class Player;

class Background : GameObject
{
public:
	Background(Scene* aLevelScene);

	void Init(int someLevelIndex);

	void Update(const float& aDeltaTime) override;

private:
	Camera* myCamera;

	std::unique_ptr<GameObject> myBackground;

	SpriteComponent* myBackgroundSprite1;
	SpriteComponent* myBackgroundSprite2;
	SpriteComponent* myBackgroundSprite3;

	std::string myBackgroundPath1;
	std::string myBackgroundPath2;
	std::string myBackgroundPath3;

	v2f myCurrentRenderSize;
	v2f myStartingCameraPos;

	float myOriginalSpeed;

	float myBackgroundSpeedOneX;
	float myBackgroundSpeedTwoX;
	float myBackgroundSpeedThreeX;

	float myBackgroundSpeedOneY;
	float myBackgroundSpeedTwoY;
	float myBackgroundSpeedThreeY;

	bool myAddedCameraPos;

	void UpdateBackground();
	void ResizeBackground();
	void MoveBackground();
	void LoadJson(Scene* aLevelScene);
	void CreateBackgrounds(Scene* aLevelScene);

};

