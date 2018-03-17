#pragma once

#include <Windows.h>
#include <winsock.h>
#include <assert.h>

#include "Vector3.h"
#include "../Utility/Utility.h"
#include "Color.h"

class VertexArray
{
public:
	enum Mode
	{
		POINTS,		// Draws Multiple Points
		LINES,		// Every 2 points is a unique line
		LINE_STRIPS,// All lines are connected from tip to back
		TRIANGLE,	// Every 3 points is a self contained triangle
	};
private:
	u_int	 m_vertex_count = -1;

	Vector3* m_positions = nullptr;
	Color3F* m_colors = nullptr;

	u_int*   m_indices = nullptr;
	u_int    m_indices_count = -1;

	Vector3* m_indexed_positions = nullptr;
	Color3F* m_indexed_colors = nullptr;

	Mode     m_mode = Mode::LINES;

	// Quick way to update indexed positions/colors with a function call
	template <typename T>
	void updateIndexedData(T*& original_array, T*& indexed_array)
	{
		if (indexed_array != nullptr)
			delete[] indexed_array;

		if (original_array != nullptr && m_indices != nullptr)
		{
			indexed_array = new T[m_indices_count];
			for (u_int i = 0; i < m_indices_count; i++)
			{
				indexed_array[i] = original_array[m_indices[i]];
			}
		}
	}
public:

	VertexArray() {}
	VertexArray(
		Vector3* pos_start,
		u_int* indices_start = nullptr,
		Color3F* color_start = nullptr,
		u_int vertex_count = 0,
		u_int indiex_count = 0,
		Mode mode = Mode::LINES)
	{
		assert(pos_start != nullptr);

		m_mode = mode;

		m_vertex_count = vertex_count;
		m_positions = new Vector3[m_vertex_count];
		Utility::CopyrArray(pos_start, m_positions, m_vertex_count);

		if (color_start != nullptr)
		{
			m_colors = new Color3F[m_vertex_count];
			Utility::CopyrArray(color_start, m_colors, m_vertex_count);
		}
		
		if (indices_start != nullptr)
		{
			m_indices_count = indiex_count;
			m_indices = new u_int[indiex_count];
			Utility::CopyrArray(indices_start, m_indices, indiex_count);
		}

		updateIndexedData<Vector3>(m_positions, m_indexed_positions);
		updateIndexedData<Color3F>(m_colors, m_indexed_colors);
	}
	~VertexArray()
	{
		if (m_positions != nullptr)
			delete[] m_positions;

		if (m_indices != nullptr)
			delete[] m_indices;

		if (m_colors != nullptr)
			delete[] m_colors;

		if (m_indexed_positions != nullptr)
			delete[] m_indexed_positions;

		if (m_indexed_colors != nullptr)
			delete[] m_indexed_colors;
	}

	// Resize
	bool resizePosition(u_int size)
	{
		if (size != m_vertex_count)
		{
			delete[] m_positions;
			m_vertex_count = size;
			m_positions = new Vector3[size];
			return true;
		}
		return false;
	}
	bool resizeIndices(u_int size)
	{
		if (size != m_indices_count)
		{
			delete[] m_indices;
			m_indices_count = size;
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

		updateIndexedData<Vector3>(m_positions, m_indexed_positions);

		return *this;
	}
	VertexArray& setColors(Color3F* start, u_int size)
	{
		assert(size == m_vertex_count);

		Utility::CopyrArray(start, m_colors, size);

		updateIndexedData<Color3F>(m_colors, m_indexed_colors);

		return *this;
	}
	VertexArray& setIndices(u_int* start, u_int size)
	{
		resizeIndices(size);

		Utility::CopyrArray(start, m_indices, size);

		updateIndexedData<Vector3>(m_positions, m_indexed_positions);
		updateIndexedData<Color3F>(m_colors, m_indexed_colors);

		return *this;
	}

	VertexArray& setPosition(int index, Vector3 vector)
	{
		assert(index >= 0 && index < (int)m_vertex_count);
		m_positions[index] = vector;

		return *this;
	}
	VertexArray& setIndex(int index, u_int indexValue)
	{
		assert(index >= 0 && index < (int)m_indices_count);
		m_indices[index] = indexValue;

		return *this;
	}
	VertexArray& setColor(int index, Color3F color)
	{
		assert(index >= 0 && index < (int)m_vertex_count);
		m_colors[index] = color;

		return *this;
	}

	VertexArray& setMode(Mode m)
	{
		m_mode = m;
		return *this;
	}
	
	// Getters for Data //
	Vector3* getPositionArrayStart() const
	{
		return m_positions;
	}
	Color3F* getColorsArrayStart() const
	{
		return m_colors;
	}
	u_int* getIndicesArrayStart() const
	{
		return m_indices;
	}
	Vector3* getIndexedPositionArrayStart() const
	{
		return m_indexed_positions;
	}
	Color3F* getIndexedColorsArrayStart() const
	{
		return m_indexed_colors;
	}

	const Vector3& getPosition(int index) const
	{
		assert(m_positions != nullptr && index < (int)m_vertex_count);
		return m_positions[index];
	}
	const Color3F& getColor(int index) const
	{
		assert(m_colors != nullptr && index < (int)m_vertex_count);
		return m_colors[index];
	}
	const u_int& getIndex(int index) const
	{
		assert(m_indices != nullptr && index < (int)m_indices_count);
		return m_indices[index];
	}
	

	// Misc Getters //
	Mode getMode() const
	{
		return m_mode;
	}

	u_int getDrawCount() const
	{
		// No indices = size of positions
		if (m_indices == nullptr)
			return m_vertex_count;
		// Indices = size of indices
		return m_indices_count;
	}

	//	VertexArray& operator=(const VertexArray& VA)
	//	{
	//		m_positions_size = VA.m_positions_size;
	//		m_positions = new Vector3[m_positions_size];
	//		Utility::CopyrArray(VA.m_positions, m_positions, m_positions_size);
	//	
	//		m_indices = new u_int[m_indices_size];
	//		m_indices_size = VA.m_indices_size;
	//		Utility::CopyrArray(VA.m_indices, m_indices, m_indices_size);
	//	
	//		m_mode = VA.m_mode;
	//		return *this;
	//	}

};