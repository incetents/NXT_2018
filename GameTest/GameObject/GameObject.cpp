
#include "stdafx.h"

#include "GameObject.h"
#include <string>
#include "../Math/Vertex.h"
#include "../Math/Transform.h"
#include "../GameObject/Entity.h"

std::vector<GameObject*> GameObject::m_allGameObjects;

// Constructor
GameObject::GameObject(VertexArray* VA, std::string _name) : name(_name)
{
	// Add components
	transform = AddComponent<Transform>(new Transform());
	renderer = AddComponent<Renderer>(new Renderer());

	// Pure Data
	GetComponent<Renderer>()->setVertexArray(VA);
	GetComponent<Renderer>()->updateVertexArray();
	GetComponent<Transform>()->setGameObjectReference(this);

	// Add to super list
	m_allGameObjects.push_back(this);

}