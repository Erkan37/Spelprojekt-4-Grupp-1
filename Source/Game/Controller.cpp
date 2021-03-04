#include "stdafx.h"
#include "Controller.h"

#pragma comment(lib, "Xinput9_1_0.lib")
#pragma comment(lib, "XInput.lib")

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30

struct ActiveButtons
{
private: bool myCross = {};
private: bool mySquare = {};
private: bool myTriangle = {};
private: bool myCircle = {};

private: bool myDpadUp = {};
private: bool myDpadDown = {};
private: bool myDpadLeft = {};
private: bool myDpadRight = {};

private: bool myLShoulder = {};
private: bool myRShoulder = {};

private: bool myLThumbStick = {};
private: bool myRThumbStick = {};

private: bool myStart = {};
private: bool myBack = {};

public: bool ActiveButton(Controller::Button aButton)
	{
		switch (aButton)
		{
		case Controller::Button::Cross: { if (myCross) return false; else { myCross = true; return true; break; } }
		case Controller::Button::Circle: { if (myCircle) return false; else { myCircle = true; return true; break; } }
		case Controller::Button::Triangle: { if (myTriangle) return false; else { myTriangle = true; return true; break; } }
		case Controller::Button::Square: { if (mySquare) return false; else { mySquare = true; return true; break; } }
		case Controller::Button::DPadDown: { if (myDpadDown) return false; else { myDpadDown = true; return true; break; } }
		case Controller::Button::DPadLeft: { if (myDpadLeft) return false; else { myDpadLeft = true; return true; break; } }
		case Controller::Button::DPadRight: { if (myDpadRight) return false; else { myDpadRight = true; return true; break; } }
		case Controller::Button::DPadUp: { if (myDpadUp) return false; else { myDpadUp = true; return true; break; } }
		case Controller::Button::LShoulder: { if (myLShoulder) return false; else { myLShoulder = true; return true; break; } }
		case Controller::Button::RShoulder: { if (myRShoulder) return false; else { myRShoulder = true; return true; break; } }
		case Controller::Button::LThumbStick: { if (myLThumbStick) return false; else { myLThumbStick = true; return true; break; } }
		case Controller::Button::RThumbStick: {	if (myRThumbStick) return false; else { myRThumbStick = true; return true; break; } }
		case Controller::Button::Start: { if (myStart) return false; else { myStart = true; return true; break; } }
		case Controller::Button::Back: { if (myBack) return false; else { myBack = true; return true; break; } }
		default: return false; break;
		}
	}

public: void LastButtonReleased(Controller::Button aButton)
	{
		switch (aButton)
		{
		case Controller::Button::Cross: { myCross = false; break; }
		case Controller::Button::Circle: { myCircle = false; break; }
		case Controller::Button::Triangle: { myTriangle = false; break; }
		case Controller::Button::Square: { mySquare = false; break; }
		case Controller::Button::DPadDown: { myDpadDown = false; break; }
		case Controller::Button::DPadLeft: { myDpadLeft = false; break; }
		case Controller::Button::DPadRight: { myDpadRight = false; break; }
		case Controller::Button::DPadUp: { myDpadUp = false; break; }
		case Controller::Button::LShoulder: { myLShoulder = false; break; }
		case Controller::Button::RShoulder: { myRShoulder = false; break; }
		case Controller::Button::LThumbStick: { myLThumbStick = false; break; }
		case Controller::Button::RThumbStick: {	myRThumbStick = false; break; }
		case Controller::Button::Start: { myStart = false; break; }
		case Controller::Button::Back: { myBack = false; break; }
		default: break;
		}
	}

};

ActiveButtons myActiveButtons;

Controller::Controller()
{
	myLastFrameActive = {};
	myControllerState = {};
	myActiveController = {};
	myControllerID = -1;
	myLeftThumbStick = {};
	myRightThumbStick = {};
	myleftThumbStickPull = {};
	myRightThumbStickPull = {};
	myActiveRightThumb = {};
	myCurrentControllerState = {};
	myLastButtonReleased = {};
}

void Controller::Init()
{
	CheckActiveController();
}

