#pragma once

#include <Windows.h>
#include <winsock.h>
#include <assert.h>

#include "Vector3.h"
#include "../Utility/Utility.h"

class VertexArray
{
public:
	enum Mode
	{
		LINES,		// Every 2 points is a unique line
		LINE_STRIPS,// All lines are connected from tip to back
		TRIANGLE,	// Every 3 points is a self contained triangle
		QUAD		// Every 4 points is a self contained quad
	};
private:
	Vector3* m_positions = nullptr;
	u_int	 m_positions_size = -1;
	u_int*   m_indices = nullptr;
	u_int    m_indices_size = -1;

	Mode     m_mode = Mode::TRIANGLE;
public:

	VertexArray() {}
	VertexArray(Vector3* start, u_int* indices, u_int size)
	{
		m_positions_size = size;
		m_indices_size = size;
		m_positions = new Vector3[size];
		m_indices = new u_int[size];
	}
	~VertexArray()
	{
		if (m_positions_size)
			delete[] m_positions;

		if (m_indices_size)
			delete[] m_indices;
	}

	bool resizePosition(u_int size)
	{
		if (size != m_positions_size)
		{
			delete[] m_positions;
			m_positions = nullptr;
			m_positions_size = size;
			m_positions = new Vector3[size];
			return true;
		}
		return false;
	}
	bool resizeIndices(u_int size)
	{
		if (size != m_indices_size)
		{
			delete[] m_indices;
			m_indices = nullptr;
			m_indices_size = size;
			m_indices = new u_int[size];
			return true;
		}
		return false;
	}

	// Setters //
	VertexArray& setPositions(Vector3* start, u_int size)
	{
		resizePosition(size);

		Utility::CopyrArray(start, m_positions, size);

		return *this;
	}
	VertexArray& setIndices(u_int* start, u_int size)
	{
		resizeIndices(size);

		Utility::CopyrArray(start, m_indices, size);

		return *this;
	}

	VertexArray& setPosition(int index, Vector3 vector)
	{
		assert(index >= 0 && index < (int)m_positions_size);
		m_positions[index] = vector;

		return *this;
	}
	VertexArray& setIndex(int index, u_int indexValue)
	{
		assert(index >= 0 && index < (int)m_indices_size);
		m_indices[index] = indexValue;

		return *this;
	}

	VertexArray& setMode(Mode m)
	{
		m_mode = m;
		return *this;
	}
	
	// Getters //
	Vector3* getPositionArrayStart() const
	{
		return m_positions;
	}
	const Vector3& getPosition(int index) const
	{
		return m_positions[index];
	}

	u_int* getIndicesArrayStart() const
	{
		return m_indices;
	}
	const u_int& getIndex(int index) const
	{
		return m_indices[index];
	}

	const Vector3& getIndexedPosition(int index) const
	{
		return m_positions[m_indices[index]];
	}

	Mode getMode() const
	{
		return m_mode;
	}

	u_int getDrawCount() const
	{
		// No indices = size of positions
		if (m_indices == nullptr)
			return m_positions_size;
		// Indices = size of indices
		return m_indices_size;
	}

};