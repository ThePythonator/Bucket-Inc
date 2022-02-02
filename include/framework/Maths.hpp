#pragma once

#include <cmath>
#include <limits>
#include <vector>

#include "linalg.h"

namespace Framework {
	typedef linalg::aliases::float2 vec2;
	typedef linalg::aliases::float2x2 mat22;

	using linalg::mul;
	using linalg::length;
	using linalg::dot;
	using linalg::cross;
	using linalg::inverse;
	using linalg::identity;

	extern const float PI;
	// extern const float EPSILON;

	extern const vec2 VEC_NULL;

	class Rect {
	public:
		Rect(vec2 _position = VEC_NULL, vec2 _size = VEC_NULL);
		Rect(float x, float y, float width = 0.0f, float height = 0.0f);
		Rect(int x, int y, int width, int height);

		vec2 position;
		vec2 size;
	};

	bool colliding(Rect a, vec2 b);
	bool colliding(Rect a, Rect b);

	float length_squared(vec2 v);
	vec2 normalise(vec2 v);

	// Convert to/from radians and degrees
	float deg_to_rad(float degrees);
	float rad_to_deg(float radians);

	// angle is in radians
	mat22 rotation_matrix(float angle);

	// Get vector perpendicular to supplied vector
	vec2 perpendicular_acw(vec2 vector);
	vec2 perpendicular_cw(vec2 vector);
}