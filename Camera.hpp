#pragma once

#include "Vector.hpp"
#include "Ray.hpp"

class Camera {
	private:
		float aspect_ratio = 16.0f / 9.0f;
		float viewport_height = 2.0f;
		float viewport_width = aspect_ratio * viewport_height;
		float focal_length = 1.0f;

		Vector origin;
		Vector horizontal;
		Vector vertical;
		Vector lower_left_corner;
	public:
		Camera() {
			origin = Vector(0.5, 0, 0);
			horizontal = Vector(viewport_width, 0, 0);
			vertical = Vector(0, viewport_height, 0);
			lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - Vector(0, 0, focal_length);
		}

		Ray get_ray(const float& u, const float& v) const {
			return Ray(origin, lower_left_corner + horizontal * u + vertical * v - origin);
		};
};
