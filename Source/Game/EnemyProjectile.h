#pragma once

class GameObject;
class EnemyProjectile : public GameObject
{
public:
	EnemyProjectile(Scene* aScene, const v2f& aPosition, const v2f& aTarget);
	~EnemyProjectile() = default;
	void SetDirection(const v2f& aPosition, const v2f& aTarget);
	void InitCollider();
	void InitVisuals();
	void Update(const float& aDeltaTime) override;
	void OnCollision(GameObject* aGameObject) override;

private:
	v2f mySpriteSize = { 10.0f, 10.0f };
	v2f myColliderSize = {10.0f, 10.0f};
	v2f myDirection;
	const float mySpeed = 300.0f;
};

