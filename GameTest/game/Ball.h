#pragma once

#include "../GameObject/GameObject.h"
#include "../Math/Vector2.h"
#include <string>

class Ball : public GameObject
{
private:
	GameObject* cube_effect;
public:
	Ball(
		std::string _name = "",
		float scale = 50.0f,
		Vector2 position = Vector2(0, 0),
		Vector2 velocity = Vector2(0, 0)
	);

	void OnCollide(Collider c) override;
	void OnTrigger(Collider c) override;
	void Update(float delta) override;
};