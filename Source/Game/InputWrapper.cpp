#include <memory>
#include "stdafx.h"
#include "InputWrapper.h"
#include <iostream>

#include "../External/Headers/CU/Utilities.h"

InputWrapper::InputWrapper()
{
	myController = {};
	myInput = {};
	myHoldDash = {};
	myMouseDirectionChanged = {};
	myMouseDirection = {};
}

void InputWrapper::Init()
{
	myMouseSensitivityX = 4.f;
	myMouseSensitivityY = 4.f;
	myController = std::make_shared<Controller>();
	myInput = std::make_shared<Utils::Input>();
	myController->Init();
}

void InputWrapper::Update(const float& aDeltaTime)
{
	myInput->Update();
	myController->Update(aDeltaTime);
	CheckMousePosition(aDeltaTime);
	CalculateMouseAxis();
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

v2f InputWrapper::GetMouseAxisMovement()
{
	//return myMouseDirection;
	return myNormalizedDirection;
}

v2f InputWrapper::GetAxisMovement()
{
	if (GetLeftStickMovement().x > 0.f || GetLeftStickMovement().x < 0.f)
	{
		return GetLeftStickMovement();
	}
	else
		return GetMouseAxisMovement();
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
			SetCursorMiddle();
			myHoldDash = true;
			SetMousePosition();
		}

		return true;
	}
	else
	{
		myNormalizedDirection = {};
		myHoldDash = false;
		return false;
	}
}

bool InputWrapper::IsDashingReleased()
{
	if (GetInput()->GetKeyJustUp(Keys::SHIFTKey) || !GetController()->IsButtonHoldDown(Controller::Button::Square))
	{
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

void InputWrapper::SetCursor()
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

	myScreenSize.x = static_cast<float>(width);
	myScreenSize.y = static_cast<float>(height);

	if (cursor.x >= width - pixels || cursor.y >= height - pixels || cursor.x <= pixels || cursor.y <= pixels)
	{
	///*	myPreviousMousePosition.x = cursor.x;
	//	myPreviousMousePosition.y = cursor.y;*/

	//	myMouseAfterLeftScreenDirection.x = cursor.x - myPreviousMousePosition.x;
	//	myMouseAfterLeftScreenDirection.y = cursor.y - myPreviousMousePosition.y;

	//	//myMouseAfterLeftScreenDirection.Normalize();

	//	myPreviousMousePosition.x = myMouseAfterLeftScreenDirection.x;
	//	myPreviousMousePosition.y = myMouseAfterLeftScreenDirection.y;

		SetCursorMiddle();
	}

}

void InputWrapper::CheckMousePosition(const float& aDeltaTime)
{
	if (myHoldDash)
	{
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

		/*if (static_cast<int>(myInput->GetMouseMovementSinceLastUpdate().y) < 0)
		{
			myMouseDirection.y = Utils::Lerp(myMouseDirection.y, -1.f, 0.1f + myMouseSensitivityX * aDeltaTime);
		}
		else if (static_cast<int>(myInput->GetMouseMovementSinceLastUpdate().y) > 0)
		{
			myMouseDirection.y = Utils::Lerp(myMouseDirection.y, 1.f, 0.1f + myMouseSensitivityX * aDeltaTime);
		}
		else if (static_cast<int>(myInput->GetMouseMovementSinceLastUpdate().x) < 0)
		{
			myMouseDirection.x = Utils::Lerp(myMouseDirection.x, -1.f, 0.1f + myMouseSensitivityX * aDeltaTime);
		}
		else if (static_cast<int>(myInput->GetMouseMovementSinceLastUpdate().x) > 0)
		{
			myMouseDirection.x = Utils::Lerp(myMouseDirection.x, 1.f, 0.1f + myMouseSensitivityX * aDeltaTime);
			
		}

		std::cout << myMouseDirection.x << std::endl;*/
		//std::cout << "REACHED" << std::endl;

		SetCursor();
	}
}

void InputWrapper::SetMousePosition()
{
	myPreviousMousePosition.x = static_cast<float>(myInput->GetMousePosition().x);
	myPreviousMousePosition.y = static_cast<float>(myInput->GetMousePosition().y);
}


void InputWrapper::CalculateMouseAxis()
{
	myNewMousePosition.x = static_cast<float>(myInput->GetMousePosition().x);
	myNewMousePosition.y = static_cast<float>(myInput->GetMousePosition().y);

	v2f mouseDistance = myNewMousePosition - myPreviousMousePosition;
	myNormalizedDirection = mouseDistance.GetNormalized();

	myNewMousePosition = {};
}

void InputWrapper::SetCursorMiddle()
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

	SetCursorPos(width / 2.f, height / 2.f);
}
