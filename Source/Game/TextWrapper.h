#pragma once

#include "GameObject.h"

#include "..\tga2dcore\tga2d\math\color.h"

#include <memory>

namespace Tga2D
{
	class CColor;
	class CText;
	class CFontData;
}

class TextWrapper : public GameObject
{
public:

	enum EFontSize
	{
		EFontSize_6 = 6,
		EFontSize_8 = 8,
		EFontSize_9 = 9,
		EFontSize_10 = 10,
		EFontSize_11 = 11,
		EFontSize_12 = 12,
		EFontSize_14 = 14,
		EFontSize_18 = 18,
		EFontSize_24 = 24,
		EFontSize_30 = 30,
		EFontSize_36 = 36,
		EFontSize_48 = 48,
		EFontSize_60 = 60,
		EFontSize_72 = 72,
		EFontSize_Count
	};

	TextWrapper(const std::string& aPathAndName = "Text/arial.ttf", EFontSize aFontSize = EFontSize::EFontSize_14, unsigned char aBorderSize = 0);
	virtual ~TextWrapper();

	void Update(const float& aDeltaTime) override;
	void Render() override;

	void SetColor(const Tga2D::CColor& aColor);
	Tga2D::CColor GetColor() const;

	void SetText(const std::string& aText);
	std::string GetText() const;

	void SetPosition(const v2f& aPosition);
	v2f GetPosition() const;

	void SetScale(float aScale);
	float GetScale() const;

	void SetRotation(float aRotation);
	float GetRotation() const;

	void SetPivot(v2f aPivot);
	v2f GetPivot() const;

	Tga2D::CFontData* GetFontDataPointer();

private:

	Tga2D::CColor myColor{ 1.0f, 1.0f, 1.0f, 1.0f };

	std::string myText;

	v2f myPosition{};
	v2f myPivot{ 0.0f, 0.0f };
	float myScale{ 1.0f };
	float myRotation{};

	Tga2D::CFontData* myFontDataPointer{};

};
