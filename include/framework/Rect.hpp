#pragma once

#include "Maths.hpp"

namespace Framework {
	class Rect {
	public:
		Rect();
		Rect(vec2 _position, vec2 _size);
		Rect(float x, float y, float width, float height);

		vec2 position;
		vec2 size;
	};
}