#pragma once

#include <cmath>
#include <sstream>

namespace kiko
{
	class Vector3
	{
	public:
		float x, y, z;

	public:
		Vector3() : x{ 0 }, y{ 0 } {}
		Vector3(float v) : x{ v }, y{ v } {}
		Vector3(float x, float y) : x{ x }, y{ y } {}
		Vector3(int x, int y) : x{ (float)x }, y{ (float)y } {}

		Vector3 operator + (const Vector3& v) const { return Vector3(x + v.x, y + v.y); }
		Vector3 operator - (const Vector3& v) const { return Vector3(x - v.x, y - v.y); }
		Vector3 operator * (const Vector3& v) const { return Vector3(x * v.x, y * v.y); }
		Vector3 operator / (const Vector3& v) const { return Vector3(x / v.x, y / v.y); }

		Vector3 operator + (float s) const { return Vector3(x + s, y + s); }
		Vector3 operator - (float s) const { return Vector3(x - s, y - s); }
		Vector3 operator * (float s) const { return Vector3(x * s, y * s); }
		Vector3 operator / (float s) const { return Vector3(x / s, y / s); }

		Vector3& operator += (const Vector3& v) { x += v.x; y += v.y; return *this; }
		Vector3& operator -= (const Vector3& v) { x -= v.x; y -= v.y; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x; y *= v.y; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x; y /= v.y; return *this; }

		float LengthSqr() const { return (x * x) + (y * y); };
		float Length() const { return sqrt(LengthSqr()); }

		float DistanceSqr(const Vector3& v) const { return (v - *this).LengthSqr(); }
		float distance(const Vector3& v) const { return (v - *this).Length(); }

		Vector3 Normalized() const { return *this / Length(); }
		void Normalize() { *this /= Length(); }
	};


	using vec3 = Vector3;
}
