
#include "stdafx.h"

#include "Matrix2x2.h"
#include "Vector2.h"
#include "MathCore.h"

// Identity Matrix
const Matrix2x2 Matrix2x2::_Identity = Matrix2x2(1, 0, 0, 1);

// Constructors
Matrix2x2::Matrix2x2(void)
{
	Identity();
}
Matrix2x2::Matrix2x2(const Vector2* Rows)
{
	for (int i = 0; i < Matrix2x2_Length; i++)
	{
		_Val[i * Matrix2x2_Length + 0] = Rows[i].x;
		_Val[i * Matrix2x2_Length + 1] = Rows[i].y;
	}
}
Matrix2x2::Matrix2x2(const Vector2& Row1, const Vector2& Row2)
{
	_Val[0] = Row1.x;
	_Val[1] = Row1.y;
	_Val[2] = Row2.x;
	_Val[3] = Row2.y;
}
Matrix2x2::Matrix2x2(const float xx, const float xy, const float yx, const float yy)
{
	_Val[0] = xx;
	_Val[1] = xy;
	_Val[2] = yx;
	_Val[3] = yy;
}
Matrix2x2::Matrix2x2(const float Values[2][2])
{
	_Val[0] = Values[0][0];
	_Val[1] = Values[0][1];
	_Val[2] = Values[1][0];
	_Val[3] = Values[1][1];
}

// Identity
void Matrix2x2::Identity()
{
	*this = Matrix2x2::_Identity;
}

// Become Rotation Matrix
Matrix2x2& Matrix2x2::Rotation(Degrees& Deg, RotationDirection Rot = RotationDirection::COUNTER_CLOCKWISE)
{
	return (this->Rotation(Radians(Deg), Rot));
}
Matrix2x2 Matrix2x2::GetRotation(Degrees& Deg, RotationDirection Rot = RotationDirection::COUNTER_CLOCKWISE)
{
	Matrix2x2 Result;
	Result.Rotation(Radians(Deg), Rot);
	return Result;
}
Matrix2x2& Matrix2x2::Rotation(Radians& Rad, RotationDirection Rot = RotationDirection::COUNTER_CLOCKWISE)
{
	float Value = Rad.Get();

	if (Rot == RotationDirection::COUNTER_CLOCKWISE)
	{
		_Val[0] = +cosf(Value);
		_Val[1] = -sinf(Value);

		_Val[2] = +sinf(Value);
		_Val[3] = +cosf(Value);
	}
	else
	{
		_Val[0] = +cosf(Value);
		_Val[1] = +sinf(Value);

		_Val[2] = -sinf(Value);
		_Val[3] = +cosf(Value);
	}

	return *this;
}
Matrix2x2 Matrix2x2::GetRotation(Radians& Rad, RotationDirection Rot = RotationDirection::COUNTER_CLOCKWISE)
{
	Matrix2x2 Result;
	Result.Rotation(Rad, Rot);
	return Result;
}

// Set Horizontal Line
void Matrix2x2::SetRow(int index, const Vector2& r)
{
	assert((index >= 0) && (index < Matrix2x2_Length));
	_Val[index * Matrix2x2_Length + 0] = r.x;
	_Val[index * Matrix2x2_Length + 1] = r.y;
}
void Matrix2x2::SetRow(Matrix2x2& m, int index, const Vector2& r)
{
	m.SetRow(index, r);
}
// Set Vertical Line
void Matrix2x2::SetColumn(int index, const Vector2& c)
{
	assert((index >= 0) && (index < Matrix2x2_Length));
	_Val[(index + 0)] = c.x;
	_Val[(index + 2)] = c.y;
}
void Matrix2x2::SetColumn(Matrix2x2& m, int index, const Vector2& c)
{
	m.SetColumn(index, c);
}

// Get Horizontal Line
Vector2 Matrix2x2::GetRow(int index) const
{
	assert((index >= 0) && (index < Matrix2x2_Length));
	return Vector2(
		_Val[0 + (index * Matrix2x2_Length)],
		_Val[1 + (index * Matrix2x2_Length)]
	);
}
Vector2 Matrix2x2::GetRow(const Matrix2x2& m, int index)
{
	return m.GetRow(index);
}
// Get Vertical Line
Vector2 Matrix2x2::GetColumn(int index) const
{
	assert((index >= 0) && (index < Matrix2x2_Length));
	return Vector2(
		_Val[(index + 0)],
		_Val[(index + 2)]
	);
}
Vector2 Matrix2x2::GetColumn(const Matrix2x2& m, int index)
{
	return m.GetColumn(index);
}

