
#pragma once

class Component
{
public:
	virtual void Init() {}
	virtual void Update(float delta) {}
	virtual void Delete() {}
};