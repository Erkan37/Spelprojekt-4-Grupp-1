#pragma once
#include "Scene.h"
#include <vector>
#include "Platform.h"
#include "BackGround.h"
#include "SpringObject.h"
#include "PauseMenu.h"

#include "Subscriber.hpp"

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

    void AddBlackScreen();
    void DecreaseBlackScreen();
    void IncreaseBlackScreen();
    const bool GetReachedFullOpacity();
    void Transitioning();

    const GameObject* GetPlayer();
private:
    GameObject* myBlackScreen;
    GameObject* myPlayer;
    Background* myBackground;
    PauseMenu* myPauseMenu;

    float myBlackScreenOpacity;
    float myBlackScreenOpacitySpeed;

    bool myReachedFullOpacity;
    bool myIsTransitioning;

};

