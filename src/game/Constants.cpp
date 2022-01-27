#include "Constants.hpp"

namespace WINDOW {
	const uint32_t WIDTH = 1024;
	const uint32_t HEIGHT = 768;

	const uint32_t WIDTH_HALF = WIDTH / 2;
	const uint32_t HEIGHT_HALF = HEIGHT / 2;

	const char* TITLE = "Bucket, Inc.";

	const float TARGET_FPS = 60.0f;
	const float TARGET_DT = 1.0f / TARGET_FPS;

	const float MAX_DT = 0.05f;
}

namespace STRINGS {

}

namespace PATHS {
	const uint8_t DEPTH = 4;

	namespace IMAGES {
		const std::string LOCATION = "images/";

		const std::string SPRITESHEET = "spritesheet.png";
	}
}

namespace GRAPHICS_OBJECTS {
	namespace IMAGES {
		// Enums would be good for this except multiple files include the header...
		const uint8_t MAIN_SPRITESHEET = 0;

		const uint8_t TOTAL_IMAGES = 1;
	}

	namespace SPRITESHEETS {
		const uint8_t MAIN_SPRITESHEET = 0;

		const uint8_t TOTAL_SPRITESHEETS = 1;
	}
}

namespace COLOURS {
	const Framework::Colour BLACK{ 0x00, 0x00, 0x00 };
	const Framework::Colour WHITE{ 0xFF, 0xFF, 0xFF };
}

namespace TIMINGS {
	namespace INTRO {
		namespace DURATION {
			const float INITIAL_DELAY = 1.0f;
			const float FADE_IN = 2.0f;
			const float INTRO_DELAY = 3.0f;
			const float FADE_OUT = 2.0f;
		}

		namespace CUMULATIVE {
			const float INITIAL_DELAY = DURATION::INITIAL_DELAY;
			const float FADE_IN = DURATION::FADE_IN + INITIAL_DELAY;
			const float INTRO_DELAY = DURATION::INTRO_DELAY + FADE_IN;
			const float FADE_OUT = DURATION::FADE_OUT + INTRO_DELAY;
		}
	}

	namespace TITLE {
		namespace DURATION {
			const float FADE_IN = 1.0f;
			//const float FADE_OUT = 1.0f;
		}
	}
}

namespace SPRITE {
	const uint8_t SIZE = 32;
	const uint8_t SIZE_HALF = SIZE / 2;
	const uint8_t SCALE = 1;

	const uint8_t SPLASH_ICON_SCALE = 8;

	namespace INDEX {
		const uint8_t SPLASH_ICON = 56;
	}
}