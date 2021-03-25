#pragma once
#include "GameObject.h"
#include "Button.h"

class Animation;
class SpriteComponent;
class Scene;

class Door : public GameObject
{
public:
	Door(Scene* aLevelScene);

	void Init(const v2f aPosition);

	void Update(const float& aDeltaTime) override;
	void AddButton(const v2f aPosition);
	
private:
	SpriteComponent* myClosedDoorSprite;
	SpriteComponent* myOpenDoorSprite;
	Button* myButton;

	v2f mySize;

	bool myDoorIsOpen;

};

