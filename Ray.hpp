#pragma once

#include "Vector.hpp"

class Ray {
	public:
		Vector origin,
		       direction;

		Ray() = default;
		Ray(const Vector& origin, const Vector& direction) :
			origin(origin),
			direction(direction)
		{}
		
		// Ray is a linear line
		// y = ax + b
		inline Vector point_at_parameter(const float& t) const {
			return origin + direction*t;
		}
};
