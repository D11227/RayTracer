#pragma once

#include <tuple>

#include "Vector.hpp"
#include "Ray.hpp"

typedef struct Object_Hitted {
	float t;
	Vector point;
	Vector normal;
	Color color;
} Object_Hitted;

class Object {
	private:
		Color color;
	public:
		Object(const Color& color) :
			color(color)
		{}

		inline Color get_color() const { return color; }
		virtual bool check_hit(const Ray& r, float& t_max, Object_Hitted& object) const = 0;
};
