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

#include "../GameObject/CameraManager.h"

class GameObject : public Entity
{
private:
	// Reference to all other GameObjects
	static std::vector<GameObject*> m_allGameObjects;

	// Constructor only called from static member
	GameObject(VertexArray* VA, std::string _name = "");

public:
	// Core Data
	std::string name = "";
	Transform*	transform;
	Renderer*	renderer;

	// Create GameObject
	static GameObject* createGameObject(VertexArray* _VA, std::string _name = "")
	{
		return new GameObject(_VA, _name);
	}

	virtual void Delete() override
	{
		// Remove from list
		m_allGameObjects.erase(std::remove(m_allGameObjects.begin(), m_allGameObjects.end(), this), m_allGameObjects.end());
	}
	
	virtual void Init() override
	{

	}

	virtual void Update(float delta) override
	{
		// Update all components
		for (auto it : m_components)
		{
		//	std::cout << " " << it.first << ":" << it.second;
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