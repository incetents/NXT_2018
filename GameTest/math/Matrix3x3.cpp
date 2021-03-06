
#include "stdafx.h"

#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Vector2.h"
#include "Vector3.h"
#include "MathCore.h"

// Identity Matrix
const Matrix3x3 Matrix3x3::_Identity = Matrix3x3(
	1, 0, 0,
	0, 1, 0,
	0, 0, 1);

// Constructors
Matrix3x3::Matrix3x3(void)
{
	Identity();
}
Matrix3x3::Matrix3x3(Matrix2x2& m)
{
	_Val[0] = m[0];
	_Val[1] = m[1];
	_Val[2] = 0;
	_Val[3] = m[2];
	_Val[4] = m[3];
	_Val[5] = 0;
	_Val[6] = 0;
	_Val[7] = 0;
	// Set last value as 1
	_Val[8]  = 1.0f;
}
Matrix3x3::Matrix3x3(const Vector3* Rows)
{
	*this = Matrix3x3(
		Vector3(*(Rows + 0)),
		Vector3(*(Rows + 1)),
		Vector3(*(Rows + 2))
	);
}
Matrix3x3::Matrix3x3(const Vector3& Row1, const Vector3& Row2, const Vector3& Row3)
{
	_Val[0] = Row1.x;
	_Val[1] = Row1.y;
	_Val[2] = Row1.z;
	_Val[3] = Row2.x;
	_Val[4] = Row2.y;
	_Val[5] = Row2.z;
	_Val[6] = Row3.x;
	_Val[7] = Row3.y;
	_Val[8] = Row3.z;
}
Matrix3x3::Matrix3x3(
	const float xx, const float xy, const float xz,
	const float yx, const float yy, const float yz,
	const float zx, const float zy, const float zz)
{
	_Val[0] = xx;
	_Val[1] = xy;
	_Val[2] = xz;
	_Val[3] = yx;
	_Val[4] = yy;
	_Val[5] = yz;
	_Val[6] = zx;
	_Val[7] = zy;
	_Val[8] = zz;
}
Matrix3x3::Matrix3x3(const float Values[3][3])
{
	_Val[0] = Values[0][0];
	_Val[1] = Values[0][1];
	_Val[2] = Values[0][2];
	_Val[3] = Values[1][0];
	_Val[4] = Values[1][1];
	_Val[5] = Values[1][2];
	_Val[6] = Values[2][0];
	_Val[7] = Values[2][1];
	_Val[8] = Values[2][2];
}

// Identity
void Matrix3x3::Identity()
{
	*this = Matrix3x3::_Identity;
}

// Become Scale Matrix
Matrix3x3& Matrix3x3::Scale(float size)
{
	return(this->Scale(size, size, size));
}
Matrix3x3& Matrix3x3::Scale(float x, float y, float z)
{
	_Val[0] = x;
	_Val[1] = 0;
	_Val[2] = 0;
	_Val[3] = 0;
	_Val[4] = y;
	_Val[5] = 0;
	_Val[6] = 0;
	_Val[7] = 0;
	_Val[8] = z;
	return *this;
}
Matrix3x3& Matrix3x3::Scale(const Vector3& v)
{
	return(this->Scale(v.x, v.y, v.z));
}
// Acquire Scale Matrix
Matrix3x3 Matrix3x3::GetScale(float size)
{
	Matrix3x3 result;
	return result.Scale(size);
}
Matrix3x3 Matrix3x3::GetScale(float x, float y, float z)
{
	Matrix3x3 result;
	return result.Scale(x, y, z);
}
Matrix3x3 Matrix3x3::GetScale(const Vector3& v)
{
	Matrix3x3 result;
	return result.Scale(v.x, v.y, v.z);
}

