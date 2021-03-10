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


private:
	Animation myAnimations[2];

	void InitButton(v2f aButtonPosition);

};

