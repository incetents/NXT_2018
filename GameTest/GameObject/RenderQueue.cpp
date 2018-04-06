#include "stdafx.h"

#include <algorithm>
#include "RenderQueue.h"
#include "GameObject.h"
#include "../Particle/Emitter.h"

template<typename T>
bool _RenderQueue::checkDuplicate(T* object)
{
	// Empty
	return false;
}

template<>
bool _RenderQueue::checkDuplicate(GameObject* object)
{
	return (std::find(m_gameobjects.begin(), m_gameobjects.end(), object) != m_gameobjects.end());
}
template<>
bool _RenderQueue::checkDuplicate(Emitter* object)
{
	return (std::find(m_emitters.begin(), m_emitters.end(), object) != m_emitters.end());
}

template<typename T>
_RenderQueue& _RenderQueue::add(T* object)
{
	// Do nothing
	return *this;
}
template<>
_RenderQueue& _RenderQueue::add(GameObject* object)
{
	if (checkDuplicate<GameObject>(object))
		return *this;

	m_gameobjects.push_back(object);
	m_totalObjects++;
	return *this;
}
template<>
_RenderQueue& _RenderQueue::add(Emitter* object)
{
	if (checkDuplicate<Emitter>(object))
		return *this;

	m_emitters.push_back(object);
	m_totalEmitters++;
	return *this;
}

template<typename T>
_RenderQueue& _RenderQueue::remove(T* object)
{
	return *this;
}
template<>
_RenderQueue& _RenderQueue::remove(GameObject* object)
{
	Utility::EraseVectorByValue(m_gameobjects, object);
	m_totalObjects = (u_int)m_gameobjects.size();
	return *this;
}
template<>
_RenderQueue& _RenderQueue::remove(Emitter* object)
{
	Utility::EraseVectorByValue(m_emitters, object);
	m_totalEmitters = (u_int)m_emitters.size();
	return *this;
}

void _RenderQueue::drawAll()
{
	for (u_int i = 0; i < m_totalObjects; i++)
	{
		m_gameobjects[i]->Draw();
	}

	for (u_int i = 0; i < m_totalEmitters; i++)
	{
		m_emitters[i]->update();
		m_emitters[i]->draw();
	}
}