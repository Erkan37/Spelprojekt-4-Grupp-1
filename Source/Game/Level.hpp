#pragma once
class Scene;

class Level
{
public:
	Level(Scene* aScene, const int aID);
	~Level();

	void Activate();
	void Deactivate();

	Scene* GetScene();
	const int& GetID();
	const bool GetIsActive();

private:
	Scene* myScene;
	int myID;
	bool myIsActive;

};

