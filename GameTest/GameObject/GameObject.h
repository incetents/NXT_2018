#pragma once

#include <string>

#include "../Math/Transform.h"
#include "../Math/Vertex.h"
#include "../app/app.h"
#include "../Math/Color.h"
#include "Renderer.h"

#include "../GameObject/CameraManager.h"

class GameObject : public Renderer
{
public:
	Transform transform;

	GameObject(VertexArray* VA)
	{
		setVertexArray(VA);
		updateVertexArray();
	}
	void draw()
	{
		// Send Model View Matrix for renderning
		render(transform.getModel());
	}
};