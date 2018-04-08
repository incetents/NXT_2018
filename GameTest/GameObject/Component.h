
#pragma once

#include "../Math/Color.h"

class Component
{
public:
	virtual void Init() {}
	virtual void Update(float delta) {}
	virtual void Draw(Color3F color = Color3F::WHITE()) const {} // Debug only
	virtual void Delete() {}
};