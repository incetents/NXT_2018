#pragma once

#include "stdafx.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x3.h"
#include "MathCore.h"

const Vector3 Vector3::ZERO		= Vector3(0, 0, 0);
const Vector3 Vector3::ONE		= Vector3(1, 1, 1);
const Vector3 Vector3::N_ONE	= Vector3(-1,-1,-1);
const Vector3 Vector3::HALF		= Vector3(0.5f,0.5f,0.5f);
const Vector3 Vector3::UP		= Vector3(0, +1, 0);
const Vector3 Vector3::DOWN		= Vector3(0, -1, 0);
const Vector3 Vector3::FORWARD	= Vector3(0, 0, +1);
const Vector3 Vector3::BACK		= Vector3(0, 0, -1);
const Vector3 Vector3::LEFT		= Vector3(-1, 0, 0);
const Vector3 Vector3::RIGHT	= Vector3(+1, 0, 0);

// Constructors
Vector3::Vector3(void) : x(0), y(0), z(0) {}
Vector3::Vector3(float all) : x(all), y(all), z(all){}
Vector3::Vector3(Vector2 v) : x(v.x), y(v.y), z(0) {}
Vector3::Vector3(Vector4 v) : x(v.x), y(v.y), z(v.z) {}
Vector3::Vector3(Radians all)
{
	x = all.Get();
	y = all.Get();
	z = all.Get();
}
Vector3::Vector3(Degrees all)
{
	x = all.Get();
	y = all.Get();
	z = all.Get();
}
Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

Vector3::Vector3(Radians _x, Radians _y, Radians _z)
{
	x = _x.Get();
	y = _y.Get();
	z = _z.Get();
}
Vector3::Vector3(Degrees _x, Degrees _y, Degrees _z)
{
	x = _x.Get();
	y = _y.Get();
	z = _z.Get();
}
Vector3::Vector3(Vector2 _v, float _z)
{
	x = _v.x;
	y = _v.y;
	z = _z;
}
Vector3::Vector3(float _x, Vector2 _v)
{
	x = _x;
	y = _v.x;
	z = _v.y;
}

// Inverse
Vector3 Vector3::Inverse() const
{
	return Vector3(
		1.0f / x,
		1.0f / y,
		1.0f / z
	);
}
Vector3 Vector3::Inverse(const Vector3& v)
{
	return v.Inverse();
}

// Compare
bool Vector3::Compare(const Vector3& v) const
{
	if (abs(x - v.x) > FLOAT_EPSILON)
		return false;

	if (abs(y - v.y) > FLOAT_EPSILON)
		return false;

	if (abs(z - v.z) > FLOAT_EPSILON)
		return false;

	return true;
}
bool Vector3::Compare(const Vector3& v1, const Vector3& v2)
{
	return v1.Compare(v2);
}

// Normalize Self (Returns Length)
float Vector3::NormalizeSelf()
{
	float Square_Length = x * x + y * y + z * z;
	float Inverse_Squareroot = MathCore::InverseSqrt(Square_Length);

	*this *= Inverse_Squareroot;

	return Square_Length * Inverse_Squareroot;
}
// Normalize
Vector3 Vector3::Normalize() const
{
	float Inverse_Squareroot = MathCore::InverseSqrt(x * x + y * y + z * z);
	return Vector3(
		x * Inverse_Squareroot,
		y * Inverse_Squareroot,
		z * Inverse_Squareroot
	);
}
Vector3 Vector3::Normalize(const Vector3& v)
{
	return v.Normalize();
}
// Magnitude
float Vector3::Magnitude() const
{
	return sqrtf(x * x + y * y + z * z);
}
float Vector3::Magnitude(const Vector3& v)
{
	return v.Magnitude();
}
// Length
float Vector3::Length() const
{
	return Magnitude();
}
float Vector3::Length(const Vector3& v)
{
	return Magnitude(v);
}
// Length Squared
float Vector3::LengthSqr() const
{
	return Vector3::Dot();
}
float Vector3::LengthSqr(const Vector3& v)
{
	return v.LengthSqr();
}

// Dot Product
float Vector3::Dot() const
{
	return (x * x + y * y + z * z);
}
float Vector3::Dot(const Vector3& v) const
{
	return (x * v.x + y * v.y + z * v.z);
}
float Vector3::Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.Dot(v2);
}

// Reflect Vector
Vector3 Vector3::Reflect(const Vector3& Normal)
{
	return Reflect(*this, Normal);
}
Vector3 Vector3::Reflect(const Vector3& Incident, const Vector3& Normal)
{
	return Incident - 2 * (Incident.Dot(Normal)) * Normal;
}

