#pragma once

#include "../GameObject/Renderer.h"
#include "../Math/Transform.h"
#include "../Math/Vertex.h"
#include "../Utility/Utility.h"
#include "Particle.h"

// Currently only updates in local space
class Emitter
{
private:
	enum ColorMode
	{
		STATIC,
		LIFE_LERP2,
		LIFE_LERP3
	};

	// Buffers
	Vector3*	m_positions;
	Vector3*	m_velocities;
	Vector3*	m_accelerations;
	Color3F*	m_colors;
	float*		m_sizes;
	int*		m_life;

	// Flags
	bool	m_activeState = true;
	bool	m_isSetup = false;


	// Particles
	int		m_maxParticles = 0;
	
	// Size
	float	m_particleSize = 5.0f;

	// Speed
	float   m_VelocityOffset = 8.0f;
	Vector3 m_inheritVelocity = Vector3(0, 0, 0);
	float   m_inheritVelocityBias = 1.0f;
	Vector3 m_GravityDirection = Vector3(0, -1, 0);
	float   m_GravityAmount = 0.95f;
	float   m_speed = 1.0f;

	// Life
	int		m_lifeCount;
	int		m_lifeCountRandomness;

	// Color Animation
	ColorMode	m_colorMode = ColorMode::STATIC;
	Color3F		m_color1;
	Color3F		m_color2;
	Color3F		m_color3;

	// Timeline
	bool m_looping = true;
	bool m_paused = false;
	bool m_stopped = false;

	Vector3 getInitialVelocity()
	{
		float r = Random::Float(1.0f, max(m_VelocityOffset, 1.0f));
		return Vector3(Vector2::GetRandomUnitVector(), 0) * r;
	}
	int getTimeAlive()
	{
		int r = (int)(Random::Float(-m_lifeCountRandomness * 0.5f, +m_lifeCountRandomness * 0.5f));
		return m_lifeCount + r;
	}

public:
	Transform transform;

	Emitter(int maxParticles = 1000, int lifetime = 100, bool looping = true, Color3F baseColor = Color3F(1,1,1))
	{
		// General Data
		m_maxParticles  = maxParticles;
		m_lifeCount		= lifetime;
		m_lifeCountRandomness = static_cast<int>((float)lifetime * 0.85f);
		m_looping		= looping;

		// Buffers of Data
		m_positions		= new Vector3[m_maxParticles];
		m_velocities	= new Vector3[m_maxParticles];
		m_accelerations	= new Vector3[m_maxParticles];
		m_sizes			= new float[m_maxParticles];
		m_life			= new int[m_maxParticles];
		m_colors		= new Color3F[m_maxParticles];

		// Default Values
		for (int i = 0; i < m_maxParticles; i++)
		{
			m_positions[i] = Vector3::ZERO;
			// Initial Color
			m_colors[i] = baseColor;
			// Initial Delay
			//m_life[i] = Random::Float(-1.f, -m_lifeCount);
		}

	}

	void startEmitter()
	{
		if (m_isSetup)
			return;

		reset();

		m_isSetup = true;
	}

	// Change Colors
	void setColor(Color3F color)
	{
		m_colorMode = ColorMode::STATIC;

		for (int i = 0; i < m_maxParticles; i++)
		{
			m_colors[i] = color;
		}
	}
	void setColorByLife(Color3F start, Color3F end)
	{
		m_colorMode = ColorMode::LIFE_LERP2;

		m_color1 = start;
		m_color2 = end;
	}
	void setColorByLife(Color3F start, Color3F middle, Color3F end)
	{
		m_colorMode = ColorMode::LIFE_LERP3;

		m_color1 = start;
		m_color2 = middle;
		m_color3 = end;
	}

	// Change Life
	void setLifeCount(int time)
	{
		m_lifeCount = time;
		m_lifeCountRandomness = static_cast<int>((float)time * 0.85f);
	}

