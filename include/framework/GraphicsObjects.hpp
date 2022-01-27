#pragma once

#include <vector>

#include "Graphics.hpp"

#include "Image.hpp"
#include "Spritesheet.hpp"

namespace Framework {
	struct GraphicsObjects {
		Graphics* graphics_ptr = nullptr;

		std::vector<Image*> image_ptrs;
		std::vector<Spritesheet*> spritesheet_ptrs;
	};
}