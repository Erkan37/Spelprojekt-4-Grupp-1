#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"
#include <string>
#include <vector>



class ButtonManager :
    public GameObject
{
public:
    ButtonManager(Scene* aScene);
    ~ButtonManager();
    void Init();

    void Render();
    void Update(const float& aDeltaTime);
    void NextColumn(const int aModifier);
    void NextRow(const int aModifier);
    void SetButtonZIndex(const int aZ);
    void SetColumns(const int aColumn);
    void SetDistance(const float aTop, const float aBot, const float aLeft, const float aRight);
    void SetSize(const Tga2D::Vector2f& aSize);
    void UpdatePosition();
    void AddButton(GameObject* aMenuButton);
    void UpdateIndex(const int aModifier);
    
    int GetIndex();

    GameObject* SelectButton();

    GameObject* myHighlight;
private:
    std::vector<GameObject*> myButtons;



    int myColumns;
    int myIndex;

    float myMaxX;
    float myMaxY;
    float myMinX;
    float myMinY;

};

