#pragma once
#include "Scene.h"

class GameObject;
class SpriteComponent;
enum class eIntroLogo;

class IntroLogosScene : public Scene
{
public:
	IntroLogosScene();
	~IntroLogosScene();

	void Load() override;
	void Update(const float &aDeltaTime) override;

	void DisplayLogo(const eIntroLogo anEnum);

private:
	GameObject* myLogo;
	SpriteComponent* mySpriteComponent;
	float myTimeSinceInited;
	float myTotalLogoTime;

};
