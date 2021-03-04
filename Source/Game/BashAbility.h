#pragma once

class InputWrapper;
class Player;
class PhysicsComponent;

class BashAbility : public GameObject
{
public:
	BashAbility();

	void Init();

	void Update();
	void Render();

	void AddPlayerPhysics(const std::shared_ptr<PhysicsComponent> somePhysics);
	void AddInputWrapper(const std::shared_ptr<InputWrapper> aInputWrapper);

private:
	std::shared_ptr<PhysicsComponent> myPhysics;
	std::shared_ptr<InputWrapper> myInput;

};

