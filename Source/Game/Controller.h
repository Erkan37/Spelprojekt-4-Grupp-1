#pragma once
#include <Xinput.h>

class Controller
{
public:
	enum class Button
	{
		Cross = 0x1000,
		Square = 0x4000,
		Triangle = 0x8000,
		Circle = 0x2000,

		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000,

		DPadUp = 0x0001,
		DPadDown = 0x0002,
		DPadLeft = 0x0004,
		DPadRight = 0x0008,

		LShoulder = 0x0100,
		RShoulder = 0x0200,

		LThumbStick = 0x0040,
		RThumbStick = 0x0080,

		Start = 0x0010,
		Back = 0x0020
	};

	Controller();

	void Init();

	void Update();

	bool IsButtonPressed(Button aButton);

	bool IsRightTriggerActive();
	bool IsLeftTriggerActive();

	bool IsLeftThumbActiveThisFrame();
	bool IsRightThumbActive();
	bool IsControllerActive();
	bool CheckActiveController();

	Tga2D::Vector2f GetLeftThumbStick() const;
	Tga2D::Vector2f GetRightThumbStick() const;

	float LeftThumbStickPull() const;
	float RightThumbStickPull() const;

	void SetRightThumbActive(bool aActiveStatement);
	void SetLeftThumbActiveThisFrame(bool aStatement);



private:
	XINPUT_STATE myCurrentControllerState;

	int myControllerState;
	int myControllerID;

	float myleftThumbStickPull;
	float myRightThumbStickPull;

	bool myActiveController;
	bool myActiveRightThumb;
	bool myLastFrameActive;
	bool myLastButtonReleased;

	Tga2D::Vector2f myLeftThumbStick;
	Tga2D::Vector2f myRightThumbStick;

	void UpdateLeftThumbStick(XINPUT_STATE& aState);
	void UpdateRightThumbStick(XINPUT_STATE& aState);

};

