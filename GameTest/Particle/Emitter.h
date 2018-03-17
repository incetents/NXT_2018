#pragma once

#include "../GameObject/Renderer.h"
#include "../Math/Transform.h"
#include "../Math/Vertex.h"
#include "../Utility/Utility.h"
#include "Particle.h"

// Currently only updates in local space
class Emitter : public Renderer
{
private:
	int m_maxParticles = 0;
	float m_particleSize = 5.0f;
	Vector3* Positions;
	Vector3* Velocities;
	Vector3* Accelerations;
public:
	Transform transform;

	Emitter(int maxParticles = 1000)
	{
		m_maxParticles = maxParticles;
		Vector3* Positions		= new Vector3[maxParticles];
		Vector3* Velocities		= new Vector3[maxParticles];
		Vector3* Accelerations	= new Vector3[maxParticles];
		Utility::ClearArray(Positions, maxParticles);

		VertexArray* VA = new VertexArray(Positions, nullptr, nullptr, maxParticles, -1, VertexArray::Mode::POINTS);
		setVertexArray(VA);
	}
	~Emitter()
	{
		deleteVertexArray();
	}

	void update()
	{

	}

	void draw()
	{
		m_pointSize = m_particleSize;

		render(Matrix4x4());
	}
};