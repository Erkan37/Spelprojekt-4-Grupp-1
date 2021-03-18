#pragma once
#include "Scene.h"

class MainMenuScene : public Scene
{
public:

    MainMenuScene();

    void Load() override;

    void Activate() override;
    void Deactivate() override;

    void Update(const float& aDeltaTime) override;


private:



};

