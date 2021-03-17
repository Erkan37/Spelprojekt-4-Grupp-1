#include "stdafx.h"
#include "TextWrapper.h"

// Forward declare here since tga2d/text/text_service.h apparently does not...
struct ID3D11ShaderResourceView;
class CSpriteBatch;

#include <tga2d/text/text.h>
#include <tga2d/text/text_service.h>

TextWrapper::TextWrapper(const std::string& aPathAndName, EFontSize aFontSize, unsigned char aBorderSize)
{
	myFontDataPointer = Tga2D::CEngine::GetInstance()->GetTextService().InitAndLoad(aPathAndName, aBorderSize, static_cast<int>(aFontSize));
}

TextWrapper::~TextWrapper()
{
	Tga2D::CEngine* engine = Tga2D::CEngine::GetInstance();
	if (!engine)
		return;

	if (myFontDataPointer)
	{
		engine->GetTextService().RemoveFontRef(myFontDataPointer);

		myFontDataPointer = nullptr;
	}
}

void TextWrapper::Update(const float& aDeltaTime)
{
}

void TextWrapper::Render()
{
}

void TextWrapper::SetColor(const Tga2D::CColor& aColor)
{
	myColor = aColor;
}

Tga2D::CColor TextWrapper::GetColor() const
{
	return myColor;
}

void TextWrapper::SetText(const std::string& aText)
{
	myText = aText;
}

std::string TextWrapper::GetText() const
{
	return myText;
}

void TextWrapper::SetPosition(const VECTOR2F& aPosition)
{
	myPosition = aPosition;
}

VECTOR2F TextWrapper::GetPosition() const
{
	return myPosition;
}

void TextWrapper::SetScale(float aScale)
{
	myScale = aScale;
}

float TextWrapper::GetScale() const
{
	return myScale;
}

void TextWrapper::SetRotation(float aRotation)
{
	myRotation = aRotation;
}

float TextWrapper::GetRotation() const
{
	return myRotation;
}

void TextWrapper::SetPivot(VECTOR2F aPivot)
{
	myPivot = aPivot;
}

VECTOR2F TextWrapper::GetPivot() const
{
	return myPivot;
}

Tga2D::CFontData* TextWrapper::GetFontDataPointer()
{
	return myFontDataPointer;
}
