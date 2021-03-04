#pragma once

class Player;
class PhysicsComponent;

class BashAbility
{
public:
	BashAbility();

	void Init();

	void Update();
	void Render();

	void AddPlayerPhysics(std::shared_ptr<Player> aPlayer);


private:
	std::shared_ptr<Player> myPlayer;
	PhysicsComponent* myPlayerPhysic;

};