// Determinant
float Matrix2x2::Determinant() const
{
	return _Val[0] * _Val[3] - _Val[1] * _Val[2];
}
float Matrix2x2::Determinant(const Matrix2x2& m)
{
	return m.Determinant();
}

// Transpose
Matrix2x2 Matrix2x2::Transpose() const
{
	return Matrix2x2(
		_Val[0], _Val[2],
		_Val[1], _Val[3]
	);
}
Matrix2x2 Matrix2x2::Transpose(const Matrix2x2& m)
{
	return m.Transpose();
}
// Transpose Self
Matrix2x2& Matrix2x2::TransposeSelf()
{
	MathCore::Swap<float>(_Val[1], _Val[2]);
	return *this;
}
Matrix2x2& Matrix2x2::TransposeSelf(Matrix2x2& m)
{
	return m.TransposeSelf();
}

// Inverse
Matrix2x2 Matrix2x2::Inverse() const
{
	float det = Determinant();
	if (abs(det) < MATRIX_INVERSE_EPSILON)
		return *this;

	float inva = 1.0f / Determinant();
	return Matrix2x2(
		+ _Val[3], - _Val[1],
		- _Val[2], + _Val[0]
	) * inva;
}
Matrix2x2 Matrix2x2::Inverse(const Matrix2x2& m)
{
	return m.Inverse();
}
// Inverse Self
Matrix2x2& Matrix2x2::InverseSelf()
{
	_Val[0] = +_Val[3];
	_Val[1] = -_Val[1];
	_Val[2] = -_Val[2];
	_Val[3] = +_Val[0];

	return *this;
}
Matrix2x2& Matrix2x2::InverseSelf(Matrix2x2& m)
{
	return m.InverseSelf();
}

// Multiply
Matrix2x2 Matrix2x2::Multiply(const Matrix2x2& m) const
{
	Matrix2x2 Result;

	for (int y = 0; y < Matrix2x2_Length; y++)
	{
		for (int x = 0; x < Matrix2x2_Length; x++)
		{
			Result[x + y * Matrix2x2_Length] = Vector2::Dot(GetRow(y), m.GetColumn(x));
		}
	}

	return Result;
}
Matrix2x2 Matrix2x2::Multiply(const Matrix2x2& m1, const Matrix2x2& m2)
{
	return m1.Multiply(m2);
}

// Compare
bool Matrix2x2::Compare(const Matrix2x2& m) const
{
	for (int i = 0; i < Matrix2x2_Size; i++)
	{
		if (_Val[i] != m._Val[i])
			return false;
	}
	return true;
}
bool Matrix2x2::Compare(const Matrix2x2& m1, const Matrix2x2& m2)
{
	return m1.Compare(m2);
}

// To String
std::string Matrix2x2::ToString()
{
	return std::string(
		std::to_string(_Val[0x0]) + ' ' +
		std::to_string(_Val[0x1]) + ' ' +
		std::to_string(_Val[0x2]) + ' ' +
		std::to_string(_Val[0x3]) + ' '
	);
}

// Lerp
Matrix2x2 Matrix2x2::Lerp(const Matrix2x2& m, float t) const
{
	Matrix2x2 Result;

	for (int i = 0; i < Matrix2x2_Size; i++)
	{
		Result[i] = MathCore::Lerp(_Val[i], m._Val[i], t);
	}

	return Result;
}
Matrix2x2 Matrix2x2::Lerp(const Matrix2x2& m1, const Matrix2x2& m2, float t)
{
	return m1.Lerp(m2, t);
}

// Matrix -- Vector Multiplication
Vector2 operator*(const Matrix2x2& m, const Vector2& v)
{
	return Vector2(
		m._Val[0] * v.x + m._Val[1] * v.y,
		m._Val[2] * v.x + m._Val[3] * v.y
	);
}
Vector2 operator*(const Vector2& v, const Matrix2x2& m)
{
	return Vector2(
		m._Val[0] * v.x + m._Val[2] * v.y,
		m._Val[1] * v.x + m._Val[3] * v.y
	);
}
// Matrix -- Matrix Multiplication
Matrix2x2 Matrix2x2::operator*(const Matrix2x2& m) const
{
	return Multiply(m);
}
Matrix2x2& Matrix2x2::operator*=(const Matrix2x2& m)
{
	return (*this = Multiply(m));
}

