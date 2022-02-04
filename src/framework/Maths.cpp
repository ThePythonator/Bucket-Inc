#include "Maths.hpp"

namespace Framework {
	const float PI = 3.14159265f;
	//const float EPSILON = 0.0001f; // todo: check if reasonable

	const vec2 VEC_NULL = vec2{ 0.0f, 0.0f };
	const Rect RECT_NULL = Rect(VEC_NULL, VEC_NULL);

	// Rect and collision detection

	Rect::Rect(vec2 _position, vec2 _size) {
		position = _position;
		size = _size;
	}

	Rect::Rect(float x, float y, float width, float height) {
		position = vec2{ x, y };
		size = vec2{ width, height };
	}

	Rect::Rect(int x, int y, int width, int height) {
		position = vec2{ static_cast<float>(x), static_cast<float>(y) };
		size = vec2{ static_cast<float>(width), static_cast<float>(height) };
	}

	vec2 Rect::centre() {
		return position + size / 2;
	}

	bool colliding(Rect a, vec2 b) {
		return b.x >= a.position.x && b.x <= a.position.x + a.size.x &&
			   b.y >= a.position.y && b.y <= a.position.y + a.size.y;
	}
	bool colliding(Rect a, Rect b) {
		return b.position.x + b.size.x >= a.position.x && b.position.x <= a.position.x + a.size.x &&
			   b.position.y + b.size.y >= a.position.y && b.position.y <= a.position.y + a.size.y;
	}

	// Maths utilities

	float length_squared(vec2 v) {
		return linalg::length2(v);
	}

	vec2 normalise(vec2 v) {
		return linalg::normalize(v);
	}

	float deg_to_rad(float degrees) {
		return PI * degrees / 180.0f;
	}
	float rad_to_deg(float radians) {
		return 180.0f * radians / PI;
	}

	mat22 rotation_matrix(float angle) {
		// Anticlockwise rotation
		float s = std::sin(angle);
		float c = std::cos(angle);
		return mat22{ {c, s}, {-s, c} };
	}

	vec2 perpendicular_acw(vec2 vector) {
		return vec2{ -vector.y, vector.x };
	}

	vec2 perpendicular_cw(vec2 vector) {
		return vec2{ vector.y, -vector.x };
	}

	float clamp(float x, float _min, float _max) {
		return std::min(_max, std::max(_min, x));
	}
}