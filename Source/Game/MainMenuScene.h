#pragma once
#include "Scene.h"

class UIObject;
class UIButton;

class MainMenuScene : public Scene
{
public:

    MainMenuScene();

    void Load() override;

    void Activate() override;
    void Deactivate() override;

    void Update(const float& aDeltaTime) override;


private:
    std::unique_ptr<UIObject> myBackground;

    std::vector<UIButton*> myButtons;

    std::unique_ptr<UIButton> myNewGameBtn;
    std::unique_ptr<UIButton> myLevelSelectBtn;
    std::unique_ptr<UIButton> myOptionsBtn;
    std::unique_ptr<UIButton> myExitGameBtn;


    void InitObjects();
    void UpdateObjects(const float& aDeltaTime);

};

