#pragma once
#include "Scene.h"
#include <vector>

class GameObject;

class LevelScene :
    public Scene
{
public:
    LevelScene();

    void Load() override;

    void Activate() override;
    void Deactivate() override;

    void Update(const float& aDeltaTime, const float& aTotalTime) override;
private:
    GameObject* myPlayer;
    GameObject* myBackground;

    GameObject* myGround;
};

