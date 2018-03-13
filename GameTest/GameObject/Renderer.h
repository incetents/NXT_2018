#pragma once

#include "../Math/Vector3.h"
#include "../Math/Vertex.h"
#include "../Math/Color.h"

#include "../App/app.h"

class Renderer
{
public:
	Renderer& setData(Vector3* position_ptr, u_int* size)
	{
		m_vertices = position_ptr;
		m_size = size;
		return *this;
	}
	Renderer& setColor(Color3F* color)
	{
		m_color = color;
		return *this;
	}
	Renderer& setMode(VertexArray::Mode mode)
	{
		updateDrawFunction(mode);
		return *this;
	}
	void draw()
	{
		// Prevents funcion from using a switch per call
		(this->*DrawFunction)();
	}
private:
	Vector3*	m_vertices;
	u_int*		m_size;
	Color3F*	m_color;
	
	void (Renderer::*DrawFunction)(void) = nullptr; // Function pointer
	void updateDrawFunction(VertexArray::Mode mode) // Point function pointer to correct function
	{
		switch (mode)
		{
		case VertexArray::Mode::LINES:
			DrawFunction = &Renderer::drawLines;
			break;

		case VertexArray::Mode::LINE_STRIPS:
			DrawFunction = &Renderer::drawLineStrips;
			break;

		case VertexArray::Mode::TRIANGLE:
			DrawFunction = &Renderer::drawTriangle;
			break;

		case VertexArray::Mode::QUAD:
			DrawFunction = &Renderer::drawQuad;
			break;
		}
	}

	void drawLineStrips()
	{
		for (u_int i = 0; i < *m_size; i ++)
		{
			// Line 1
			App::DrawLine(
				m_vertices[i + 0].x, m_vertices[i + 0].y,
				m_vertices[i + 1].x, m_vertices[i + 1].y,
				m_color->r, m_color->g, m_color->b
			);
		}
	}
	void drawLines()
	{
		assert(*m_size % 2 == 0); // Lines must have multiples of 2

		for (u_int i = 0; i < *m_size; i += 2)
		{
			// Line 1
			App::DrawLine(
				m_vertices[i + 0].x, m_vertices[i + 0].y,
				m_vertices[i + 1].x, m_vertices[i + 1].y,
				m_color->r, m_color->g, m_color->b
			);
		}
	}
	void drawTriangle()
	{
		assert(*m_size % 3 == 0); // Triangles must have multiples of 3

		for (u_int i = 0; i < *m_size; i += 3)
		{
			// Line 1
			App::DrawLine(
				m_vertices[i + 0].x, m_vertices[i + 0].y,
				m_vertices[i + 1].x, m_vertices[i + 1].y,
				m_color->r, m_color->g, m_color->b
			);
			// Line 2
			App::DrawLine(
				m_vertices[i + 1].x, m_vertices[i + 1].y,
				m_vertices[i + 2].x, m_vertices[i + 2].y,
				m_color->r, m_color->g, m_color->b
			);
			// Line 3
			App::DrawLine(
				m_vertices[i + 2].x, m_vertices[i + 2].y,
				m_vertices[i + 0].x, m_vertices[i + 0].y,
				m_color->r, m_color->g, m_color->b
			);
		}
	}
	void drawQuad()
	{
		assert(*m_size % 4 == 0); // Quads must have multiples of 4

		for (u_int i = 0; i < *m_size; i += 4)
		{
			// Line 1
			App::DrawLine(
				m_vertices[i + 0].x, m_vertices[i + 0].y,
				m_vertices[i + 1].x, m_vertices[i + 1].y,
				m_color->r, m_color->g, m_color->b
			);
			// Line 2
			App::DrawLine(
				m_vertices[i + 1].x, m_vertices[i + 1].y,
				m_vertices[i + 2].x, m_vertices[i + 2].y,
				m_color->r, m_color->g, m_color->b
			);
			// Line 3
			App::DrawLine(
				m_vertices[i + 2].x, m_vertices[i + 2].y,
				m_vertices[i + 3].x, m_vertices[i + 3].y,
				m_color->r, m_color->g, m_color->b
			);
			// Line 4
			App::DrawLine(
				m_vertices[i + 3].x, m_vertices[i + 3].y,
				m_vertices[i + 0].x, m_vertices[i + 0].y,
				m_color->r, m_color->g, m_color->b
			);
		}
	}
};