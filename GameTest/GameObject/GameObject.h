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

#include "../GameObject/CameraManager.h"

class GameObject : public Entity
{
private:
	// Reference to all other GameObjects
	static std::vector<GameObject*> m_allGameObjects;

	void SetupComponents();

public:
	// Core Data
	std::string name = "";
	Transform*	transform;
	Renderer*	renderer;

	// Constructor
	GameObject( std::string _name = ""); // Vertex Array
	GameObject(VertexArray* VA, std::string _name = ""); // Init Vertex Array

	virtual void onCollide(const Collider& c) {}

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
		// Update all components
		for (auto it : m_components)
		{
			it.second->Update(delta);
		}
	}

	virtual void Draw() override
	{
		// MVP
		Matrix4x4 MVP = transform->getModel();

		// Send Model View Matrix for renderning
		renderer->render(MVP);
		// Draw Transform
#if _DEBUG
		transform->drawDirections(MVP);
#endif
	}
};