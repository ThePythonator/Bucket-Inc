#include "Rect.hpp"

namespace Framework {
	Rect::Rect(vec2 _position, vec2 _size) {
		position = _position;
		size = _size;
	}

	Rect::Rect(float x, float y, float width, float height) {
		position = vec2{ x, y };
		size = vec2{ width, height };
	}
}