// Project Vector
Vector3 Vector3::Project(const Vector3& v) const
{
	// Formula:	(Dot / (b length * b length)) * b
	float D = Vector3::Dot(*this, v);
	float S = (v.x * v.x + v.y * v.y + v.z + v.z);

	return v * (D / S);
}
Vector3 Vector3::Project(const Vector3& v1, const Vector3& v2)
{
	Vector3 Result = v1.Project(v2);
	return Result;
}
float Vector3::ProjectLength(const Vector3& v) const
{
	float D = Vector3::Dot(*this, v);
	float L = v.Length();
	return D / L;
}
float Vector3::ProjectLength(const Vector3& v1, const Vector3& v2)
{
	return v1.ProjectLength(v2);
}

// Cross Product
Vector3 Vector3::Cross(const Vector3& v) const
{
	return Vector3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}
Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
{
	return v1.Cross(v2);
}

// Rotate
void Vector3::Rotate(Degrees& Deg, Axis Axis_Selected, RotationDirection Rot)
{
	Rotate(Radians(Deg.GetRadians()), Axis_Selected, Rot);
}
void Vector3::Rotate(Vector3& V, Degrees& Deg, Axis Axis_Selected, RotationDirection Rot)
{
	V.Rotate(Deg, Axis_Selected, Rot);
}
// 
void Vector3::Rotate(Radians& Rad, Axis Axis_Selected, RotationDirection Rot)
{
	// Radians
	float Val = Rad.GetDegrees();

	switch (Axis_Selected)
	{
	case Axis::X:
		//
		if (Rot == RotationDirection::COUNTER_CLOCKWISE)
		{
			*this = Vector3(
				+x,
				+y * cosf(Val) - z * sinf(Val),
				+z * sinf(Val) + z * cosf(Val)
			);
		}
		else
		{
			*this = Vector3(
				+x,
				+y * cosf(Val) + z * sinf(Val),
				-z * sinf(Val) + z * cosf(Val)
			);
		}
		//
		break;

	case Axis::Y:
		//
		if (Rot == RotationDirection::COUNTER_CLOCKWISE)
		{
			*this = Vector3(
				+x * cosf(Val) + z * sinf(Val),
				+y,
				-x * sinf(Val) + z * cosf(Val)
			);
		}
		else
		{
			*this = Vector3(
				+x * cosf(Val) - z * sinf(Val),
				+y,
				+x * sinf(Val) + z * cosf(Val)
			);
		}
		//
		break;

	case Axis::Z:
		//
		if (Rot == RotationDirection::COUNTER_CLOCKWISE)
		{
			*this = Vector3(
				+x * cosf(Val) - y * sinf(Val),
				+x * sinf(Val) + y * cosf(Val),
				+z
			);
		}
		else
		{
			*this = Vector3(
				+x * cosf(Val) + y * sinf(Val),
				-x * sinf(Val) + y * cosf(Val),
				+z
			);
		}
		//
		break;
	}

}
void Vector3::Rotate(Vector3& V, Radians& Rad, Axis Axis_Selected, RotationDirection Rot)
{
	V.Rotate(Rad, Axis_Selected, Rot);
}


// Get Angle Degrees
Degrees Vector3::GetAngleDegrees(Vector3& v)
{
	return Degrees(GetAngleRadians(v));
}
Degrees Vector3::GetAngleDegrees(Vector3& v1, Vector3& v2)
{
	return v1.GetAngleDegrees(v2);
}

// Get Angle Radians
Radians Vector3::GetAngleRadians(Vector3& v)
{
	return Radians(
		acosf(
			Dot(v) / (Magnitude() * v.Magnitude())
		)
	);
}
Radians Vector3::GetAngleRadians(Vector3& v1, Vector3& v2)
{
	return v1.GetAngleRadians(v2);
}

// Random Vector3 Unit Vector
Vector3 Vector3::GetRandomUnitVector()
{
	float _x = Random::Range(-1.0f, 1.0f);
	float _y = Random::Range(-1.0f, 1.0f);
	float _z = Random::Range(-1.0f, 1.0f);

	return Vector3(_x, _y, _z).Normalize();
}

// Fix Denormals (Fix Numbers close to zero)
bool Vector3::FixDenormals()
{
	bool denormal = false;
	if (fabs(x) < 1e-30f) {
		x = 0.0f;
		denormal = true;
	}
	if (fabs(y) < 1e-30f) {
		y = 0.0f;
		denormal = true;
	}
	if (fabs(z) < 1e-30f) {
		z = 0.0f;
		denormal = true;
	}
	return denormal;
}
bool Vector3::FixDenormals(Vector3& v)
{
	return v.FixDenormals();
}

// Resize
Vector3 Vector3::Resize(float length)
{
	// If length is zero, return empty vector
	if (!length)
		return Vector3();

	// Normalize then multiply length
	return Normalize() * length;

}

// Clamp
void Vector3::Clamp(const Vector3& lower, const Vector3& upper)
{
	// Fix X Values
	x = MacroClamp(x, lower.x, upper.x);
	// Fix Y Values
	y = MacroClamp(y, lower.y, upper.y);
	// Fix Y Values
	z = MacroClamp(z, lower.z, upper.z);
}
Vector3 Vector3::Clamp(Vector3 v, const Vector3& min, const Vector3& max)
{
	v.Clamp(min, max);
	return v;
}

