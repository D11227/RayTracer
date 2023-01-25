#pragma once

#include <tuple>
#include <math.h>
#include <limits>
#include "Vector.hpp"
#include "Ray.hpp"

class Sphere {
	private:
		Vector center;
		float radius;	
	public:
		Sphere(const Vector& center, const float& radius) :
			center(center),
			radius(radius)
		{}

		Vector get_center() const { return center; }
		float get_radius() const { return radius; }

		std::tuple<bool, float, Vector, Vector> check_hit(const Ray& r, const float& t_max) const {
			const float a = Vector::Dot(r.direction, r.direction);
			const float b = Vector::Dot(r.direction, r.origin - center);
			const float c = Vector::Dot((r.origin - center), (r.origin - center)) - radius*radius;

			const float delta = b*b - a*c;
			
			if (delta < 0) return { false, 0, Vector(), Vector()  };
			
			float t = (- b - sqrt(delta)) / a;
			if (t < 0.001 || t > t_max) {
				t = (-b + sqrt(delta)) / a;
				if (t < 0.001 || t > t_max)
					return { false, 0, Vector(), Vector() };
			}

			const Vector point_at = r.point_at_parameter(t);
			Vector normal = (point_at - center) / radius;

			bool same_direction = (Vector::Dot(r.direction, normal) > 0);
			normal = (same_direction) ? normal.Opposite() : normal;

			return { true, t, point_at, normal };
		}
};
