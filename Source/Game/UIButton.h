#pragma once
#include "GameObject.h"

class Scene;
class Player;

class UIButton : public GameObject
{
public:
	UIButton(Scene* aLevelScene);

	void Init(const std::string aPathString, const v2f aSize);

	void Update(const float& aDeltaTime);


private:
	Scene* myScene;
	Player* myPlayer;

};

