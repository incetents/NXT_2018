
#pragma once

#include "Scene.h"

class SceneTest : public Scene
{
protected:
	GameObject* ball;
	std::vector<GameObject*> walls;

public:
	void Init() override;
	void Update(float delta) override;
	void Render() override;
	void Delete() override;
};