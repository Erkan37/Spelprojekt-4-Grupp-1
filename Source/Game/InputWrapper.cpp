#include <memory>
#include "stdafx.h"
#include "InputWrapper.h"

#include "../External/Headers/CU/Utilities.h"

InputWrapper::InputWrapper()
{
	myController = {};
	myInput = {};
}

void InputWrapper::Init()
{
	myController = std::make_shared<Controller>();
	myInput = std::make_shared<Utils::Input>();
	myController->Init();
}

void InputWrapper::Update()
{
	myInput->Update();
	myController->Update();
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

bool InputWrapper::IsMovingUp()
{
	if (myInput->GetKeyDown(Keys::WKey) || myController->GetLeftThumbStick().y < 0 || GetController()->IsButtonHoldDown(Controller::Button::DPadUp))
		return true;
	else
		return false;
}

bool InputWrapper::IsMovingLeft()
{
	if (myInput->GetKeyDown(Keys::AKey) || myController->GetLeftThumbStick().x < 0 || GetController()->IsButtonHoldDown(Controller::Button::DPadLeft))
		return true;
	else
		return false;
}

bool InputWrapper::IsMovingDown()
{
	if (myInput->GetKeyDown(Keys::SKey) || myController->GetLeftThumbStick().y > 0 || GetController()->IsButtonHoldDown(Controller::Button::DPadDown))
		return true;
	else
		return false;
}

bool InputWrapper::IsMovingRight()
{
	if (myInput->GetKeyDown(Keys::DKey) || myController->GetLeftThumbStick().x > 0 || GetController()->IsButtonHoldDown(Controller::Button::DPadRight))
		return true;
	else
		return false;
}


bool InputWrapper::IsJumping()
{
	if (GetInput()->GetKeyJustDown(Keys::SPACEBAR) || GetController()->IsButtonPressed(Controller::Button::Cross))
		return true;
	else
		return false;
}

bool InputWrapper::IsDashing()
{
	if (GetInput()->GetKeyJustDown(Keys::SHIFTKey) || GetController()->IsButtonPressed(Controller::Button::Square))
		return true;
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
