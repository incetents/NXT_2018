#pragma once

#include <string>

class Matrix2x2;
class Matrix3x3;
class Vector2;
class Vector3;
class Vector4;
class Degrees;
class Radians;
enum class Axis;
enum class RotationDirection;

class Matrix4x4
{
public:
	// Identity Matrix
	static const Matrix4x4 _Identity;

	// Data
	float _Val[16];
	// 0 1 2 3
	// 4 5 6 7
	// 8 9 A B
	// C D E F

public:

			// Constructors
			 Matrix4x4(void);
	explicit Matrix4x4(Matrix2x2& m);
	explicit Matrix4x4(Matrix2x2& m, const Vector3& center);
	explicit Matrix4x4(Matrix3x3& m);
	explicit Matrix4x4(Matrix3x3& m, const Vector3& center);
	explicit Matrix4x4(Vector3* Rows);
	explicit Matrix4x4(Vector4* Rows);
	explicit Matrix4x4(const Vector3& Row1, const Vector3& Row2, const Vector3& Row3);
	explicit Matrix4x4(const Vector4& Row1, const Vector4& Row2, const Vector4& Row3, const Vector4& Row4);
	explicit Matrix4x4(
		const float xx, const float xy, const float xz, const float xw,
		const float yx, const float yy, const float yz, const float yw,
		const float zx, const float zy, const float zz, const float zw,
		const float wx, const float wy, const float wz, const float ww);
	explicit Matrix4x4(const float Values[4][4]);

			// Become default empty matrix
			void Identity();

			// Become View Matrix
			Matrix4x4&    LookAt(Vector3 Eye, Vector3 Target, Vector3 Up);
	static	Matrix4x4  GetLookAt(Vector3 Eye, Vector3 Target, Vector3 Up);
			// Become Perspective Matrix
			Matrix4x4&    Perspective(float fovy, float aspect, float near, float far);
	static	Matrix4x4  GetPerspective(float fovy, float aspect, float near, float far);
			// Become Orthographic Matrix
			Matrix4x4&    Orthographic(float xmin, float xmax, float ymin, float ymax, float znear, float zfar);
	static	Matrix4x4  GetOrthographic(float xmin, float xmax, float ymin, float ymax, float znear, float zfar);

			// Special Sets
			Matrix4x4& OverrideCenter(const Vector3& center);
			Matrix4x4& OverrideCenter(float x, float y, float z);
			Matrix4x4&  OverrideScale(const Vector3& scale);
			Matrix4x4&  OverrideScale(float x, float y, float z);

			// Become Rotation Matrix
			Matrix4x4&   Rotation(Degrees&, Axis, RotationDirection = RotationDirection(0));
	static	Matrix4x4 GetRotation(Degrees&, Axis, RotationDirection = RotationDirection(0));
			//
			Matrix4x4&   Rotation(Radians&, Axis, RotationDirection = RotationDirection(0));
	static	Matrix4x4 GetRotation(Radians&, Axis, RotationDirection = RotationDirection(0));

			// Become Rotation Matrix for ANY axis
			Matrix4x4&   Rotation(Degrees&, const Vector3& Direction, RotationDirection = RotationDirection(0));
	static	Matrix4x4 GetRotation(Degrees&, const Vector3& Direction, RotationDirection = RotationDirection(0));
			//
			Matrix4x4&   Rotation(Radians&, const Vector3& Direction, RotationDirection = RotationDirection(0));
	static	Matrix4x4 GetRotation(Radians&, const Vector3& Direction, RotationDirection = RotationDirection(0));

			// Set Horizontal Line
			void SetRow(int index, const Vector4&);
	static	void SetRow(Matrix4x4&, int index, const Vector4&);
			// Set Vertical Line
			void SetColumn(int index, const Vector4&);
	static	void SetColumn(Matrix4x4&, int index, const Vector4&);

			// Get Horizontal Line
			Vector4 GetRow(int index) const;
	static	Vector4 GetRow(const Matrix4x4&, int index);
			// Get Vertical Line
			Vector4 GetColumn(int index) const;
	static	Vector4 GetColumn(const Matrix4x4&, int index);

			// Determinant
			float Determinant() const;
	static	float Determinant(const Matrix4x4&);

			// Transpose
			Matrix4x4 Transpose() const;
	static	Matrix4x4 Transpose(const Matrix4x4&);
			// Transpose Self
			Matrix4x4& TransposeSelf();
	static	Matrix4x4& TransposeSelf(Matrix4x4&);

			// Inverse
			Matrix4x4 Inverse() const;
	static	Matrix4x4 Inverse(const Matrix4x4&);
			// Inverse Self
			Matrix4x4& InverseSelf();
	static	Matrix4x4& InverseSelf(Matrix4x4&);

			// Multiply
			Matrix4x4 Multiply(const Matrix4x4&) const;
	static	Matrix4x4 Multiply(const Matrix4x4&, const Matrix4x4&);

			// Compare
			bool Compare(const Matrix4x4&) const;
	static	bool Compare(const Matrix4x4&, const Matrix4x4&);

			// Get Start Pointer
	inline const float* GetStartPointer()
	{
		return &_Val[0];
	}
			// Get Start Reference
	inline const float& GetStartReference() const
	{
		return _Val[0];
	}

			// Vector to string
			std::string ToString();

			// Lerp
			Matrix4x4 Lerp(const Matrix4x4&, float t) const;
	static	Matrix4x4 Lerp(const Matrix4x4&, const Matrix4x4&, float t);

	// Special Operator Overloads
	float& operator[](int);
	float operator[](int) const;
	Matrix4x4 operator-(void) const;

	// Matrix -- Vector Multiplication
	friend Vector4 operator*(const Matrix4x4& m, const Vector4& v);
	friend Vector3 operator*(const Matrix4x4& m, const Vector3& v);
	friend Vector2 operator*(const Matrix4x4& m, const Vector2& v);
	friend Vector4 operator*(const Vector4& v, const Matrix4x4& m);
	friend Vector3 operator*(const Vector3& v, const Matrix4x4& m);
	friend Vector2 operator*(const Vector2& v, const Matrix4x4& m);
	// Matrix -- Matrix Multiplication
	Matrix4x4 operator*(const Matrix4x4&) const;
	Matrix4x4& operator*=(const Matrix4x4&);
	
	// Operator Overloads
	Matrix4x4 operator+(const Matrix4x4&) const;
	Matrix4x4 operator-(const Matrix4x4&) const;
	Matrix4x4& operator+=(const Matrix4x4&);
	Matrix4x4& operator-=(const Matrix4x4&);
	Matrix4x4 operator+(const float) const;
	Matrix4x4 operator-(const float) const;
	Matrix4x4 operator*(const float) const;
	Matrix4x4 operator/(const float) const;
	Matrix4x4& operator+=(const float);
	Matrix4x4& operator-=(const float);
	Matrix4x4& operator*=(const float);
	Matrix4x4& operator/=(const float);

	// Operator Comparison Overloading
	Matrix4x4& operator= (const Matrix4x4&);
	bool operator== (const Matrix4x4&) const;
	bool operator!= (const Matrix4x4&) const;

	// Cout Overload
	friend std::ostream &operator<<(std::ostream &stream, const Matrix4x4&);
};