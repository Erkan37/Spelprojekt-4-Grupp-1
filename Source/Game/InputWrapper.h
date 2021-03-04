#pragma once
#include "Controller.h"


namespace Utils
{
	class Input;
}

class InputWrapper
{
public:
	InputWrapper();
	~InputWrapper() = default;

	void Init();

	void Update();

	std::shared_ptr<Utils::Input> GetInput();
	std::shared_ptr<Controller> GetController();

private:
	std::shared_ptr<Utils::Input> myInput;
	std::shared_ptr<Controller> myController;

};

