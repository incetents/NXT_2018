
#pragma once

#include "Scene.h"
#include "../game/Ball.h"
#include "../game/Bumper.h"
#include "../game/Wall.h"
#include "../game/Bouncer.h"

class SceneTest : public Scene
{
protected:
	Ball* ball;
	Bumper* bumper1;
	std::vector<Wall*> walls;
	std::vector<Bouncer*> bouncers;

public:
	SceneTest(GameState newstate) : Scene(newstate) {}

	void Init() override;
	GameState Update(float delta) override;
	void Render() override;
	void Delete() override;
};