// Operator Overloads
float& Matrix2x2::operator[](int index)
{
	assert((index >= 0) && (index < Matrix2x2_Size));
	return _Val[index];
}
float Matrix2x2::operator[](int index) const
{
	assert((index >= 0) && (index < Matrix2x2_Size));
	return _Val[index];
}

Matrix2x2 Matrix2x2::operator-() const
{
	return Matrix2x2(
		-_Val[0], -_Val[1],
		-_Val[2], -_Val[3]
	);
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2& m) const
{
	return Matrix2x2(
		_Val[0] + m._Val[0],
		_Val[1] + m._Val[1],
		_Val[2] + m._Val[2],
		_Val[3] + m._Val[3]
	);
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2& m) const
{
	return Matrix2x2(
		_Val[0] - m._Val[0],
		_Val[1] - m._Val[1],
		_Val[2] - m._Val[2],
		_Val[3] - m._Val[3]
	);
}

Matrix2x2& Matrix2x2::operator+=(const Matrix2x2& m)
{
	_Val[0] += m._Val[0];
	_Val[1] += m._Val[1];
	_Val[2] += m._Val[2];
	_Val[3] += m._Val[3];

	return *this;
}

Matrix2x2& Matrix2x2::operator-=(const Matrix2x2& m)
{
	_Val[0] -= m._Val[0];
	_Val[1] -= m._Val[1];
	_Val[2] -= m._Val[2];
	_Val[3] -= m._Val[3];

	return *this;
}

Matrix2x2  Matrix2x2::operator+(const float f) const
{
	return Matrix2x2(
		_Val[0] + f,
		_Val[1] + f,
		_Val[2] + f,
		_Val[3] + f
	);
}

Matrix2x2 Matrix2x2::operator-(const float f) const
{
	return Matrix2x2(
		_Val[0] - f,
		_Val[1] - f,
		_Val[2] - f,
		_Val[3] - f
	);
}

Matrix2x2 Matrix2x2::operator*(const float f) const
{
	return Matrix2x2(
		_Val[0] * f,
		_Val[1] * f,
		_Val[2] * f,
		_Val[3] * f
	);
}

Matrix2x2 Matrix2x2::operator/(const float f) const
{
	float inva = 1.0f / f;

	return Matrix2x2(
		_Val[0] * inva,
		_Val[1] * inva,
		_Val[2] * inva,
		_Val[3] * inva);
}

Matrix2x2& Matrix2x2::operator+=(const float f)
{
	_Val[0] += f;
	_Val[1] += f;
	_Val[2] += f;
	_Val[3] += f;

	return *this;
}

Matrix2x2& Matrix2x2::operator-=(const float f)
{
	_Val[0] -= f;
	_Val[1] -= f;
	_Val[2] -= f;
	_Val[3] -= f;

	return *this;
}

Matrix2x2& Matrix2x2::operator*=(const float f)
{
	_Val[0] *= f;
	_Val[1] *= f;
	_Val[2] *= f;
	_Val[3] *= f;

	return *this;
}

Matrix2x2& Matrix2x2::operator/=(const float f)
{
	assert(f != 0.f);
	float inva = 1.0f / f;

	_Val[0] *= inva;
	_Val[1] *= inva;
	_Val[2] *= inva;
	_Val[3] *= inva;

	return *this;
}

// Operator Comparison Overloading
Matrix2x2& Matrix2x2::operator= (const Matrix2x2& m)
{
	for (int i = 0; i < Matrix2x2_Size; i++)
	{
		_Val[i] = m._Val[i];
	}
	return *this;
}
bool Matrix2x2::operator== (const Matrix2x2& m) const
{
	return Compare(m);
}
bool Matrix2x2::operator!= (const Matrix2x2& m) const
{
	return !Compare(m);
}

std::ostream &operator<<(std::ostream &stream, const Matrix2x2& m)
{
	return (stream << m.GetRow(0) << '\n' << m.GetRow(1));
}
