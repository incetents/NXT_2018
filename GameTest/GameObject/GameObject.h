#pragma once

#include <string>
#include <algorithm>

#include "../Math/Transform.h"
#include "../Math/Vertex.h"
#include "../app/app.h"
#include "../Math/Color.h"
#include "../Math/Matrix4x4.h"
#include "Renderer.h"
#include "Entity.h"
#include "../App/SimpleLogger.h"
#include "../Collision/Collider.h"
#include "../Collision/Rigidbody.h"

#include "../GameObject/CameraManager.h"

class GameObject : public Entity
{
private:
	// Reference to all other GameObjects
	static std::vector<GameObject*> m_allGameObjects;
	bool m_active = true;

	// Setup function
	void SetupComponents();


public:
	// Core Data
	std::string name = "";
	Transform*	transform;
	Renderer*	renderer;

	// Constructor
	GameObject( std::string _name = ""); // Vertex Array
	GameObject(VertexArray* VA, std::string _name = ""); // Init Vertex Array

	void setActive(bool state)
	{
		m_active = state;
	}

	virtual void OnCollide(Collider c) {}
	virtual void OnTrigger(Collider c) {}

	virtual void Delete() override
	{
		// Remove from list
		m_allGameObjects.erase(std::remove(m_allGameObjects.begin(), m_allGameObjects.end(), this), m_allGameObjects.end());
		
		// Delete all components
		for (auto it : m_components)
		{
			it.second->Delete();
			delete it.second;
		}
	}
	
	virtual void Init() override
	{
		// Init all components
		for (auto it : m_components)
		{
			it.second->Init();
		}
	}

	virtual void Update(float delta) override
	{
		if (!m_active)
			return;

		// Update all components
		for (auto it : m_components)
		{
			it.second->Update(delta);
		}
	}

	virtual void Draw() override
	{
		if (!m_active)
			return;

		// MVP
		Matrix4x4 MVP = transform->getModel();

		// Send Model View Matrix for renderning
		renderer->render(MVP);

#if _DEBUG

		// Reset line width
		glLineWidth(1.0f);

		// Draw Transform directions
		transform->drawDirections(MVP);

		// Draw all components that have the draw function
		for (auto it : m_components)
		{
			it.second->Draw(Color3F::YELLOW());
		}
#endif

		// Draw children
		std::vector<Transform*> children = transform->getChildren();
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->getGameObjectReference()->renderer->render(MVP);

#if _DEBUG
			// Reset line width
			glLineWidth(1.0f);

			// Draw child components
			for (auto it : children[i]->getGameObjectReference()->m_components)
			{
				it.second->Draw(Color3F::YELLOW());
			}
#endif
		}

	}
};