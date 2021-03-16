#pragma once
#include "GameObject.h"
#include "UIButton.h"

class SpriteComponent;
class InputWrapper;
class Scene;

class PauseMenu : public GameObject
{
public:
	PauseMenu(Scene* aLevelScene);

	void Init() override;

	void Update(const float& aDeltaTime) override;
	void Render() override;


private:
	Scene* myScene;
	Camera& myCamera;

	v2f myPosition;

	std::vector<UIButton*> myButtons;

	SpriteComponent* myBackground;
	std::unique_ptr<UIButton> myContinueBtn;
	std::unique_ptr<UIButton> myLevelSelectBtn;
	std::unique_ptr<UIButton> myMainMenuBtn;

	std::shared_ptr<InputWrapper> myInput;

};