// Snap to nearest integer value
void Vector3::Snap()
{
	x = floor(x + 0.5f);
	y = floor(y + 0.5f);
	z = floor(z + 0.5f);
}
Vector3 Vector3::Snap(Vector3 v)
{
	v.Snap();
	return v;
}

// Get Float pointer of values
float* Vector3::GetStartPointer(void)
{
	return &x;
}
float* Vector3::GetStartPointer(Vector3& v)
{
	return &v.x;
}

// Vector to string
std::string Vector3::ToString()
{
	return std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(z);
}

// Lerp
Vector3 Vector3::Lerp(const Vector3& v, const float t)
{
	return MacroLerp(*this, v, t);
}
Vector3 Vector3::Lerp(const Vector3& v1, const Vector3& v2, float t)
{
	return MacroLerp(v1, v2, t);
}
// Slerp
Vector3 Vector3::Slerp(const Vector3& v, const float t)
{
	return Slerp(*this, v, t);
}
Vector3 Vector3::Slerp(const Vector3& v1, const Vector3& v2, float t)
{
	float dot = Vector3::Dot(v1, v2);
	MacroClamp(dot, -1.0f, 1.0f);
	float theta = acosf(dot)*t;
	Vector3 RelativeVec = v2 - v1*dot;
	RelativeVec.Normalize();

	return ((v1*cosf(theta)) + (RelativeVec*sinf(theta)));
}
// Nlerp
Vector3 Vector3::Nlerp(const Vector3& v, const float t)
{
	return Nlerp(*this, v, t);
}
Vector3 Vector3::Nlerp(const Vector3& v1, const Vector3& v2, float t)
{
	return (MacroLerp(v1, v2, t)).Normalize();
}


// Special Operator Overloads
float Vector3::operator[](const int index) const
{
	assert((index >= 0) && (index < 3));
	return (&x)[index];
}
float& Vector3::operator[](const int index)
{
	assert((index >= 0) && (index < 3));
	return (&x)[index];
}
Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

// Basic Operator Overloading
Vector3 Vector3::operator+ (const Vector3& v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}
Vector3 Vector3::operator- (const Vector3& v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}
Vector3 Vector3::operator* (const Vector3& v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}
Vector3 Vector3::operator/ (const Vector3& v) const
{
	return Vector3(x / v.x, y / v.y, z / v.z);
}
Vector3& Vector3::operator+= (const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
Vector3& Vector3::operator-= (const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
Vector3& Vector3::operator*= (const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}
Vector3& Vector3::operator/= (const Vector3& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

// Operator Overloading with Float
Vector3 operator+ (const Vector3& v, const float f)
{
	return Vector3(v.x + f, v.y + f, v.z + f);
}
Vector3 operator- (const Vector3& v, const float f)
{
	return Vector3(v.x - f, v.y - f, v.z - f);
}
Vector3 operator* (const Vector3& v, const float f)
{
	return Vector3(v.x * f, v.y * f, v.z * f);
}
Vector3 operator/ (const Vector3& v, const float f)
{
	float inva = 1.0f / f;
	return Vector3(v.x * inva, v.y * inva, v.z * inva);
}

Vector3 operator+ (const float f, const Vector3& v)
{
	return v + f;
}
Vector3 operator- (const float f, const Vector3& v)
{
	return v - f;
}
Vector3 operator* (const float f, const Vector3& v)
{
	return v * f;
}
Vector3 operator/ (const float f, const Vector3& v)
{
	return v / f;
}


Vector3& Vector3::operator+= (float f)
{
	x += f;
	y += f;
	z += f;
	return *this;
}
Vector3& Vector3::operator-= (float f)
{
	x -= f;
	y -= f;
	z -= f;
	return *this;
}
Vector3& Vector3::operator*= (float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}
Vector3& Vector3::operator/= (float f)
{
	float inva = 1.0f / f;
	x *= inva;
	y *= inva;
	z *= inva;
	return *this;
}

Vector3& Vector3::operator= (const Vector2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}
Vector3& Vector3::operator= (const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
Vector3& Vector3::operator= (const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
bool Vector3::operator== (const Vector3& v) const
{
	return Compare(v);
}
bool Vector3::operator!= (const Vector3& v) const
{
	return !Compare(v);
}

std::ostream &operator<<(std::ostream &stream, Vector3& ob)
{
	return (stream << '[' << ob.x << ' ' << ob.y << ' ' << ob.z << ']');
}

// Return Vec3
Vector3 Vector3::GetVector3(int index1, int index2, int index3) const
{
	return Vector3(*(&x + index1), *(&x + index2), *(&x + index3));
}
// Return Vec2
Vector2 Vector3::GetVector2(int index1, int index2) const
{
	return Vector2(*(&x + index1), *(&x + index2));
}