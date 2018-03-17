#pragma once

#include <string>

class Matrix2x2;
class Vector2;
class Vector3;
class Degrees;
class Radians;
enum class Axis;
enum class RotationDirection;

class Matrix3x3 {
private:
	// Identity Matrix
	static const Matrix3x3 _Identity;

	// Data
	float _Val[9];
	// 0 1 2
	// 3 4 5
	// 6 7 8

public:

			// Constructors
			 Matrix3x3(void);
	explicit Matrix3x3(Matrix2x2& m);
	explicit Matrix3x3(const Vector3* Rows);
	explicit Matrix3x3(const Vector3& Row1, const Vector3& Row2, const Vector3& Row3);
	explicit Matrix3x3(
		const float xx, const float xy, const float xz,
		const float yx, const float yy, const float yz,
		const float zx, const float zy, const float zz);
	explicit Matrix3x3(const float Values[3][3]);

			// Become default empty matrix
			void Identity();

			// Become Scale Matrix
			Matrix3x3&   Scale(float size);
			Matrix3x3&   Scale(float x, float y, float z);
			Matrix3x3&   Scale(const Vector3& v);
	static  Matrix3x3 GetScale(float size);
	static  Matrix3x3 GetScale(float x, float y, float z);
	static  Matrix3x3 GetScale(const Vector3& v);

			// Become Rotation Matrix
			Matrix3x3&   Rotation(Degrees&, Axis, RotationDirection = (RotationDirection)0);
	static	Matrix3x3 GetRotation(Degrees&, Axis, RotationDirection = (RotationDirection)0);
			//
			Matrix3x3&   Rotation(Radians&, Axis, RotationDirection = (RotationDirection)0);
	static	Matrix3x3 GetRotation(Radians&, Axis, RotationDirection = (RotationDirection)0);

			// Become Rotation Matrix for all axis
			Matrix3x3&   Rotation(Degrees&, const Vector3& Direction, RotationDirection = (RotationDirection)0);
	static	Matrix3x3 GetRotation(Degrees&, const Vector3& Direction, RotationDirection = (RotationDirection)0);
			//
			Matrix3x3&   Rotation(Radians&, const Vector3& Direction, RotationDirection = (RotationDirection)0);
	static  Matrix3x3 GetRotation(Radians&, const Vector3& Direction, RotationDirection = (RotationDirection)0);

			// Set Horizontal Line
			void SetRow(int index, const Vector3&);
	static  void SetRow(Matrix3x3&, int index, const Vector3&);
			// Set Vertical Line
			void SetColumn(int index, const Vector3&);
	static	void SetColumn(Matrix3x3&, int index, const Vector3&);

			// Get Horizontal Line
			Vector3 GetRow(int index) const;
	static  Vector3 GetRow(const Matrix3x3&, int index);
			// Get Vertical Line
			Vector3 GetColumn(int index) const;
	static  Vector3 GetColumn(const Matrix3x3&, int index);

			// Determinant
			float Determinant() const;
	static  float Determinant(const Matrix3x3&);

			// Transpose
			Matrix3x3 Transpose() const;
	static  Matrix3x3 Transpose(const Matrix3x3&);
			// Transpose Self
			Matrix3x3& TransposeSelf();
	static  Matrix3x3& TransposeSelf(Matrix3x3&);

			// Inverse
			Matrix3x3 Inverse() const;
	static  Matrix3x3 Inverse(const Matrix3x3&);
			// Inverse Self
			Matrix3x3& InverseSelf();
	static	Matrix3x3& InverseSelf(Matrix3x3&);

			// Multiply
			Matrix3x3 Multiply(const Matrix3x3&) const;
	static	Matrix3x3 Multiply(const Matrix3x3&, const Matrix3x3&);

			// Compare
			bool Compare(const Matrix3x3&) const;
	static	bool Compare(const Matrix3x3&, const Matrix3x3&);

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
			Matrix3x3 Lerp(const Matrix3x3&, float t) const;
	static	Matrix3x3 Lerp(const Matrix3x3&, const Matrix3x3&, float t);

	// Special Operator Overloads
	float& operator[](int);
	float operator[](int) const;
	Matrix3x3 operator-() const;

	// Matrix -- Vector Multiplication
	friend Vector3 operator*(const Matrix3x3& m, const Vector3& v);
	friend Vector3 operator*(const Vector3& v, const Matrix3x3& m);
	// Matrix -- Matrix Multiplication
	Matrix3x3 operator*(const Matrix3x3&) const;
	Matrix3x3& operator*=(const Matrix3x3&);

	// Operator Overloads
	Matrix3x3 operator+(const Matrix3x3&) const;
	Matrix3x3 operator-(const Matrix3x3&) const;
	Matrix3x3& operator+=(const Matrix3x3&);
	Matrix3x3& operator-=(const Matrix3x3&);
	Matrix3x3 operator+(const float) const;
	Matrix3x3 operator-(const float) const;
	Matrix3x3 operator*(const float) const;
	Matrix3x3 operator/(const float) const;
	Matrix3x3& operator+=(const float);
	Matrix3x3& operator-=(const float);
	Matrix3x3& operator*=(const float);
	Matrix3x3& operator/=(const float);

	// Operator Comparison Overloading
	Matrix3x3& operator= (const Matrix3x3&);
	bool operator== (const Matrix3x3&) const;
	bool operator!= (const Matrix3x3&) const;

	// Cout Overload
	friend std::ostream &operator<<(std::ostream &stream, const Matrix3x3&);
};