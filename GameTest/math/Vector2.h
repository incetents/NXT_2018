#pragma once

#include <string>
#include <iostream>
#include <sstream>

class Vector3;
class Vector4;
class Matrix2x2;
class Radians;
class Degrees;
enum class RotationDirection;

class Vector2
{
public:
	// Common Vector Types
	static const Vector2 UP;
	static const Vector2 DOWN;
	static const Vector2 LEFT;
	static const Vector2 RIGHT;

	// Data
	float x, y;

	// Is Empty
	inline bool Is_Empty()
	{
		if (x && y) return true;
		return false;
	}

	// Empty Constructor
	explicit Vector2(void);
	explicit Vector2(float all);
	explicit Vector2(Vector3 v);
	explicit Vector2(Vector4 v);
	explicit Vector2(Radians all);
	explicit Vector2(Degrees all);
	explicit Vector2(float _x, float _y);
	explicit Vector2(Radians _x, Radians _y);
	explicit Vector2(Degrees _x, Degrees _y);

	// Switch X and Y values
	inline Vector2& Flip();
	inline Vector2 GetFlip();
	inline static Vector2 GetFlip(const Vector2& v);

	// Inverse
	Vector2 Inverse(void) const;
	static Vector2 Inverse(const Vector2&);

	// Compare
	bool Compare(const Vector2&) const;
	static bool Compare(const Vector2&, const Vector2&);

	// Normalize Self (Returns Length)
	float NormalizeSelf();
	// Normalize
	Vector2 Normalize() const;
	static Vector2 Normalize(const Vector2&);
	// Magnitude
	float Magnitude() const;
	static float Magnitude(const Vector2&);
	// Length
	float Length() const;
	static float Length(const Vector2&);
	// Length Squared
	float LengthSqr() const;
	static float LengthSqr(const Vector2&);

	// Dot Product
	float Dot() const;
	float Dot(const Vector2&) const;
	static float Dot(const Vector2&, const Vector2&);

	// Reflect Vector
	Vector2 Reflect(const Vector2& Normal);
	static Vector2 Reflect(const Vector2& Incident, const Vector2& Normal);

	// Perpendicular
	Vector2 Perpendicular() const;

	// Project Vector
	Vector2 Project(const Vector2&) const;
	static Vector2 Project(const Vector2&, const Vector2&);
	// Projection Length
	float ProjectLength(const Vector2&) const;
	static float ProjectLength(const Vector2&, const Vector2&);

	// Rotate Degrees
	Vector2 Rotate(Degrees&, RotationDirection = RotationDirection(0));
	// Rotate Radians
	Vector2 Rotate(Radians&, RotationDirection = RotationDirection(0));

	// Get Angle Degrees
	Degrees GetAngleDegrees(Vector2&);
	static Degrees GetAngleDegrees(Vector2&, Vector2&);
	// Get Angle Radians
	Radians GetAngleRadians(Vector2&);
	static Radians GetAngleRadians(Vector2&, Vector2&);

	// Random Vector2 Unit Vector
	static Vector2 GetRandomUnitVector();

	// Fix Denormals (Fix Numbers close to zero)
	bool FixDenormals();
	static bool FixDenormals(Vector2&);

	// Resize Vector
	Vector2 Resize(float length);

	// Clamp
	void Clamp(const Vector2& min, const Vector2& max);
	static Vector2 Clamp(Vector2, const Vector2& min, const Vector2& max);

	// Snap to nearest integer value
	void Snap(void);
	static Vector2 Snap(Vector2);

	// Get Float pointer of values
	inline float* GetStartPointer(void);
	inline static float* GetStartPointer(Vector2&);

	// Vector to string
	std::string ToString();

	// Lerp
	Vector2 Lerp(const Vector2&, const float t);
	static Vector2 Lerp(const Vector2&, const Vector2&, float t);
	// Slerp
	Vector2 Slerp(const Vector2&, const float t);
	static Vector2 Slerp(const Vector2&, const Vector2&, float t);
	// Nlerp
	Vector2 Nlerp(const Vector2&, const float t);
	static Vector2 Nlerp(const Vector2&, const Vector2&, float t);

	// Special Operator Overloading
	float operator[](const int) const;
	float& operator[](const int);
	Vector2 operator-() const;

	// Basic Operator Overloading
	Vector2 operator+ (const Vector2&) const;
	Vector2 operator- (const Vector2&) const;
	Vector2 operator* (const Vector2&) const;
	Vector2 operator/ (const Vector2&) const;
	Vector2& operator+= (const Vector2&);
	Vector2& operator-= (const Vector2&);
	Vector2& operator*= (const Vector2&);
	Vector2& operator/= (const Vector2&);

	// Operator Overloading with Float
	friend Vector2 operator+ (const Vector2&, const float);
	friend Vector2 operator- (const Vector2&, const float);
	friend Vector2 operator* (const Vector2&, const float);
	friend Vector2 operator/ (const Vector2&, const float);

	friend Vector2 operator+ (const float, const Vector2&);
	friend Vector2 operator- (const float, const Vector2&);
	friend Vector2 operator* (const float, const Vector2&);
	friend Vector2 operator/ (const float, const Vector2&);

	Vector2& operator+= (const float);
	Vector2& operator-= (const float);
	Vector2& operator*= (const float);
	Vector2& operator/= (const float);

	// Operator Comparison Overloading
	Vector2& operator= (const Vector2&);
	Vector2& operator= (const Vector3&);
	Vector2& operator= (const Vector4&);
	bool operator== (const Vector2&) const;
	bool operator!= (const Vector2&) const;

	// Cout Overload
	friend std::ostream &operator<<(std::ostream &stream, Vector2& ob);

};

// Shorthand
typedef Vector2 Vec2;