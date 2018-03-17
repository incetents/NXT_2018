#pragma once

#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"
#include "../Math/Vertex.h"
#include "../Math/Color.h"

#include "../App/app.h"

class Renderer
{
public:
	Renderer(){}
	void setVertexArray(VertexArray* VA)
	{
		m_vertexArray = VA;
		updateRenderFunction(VA->getMode());
		m_indexMode = VA->getIndicesArrayStart() != nullptr;
		m_hasColor = VA->getColorsArrayStart() != nullptr;

		// Update Temp Values
		t_drawCount = m_vertexArray->getDrawCount();

		if (m_indexMode)
		{
			t_positions = m_vertexArray->getIndexedPositionArrayStart();
			t_colors = m_vertexArray->getIndexedColorsArrayStart();
		}
		else
		{
			t_positions = m_vertexArray->getPositionArrayStart();
			t_colors = m_vertexArray->getColorsArrayStart();
		}
	}
	void deleteVertexArray()
	{
		if (m_vertexArray != nullptr)
			delete[] m_vertexArray;
	}
	
private:
	VertexArray* m_vertexArray = nullptr;
	bool		 m_indexMode = false;
	bool		 m_hasColor = false;
protected:

	float    m_pointSize = 1.0f;
	float	 m_lineWidth = 1.0f;
	bool	 m_wireframeMode = false;

	Matrix4x4 t_modelMatrix;// Transform Data (Temp for draw call)
	u_int	  t_drawCount;  // VertexArray Data (Temp for draw call)
	Vector3*  t_positions;  //
	Color3F*  t_colors;		//

	void render(const Matrix4x4& _ModelMatrix)
	{
		t_modelMatrix = _ModelMatrix;
		// Prevents funcion from using a switch per call
		(this->*RenderFunction)();
	}
	void (Renderer::*RenderFunction)(void) = &Renderer::null; // Function pointer
	void updateRenderFunction(VertexArray::Mode mode) // Point function pointer to correct function
	{
		switch (mode)
		{
		case VertexArray::Mode::POINTS:
			RenderFunction = &Renderer::drawPoints;
			break;

		case VertexArray::Mode::LINES:
			RenderFunction = &Renderer::drawLines;
			break;

		case VertexArray::Mode::LINE_STRIPS:
			RenderFunction = &Renderer::drawLineStrips;
			break;

		case VertexArray::Mode::TRIANGLE:
			RenderFunction = &Renderer::drawTriangle;
			break;
		}
	}

	// if enum for mode fails, it will update this function as a fail-safe
	void null() {}

	void drawPoints()
	{
		glPointSize(m_pointSize);

		App::DrawPoints(
			t_modelMatrix,
			t_positions,
			t_colors,
			t_drawCount
		
		);
	}
	void drawLineStrips()
	{
		glLineWidth(m_lineWidth);

		for (u_int i = 0; i < t_drawCount - 1; i++)
		{
			// Points
			App::DrawLine(
				t_modelMatrix * t_positions[i+0],
				t_modelMatrix * t_positions[i+1],
				(m_hasColor) ? t_colors[i+0] : Color::WHITE,
				(m_hasColor) ? t_colors[i+1] : Color::WHITE
			);
		}
	}
	void drawLines()
	{
		assert(t_drawCount % 2 == 0); // Lines must have multiples of 2

		glLineWidth(m_lineWidth);

		for (u_int i = 0; i < t_drawCount; i+=2)
		{
			// Points
			App::DrawLine(
				t_modelMatrix * t_positions[i + 0],
				t_modelMatrix * t_positions[i + 1],
				(m_hasColor) ? t_colors[i + 0] : Color::WHITE,
				(m_hasColor) ? t_colors[i + 1] : Color::WHITE
			);
		}
	}
	void drawTriangle()
	{
		assert(t_drawCount % 3 == 0); // Triangles must have multiples of 3

		App::SetWireframeMode(m_wireframeMode);

		for (u_int i = 0; i < t_drawCount; i+=3)
		{
			// Points
			App::DrawTriangle(
				t_modelMatrix * t_positions[i + 0],
				t_modelMatrix * t_positions[i + 1],
				t_modelMatrix * t_positions[i + 2],
				(m_hasColor) ? t_colors[i + 0] : Color::WHITE,
				(m_hasColor) ? t_colors[i + 1] : Color::WHITE,
				(m_hasColor) ? t_colors[i + 2] : Color::WHITE
			);
		}
	}
};