// Become Rotation Matrix
Matrix3x3&   Matrix3x3::Rotation(Degrees& Deg, Axis Ax, RotationDirection Rot)
{
	// Convert to Radians
	return (Rotation(Radians(Deg.GetRadians()), Ax, Rot));
}
Matrix3x3 Matrix3x3::GetRotation(Degrees& Deg, Axis Ax, RotationDirection Rot)
{
	// Create Rotated Matrix
	Matrix3x3 Result;
	return (Result.Rotation(Deg, Ax, Rot));
}
// Become Rotation Matrix
Matrix3x3&   Matrix3x3::Rotation(Radians& Rad, Axis Ax, RotationDirection Rot)
{
	// Float Radians
	float Val = Rad.Get();

	// Rows
	Vector3 Row1;
	Vector3 Row2;
	Vector3 Row3;

	// Check Axis
	switch (Ax)
	{
	case Axis::X:
		//
		if (Rot == RotationDirection::COUNTER_CLOCKWISE)
		{
			// Matrix Values
			Row1 = Vector3(1.0f, 0.0f, 0.0f);
			Row2 = Vector3(0.0f, +cosf(Val), -sinf(Val));
			Row3 = Vector3(0.0f, +sinf(Val), +cosf(Val));
		}
		else
		{
			// Matrix Values
			Row1 = Vector3(1.0f, 0.0f, 0.0f);
			Row2 = Vector3(0.0f, +cosf(Val), +sinf(Val));
			Row3 = Vector3(0.0f, -sinf(Val), +cosf(Val));
		}
		//
		break;

	case Axis::Y:
		//
		if (Rot == RotationDirection::COUNTER_CLOCKWISE)
		{
			// Matrix Values
			Row1 = Vector3(+cosf(Val), 0.0f, +sinf(Val));
			Row2 = Vector3(0.0f, 1.0f, 0.0f);
			Row3 = Vector3(-sinf(Val), 0.0f, +cosf(Val));
		}
		else
		{
			// Matrix Values
			Row1 = Vector3(+cosf(Val), 0.0f, -sinf(Val));
			Row2 = Vector3(0.0f, 1.0f, 0.0f);
			Row3 = Vector3(+sinf(Val), 0.0f, +cosf(Val));
		}
		//
		break;

	case Axis::Z:
		//
		if (Rot == RotationDirection::COUNTER_CLOCKWISE)
		{
			// Matrix Values
			Row1 = Vector3(+cosf(Val), -sinf(Val), 0.0f);
			Row2 = Vector3(+sinf(Val), +cosf(Val), 0.0f);
			Row3 = Vector3(0.0f, 0.0f, 1.0f);
		}
		else
		{
			// Matrix Values
			Row1 = Vector3(+cosf(Val), +sinf(Val), 0.0f);
			Row2 = Vector3(-sinf(Val), +cosf(Val), 0.0f);
			Row3 = Vector3(0.0f, 0.0f, 1.0f);
		}
		//
		break;
	}

	// Convert to matrix
	return (*this = Matrix3x3(Row1, Row2, Row3));
}
Matrix3x3 Matrix3x3::GetRotation(Radians& Rad, Axis Ax, RotationDirection Rot)
{
	// Create Rotated Matrix
	Matrix3x3 Result;
	// Return
	return (Result.Rotation(Rad, Ax, Rot));
}

// Become Rotation Matrix for all axis
Matrix3x3&   Matrix3x3::Rotation(Degrees& Deg, const Vector3& Direction, RotationDirection Rot)
{
	return (Rotation(Radians(Deg.GetRadians()), Direction, Rot));
}
Matrix3x3 Matrix3x3::GetRotation(Degrees& Deg, const Vector3& Direction, RotationDirection Rot)
{
	Matrix3x3 Result;
	return (Result.Rotation(Deg, Direction, Rot));
}
// Become Rotation Matrix for all axis
Matrix3x3&   Matrix3x3::Rotation(Radians& Rad, const Vector3& Direction, RotationDirection Rot)
{
	// Get Rotation Amount
	float R = Rad.Get();
	// Get Direction and normalize it
	Vector3 V = Direction.Normalize();

	// Calculate some numbers beforehand
	float xy = V.x * V.y;
	float xz = V.x * V.z;
	float yz = V.y * V.z;
	float Inv_Cos = 1 - cosf(R);

	Matrix3x3 M;
	if (Rot == RotationDirection::CLOCKWISE)
	{
		// Inverse Rotation Direction
		R = (2 * PI) - R;
	}

	M[0] = V.x * V.x * (Inv_Cos)+cosf(R);
	M[1] = xy		* (Inv_Cos)-sinf(R) * V.z;
	M[2] = xz		* (Inv_Cos)+sinf(R) * V.y;
	M[3] = xy		* (Inv_Cos)+sinf(R) * V.z;
	M[4] = V.y * V.y * (Inv_Cos)+cosf(R);
	M[5] = yz		* (Inv_Cos)-sinf(R) * V.x;
	M[6] = xz		* (Inv_Cos)-sinf(R) * V.y;
	M[7] = yz		* (Inv_Cos)+sinf(R) * V.x;
	M[8] = V.z * V.z * (Inv_Cos)+cosf(R);

	return (*this = M);
}
Matrix3x3 Matrix3x3::GetRotation(Radians& Rad, const Vector3& Direction, RotationDirection Rot)
{
	Matrix3x3 Result;
	return (Result.Rotation(Rad, Direction, Rot));
}

