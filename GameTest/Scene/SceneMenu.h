
#pragma once

#include "Scene.h"

class SceneMenu : public Scene
{
protected:
	Emitter* emitter;
public:
	SceneMenu(GameState newstate) : Scene(newstate) {}

	void Init() override;
	GameState Update(float delta) override;
	void Render() override;
	void Delete() override;
};