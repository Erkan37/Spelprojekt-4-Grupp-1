#pragma once
#include "Scene.h"

class UIObject;

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


};

