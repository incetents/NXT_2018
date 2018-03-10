#pragma once

class Vector3;
class Vector4;
class Matrix4x4;
class Degrees;
class Radians;
class RotationValue;
enum class RotationDirection;

class Quaternion
{
private:
	// Identity Quaternion
	static const Quaternion _Identity;

	
public:

	// Values
	float x, y, z, w;
	
	// Create Angle Axis Quaternion
	explicit Quaternion();
	explicit Quaternion(const float _x, const float _y, const float _z, const float _w);
	explicit Quaternion(const Degrees& rotation, const Vector3& axis, RotationDirection = RotationDirection(0));
	explicit Quaternion(const Radians& rotation, const Vector3& axis, RotationDirection = RotationDirection(0));

	// Become default empty quaternion
	void Identity();

	// Create Quaternion from euler angles
	static Quaternion Quaternion::GetEuler(const Degrees& Deg_X, const Degrees& Deg_Y, const Degrees& Deg_Z);
	static Quaternion Quaternion::GetEuler(const Radians& Rad_X, const Radians& Rad_Y, const Radians& Rad_Z);
	// Convert Quaternion to euler angles
	static void ToEuler(const Quaternion& q, Degrees& roll, Degrees& pitch, Degrees& yaw);
	static void ToEuler(const Quaternion& q, Radians& roll, Radians& pitch, Radians& yaw);

	// Get Matrix4x4
	Matrix4x4 GetMatrix() const;
	Matrix4x4 GetMatrix(const Vector3& center) const;
	static Matrix4x4 GetMatrix(const Quaternion& quat);
	static Matrix4x4 GetMatrix(const Quaternion& quat, const Vector3& center);

	// Create Angle Axis
	static Quaternion AngleAxis(const Degrees& rotation, const Vector3& axis, RotationDirection = RotationDirection(0));
	static Quaternion AngleAxis(const Radians& rotation, const Vector3& axis, RotationDirection = RotationDirection(0));

	// Inverse
		   Quaternion& InverseSelf();
		   Quaternion  Inverse() const;
	static Quaternion  Inverse(const Quaternion&);

	// Normalize
		   Quaternion& NormalizeSelf();
		   Quaternion  Normalize();
	static Quaternion  Normalize(const Quaternion&);

	// Dot Product
	inline float Dot();
	inline float Dot(const Quaternion&);
	static float Dot(const Quaternion&, const Quaternion&);

	// Special Operator Overloads
	float				operator[](const int) const;
	float&				operator[](const int);
	Quaternion			operator-();
	// Operator Overload (Math)
	Quaternion			operator+(const Quaternion&) const;
	Quaternion			operator-(const Quaternion&) const;
	Quaternion			operator*(const Quaternion&) const;
	Quaternion			operator*(const float) const;
	friend Vector3		operator*(const Quaternion&, const Vector3&);
	// Operator Overload (Math Change)
	Quaternion&			operator*=(const Quaternion& other);
	Quaternion&			operator*=(float s);
	// Operator Comparison Overloading
	inline Quaternion&	operator= (const Quaternion&);
	//inline Quaternion& operator=(const Matrix4x4&);
	bool				operator== (const Quaternion&) const;
	bool				operator!= (const Quaternion&) const;
};

