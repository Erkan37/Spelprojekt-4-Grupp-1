#pragma once
#include "Scene.h"
#include <vector>
#include "Platform.h"
#include "BackGround.h"
#include "SpringObject.h"

#include "Subscriber.hpp"

class GameObject;

class LevelScene :
    public Scene, public Subscriber
{
public:
    LevelScene();

    void Load() override;

    void Activate() override;
    void Deactivate() override;

    void Update(const float& aDeltaTime) override;

    void Notify(const Message& aMessage) override;

    const GameObject* GetPlayer();
private:
    GameObject* myPlayer;
    Background* myBackground;

};

