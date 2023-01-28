#pragma once

#include <math.h>

#include "Object.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

class Sphere : public Object {
	private:
		Vector center;
		float radius;	
	public:
		Sphere(const Vector& center, const float& radius, const Color& color) :
			center(center),
			radius(radius),
			Object(color)
		{}

		inline Vector get_center() const { return center; }
		inline float get_radius() const { return radius; }

		virtual bool check_hit(const Ray& r, float& t_max, Object_Hitted& object) const override {
			const float a = Vector::Dot(r.direction, r.direction);
			const float b = Vector::Dot(r.direction, r.origin - center);
			const float c = Vector::Dot((r.origin - center), (r.origin - center)) - radius*radius;

			const float delta = b*b - a*c;
			
			if (delta < 0) return false;
			
			float t = (- b - sqrt(delta)) / a;
			if (t < 0.001 || t > t_max) {
				t = (-b + sqrt(delta)) / a;
				if (t < 0.001 || t > t_max)
					return false;
			}

			const Vector point = r.point_at_parameter(t);
			Vector normal = (point - center) / radius; // Normalize

			bool same_direction = (Vector::Dot(r.direction, normal) > 0);
			normal = (same_direction) ? normal.Opposite() : normal;
			
			object.t = t_max = t;
			object.point = point;
			object.normal = normal;
			object.color = get_color();
			return true;
		}
};
