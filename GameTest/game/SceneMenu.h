
#pragma once

#include "Scene.h"

class SceneMenu : public Scene
{
protected:

public:
	void Init() override;
	void Update(float delta) override;
	void Render() override;
	void Delete() override;
};