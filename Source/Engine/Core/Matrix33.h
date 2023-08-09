//#pragma once
//
//#include "Vector.h"
//#include "Vector3.h"
//
//namespace kiko
//{
//	class Matrix33
//	{
//	public:
//		vec3 rows[3];
//		// [row][column]
//		// rows[0] = vec3{ 0, 0, 0 }
//		// rows[1] = vec3{ 0, 0, 0 }
//		// rows[2] = vec3{ 0, 0, 0 }
//
//		Matrix33() = default;
//		Matrix33(const vec3& row1, const vec3& row2)
//		{
//			rows[0] = row1;
//			rows[1] = row2;
//		}
//
//		vec3  operator [] (size_t index) const { return rows[index]; }
//		vec3& operator [] (size_t index) { return rows[index]; }
//
//		vec3 operator * (const vec3& v);
//		Matrix33 operator * (const Matrix33& mx);
//
//		static Matrix33 CreateScale(const vec3& scale);
//		static Matrix33 CreateScale(float scale);
//		static Matrix33 CreateRotation(float radians);
//
//		static Matrix33 CreateIdentity();
//	};
//
//	inline vec3 Matrix33::operator*(const vec3& v)
//	{
//		vec3 result;
//		result.x = rows[0][0] * v.x + rows[0][1] * v.y;
//		result.y = rows[1][0] * v.x + rows[1][1] * v.y;
//
//		return result;
//	}
//
//	inline Matrix33 Matrix33::operator*(const Matrix33& mx)
//	{
//		Matrix33 result;
//		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] + mx[1][0];
//
//		return result;
//	}
//
//	inline Matrix33 Matrix33::CreateIdentity()
//	{
//		return
//		{
//			{ 1, 0, 0 },
//			{ 0, 1 }
//		};
//	}
//
//	inline Matrix33 Matrix33::CreateScale(const vec2& scale)
//	{
//		Matrix33 mx = CreateIdentity();
//		mx[0][0] = scale.x;
//		mx[1][1] = scale.y;
//
//		return mx;
//	}
//
//	inline Matrix33 Matrix33::CreateScale(float scale)
//	{
//		Matrix33 mx = CreateIdentity();
//		mx[0][0] = scale;
//		mx[1][1] = scale;
//
//		return mx;
//	}
//
//	inline Matrix33 Matrix33::CreateRotation(float radians)
//	{
//		Matrix33 mx = CreateIdentity();
//		float c = cos(radians);
//		float s = sin(radians);
//
//		mx[0][0] = c; mx[0][1] = -s;
//		mx[1][0] = s; mx[1][1] = c;
//	}
//
//	using mat3 = Matrix33;
//}
