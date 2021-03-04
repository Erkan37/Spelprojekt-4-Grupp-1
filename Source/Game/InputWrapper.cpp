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
	myController->CheckActiveController();
}

std::shared_ptr<Utils::Input> InputWrapper::GetInput()
{
	return myInput;
}
