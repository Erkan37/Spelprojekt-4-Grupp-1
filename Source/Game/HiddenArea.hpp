#pragma once
#include "GameObject.h"

class SpriteComponent;
class Scene;

class HiddenArea : public GameObject
{
public:
	HiddenArea(Scene* aLevelScene, const v2f& aPosition, const v2f& aSize);
	~HiddenArea();

	void Update(const float& aDeltaTime) override;

	void OnCollision(GameObject* aGameObject) override;

private:
	SpriteComponent* myHiddenSprite;
	float myOpacity;
	float myOpacityChangeSpeed;
	bool myPlayerCollided;

};

