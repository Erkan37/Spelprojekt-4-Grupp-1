#pragma once
#include "GameObject.h"
#include "..\External\Headers\CU\Vector4.hpp"

class Camera;
class Scene;
class Player;

class UIButton : public GameObject
{
public:
	UIButton(Scene* aLevelScene);
	~UIButton();

	void Init(const std::string aPathString, const v2f aSize, const v2f aPosition);

	void UpdateButton(const float& aDeltaTime);
	void Render() override;

	void SetIsHighlightActive(const bool aHighlightBool);
	void SetLightedColor(const v4f aColor);
	void SetActive(const bool aActiveState);


private:
	Camera& myCamera;

	bool myBtnHighlighted;
	bool myIsActive;

	v4f myOriginalColor;
	v4f myHighlightedColor;

	v2f myPosition;

};

