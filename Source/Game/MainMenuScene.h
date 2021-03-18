#pragma once
#include "Scene.h"

class InputWrapper;
class UIObject;
class UIButton;

class MainMenuScene : public Scene
{
public:
    enum class eMainMenuButton
    {
        StartGame,
        LevelSelect,
        Options,
        ExitGame
    };

    MainMenuScene();

    void Load() override;

    void Activate() override;
    void Deactivate() override;

    void Update(const float& aDeltaTime) override;


private:
    std::unique_ptr<UIObject> myBackground;
    std::unique_ptr<UIObject> myTitleSprite;

    std::vector<UIButton*> myButtons;

    std::unique_ptr<UIButton> myNewGameBtn;
    std::unique_ptr<UIButton> myLevelSelectBtn;
    std::unique_ptr<UIButton> myOptionsBtn;
    std::unique_ptr<UIButton> myExitGameBtn;

    std::shared_ptr<InputWrapper> myInput;

    int myMovingIndex;

    void InitObjects();
    void UpdateObjects(const float& aDeltaTime);
    void CheckButtonsPress();

    void SetActiveMenu(const bool aStateBool);
    void CheckActiveAnimations();

};

