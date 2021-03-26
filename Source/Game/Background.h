#pragma once
#include "GameObject.h"
#include "rapidjson/document.h"

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
	std::unique_ptr<GameObject> myCloud;

	SpriteComponent* myBackgroundSprite1;
	SpriteComponent* myBackgroundSprite2;
	SpriteComponent* myBackgroundSprite3;
	SpriteComponent* myBackgroundSprite4;
	SpriteComponent* myBackgroundSprite5;
	SpriteComponent* myBackgroundSprite6;

	v2f myCurrentRenderSize;
	v2f myStartingCameraPos;
	
	v2f myOffsetBackground1;
	v2f myOffsetBackground2;
	v2f myOffsetBackground3;
	v2f myOffsetBackground4;
	v2f myOffsetBackground5;
	v2f myOffsetBackground6;

	float myOriginalSpeed;
	float myCloudSpeed;
	float myCloudDistance;

	float myBackgroundSpeedOneX;
	float myBackgroundSpeedTwoX;
	float myBackgroundSpeedThreeX;
	float myBackgroundSpeedFourX;
	float myBackgroundSpeedFiveX;
	float myBackgroundSpeedSixX;

	float myBackgroundSpeedOneY;
	float myBackgroundSpeedTwoY;
	float myBackgroundSpeedThreeY;
	float myBackgroundSpeedFourY;
	float myBackgroundSpeedFiveY;
	float myBackgroundSpeedSixY;

	bool myAddedCameraPos;

	void UpdateBackground(const float& aDeltaTime);
	void ResizeBackground();
	void MoveBackground(const float& aDeltaTime);
	void LoadJson(Scene* aLevelScene);
	void LoadBackgrounds(Scene* aLevelScene, rapidjson::Document& someDocuments);
	void CreateBackgrounds(Scene* aLevelScene, const std::string aPath, const int aIndex, const v2f anOffset);
	void SetSpeedVariables(const std::string aPath);

};

