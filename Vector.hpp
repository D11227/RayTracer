#pragma once

#include <math.h>

class Vector {
	public:
		float x = 0.0f,
		      y = 0.0f,
		      z = 0.0f;

		Vector() = default;
		Vector(const float& x, const float& y, const float& z) :
			x(x),
			y(y),
			z(z)
		{}

		inline Vector operator+(const Vector& other) const { return Vector(x + other.x, y + other.y, z + other.z); }
		inline Vector operator-(const Vector& other) const { return Vector(x - other.x, y - other.y, z - other.z); }
		inline Vector operator*(const float& scalar) const { return Vector(x * scalar, y * scalar, z * scalar); }
		inline Vector operator/(const float& scalar) const { return Vector(x / scalar, y / scalar, z / scalar); }
		inline Vector& operator+=(const Vector& other) { return *this = *this + other; }
		inline Vector& operator-=(const Vector& other) { return *this = *this - other; }
		inline Vector& operator*=(const float& scalar) { return *this = *this * scalar; }
		inline Vector& operator/=(const float& scalar) { return *this = *this / scalar; }
		inline const Vector Opposite() const { return Vector(-x, -y, -z); }
		inline const float Length() const { return std::sqrt(x * x + y * y + z * z); }
		inline const float Length_Squared() const { return x * x + y * y + z * z; }

		inline Vector Normalize() const {
			const float length = Length();
			return *this / length;
		}
		
		static float Dot(const Vector& u, const Vector& v) {
			return u.x * v.x + u.y * v.y + u.z * v.z;
		}
		
		static Vector Cross(const Vector& u, const Vector& v) {
			return (Vector){
				u.y * v.z - u.z * v.y,
				u.z * v.x - u.x * v.z,
				u.x * v.y - u.y * v.x
			};
		}
};

using Color = Vector;
