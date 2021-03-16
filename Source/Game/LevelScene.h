#pragma once
#include "Scene.h"
#include <vector>
#include "Platform.h"
#include "BackGround.h"
#include "SpringObject.h"
#include "PauseMenu.h"

class GameObject;
class TiledMap;

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
    std::unique_ptr<TiledMap> myTiledMap;
    std::unique_ptr<PauseMenu> myPauseMenu;
};

