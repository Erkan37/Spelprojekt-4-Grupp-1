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

	GameObject* myBackgroundSprite1;
	GameObject* myBackgroundSprite2;
	GameObject* myBackgroundSprite3;
	GameObject* myBackgroundSprite4;
	GameObject* myBackgroundSprite5;
	GameObject* myBackgroundSprite6;

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

	const void UpdateBackground(const float& aDeltaTime);
	const void ResizeBackground();
	const void MoveBackground(const float& aDeltaTime);
	const void LoadJson(Scene* aLevelScene);
	const void LoadBackgrounds(Scene* aLevelScene, rapidjson::Document& someDocuments);
	const void CreateBackgrounds(Scene* aLevelScene, const std::string aPath, const int aIndex, const v2f anOffset);
	const void SetSpeedVariables(const std::string aPath);
	const v2f GetHalfImageSize(GameObject* aSprite);

};

