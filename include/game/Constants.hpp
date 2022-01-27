#pragma once

#include <cstdint>
#include <string>

#include "Colour.hpp"

namespace WINDOW {
	extern const uint32_t WIDTH;
	extern const uint32_t HEIGHT;

	extern const uint32_t WIDTH_HALF;
	extern const uint32_t HEIGHT_HALF;

	extern const char* TITLE;

	extern const float TARGET_FPS;
	extern const float TARGET_DT;

	extern const float MAX_DT;
}

namespace STRINGS {

}

namespace PATHS {
	extern const uint8_t DEPTH;

	namespace IMAGES {
		extern const std::string LOCATION;

		extern const std::string SPRITESHEET;
	}
}

namespace GRAPHICS_OBJECTS {
	namespace IMAGES {
		extern const uint8_t MAIN_SPRITESHEET;

		extern const uint8_t TOTAL_IMAGES;
	}

	namespace SPRITESHEETS {
		extern const uint8_t MAIN_SPRITESHEET;

		extern const uint8_t TOTAL_SPRITESHEETS;
	}
}

namespace COLOURS {
	extern const Framework::Colour BLACK;
	extern const Framework::Colour WHITE;
}

namespace TIMINGS {
	namespace INTRO {
		namespace DURATION {
			extern const float INITIAL_DELAY;
			extern const float FADE_IN;
			extern const float INTRO_DELAY;
			extern const float FADE_OUT;
		}

		namespace CUMULATIVE {
			extern const float INITIAL_DELAY;
			extern const float FADE_IN;
			extern const float INTRO_DELAY;
			extern const float FADE_OUT;
		}
	}

	namespace TITLE {
		namespace DURATION {
			extern const float FADE_IN;
			//extern const float FADE_OUT;
		}
	}
}

namespace SPRITE {
	extern const uint8_t SIZE;
	extern const uint8_t SIZE_HALF;
	extern const uint8_t SCALE;

	extern const uint8_t SPLASH_ICON_SCALE;

	namespace INDEX {
		extern const uint8_t SPLASH_ICON;
	}
}