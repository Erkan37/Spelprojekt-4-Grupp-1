#include <memory>
#include "stdafx.h"
#include "InputWrapper.h"

#include "../External/Headers/CU/Utilities.h"

InputWrapper::InputWrapper()
{
	myController = {};
	myInput = {};
	myHoldDash = {};
	myMouseDirectionChanged = {};
}

void InputWrapper::Init()
{
	myController = std::make_shared<Controller>();
	myInput = std::make_shared<Utils::Input>();
	myController->Init();
}

void InputWrapper::Update(const float& aDeltaTime)
{
	CheckMousePosition();

	myInput->Update();
	myController->Update(aDeltaTime);
}

float InputWrapper::GetLeftPullForce()
{
	return std::abs(myController->LeftThumbStickPull());
}

float InputWrapper::GetRightPullForce()
{
	return std::abs(myController->RightThumbStickPull());
}

v2f InputWrapper::GetLeftStickMovement()
{
	return myController->GetLeftThumbStick();
}

v2f InputWrapper::GetRightStickMovement()
{
	return myController->GetRightThumbStick();
}

v2f InputWrapper::GetAxisMovement()
{
	v2f position = GetLeftStickMovement() + CalculateMouseAxis();
	v2f normalizedPosition = position.GetNormalized();
	
	return normalizedPosition;
}

bool InputWrapper::IsMovingUp()
{
	if (myInput->GetKeyDown(Keys::WKey) || GetController()->GetLeftThumbStick().y < 0 || GetController()->IsButtonHoldDown(Controller::Button::DPadUp))
		return true;
	else
		return false;
}

bool InputWrapper::IsMovingLeft()
{
	if (myInput->GetKeyDown(Keys::AKey) || GetController()->GetLeftThumbStick().x < 0 || GetController()->IsButtonHoldDown(Controller::Button::DPadLeft))
		return true;
	else
		return false;
}

bool InputWrapper::IsMovingDown()
{
	if (myInput->GetKeyDown(Keys::SKey) || GetController()->GetLeftThumbStick().y > 0 || GetController()->IsButtonHoldDown(Controller::Button::DPadDown))
		return true;
	else
		return false;
}

bool InputWrapper::IsMovingRight()
{
	if (myInput->GetKeyDown(Keys::DKey) || GetController()->GetLeftThumbStick().x > 0 || GetController()->IsButtonHoldDown(Controller::Button::DPadRight))
		return true;
	else
		return false;
}


bool InputWrapper::IsJumping()
{
	if (GetInput()->GetKeyJustDown(Keys::SPACEBAR) || GetInput()->GetKeyJustDown(Keys::WKey) ||GetController()->IsButtonPressed(Controller::Button::Cross))
		return true;
	else
		return false;
}

bool InputWrapper::IsDashing()
{
	if (GetInput()->GetKeyDown(Keys::SHIFTKey) || GetController()->IsButtonHoldDown(Controller::Button::Square))
	{
		if (!myHoldDash)
		{
			SetMousePosition();
			myHoldDash = true;
		}

		return true;
	}
	else
		return false;
}

bool InputWrapper::IsDashingReleased()
{
	if (GetInput()->GetKeyJustUp(Keys::SHIFTKey) || !GetController()->IsButtonHoldDown(Controller::Button::Square))
	{
		if (myHoldDash)
			myHoldDash = false;

		return true;
	}
	else
		return false;
}

std::shared_ptr<Utils::Input> InputWrapper::GetInput()
{
	return myInput;
}

std::shared_ptr<Controller> InputWrapper::GetController()
{
	return myController;
}

void InputWrapper::SetCursorToMiddle()
{
	HMONITOR monitor = MonitorFromWindow(*Tga2D::CEngine::GetInstance()->GetHWND(), MONITOR_DEFAULTTONEAREST);
	MONITORINFO info;
	info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &info);

	POINT cursor;
	GetCursorPos(&cursor);

	int pixels = 30;
	int width = static_cast<int>(info.rcMonitor.right);
	int height = static_cast<int>(info.rcMonitor.bottom);

	if (cursor.x >= width - pixels || cursor.y >= height - pixels || cursor.x <= pixels || cursor.y <= pixels)
		SetCursorPos(width / 2, height / 2);

}

void InputWrapper::CheckMousePosition()
{
	if (myHoldDash)
	{
		SetCursorToMiddle();

		if (static_cast<int>(myInput->GetMouseMovementSinceLastUpdate().y) < 0 && myMouseDirectionChanged == false)
		{
			myMouseDirectionChanged = true;
			SetMousePosition();
		}
		else if (static_cast<int>(myInput->GetMouseMovementSinceLastUpdate().y) > 0 && myMouseDirectionChanged)
		{
			myMouseDirectionChanged = false;
			SetMousePosition();
		}
	}
}

void InputWrapper::SetMousePosition()
{
	myPreviousMousePosition.x = static_cast<float>(myInput->GetMousePosition().x);
	myPreviousMousePosition.y = static_cast<float>(myInput->GetMousePosition().y);
}


v2f InputWrapper::CalculateMouseAxis()
{
	myNewMousePosition.x = static_cast<float>(myInput->GetMousePosition().x);
	myNewMousePosition.y = static_cast<float>(myInput->GetMousePosition().y);

	v2f mouseDistance = myNewMousePosition - myPreviousMousePosition;
	v2f normalizedDistance = mouseDistance.GetNormalized();

	myNewMousePosition = {};
	myPreviousMousePosition = {};

	return normalizedDistance;
}
