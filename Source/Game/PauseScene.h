#pragma once
#include "Scene.h"

namespace Utils
{
    class Input;
}

class UIManager;
class InputWrapper;

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


private:
    UIManager* myUIManager;
    GameObject* myBackGround;
    std::shared_ptr<InputWrapper> myInputHandler;


};

