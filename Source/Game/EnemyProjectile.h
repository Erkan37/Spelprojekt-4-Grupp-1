#pragma once

class GameObject;
class EnemyProjectile : public GameObject
{
public:
	EnemyProjectile(Scene* aScene);
	~EnemyProjectile() = default;
	void InitProjectile(const v2f& aPosition, const v2f& aTarget);

	void Update(const float& aDeltaTime) override;
	void OnCollision(GameObject* aGameObject) override;

private:
	void InitCollider();
	v2f mySize = {10.0f, 10.0f};
	v2f myDirection;
	const float mySpeed = 300.0f;
};