	// Timeline
	void setLooping(bool state)
	{
		m_looping = state;
	}
	void play()
	{
		if (!m_looping)
			reset();

		m_paused = false;
		m_stopped = false;
	}
	void pause()
	{
		m_paused = true;
	}
	void stop()
	{
		m_paused = false;
		m_stopped = true;
	}
	void reset()
	{
		for (int i = 0; i < m_maxParticles; i++)
		{
			m_positions[i] = transform.getPosition();
			m_velocities[i] = getInitialVelocity();
			m_sizes[i] = (Random::Float01() * 8.0f);
			m_life[i] = getTimeAlive();
		}
	}

	// Speed Modifiers
	void setSpeed(float speed)
	{
		m_speed = speed;
	}
	void setActive(bool state)
	{
		m_activeState = state;
	}
	void setGravity(Vector3 direction, float amount)
	{
		m_GravityDirection = direction.Normalize();
		m_GravityAmount = amount;
	}
	void setVelocityRange(float range)
	{
		m_VelocityOffset = range;
	}
	void setInheritVelocity(Vector3 v, float bias)
	{
		m_inheritVelocity = v.Normalize();
		m_inheritVelocityBias = bias;
	}
	
	void update()
	{
		if (m_paused || !m_isSetup)
			return;
 
		Vector3 Vel_Inherit = m_inheritVelocity * m_inheritVelocityBias;
		Vector3 Grav = (m_GravityDirection * m_GravityAmount);

		for (int i = 0; i < m_maxParticles; i++)
		{
			float t = 1.0f - ((float)m_life[i] / (float)m_lifeCount);

			m_positions[i] += m_velocities[i] * m_speed;
			m_velocities[i] += t * t * Grav/2 + t * (m_inheritVelocity * Vel_Inherit);

			// Alive
			if (m_life[i] > 0)
			{
				m_life[i]--;

				// Color animation
				
				if (m_colorMode == ColorMode::LIFE_LERP2)
				{
					m_colors[i] = Color3F::lerp(m_color1, m_color2, t);
				}
				else if (m_colorMode == ColorMode::LIFE_LERP3)
				{
					m_colors[i] = Color3F::lerp(m_color1, m_color2, t);
					m_colors[i] = Color3F::lerp(m_colors[i], m_color3, t);
				}
			}
			// Dead
			if (m_life[i] == 0)
			{
				m_positions[i] = Vector3::ZERO;

				// Loop
				if (m_looping && !m_stopped)
				{
					m_life[i] = getTimeAlive();
					m_positions[i] = transform.getPosition();
					m_velocities[i] = getInitialVelocity();
				}
			}

			/*
			// Delay is negative life going upwards
			if (m_life[i] < 0)
			{
				m_positions[i] = Vector3::ZERO;

				m_life[i]++;

				if (m_life[i] == 0)
				{
					m_life[i] = (int)getTimeAlive();
				}
			}

			// Die overtime
			if (m_life[i] > 0)
			{
				// Color animation
				float t = (float)m_life[i] / (float)m_lifeCount;
				if (m_colorMode == ColorMode::LIFE_LERP2)
				{
					m_colors[i] = Color3F::lerp(m_color2, m_color1, t);
				}
				else if (m_colorMode == ColorMode::LIFE_LERP3)
				{
					m_colors[i] = Color3F::lerp(m_color2, m_color1, t);
					m_colors[i] = Color3F::lerp(m_color3, m_colors[i], t);
				}


				m_life[i]--;
			}

			// Dead
			if (m_life[i] == 0)
			{
				// Revive
				if (m_looping && !m_stopped)
				{
					m_life[i] = (int)getTimeAlive();
					m_positions[i] = transform.getPosition();
					m_velocities[i] = getInitialVelocity();
				}
				else if (!m_looping || m_stopped)
				{
					//m_positions[i] = transform.getPosition();
				}
			}
			*/
		}
	}

	// Drawing here instead of app because it's more convenient due to all the buffers
	void draw()
	{
		Matrix4x4 ViewProjection = CameraManager.getMain()->getViewProjection();

		glPointSize(m_particleSize);

		glBegin(GL_POINTS);
		for (int i = 0; i < m_maxParticles; i++)
		{
			if (m_life[i] != 0)
			{
				Vector3 P = ViewProjection * m_positions[i];

				glColor3f(m_colors[i].r, m_colors[i].g, m_colors[i].b);
				glVertex3f(P.x, P.y, P.z);
			}
		}
		glEnd();
	}
};