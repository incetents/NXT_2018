
#pragma once

#include <vector>
#include <iostream>
#include <Windows.h>
#include <winsock.h>
#include <unordered_map>
#include <stdio.h>
#include <string>

#include "Component.h"
#include "../Utility/Utility.h"

class Entity
{
protected:
	// Components
	std::unordered_map<const std::type_info*, Component*> m_components;

public:
	// Override Functions
	virtual void Init(void) = 0;
	virtual void Update(float delta) = 0;
	virtual void Draw(void) = 0;
	virtual void Delete(void) = 0;

	// Check for component
	template <typename T>
	bool CheckComponentExists()
	{
		return m_components.count(&typeid(T)) != 0;
	}

	// Add Component
	template <typename T = Component*>
	T* AddComponent(T* a_component)
	{
		if (a_component != nullptr && m_components.count(&typeid(*a_component)) == 0)
		{
			m_components[&typeid(*a_component)] = (a_component);

			return a_component;
		}
		return nullptr;
	}

	// Get Component
	template <typename T>
	T* GetComponent()
	{
		if (m_components.count(&typeid(T)) != 0)
		{
			return static_cast<T*>(m_components[&typeid(T)]);
		}
		return nullptr;
	}

};