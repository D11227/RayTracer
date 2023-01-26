#include <iostream>
#include <array>
#include <random>

#include "Sphere.hpp"
#include "Ray.hpp"
#include "Camera.hpp"

const auto infinity = std::numeric_limits<float>::infinity();
std::uniform_real_distribution<float> distribution(0, 1);
std::mt19937 generator;

inline float random_number() {
	return distribution(generator);
}

inline float random_number(const int& min, const int& max) {
	return min + (max - min) * random_number();
}

Vector random_vector(const int& min, const int& max) {
	while (true) {
		const Vector p = Vector(random_number(-1, 1), random_number(-1, 1), random_number(-1, 1));
		if (p.Length_Squared() < 1) return p;
	}
}

Color trace(const std::array<Sphere, 2>& world, const Ray& r, int ray_limit) {
	if (ray_limit <= 0) return Color(0, 0, 0);
	
	float closest_object = infinity;
	Object_Hitted object_hitted;
	bool is_hitted_something = false;
	for (const auto& object : world)
		if (object.check_hit(r, closest_object, object_hitted))
			is_hitted_something = true;		

	if (is_hitted_something) {
		auto target = object_hitted.point + object_hitted.normal + random_vector(-1, 1);
		return trace(world, Ray(object_hitted.point, target - object_hitted.point), ray_limit - 1) * object_hitted.color;
	}

	Vector direction = r.direction.Normalize();
	const float t = 0.5f * (direction.y + 1);
	return Color(1.0f, 1.0f, 1.0f) * (1 - t) + Color(0.3f, 0.5f, 1.0f) * t;
}

int32_t main() {
	const float aspect_ratio = 16.0f / 9.0f;
	const int image_width = 800;
	// aspect_ratio = width / height => height = width / aspec_ratio
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int ray_limit = 50;

	const std::array<Sphere, 2> world = {
		Sphere(Vector(0, 0, -1), 0.5, Color(0.3, 1., 0.5)),
		Sphere(Vector(0, -100.5, -1), 100, Color(0.3, 0.5, 1.))
	};

	Camera camera;
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	auto clamp = [](const float& x, const float& min = 0.0f, const float& max = 0.99f) -> float {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	};

	for (int j = image_height - 1; j >= 0; --j) {
		for (int i = 0; i < image_width; ++i) {
			Color color;
			for (int s = 0; s < samples_per_pixel; ++s) {
				const float u = float(i + random_number()) / (image_width - 1);
				const float v = float(j + random_number()) / (image_height - 1);
				const Ray r = camera.get_ray(u, v);
				color += trace(world, r, ray_limit);
			}
			color /= samples_per_pixel;
#ifndef _DEBUG 
			std::cout << (int)(clamp(color.x) * 255) << ' '
				  << (int)(clamp(color.y) * 255) << ' '
				  << (int)(clamp(color.z) * 255) << '\n';
#endif
		}
	}
	return 0;
}
