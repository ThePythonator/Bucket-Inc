#pragma once

#include "Maths.hpp"

namespace Framework {
	class Rect {
	public:
		Rect(vec2 _position = VEC_NULL, vec2 _size = VEC_NULL);
		Rect(float x, float y, float width = 0.0f, float height = 0.0f);

		vec2 position;
		vec2 size;
	};
}