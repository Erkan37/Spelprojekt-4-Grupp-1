/*
*	Author: Elia Rönning
*/

#pragma once
#include "Component.hpp"
#include "../External/Headers/CU/Vector2.hpp"

class ColliderComponent;
class SpriteComponent;

class PhysicsComponent :
    public Component
{
public:
    PhysicsComponent(bool aApplyGravity = false, bool aIsStatic = false);
    PhysicsComponent(const PhysicsComponent& aComponent) = default;
    ~PhysicsComponent() = default;

    const bool& GetApplyGravity() const;
    const bool& GetIsStatic() const;
    const bool& GetCanCollide() const;
    const v2f& GetVelocity() const;
    const float& GetVelocityX() const;
    const float& GetVelocityY() const;
    const v2f& GetDashVelocity() const;

    PhysicsComponent& SetApplyGravity(const bool& aApplyGravity);
    PhysicsComponent& SetIsStatic(const bool& aIsStatic);
    PhysicsComponent& SetCanCollide(const bool& aCanCollide);
    PhysicsComponent& SetVelocity(const v2f& aVelocity);
    PhysicsComponent& SetVelocityX(const float& aVelocity);
    PhysicsComponent& SetVelocityY(const float& aVelocity);
    PhysicsComponent& SetDashVelocity(const v2f& aVelocity);

    // Does not take pivot into account.
    ColliderComponent* CreateColliderFromSprite(SpriteComponent* aSprite, GameObject* aGameObject) const;

private:
    v2f myVelocity;
    v2f myDashVelocity;

    bool myApplyGravity;
    bool myIsStatic;
    bool myCanCollide;
};

