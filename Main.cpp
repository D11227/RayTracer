#include <iostream>
#include <vector>
#include <random>

#include "Sphere.hpp"
#include "Ray.hpp"
#include "Camera.hpp"

const auto infinity = std::numeric_limits<float>::infinity();

inline float random_number() {
	static std::uniform_real_distribution<float> distribution(0, 1);
	static std::mt19937 generator;
	return distribution(generator);
}

inline float random_number(const int& min, const int& max) {
	return min + (max - min) * random_number();
}

Vector random_vector(const int& min, const int& max) {
	while (true) {
		Vector p = Vector(random_number(-1, 1), random_number(-1, 1), random_number(-1, 1));
		if (p.Length_Squared() >= 1) continue;
		return p;
	}
}

Color trace(const std::vector<Sphere>& world, const Ray& r, int ray_limit) {
	if (ray_limit <= 0) return Color(0, 0, 0);
	float closest = infinity, t;
	Vector p, n;
	bool is_hitted_something = false;
	for (const auto& object : world) {
		auto [is_hitted, t_, point_at, normal] = object.check_hit(r, closest);
		if (is_hitted) {
			is_hitted_something = true;
			closest = t = t_;
			p = point_at;
			n = normal;
		}
	}
	if (is_hitted_something) {
		auto target = p + n + random_vector(-1, 1);
		return trace(world, Ray(p, target - p), ray_limit - 1) * 0.5f;
	}

	Vector direction = r.direction.Normalize();
	t = 0.5f * (direction.y + 1);
	return Color(1.0f, 1.0f, 1.0f) * (1 - t) + Color(0.3f, 0.5f, 1.0f) * t;
}

int32_t main() {
	const float aspect_ratio = 16.0f / 9.0f;
	const int image_width = 1200;
	// aspect_ratio = width / height => height = width / aspec_ratio
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int ray_limit = 100;

	std::vector<Sphere> world;
	world.push_back(Sphere(Vector(0, 0, -1), 0.5));
	world.push_back(Sphere(Vector(0, -100.5, -1), 100));

	Camera camera;
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	auto clamp = [](const float& x, const float& min = 0.0f, const float& max = 0.99f) -> float {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	};

	for (int j = image_height - 1; j >= 0; --j) {
		for (int i = 0; i < image_width; ++i) {
			const float u = float(i) / (image_width - 1);
			const float v = float(j) / (image_height - 1);
			const Ray r = camera.get_ray(u, v);
			Color color = trace(world, r, ray_limit);
#ifndef _DEBUG 
			std::cout << (int)(clamp(color.x) * 255.99) << ' ' << (int)(clamp(color.y) * 255.99) << ' ' << (int)(clamp(color.z) * 255.99) << '\n';
#endif
		}
	}
	return 0;
}
