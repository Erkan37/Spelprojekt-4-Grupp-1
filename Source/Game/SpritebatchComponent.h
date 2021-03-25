/*
*	Author: Elia Rönning
*/

#pragma once
#include "Component.hpp"
#include <vector>

class SpriteComponent;
namespace Tga2D
{
    class CSpriteBatch;
}

class SpritebatchComponent :
    public Component
{
public:
    SpritebatchComponent();
    SpritebatchComponent(const SpritebatchComponent& aSpritebatch) = default;
    ~SpritebatchComponent();

    void Init();
    void Render(Transform& aTransform, GameObject& aGameObject) override;

    SpritebatchComponent& SetSpritePath(const std::string& aSpritePath);
    const std::string GetSpritePath() const;
    SpritebatchComponent& AddSprite(SpriteComponent* aSprite);

    void SetBlendState(const EBlendState aBlendState);
    const EBlendState& GetBlendState() const;

    void SetSamplerFilter(const ESamplerFilter& aSamplerFilter);
    const ESamplerFilter& GetSamplerFilter() const;

    void SetOpacity(const float& aOpacity);

private:
    void Reset();

    std::vector<SpriteComponent*> mySprites;
    Tga2D::CSpriteBatch* myBatch;

    std::string mySpritePath;

    EBlendState myBlendState;
    ESamplerFilter mySamplerFilter;

    float myOpacity;
};