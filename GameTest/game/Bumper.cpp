#include "stdafx.h"

#include "Bumper.h"

Bumper::Bumper(std::string _name, Vector2 position, Vector2 size) : GameObject(_name)
{
	GetComponent<Renderer>()->setVertexArray(SimpleShapes.v_box);
}