// Set Horizontal Line
void Matrix3x3::SetRow(int index, const Vector3& r)
{
	assert((index >= 0) && (index < Matrix3x3_Length));
	_Val[index * Matrix3x3_Length + 0] = r.x;
	_Val[index * Matrix3x3_Length + 1] = r.y;
	_Val[index * Matrix3x3_Length + 2] = r.z;
}
void Matrix3x3::SetRow(Matrix3x3& m, int index, const Vector3& r)
{
	assert((index >= 0) && (index < Matrix3x3_Length));
	m.SetRow(index, r);
}
// Set Vertical Line
void Matrix3x3::SetColumn(int index, const Vector3& c)
{
	assert((index >= 0) && (index < Matrix3x3_Length));
	_Val[(index + 0)] = c.x;
	_Val[(index + 3)] = c.y;
	_Val[(index + 6)] = c.z;
}
void Matrix3x3::SetColumn(Matrix3x3& m, int index, const Vector3& c)
{
	assert((index >= 0) && (index < Matrix3x3_Length));
	m.SetColumn(index, c);
}

// Get Horizontal Line
Vector3 Matrix3x3::GetRow(int index) const
{
	assert((index >= 0) && (index < Matrix3x3_Length));
	return Vector3(
		_Val[0 + (index * Matrix3x3_Length)],
		_Val[1 + (index * Matrix3x3_Length)],
		_Val[2 + (index * Matrix3x3_Length)]
	);
}
Vector3 Matrix3x3::GetRow(const Matrix3x3& m, int index)
{
	assert((index >= 0) && (index < Matrix3x3_Length));
	return m.GetRow(index);
}
// Get Vertical Line
Vector3 Matrix3x3::GetColumn(int index) const
{
	assert((index >= 0) && (index < Matrix3x3_Length));
	return Vector3(
		_Val[(index + 0)],
		_Val[(index + 3)],
		_Val[(index + 6)]
	);
}
Vector3 Matrix3x3::GetColumn(const Matrix3x3& m, int index)
{
	assert((index >= 0) && (index < Matrix3x3_Length));
	return m.GetColumn(index);
}

// Determinant
float Matrix3x3::Determinant() const
{
	/*
	float det2_12_01 = _Val[1][0] * _Val[2][1] - _Val[1][1] * _Val[2][0];
	float det2_12_02 = _Val[1][0] * _Val[2][2] - _Val[1][2] * _Val[2][0];
	float det2_12_12 = _Val[1][1] * _Val[2][2] - _Val[1][2] * _Val[2][1];
	*/
	float det2_12_01 = _Val[3] * _Val[7] - _Val[4] * _Val[6];
	float det2_12_02 = _Val[3] * _Val[8] - _Val[5] * _Val[6];
	float det2_12_12 = _Val[4] * _Val[8] - _Val[5] * _Val[7];

	return _Val[0] * det2_12_12 - _Val[1] * det2_12_02 + _Val[2] * det2_12_01;
}
float Matrix3x3::Determinant(const Matrix3x3& m)
{
	return m.Determinant();
}

// Transpose
Matrix3x3 Matrix3x3::Transpose() const
{
	return Matrix3x3(
		_Val[0], _Val[3], _Val[6],
		_Val[1], _Val[4], _Val[7],
		_Val[2], _Val[5], _Val[8]);
}
Matrix3x3 Matrix3x3::Transpose(const Matrix3x3& m)
{
	return m.Transpose();
}
// Transpose Self
Matrix3x3& Matrix3x3::TransposeSelf()
{
	*this = Transpose();

	return *this;
}
Matrix3x3& Matrix3x3::TransposeSelf(Matrix3x3& m)
{
	return m.TransposeSelf();
}

