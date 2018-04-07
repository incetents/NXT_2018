#pragma once

#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Rotation.h"

#include <assert.h>
#include <vector>

#include "../GameObject/Component.h"

class GameObject;

class Transform : public Component
{
private:
	// GameObject Reference
	GameObject* m_gameObject;

	// Model for transformations
	Matrix4x4	m_ModelMatrix;

	// Raw Values
	Vector3		m_position;
	Vector3		m_euler_rotation;
	Vector3		m_scale;
	Quaternion	m_rotation;

	// Direction Space
	Vector3		m_forward = Vector3::FORWARD;
	Vector3     m_up = Vector3::UP;
	Vector3     m_right = Vector3::RIGHT;

	// Parent/Child relationships
	Transform*				m_parent = nullptr;
	std::vector<Transform*> m_children;
	u_int					m_totalChildren = 0;

	// Parent / Child Functionality
	void simpleRemoveParent()
	{
		m_parent = nullptr;
	}
	void SimpleRemoveChild(int index) 
	{
		m_children.erase(m_children.begin() + index);
		m_totalChildren--;
	}
	void SimpleRemoveChild(Transform* child)
	{
		int child_index = getChildIndex(child);
		if (child_index != -1)
		{
			SimpleRemoveChild(child_index);
		}
	}
	void SimpleAddChild(Transform* child)
	{
		m_children.push_back(child);
		m_totalChildren++;
	}
	void InheritChildren() 
	{
		// Parent takes this node's children, this node then becomes an orphan
		if (m_parent == nullptr)
			return;

		for (u_int i = 0; i < m_totalChildren; i++)
		{
			m_parent->SimpleAddChild(m_children[i]);
		}
		m_children.clear();
		m_totalChildren = 0;
		m_parent = nullptr;
	}

	// Update Flag
	bool isDirty = true;

public:
	Transform();
	Transform(const Vector3& position, const Vector3& euler_rotation, const Vector3& scale);

	const Matrix4x4 getModel();

	// GameObject Reference
	void		setGameObjectReference(GameObject* G)
	{
		m_gameObject = G;
	}
	GameObject*	getGameObjectReference() const
	{
		return m_gameObject;
	}

	// Returns index of child in list of children (-1 = child does not exist)
	bool					checkChildDuplicate(Transform* c)
	{
		for (u_int i = 0; i < m_totalChildren; i++)
		{
			if (c == m_children[i])
				return true;
		}
		return false;
	}

	// Get Children Data
	int						getChildIndex(Transform* c)
	{
		for (u_int i = 0; i < m_totalChildren; i++)
		{
			if (c == m_children[i])
				return i;
		}
		// Nothing found
		return -1;
	}
	std::vector<Transform*> getChildren()
	{
		return m_children;
	}
	Transform*				getChild(u_int index)
	{
		assert(index >= 0 && index < m_totalChildren);

		return m_children[index];
	}
	u_int					getChildCount()
	{
		return m_totalChildren;
	}
	// Get Parent
	Transform*				getParent()
	{
		return m_parent;
	}

	// Parent / Child - Changes
	void setParent(Transform* parent)
	{
		// cannot parent self
		if (parent == this)
			return;

		// Check if new parent is found somewhere in the chain upwards
		Transform* current = parent;
		while (current != nullptr)
		{
			if (current->m_parent == this)
			{
				// New parent must have his parent disconnect from it
				parent->m_parent->SimpleRemoveChild(parent);
				// New parent must disconnect from his parent
				parent->simpleRemoveParent();
				break;
			}
			else
			{
				current = current->m_parent;
			}
		}
		
		// Make sure previous parent removes this
		if(m_parent != nullptr)
			m_parent->removeChild(this);
		
		// Set Parent
		m_parent = parent;
		
		// Make sure parent has child
		m_parent->addChild(this);

		
	}
	void addChild(Transform* child)
	{
		// cannot child self
		if (child == this)
			return;
		
		// Ignore if child is already present
		if (checkChildDuplicate(child))
			return;

		// Check if new child is found somewhere in the chain upwards
		Transform* current = this;
		while (current != nullptr)
		{
			if (current->m_parent == child)
			{
				// Chain Link discovered, disconnect from current
				current->m_parent->SimpleRemoveChild(current);
				// Current removes parent
				current->simpleRemoveParent();
				break;
			}
			else
			{
				current = current->m_parent;
			}
		}
		
		// Child removes its current parent
		child->removeParent();
		
		// Child now treats this class as its parent
		child->m_parent = this;

		// Add child
		SimpleAddChild(child);

	}
	void removeParent()
	{
		// Ignore if no parent present
		if (m_parent == nullptr)
			return;
		
		// Parent removes this child
		m_parent->SimpleRemoveChild(this);
		
		// Child removes parent
		m_parent = nullptr;
	}
	void removeChild(Transform* child)
	{
		int child_index = getChildIndex(child);
		if (child_index == -1)
			return;
		
		// Child removes parent
		m_children[child_index]->simpleRemoveParent();
		
		// This loses child
		SimpleRemoveChild(child_index);
	}

	// Setters
	inline Transform& setPosition(const Vector2& position)
	{
		m_position = position;
		isDirty = true;
		return *this;
	}
	inline Transform& setPosition(const Vector3& position)
	{
		m_position = position;
		isDirty = true;
		return *this;
	}
	inline Transform& setRotation(const Vector3& euler_rotation)
	{
		m_euler_rotation = euler_rotation;
		isDirty = true;
		return *this;
	}
	inline Transform& setScale(const Vector3 scale)
	{
		m_scale = scale;
		isDirty = true;
		return *this;
	}
	inline Transform& setScale(float scaleAll)
	{
		m_scale = Vector3(scaleAll);
		isDirty = true;
		return *this;
	}

	// Increasers
	inline Transform& increasePosition(const Vector2& translate)
	{
		m_position += Vector3(translate);
		isDirty = true;
		return *this;
	}
	inline Transform& increasePosition(const Vector3& translate)
	{
		m_position += translate;
		isDirty = true;
		return *this;
	}
	inline Transform& increaseRotation(const Vector3& euler_increase)
	{
		m_euler_rotation += euler_increase;
		isDirty = true;
		return *this;
	}
	inline Transform& increaseScale(const Vector3& scaler)
	{
		m_scale += scaler;
		isDirty = true;
		return *this;
	}
	// Alt name
	inline Transform& translate(const Vector3& translate)
	{
		return increasePosition(translate);
	}
	inline Transform& rotate(const Vector3& euler_increase)
	{
		return increaseRotation(euler_increase);
	}

	// Getters
	inline Vector3		getPosition() const
	{
		return m_position;
	}
	inline Vector3		getRotationEuler() const
	{
		return m_euler_rotation;
	}
	inline Quaternion	getRotation() const
	{
		return m_rotation;
	}
	inline Vector3		getScale() const
	{
		return m_scale;
	}
	inline Vector3		getForward() const
	{
		return m_forward;
	}
	inline Vector3		getUp() const
	{
		return m_up;
	}
	inline Vector3		getRight() const
	{
		return m_right;
	}

	// Special
	void drawDirections(const Matrix4x4& model);
};