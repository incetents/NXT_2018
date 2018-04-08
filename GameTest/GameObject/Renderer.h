#pragma once

#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"
#include "../Math/Vertex.h"
#include "../Math/Color.h"

#include "../App/app.h"
#include <string>

#include "../App/SimpleLogger.h"
#include "../GameObject/Component.h"

class Renderer : public Component
{
public:
	Renderer(){}
	~Renderer()
	{
		if (m_vertexArray != nullptr)
			delete m_vertexArray;
	}
	void setVertexArray(VertexArray* VA)
	{
		if (VA == nullptr)
		{
			SimpleLogger.ErrorStatic("Cannot Set Vertex Array with nullptr");
			return;
		}

		m_vertexArray = VA;

		// Update Mode
		VertexArray::Mode M = m_vertexArray->getMode();
		updateRenderFunction(M);

		// Update Temp Values
		t_drawCount = m_vertexArray->getDrawCount();

		// Pointers for drawing
		t_positions = m_vertexArray->getPositions();
		t_colors = m_vertexArray->getColors();
		t_sizes = m_vertexArray->getSizes();
		//

		// Flags
		HasColor = m_vertexArray->getColors() != nullptr;
		HasSizes = m_vertexArray->getSizes() != nullptr;
	}
	void resendPositions(Vector3* _Positions)
	{
		if (m_vertexArray == nullptr)
			return;

		m_vertexArray->setPositions(_Positions, m_vertexArray->getVertexCount());
	}
	void resendColors(Color3F* _Colors)
	{
		if (m_vertexArray == nullptr)
			return;

		m_vertexArray->setColors(_Colors, m_vertexArray->getVertexCount());
	}

	void render(const Matrix4x4& _ModelMatrix)
	{
		if (!m_activeState)
			return;

		t_modelMatrix = _ModelMatrix;
		// Prevents funcion from using a switch per call
		(this->*RenderFunction)();
	}

	float   m_pointSize = 1.0f;
	float	m_lineWidth = 1.0f;
	bool	m_activeState = true;
	
private:
	VertexArray* m_vertexArray = nullptr;

	Matrix4x4 t_modelMatrix;	// Transform Data (Temp for draw call)
	u_int	  t_drawCount = 0;  // VertexArray Data (Temp for draw call)
	Vector3*  t_positions	= nullptr; //
	Color3F*  t_colors		= nullptr; //
	float*	  t_sizes		= nullptr; //

	bool HasColor = false;
	bool HasSizes = false;
	
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
			t_sizes,
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
				(HasColor) ? t_colors[i+0] : Color3F::WHITE(),
				(HasColor) ? t_colors[i+1] : Color3F::WHITE()
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
				(HasColor) ? t_colors[i + 0] : Color3F::WHITE(),
				(HasColor) ? t_colors[i + 1] : Color3F::WHITE()
			);
		}
	}
	void drawTriangle()
	{
		assert(t_drawCount % 3 == 0); // Triangles must have multiples of 3

		// No point for this engine to have wireframe triangles
		//App::SetWireframeMode(false);

		for (u_int i = 0; i < t_drawCount; i+=3)
		{
			// Points
			App::DrawTriangle(
				t_modelMatrix * t_positions[i + 0],
				t_modelMatrix * t_positions[i + 1],
				t_modelMatrix * t_positions[i + 2],
				(HasColor) ? t_colors[i + 0] : Color3F::WHITE(),
				(HasColor) ? t_colors[i + 1] : Color3F::WHITE(),
				(HasColor) ? t_colors[i + 2] : Color3F::WHITE()
			);
		}
	}
};