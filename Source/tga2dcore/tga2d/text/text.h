/*
Use this class to create and show a text
*/

#pragma once
#include <tga2d/math/Color.h>
#include <tga2d/math/vector2.h>
#include <tga2d/render/render_common.h>
#include <string>
#include "..\Game\EFontsSizes.hpp"

namespace Tga2D
{
	class CTextService;
	class CCustomShaderBatched;
	class CText
	{
		friend class CTextService;
	public:
		// If this is the first time creating the text, the text will be loaded in memory, dont do this runtime

		/*aPathAndName: ex. taxe/arial.ttf, */
		CText(const char* aPathAndName = "Text/arial.ttf", EFontSize aFontSize = EFontSize_14, unsigned char aBorderSize = 0);
		~CText();
		void Render();
		void Render(Tga2D::CCustomShaderBatched* aCustomShaderToRenderWith);
		float GetWidth();
		float GetHeight();

		void SetColor(const CColor& aColor);
		CColor GetColor() const;

		void SetText(const std::string& aText);
		std::string GetText() const;

		void SetPosition(const VECTOR2F& aPosition);
		VECTOR2F GetPosition() const;

		void SetScale(float aScale);
		float GetScale() const;

		std::string GetPathAndName() const;

		void SetRotation(float aRotation) { myRotation = aRotation; }
		float GetRotation() const { return myRotation; }
		void SetFontSize(EFontSize aFontSize);
		
	protected:
		CTextService* myTextService;
		class CFontData* myFontDataPointer;
		std::string myPathAndName;
		std::string myText;
		VECTOR2F myPosition;
		float myScale;
		float myRotation;
		CColor myColor;
		
		
	};
}

