#pragma once


namespace Utils
{
	class Input;
}

class Controller;


class InputWrapper
{
public:
	InputWrapper();

	void Init();

	void Update();

	std::shared_ptr<Utils::Input> GetInput();



private:
	std::shared_ptr<Utils::Input> myInput;
	std::shared_ptr<Controller> myController;

};

