#include "stdafx.h"

#include "RenderQueue.h"
#include "GameObject.h"

template<typename T>
bool _RenderQueue::checkDuplicate(T* object)
{
	// Empty
	return false;
}

template<>
bool _RenderQueue::checkDuplicate(GameObject* object)
{
	for (u_int i = 0; i < m_totalObjects; i++)
	{
		if (m_objects[i] == object)
			return true;
	}
	return false;
}
template<>
bool _RenderQueue::checkDuplicate(Emitter* object)
{
	for (u_int i = 0; i < m_totalEmitters; i++)
	{
		if (m_emitters[i] == object)
			return true;
	}
	return false;
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

	m_objects.push_back(object);
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
	Utility::EraseVectorByValue(m_objects, object);
	m_totalObjects = (u_int)m_objects.size();
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
		m_objects[i]->Draw();
	}
}