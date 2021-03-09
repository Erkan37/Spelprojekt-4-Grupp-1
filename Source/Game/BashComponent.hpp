#pragma once
#include "Component.hpp"

class BashComponent : public Component
{
public:
	BashComponent();
	~BashComponent();

	void SetRadius(const float& aRadius);
	const float GetRadius();

private:
	float myRadius;

};

