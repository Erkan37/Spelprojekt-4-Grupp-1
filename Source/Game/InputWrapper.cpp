#include "stdafx.h"

#include "InputWrapper.h"
#include <memory>
#include "Controller.h"
#include "../External/Headers/CU/Utilities.h"

InputWrapper::InputWrapper()
{
}

void InputWrapper::Init()
{
	myController = std::make_shared<Controller>();
	myController->Init();
	myInput = std::make_shared<Utils::Input>();
}

void InputWrapper::Update()
{
}

std::shared_ptr<Utils::Input> InputWrapper::GetInput()
{
	return myInput;
}
