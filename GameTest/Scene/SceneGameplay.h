
#pragma once

#include "Scene.h"

class SceneGameplay : public Scene
{
protected:

public:
	SceneGameplay(GameState newstate) : Scene(newstate) {}

	void Init() override;
	GameState Update(float delta) override;
	void Render() override;
	void Delete() override;
};