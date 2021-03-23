/*
*	Author: Elia Rönning
*/

#pragma once
#include "../External/Headers/CU/Vector2.hpp"

class GameObject;

class Camera
{
public:
	Camera();
	Camera(const Camera& aCamera) = delete;
	~Camera() = default;

	void Update(const float& aDeltaTime);

	/* Getters */
	const v2f GetPosition() const;
	const float& GetPositionX() const;
	const float& GetPositionY() const;
	const float& GetAlpha() const;

	/* Setters */
	Camera& SetPosition(const v2f& aPosition);
	Camera& SetPositionX(const float& anX);
	Camera& SetPositionY(const float& aY);
	Camera& SetAlpha(const float& anAlpha);

	/* Camera Follow */
	const bool& IsFollowing() const;
	GameObject*& GetTarget();
	const v2f& GetOffset() const;
	const v2f& GetLerp() const;
	const v2f& GetTargetPosition() const;

	Camera& SetTarget(GameObject*& aTarget);
	Camera& SetOffset(const v2f& anOffset);
	Camera& SetOffsetX(const float& anX);
	Camera& SetOffsetY(const float& aY);
	Camera& SetLerp(const v2f& aLerp);
	Camera& SetLerpX(const float& anX);
	Camera& SetLerpY(const float& aY);

	Camera& StartFollowing(GameObject* aGameObject, const v2f& aLerp = { 1.0f, 1.0f }, const v2f& anOffset = { 0.0f, 0.0f });
	Camera& StartFollowing(const v2f& aStaticTarget, const v2f& aLerp = { 1.0f, 1.0f }, const v2f& anOffset = { 0.0f, 0.0f });
	Camera& ResumeFollowing();
	Camera& StopFollowing();

	/* Camera Bounds */
	Camera& SetBounds(const v2f& aCoordinate, const v2f& aSize);
	Camera& SetBounds(const float& anX, const float& aY, const float& aWidth, const float& aHeight);
	Camera& ResetBounds();

	const bool& HasBounds() const;
	const v2f& GetBounds() const;
	const v2f& GetBoundSize() const;
	const bool GetActive() const;
	void SetActive();

	/* Camera Shake */
	bool IsShaking() const;

	Camera& Shake(const float& aDuration, const float& anIntensity, const float& aDropOff = 1.0f);
	Camera& Shake(const float& aDuration, const v2f& anIntensity, const float& aDropOff = 1.0f);

	/* Camera Zoom */
	const float& GetZoom() const;
	v2f GetViewportSize() const;
	Camera& SetZoom(const float& aZoom);

private:
	Camera& ShakeUpdate(const float& aDeltaTime);
	float GetScaleFactor();

	bool myCameraActive;
	float myX;
	float myY;
	float myAlpha;

	/* Camera Follow */
	GameObject* myTarget;
	v2f myStaticTarget;
	v2f myOffset;
	v2f myLerp;
	bool myUseStaticTarget;
	bool myIsFollowing;

	/* Camera Bounds */
	v2f myBounds;
	v2f myBoundSize;
	v2f myWorldViewSize;
	bool myHasBounds;

	/* Camera Shake */
	v2f myShakeIntensity;
	v2f myCurrentShakeOffset;
	float myShakeDuration;
	float myShakeDropoff;
	bool myIsShaking;

	bool myLesserThanViewPortX;
	bool myLesserThanViewPortY;

	/* Camera Zoom */
	float myZoom;
	float myInverseZoom;
};