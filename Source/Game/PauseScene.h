#pragma once
#include "Scene.h"

namespace Utils
{
    class Input;
}

namespace Tga2D
{
    class CText;
}

class UIManager;
class InputWrapper;
class ButtonManager;

class PauseScene :
    public Scene
{
public:
    PauseScene();
    ~PauseScene();

    void Load();
    void Unload();
    
    void Activate();
    void Deactivate();

    void Update(const float& aDeltaTime, const float& aTotalTime);

    //void ImguiUpdate();

private:
    UIManager* myUIManager;
    ButtonManager* myButtonManager;
    GameObject* myBackGround;
    GameObject* myPauseTitle;


    std::shared_ptr<InputWrapper> myInputHandler;

    float myTitlePositionX;
    float myTitlePositionY;


    void SelectButton();
};

