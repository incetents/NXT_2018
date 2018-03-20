#pragma once

#include <Windows.h>
#include <winsock.h>
#include <assert.h>

#include "Vector3.h"
#include "../Utility/Utility.h"
#include "Color.h"

template <class Type>
class VertexBuffer
{
private:
	u_int m_size = -1;
	Type* m_data = nullptr;
	Type* m_indexed_data = nullptr;

public:
	u_int getSize()
	{
		return m_size;
	}

	void createData(Type* data, u_int size)
	{
		if (m_size != size)
		{
			deleteData();
			m_size = size;
			m_data = new Type[size];
		}

		Utility::CopyArray(data, m_data, size);

	}
	void deleteData()
	{
		if (m_data != nullptr)
			delete[] m_data;

		m_size = -1;
		m_data = nullptr;
	}
	Type* getData()
	{
		return m_data;
	}

	void createIndexedData(u_int* indices, u_int size)
	{
		deleteIndexedData();

		assert(m_data != nullptr);

		// Create indexed data from main data
		m_indexed_data = new Type[size];
		for (u_int i = 0; i < size; i++)
		{
			Type test = m_data[indices[i]];
			m_indexed_data[i] = m_data[indices[i]];
		}
	}
	void deleteIndexedData()
	{
		if (m_indexed_data != nullptr)
			delete[] m_indexed_data;

		m_indexed_data = nullptr;
	}
	Type* getIndexedData()
	{
		return m_indexed_data;
	}

	void deleteAll()
	{
		deleteData();
		deleteIndexedData();
	}
};

class VertexArray
{
public:
	enum BufferType
	{
		POSITION,
		COLORS,
		SIZES
	};
	enum Mode
	{
		POINTS,		// Draws Multiple Points
		LINES,		// Every 2 points is a unique line
		LINE_STRIPS,// All lines are connected from tip to back
		TRIANGLE,	// Every 3 points is a self contained triangle
	};
protected:

	u_int	 m_vertex_count = -1;
	u_int    m_index_count  = -1;

	VertexBuffer<Vector3> m_positions;
	VertexBuffer<Color3F> m_colors;
	VertexBuffer<float>   m_sizes;

	u_int*   m_indices = nullptr;

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

	VertexArray(u_int vertexCount, Mode mode = Mode::LINES)
	{
		m_vertex_count = vertexCount;
		m_mode = mode;
	}
	~VertexArray()
	{
		m_positions.deleteAll();
		m_colors.deleteAll();
		m_sizes.deleteAll();
	}

	// Setting Data
	VertexArray& setPositions(Vector3 positions[], u_int size)
	{
		if (m_vertex_count <= 0)
			return *this;

		m_positions.createData(positions, size);

		if (m_indices != nullptr)
			m_positions.createIndexedData(m_indices, m_index_count);

		return *this;
	}
	VertexArray& setColors(Color3F colors[], u_int size)
	{
		if (m_vertex_count <= 0)
			return *this;

		m_colors.createData(colors, size);

		if (m_indices != nullptr)
			m_colors.createIndexedData(m_indices, m_index_count);

		return *this;
	}
	VertexArray& setSizes(float sizes[], u_int size)
	{
		if (m_vertex_count <= 0)
			return *this;

		m_sizes.createData(sizes, size);

		if (m_indices != nullptr)
			m_sizes.createIndexedData(m_indices, m_index_count);

		return *this;
	}
	VertexArray& setIndices(u_int indices[], u_int size)
	{
		if (m_indices != nullptr)
			delete[] m_indices;

		m_indices = new u_int[size];
		Utility::CopyArray(indices, m_indices, size);

		m_index_count = size;

		// Update Indexed for all 
		if(m_positions.getData() != nullptr)
			m_positions.createIndexedData(m_indices, m_index_count);

		if (m_colors.getData() != nullptr)
			m_colors.createIndexedData(m_indices, m_index_count);

		if (m_sizes.getData() != nullptr)
			m_sizes.createIndexedData(m_indices, m_index_count);
		//
		return *this;
	}

	// Removing Data
	VertexArray& removePositions()
	{
		m_positions.deleteData();
		return *this;
	}
	VertexArray& removeColors()
	{
		m_colors.deleteData();
		return *this;
	}
	VertexArray& removeSizes()
	{
		m_sizes.deleteData();
		return *this;
	}
	VertexArray& removeIndices()
	{
		if (m_indices != nullptr)
			delete[] m_indices;

		m_indices = nullptr;
		m_index_count = -1;
		return *this;
	}

	// Getters (accounts for indexed mode or not)
	Vector3* getPositions()
	{
		// Vertex Count
		if(m_indices == nullptr)
			return m_positions.getData();
		else
			return m_positions.getIndexedData();
	}
	Color3F* getColors()
	{
		// Vertex Count
		if (m_indices == nullptr)
			return m_colors.getData();
		else
			return m_colors.getIndexedData();
	}
	float* getSizes()
	{
		// Vertex Count
		if (m_indices == nullptr)
			return m_sizes.getData();
		else
			return m_sizes.getIndexedData();
	}

	// Misc Getters //
	const Mode& getMode() const
	{
		return m_mode;
	}
	const u_int& getDrawCount() const
	{
		// No indices = size of positions
		if (m_indices == nullptr)
			return m_vertex_count;
		// Indices = size of indices
		return m_index_count;
	}
	const u_int& getVertexCount() const
	{
		return m_vertex_count;
	}


	//	VertexArray(
	//		Vector3* pos_start,
	//		u_int* indices_start = nullptr,
	//		Color3F* color_start = nullptr,
	//		u_int vertex_count = 0,
	//		u_int indiex_count = 0,
	//		Mode mode = Mode::LINES)
	//	{
	//		assert(pos_start != nullptr);
	//	
	//		m_mode = mode;
	//	
	//		m_vertex_count = vertex_count;
	//		m_positions = new Vector3[m_vertex_count];
	//		Utility::CopyrArray(pos_start, m_positions, m_vertex_count);
	//	
	//		if (color_start != nullptr)
	//		{
	//			m_colors = new Color3F[m_vertex_count];
	//			Utility::CopyrArray(color_start, m_colors, m_vertex_count);
	//		}
	//		
	//		if (indices_start != nullptr)
	//		{
	//			m_indices_count = indiex_count;
	//			m_indices = new u_int[indiex_count];
	//			Utility::CopyrArray(indices_start, m_indices, indiex_count);
	//		}
	//	
	//		updateIndexedData<Vector3>(m_positions, m_indexed_positions);
	//		updateIndexedData<Color3F>(m_colors, m_indexed_colors);
	//	}
	//	~VertexArray()
	//	{
	//		if (m_positions != nullptr)
	//			delete[] m_positions;
	//	
	//		if (m_indices != nullptr)
	//			delete[] m_indices;
	//	
	//		if (m_colors != nullptr)
	//			delete[] m_colors;
	//	
	//		if (m_indexed_positions != nullptr)
	//			delete[] m_indexed_positions;
	//	
	//		if (m_indexed_colors != nullptr)
	//			delete[] m_indexed_colors;
	//	}

	/*
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

	// Re-update Indexed Position
	void ReupdateIndexedData()
	{
		updateIndexedData<Vector3>(m_positions, m_indexed_positions);
		updateIndexedData<Color3F>(m_colors, m_indexed_colors);
	}

	// Checkers
	inline bool CheckIndexMode()
	{
		return (m_indices != nullptr);
	}
	inline bool CheckHasColor()
	{
		return (m_colors != nullptr);
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
	*/
	

};