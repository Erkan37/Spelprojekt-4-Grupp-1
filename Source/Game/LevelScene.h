#pragma once
#include "Scene.h"
#include <vector>
#include "Platform.h"

class GameObject;

class LevelScene :
    public Scene
{
public:
    LevelScene();

    void Load() override;

    void Activate() override;
    void Deactivate() override;

    void Update(const float& aDeltaTime) override;
private:
    GameObject* myPlayer;

};

