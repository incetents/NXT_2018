#pragma once

#include <string>
#include <sstream>

class Vector2;
class Degrees;
class Radians;
enum class Axis;
enum class RotationDirection;

class Matrix2x2
{
private:
	// Identity Matrix
	static const Matrix2x2 _Identity;

	// Data in Row Format
	float _Val[4];
	// 0 1
	// 2 3

public:

			// Constructors
			 Matrix2x2(void);
	explicit Matrix2x2(const Vector2* Rows);
	explicit Matrix2x2(const Vector2& Row1, const Vector2& Row2);
	explicit Matrix2x2(const float xx, const float xy, const float yx, const float yy);
	explicit Matrix2x2(const float Values[2][2]);

			// Become default empty matrix
			void Identity();

			// Become Rotation Matrix
			Matrix2x2&   Rotation(Degrees& Deg, RotationDirection Rot);
	static	Matrix2x2 GetRotation(Degrees& Deg, RotationDirection Rot);
			//
			Matrix2x2&   Rotation(Radians& Rad, RotationDirection Rot);
	static	Matrix2x2 GetRotation(Radians& Rad, RotationDirection Rot);

			// Set Horizontal Line
			void SetRow(int index, const Vector2&);
	static	void SetRow(Matrix2x2&, int index, const Vector2&);
			// Set Vertical Line
			void SetColumn(int index, const Vector2&);
	static	void SetColumn(Matrix2x2&, int index, const Vector2&);

			// Get Horizontal Line
			Vector2 GetRow(int index) const;
	static	Vector2 GetRow(const Matrix2x2&, int index);
			// Get Vertical Line
			Vector2 GetColumn(int index) const;
	static	Vector2 GetColumn(const Matrix2x2&, int index);

			// Determinant
			float Determinant() const;
	static	float Determinant(const Matrix2x2&);

			// Transpose
			Matrix2x2 Transpose() const;
	static	Matrix2x2 Transpose(const Matrix2x2&);
			// Transpose Self
			Matrix2x2& TransposeSelf();
	static	Matrix2x2& TransposeSelf(Matrix2x2&);

			// Inverse
			Matrix2x2 Inverse() const;
	static	Matrix2x2 Inverse(const Matrix2x2&);
			// Inverse Self
			Matrix2x2& InverseSelf();
	static	Matrix2x2& InverseSelf(Matrix2x2&);

			// Multiply
			Matrix2x2 Multiply(const Matrix2x2&) const;
	static	Matrix2x2 Multiply(const Matrix2x2&, const Matrix2x2&);

			// Compare
			bool Compare(const Matrix2x2&) const;
	static	bool Compare(const Matrix2x2&, const Matrix2x2&);

	inline const float* GetStartPointer()
	{
		return &_Val[0];
	}
	inline const float& GetStartReference() const
	{
		return _Val[0];
	}

			// Vector to string
			std::string ToString();

			// Lerp
			Matrix2x2 Lerp(const Matrix2x2&, float t) const;
	static	Matrix2x2 Lerp(const Matrix2x2&, const Matrix2x2&, float t);

	// Special Operator Overloads
	float& operator[](int);
	float operator[](int) const;
	Matrix2x2 operator-() const;

	// Matrix -- Vector Multiplication
	friend Vector2 operator*(const Matrix2x2& m, const Vector2& v);
	friend Vector2 operator*(const Vector2& v, const Matrix2x2& m);
	// Matrix -- Matrix Multiplication
	Matrix2x2 operator*(const Matrix2x2&) const;
	Matrix2x2& operator*=(const Matrix2x2&);

	// Operator Overloads
	Matrix2x2 operator+(const Matrix2x2&) const;
	Matrix2x2 operator-(const Matrix2x2&) const;
	Matrix2x2& operator+=(const Matrix2x2&);
	Matrix2x2& operator-=(const Matrix2x2&);
	Matrix2x2 operator+(const float) const;
	Matrix2x2 operator-(const float) const;
	Matrix2x2 operator*(const float) const;
	Matrix2x2 operator/(const float) const;
	Matrix2x2& operator+=(const float);
	Matrix2x2& operator-=(const float);
	Matrix2x2& operator*=(const float);
	Matrix2x2& operator/=(const float);

	// Operator Comparison Overloading
	Matrix2x2& operator= (const Matrix2x2&);
	bool operator== (const Matrix2x2&) const;
	bool operator!= (const Matrix2x2&) const;

	// Cout Overload
	friend std::ostream &operator<<(std::ostream &stream, const Matrix2x2&);


};