void Controller::Update()
{
	if (IsControllerActive())
	{
		ZeroMemory(&myCurrentControllerState, sizeof(XINPUT_STATE));
		XInputGetState(myControllerID, &myCurrentControllerState);

		if (myCurrentControllerState.dwPacketNumber != 0)
		{
			UpdateLeftThumbStick(myCurrentControllerState);
			UpdateRightThumbStick(myCurrentControllerState);
		}
		else
		{
			myActiveController = false;
		}
	}
	else
		CheckActiveController();
}

bool Controller::IsButtonPressed(Button aButton)
{
	if (IsControllerActive())
	{
		if ((myCurrentControllerState.Gamepad.wButtons & static_cast<WORD>(aButton)) != 0)
		{
			return myActiveButtons.ActiveButton(aButton);
		}
		else
		{
			myActiveButtons.LastButtonReleased(aButton);
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Controller::IsButtonHoldDown(Button aButton)
{
	if (IsControllerActive())
	{
		return (myCurrentControllerState.Gamepad.wButtons & static_cast<WORD>(aButton)) != 0;
	}
	else
		return false;
}

bool Controller::IsRightTriggerActive()
{
	if (myCurrentControllerState.Gamepad.bRightTrigger) { return true; }
	else { return false; }
}

bool Controller::IsLeftTriggerActive()
{
	if (myCurrentControllerState.Gamepad.bLeftTrigger) { return true; }
	else { return false; }
}


v2f Controller::GetLeftThumbStick() const
{
	if (myActiveController)
		return myLeftThumbStick;
	else
		return v2f(0, 0);
}

v2f Controller::GetRightThumbStick() const
{
	if (myActiveController)
		return myRightThumbStick;
	else
		return v2f(0, 0);
}

float Controller::LeftThumbStickPull() const
{
	if (myActiveController)
		return myleftThumbStickPull;
	else
		return float(0.f);
}

float Controller::RightThumbStickPull() const
{
	if (myActiveController)
		return myRightThumbStickPull;
	else
		return float(0.f);
}

void Controller::SetRightThumbActive(bool aActiveStatement)
{
	myActiveRightThumb = aActiveStatement;
}

void Controller::SetLeftThumbActiveThisFrame(bool aStatement)
{
	myLastFrameActive = aStatement;
}

bool Controller::IsLeftThumbActiveThisFrame()
{
	return myLastFrameActive;
}

bool Controller::IsRightThumbActive()
{
	return myActiveRightThumb;
}

bool Controller::IsControllerActive()
{
	return myActiveController;
}

void Controller::UpdateLeftThumbStick(XINPUT_STATE& aState)
{

	float leftX = aState.Gamepad.sThumbLX;
	float leftY = aState.Gamepad.sThumbLY;

	float magnitude = sqrt(leftX * leftX + leftY * leftY);

	float normalizedLX = leftX / magnitude;
	float normalizedLY = -(leftY / magnitude);

	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		if (magnitude > 32767) magnitude = 32767;

		magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

		myleftThumbStickPull = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		myLeftThumbStick = { normalizedLX, normalizedLY };

	}
	else
	{
		myleftThumbStickPull = 0.f;
		myLeftThumbStick = { 0.f, 0.f };
	}

}

void Controller::UpdateRightThumbStick(XINPUT_STATE& aState)
{

	float rightX = aState.Gamepad.sThumbRX;
	float rightY = aState.Gamepad.sThumbRY;


	float magnitude = sqrt(rightX * rightX + rightY * rightY);

	float normalizedLX = rightX / magnitude;
	float normalizedLY = -(rightY / magnitude);

	if (magnitude > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		if (magnitude > 32767) magnitude = 32767;

		magnitude -= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

		myRightThumbStickPull = magnitude / (32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		myRightThumbStick = { normalizedLX, normalizedLY };

	}
	else
	{
		myRightThumbStickPull = 0.f;
		myRightThumbStick = { 0.f, 0.f };
	}

}

bool Controller::CheckActiveController()
{
	XInputGetState(myControllerID, &myCurrentControllerState);

	if (myCurrentControllerState.dwPacketNumber != 0)
	{
		myActiveController = true;
		return true;
	}
	else
	{
		myActiveController = false;
		myControllerID = -1;
	}

	DWORD dwResult{};

	for (DWORD i = 0; i < 1; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			myCurrentControllerState = state;
			myControllerID = i;
			return true;
			break;
		}
	}

	return false;
}
