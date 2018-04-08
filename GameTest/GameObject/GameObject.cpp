
#include "stdafx.h"

#include "GameObject.h"
#include <string>
#include "../Math/Vertex.h"
#include "../Math/Transform.h"
#include "../GameObject/Entity.h"

std::vector<GameObject*> GameObject::m_allGameObjects;

void GameObject::SetupComponents()
{
	// Add components
	transform = AddComponent<Transform>(new Transform());
	renderer = AddComponent<Renderer>(new Renderer());

	// Pure Data
	GetComponent<Transform>()->setGameObjectReference(this);
}

// Constructor
GameObject::GameObject(std::string _name) : name(_name)
{
	SetupComponents();

	// Add to super list
	m_allGameObjects.push_back(this);

}
GameObject::GameObject(VertexArray* VA, std::string _name) : name(_name)
{
	SetupComponents();

	// Pure Data
	GetComponent<Renderer>()->setVertexArray(VA);

	// Add to super list
	m_allGameObjects.push_back(this);

}