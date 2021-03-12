#pragma once
#include "Scene.h"
#include <vector>
#include "Platform.h"
#include "BackGround.h"
#include "SpringObject.h"

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

    const GameObject* GetPlayer();
private:
    GameObject* myPlayer;
    GameObject* myEnemy;
    std::unique_ptr<Background> myBackground;
    std::unique_ptr<SpringObject> mySpring;

};

