#pragma once

#include <string>

#include "../Math/Transform.h"
#include "../Math/Vertex.h"
#include "../app/app.h"
#include "../Math/Color.h"
#include "Renderer.h"

class GameObject
{
private:
	VertexArray m_VertexArray;
	Renderer	m_renderer;
public:
	Transform transform;
	Color3F color = Color3F(1);

	GameObject(
		Vector3* start, u_int pos_size,
		u_int* indices = nullptr, u_int index_size = -1)
	{
		// Setup vertex array
		m_VertexArray.setPositions(start, pos_size);
		if (indices != nullptr)
			m_VertexArray.setIndices(indices, index_size);

		// Setup renderer
		m_renderer
			.setMode(m_VertexArray.getMode())
			.setColor(&color);
	}
	void render()
	{
		// Model Matrix
		Matrix4x4 modelMatrix = transform.getModel();

		// Create list of MVP vertices
		u_int DrawCount = m_VertexArray.getDrawCount();
		Vector3* vertices = new Vector3[DrawCount];

		// Create Vertices from positions
		if (m_VertexArray.getIndicesArrayStart() == nullptr)
		{
			for (u_int i = 0; i < DrawCount; i++)
			{
				vertices[i] = modelMatrix * m_VertexArray.getPosition(i);
			}
		}
		// Create vertices from indices
		else
		{
			for (u_int i = 0; i < DrawCount; i++)
			{
				vertices[i] = modelMatrix * m_VertexArray.getIndexedPosition(i);
			}
		}

		// Send Data to render and draw
		m_renderer
			.setData(vertices, &DrawCount)
			.draw();


		//	for (int i = 0; i < DrawCount - 1; i++)
		//	{
		//		App::DrawLine(
		//			vertices[i+0].x, vertices[i+0].y,
		//			vertices[i+1].x, vertices[i+1].y,
		//			color.r, color.g, color.b
		//		);
		//	}
		//	
		//	// Last line
		//	App::DrawLine(
		//		vertices[DrawCount - 1].x, vertices[DrawCount - 1].y,
		//		vertices[0].x, vertices[0].y,
		//		color.r, color.g, color.b
		//	);
	}
};