// Inverse
Matrix3x3 Matrix3x3::Inverse() const
{
	float det = Determinant();
	if (abs(det) < MATRIX_INVERSE_EPSILON)
		return *this;

	float inva = 1.0f / det;
	return Matrix3x3(
		_Val[4] * _Val[8] - _Val[7] * _Val[5],
		_Val[6] * _Val[5] - _Val[3] * _Val[8],
		_Val[3] * _Val[7] - _Val[6] * _Val[6],
		_Val[7] * _Val[2] - _Val[1] * _Val[8],
		_Val[0] * _Val[8] - _Val[6] * _Val[2],
		_Val[6] * _Val[1] - _Val[0] * _Val[7],
		_Val[1] * _Val[5] - _Val[4] * _Val[2],
		_Val[3] * _Val[2] - _Val[0] * _Val[5],
		_Val[0] * _Val[4] - _Val[3] * _Val[1]
	) * inva;
}
Matrix3x3 Matrix3x3::Inverse(const Matrix3x3& m)
{
	return m.Inverse();
}
// Inverse Self
Matrix3x3& Matrix3x3::InverseSelf()
{
	return (*this = this->Inverse());
}
Matrix3x3& Matrix3x3::InverseSelf(Matrix3x3& m)
{
	return m.InverseSelf();
}

// Multiply
Matrix3x3 Matrix3x3::Multiply(const Matrix3x3& m) const
{
	Matrix3x3 Result;

	for (int y = 0; y < Matrix3x3_Length; y++)
	{
		for (int x = 0; x < Matrix3x3_Length; x++)
		{
			Result[x + y * Matrix3x3_Length] = Vector3::Dot(GetRow(y), m.GetColumn(x));
		}
	}

	return Result;
}
Matrix3x3 Matrix3x3::Multiply(const Matrix3x3& m1, const Matrix3x3& m2)
{
	return m1.Multiply(m2);
}

// Compare
bool Matrix3x3::Compare(const Matrix3x3& m) const
{
	for (int i = 0; i < Matrix3x3_Size; i++)
	{
		if (_Val[i] != m._Val[i])
			return false;
	}

	return true;
}
bool Matrix3x3::Compare(const Matrix3x3& m1, const Matrix3x3& m2)
{
	return m1.Compare(m2);
}

// To String
std::string Matrix3x3::ToString()
{
	return std::string(
		std::to_string(_Val[0x0]) + ' ' +
		std::to_string(_Val[0x1]) + ' ' +
		std::to_string(_Val[0x2]) + ' ' +
		std::to_string(_Val[0x3]) + ' ' +
		std::to_string(_Val[0x4]) + ' ' +
		std::to_string(_Val[0x5]) + ' ' +
		std::to_string(_Val[0x6]) + ' ' +
		std::to_string(_Val[0x7]) + ' ' +
		std::to_string(_Val[0x8]) + ' '
	);
}

// Lerp
Matrix3x3 Matrix3x3::Lerp(const Matrix3x3& m, float t) const
{
	Matrix3x3 Result;

	for (int i = 0; i < Matrix3x3_Size; i++)
	{
		Result[i] = MathCore::Lerp(_Val[i], m._Val[i], t);
	}

	return Result;
}
Matrix3x3 Matrix3x3::Lerp(const Matrix3x3& m1, const Matrix3x3& m2, float t)
{
	return m1.Lerp(m2, t);
}

// Operator Overloads
float& Matrix3x3::operator[](int index)
{
	assert((index >= 0) && (index < Matrix3x3_Size));
	return _Val[index];
}
float Matrix3x3::operator[](int index) const
{
	assert((index >= 0) && (index < Matrix3x3_Size));
	return _Val[index];
}

Matrix3x3 Matrix3x3::operator-() const
{
	return Matrix3x3(
		-_Val[0],
		-_Val[1],
		-_Val[2],
		-_Val[3],
		-_Val[4],
		-_Val[5],
		-_Val[6],
		-_Val[7],
		-_Val[8]
	);
}

// Matrix -- Vector Multiplication
Vector3 operator*(const Matrix3x3& m, const Vector3& v)
{
	return Vector3(
		m._Val[0] * v.x + m._Val[1] * v.y + m._Val[2] * v.z,
		m._Val[3] * v.x + m._Val[4] * v.y + m._Val[5] * v.z,
		m._Val[6] * v.x + m._Val[7] * v.y + m._Val[8] * v.z
	);
}
Vector3 operator*(const Vector3& v, const Matrix3x3& m)
{
	return Vector3(
		m._Val[0] * v.x + m._Val[1] * v.x + m._Val[2] * v.x,
		m._Val[3] * v.y + m._Val[4] * v.y + m._Val[5] * v.y,
		m._Val[6] * v.z + m._Val[7] * v.z + m._Val[8] * v.z
	);
}
// Matrix -- Matrix Multiplication
Matrix3x3 Matrix3x3::operator*(const Matrix3x3& m) const
{
	return Multiply(m);
}
Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& m)
{
	*this = Multiply(m);

	return *this;
}


