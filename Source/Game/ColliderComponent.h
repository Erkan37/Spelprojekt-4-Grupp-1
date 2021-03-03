/*
*	Author: Elia Rönning
*/

#pragma once
#include "Component.hpp"
#include "Vector2.hpp"

class ColliderComponent :
    public Component
{
public:
    ColliderComponent();
    ColliderComponent(const ColliderComponent& aColliderComponent) = default;
    ~ColliderComponent();

    void Init(Transform& aTransform, GameObject& aGameObject);

    GameObject*& GetGameObject();

    const float& GetX() const;
    const float& GetY() const;
    const float& GetWidth() const;
    const float& GetHeight() const;

    const v2f GetPosition() const;
    const v2f GetSize() const;

    ColliderComponent& SetX(const float& anX);
    ColliderComponent& SetY(const float& aY);
    ColliderComponent& SetWidth(const float& aWidth);
    ColliderComponent& SetHeight(const float& aHeight);

    ColliderComponent& SetPosition(const v2f& aPosition);
    ColliderComponent& SetPosition(const float& anX, const float& aY);
    ColliderComponent& SetSize(const v2f& aSize);
    ColliderComponent& SetSize(const float& aWidth, const float& aHeight);

private:
    GameObject* myGameObject;

    float myX;
    float myY;
    float myWidth;
    float myHeight;
};

