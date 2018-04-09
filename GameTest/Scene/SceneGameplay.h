
#pragma once

#include "Scene.h"

class SceneGameplay : public Scene
{
	friend class Ball;
	friend class Flipper;
	friend class Wall;
	friend class Bouncer;
protected:
	bool ballSpawn = true;
	GameObject* arrow;
	Ball* ball;
	std::vector<Flipper*> bumpers;
	std::vector<Wall*> walls;
	std::vector<Bouncer*> bouncers;

public:
	SceneGameplay(GameState newstate) : Scene(newstate) {}

	void Init() override;
	GameState Update(float delta) override;
	void Render() override;
	void Delete() override;
};