// Operator Overloads
Matrix3x3  Matrix3x3::operator+(const Matrix3x3& m) const
{
	return Matrix3x3(
		_Val[0] + m._Val[0],
		_Val[1] + m._Val[1],
		_Val[2] + m._Val[2],
		_Val[3] + m._Val[3],
		_Val[4] + m._Val[4],
		_Val[5] + m._Val[5],
		_Val[6] + m._Val[6],
		_Val[7] + m._Val[7],
		_Val[8] + m._Val[8]
	);
}

Matrix3x3  Matrix3x3::operator-(const Matrix3x3& m) const
{
	return Matrix3x3(
		_Val[0] - m._Val[0],
		_Val[1] - m._Val[1],
		_Val[2] - m._Val[2],
		_Val[3] - m._Val[3],
		_Val[4] - m._Val[4],
		_Val[5] - m._Val[5],
		_Val[6] - m._Val[6],
		_Val[7] - m._Val[7],
		_Val[8] - m._Val[8]
	);
}

Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& m)
{
	for (int i = 0; i < Matrix3x3_Size; i++)
	{
		_Val[i] += m._Val[i];
	}

	return *this;
}

Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& m)
{
	for (int i = 0; i < Matrix3x3_Size; i++)
	{
		_Val[i] -= m._Val[i];
	}

	return *this;
}

Matrix3x3  Matrix3x3::operator+(const float f) const
{
	return Matrix3x3(
		_Val[0] + f,
		_Val[1] + f,
		_Val[2] + f,
		_Val[3] + f,
		_Val[4] + f,
		_Val[5] + f,
		_Val[6] + f,
		_Val[7] + f,
		_Val[8] + f
	);
}

Matrix3x3  Matrix3x3::operator-(const float f) const
{
	return Matrix3x3(
		_Val[0] - f,
		_Val[1] - f,
		_Val[2] - f,
		_Val[3] - f,
		_Val[4] - f,
		_Val[5] - f,
		_Val[6] - f,
		_Val[7] - f,
		_Val[8] - f
	);
}

Matrix3x3  Matrix3x3::operator*(const float f) const
{
	return Matrix3x3(
		_Val[0] * f,
		_Val[1] * f,
		_Val[2] * f,
		_Val[3] * f,
		_Val[4] * f,
		_Val[5] * f,
		_Val[6] * f,
		_Val[7] * f,
		_Val[8] * f
	);
}

Matrix3x3  Matrix3x3::operator/(const float f) const
{
	float inva = 1.0f / f;

	return Matrix3x3(
		_Val[0] * inva,
		_Val[1] * inva,
		_Val[2] * inva,
		_Val[3] * inva,
		_Val[4] * inva,
		_Val[5] * inva,
		_Val[6] * inva,
		_Val[7] * inva,
		_Val[8] * inva
	);
}

Matrix3x3& Matrix3x3::operator+=(const float f)
{
	for (int i = 0; i < Matrix3x3_Size; i++)
	{
		_Val[i] += f;
	}

	return *this;
}

Matrix3x3& Matrix3x3::operator-=(const float f)
{
	for (int i = 0; i < Matrix3x3_Size; i++)
	{
		_Val[i] -= f;
	}

	return *this;
}

Matrix3x3& Matrix3x3::operator*=(const float f)
{
	for (int i = 0; i < Matrix3x3_Size; i++)
	{
		_Val[i] *= f;
	}

	return *this;
}

Matrix3x3& Matrix3x3::operator/=(const float f)
{
	float inva = 1.0f / f;

	for (int i = 0; i < Matrix3x3_Size; i++)
	{
		_Val[i] *= inva;
	}

	return *this;
}

// Operator Comparison Overloading
Matrix3x3& Matrix3x3::operator= (const Matrix3x3& m)
{
	for (int i = 0; i < Matrix3x3_Size; i++)
	{
		_Val[i] = m._Val[i];
	}
	return *this;
}
bool Matrix3x3::operator== (const Matrix3x3& m) const
{
	return Compare(m);
}
bool Matrix3x3::operator!= (const Matrix3x3& m) const
{
	return !Compare(m);
}

std::ostream &operator<<(std::ostream &stream, const Matrix3x3& m)
{
	return (stream << m.GetRow(0) << '\n' << m.GetRow(1) << '\n' << m.GetRow(2));
}
