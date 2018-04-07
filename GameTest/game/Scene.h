#pragma once

#include "../GameObject/RenderQueue.h"

class Scene
{
protected:
	// Render Stuff
	RenderQueue rq;
public:

	// States
	virtual void Init() = 0;
	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
	virtual void Delete() = 0;
};