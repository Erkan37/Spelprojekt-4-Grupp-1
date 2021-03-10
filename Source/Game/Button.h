#pragma once
#include "GameObject.h"
#include "Animation.hpp"

class AnimationComponent;
class SpriteComponent;
class LevelScene;

class Button : GameObject
{
public:

	Button(Scene* aLevelScene);
	~Button();

	void Init();

	void Update(const float& aDeltaTime) override;
	void OnCollision(GameObject* myGameObject) override;

	bool GetActiveButton();


private:
	Animation myAnimation[2];

	bool myButtonActive;
	bool myHasCollided;

	void InitButton(v2f aButtonPosition);

};

