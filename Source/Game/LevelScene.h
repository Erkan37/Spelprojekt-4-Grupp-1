#pragma once
#include "Scene.h"
#include <vector>
#include "Platform.h"
#include "BackGround.h"
#include "SpringObject.h"
#include "ParticleEffectFactory.h"

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

    GameObject* GetPlayer();
private:
    GameObject* myPlayer;
    GameObject* myEnemy;

    std::unique_ptr<ParticleEffectFactory> myFactory;
    std::unique_ptr<Background> myBackground;
    std::unique_ptr<SpringObject> mySpring;

};

