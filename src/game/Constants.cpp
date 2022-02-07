#include "Constants.hpp"

namespace WINDOW {
	const uint32_t WIDTH = 1024;//1280;
	const uint32_t HEIGHT = 768;

	const Framework::vec2 SIZE = Framework::vec2{ WIDTH, HEIGHT };

	const uint32_t WIDTH_HALF = WIDTH / 2;
	const uint32_t HEIGHT_HALF = HEIGHT / 2;

	const Framework::vec2 SIZE_HALF = Framework::vec2{ WIDTH_HALF, HEIGHT_HALF };

	const char* TITLE = "Bucket, Inc.";

	const float TARGET_FPS = 60.0f;
	const float TARGET_DT = 1.0f / TARGET_FPS;

	const float MAX_DT = 0.05f;
}

namespace STRINGS {
	namespace TITLE {
		const std::vector<std::string> BUTTONS = {
			"Play",
			"Settings",
			"Quit"
		};
	}

	namespace SETTINGS {
		const std::vector<std::string> BUTTONS = {
			"Sound",
			"Music",
			"Back"
		};
	}
}

namespace PATHS {
	const uint8_t DEPTH = 4;

	namespace IMAGES {
		const std::string LOCATION = "images/";

		const std::string MAIN_SPRITESHEET = "spritesheet.png";
		const std::string FONT_SPRITESHEET = "font.png";
		const std::string BACKGROUND = "background.png";
		const std::string POPUP = "popup.png";
		const std::string BUTTON_UNSELECTED = "button_unselected.png";
		const std::string BUTTON_SELECTED = "button_selected.png";
	}
}

namespace GRAPHICS_OBJECTS {
	namespace IMAGES {
	
	}

	namespace SPRITESHEETS {

	}

	namespace FONTS {

	}
}

namespace FONTS {
	namespace SIZE {
		const uint8_t MAIN_FONT = 16;
	}

	namespace SCALE {
		const uint8_t MAIN_FONT = 4;
	}

	namespace SPACING {
		const uint8_t MAIN_FONT = 1;
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

	namespace MENU {
		namespace DURATION {
			const float FADE = 1.2f;
		}
	}
}

namespace SPRITE {
	const uint8_t SIZE = 32;
	const uint8_t SIZE_HALF = SIZE / 2;
	const uint8_t SCALE = 2;
	const uint8_t UI_SCALE = 4;

	const uint8_t SPLASH_ICON_SCALE = 8;

	namespace INDEX {
		const uint8_t SPLASH_ICON = 56;

		const std::vector<uint8_t> CRACKED_PIPES_VERTICAL = { 11, 19, 26, 27 };
		const std::vector<uint8_t> CRACKED_PIPES_HORIZONTAL = { 10, 18 };

		const uint8_t PIPE_VERTICAL = 3;
		const uint8_t PIPE_HORIZONTAL = 2;
	}

	const uint8_t PIPES_ARRAY_WIDTH = 16;
	const uint8_t PIPES_ARRAY_HEIGHT = 5;
	const uint8_t PIPES_ARRAY_SIZE = PIPES_ARRAY_WIDTH * PIPES_ARRAY_HEIGHT;

	// Can just paste in from the .tmx file (makes life easier)
	// Tiled sets 0 to blank, so all are off by one
	const uint8_t PIPES[PIPES_ARRAY_SIZE] = {
		0,0,28,0,0,0,0,12,0,20,0,13,11,19,6,0,
		0,0,15,19,11,19,7,14,0,27,0,0,0,0,28,0,
		19,11,14,0,0,0,20,0,0,12,0,5,19,11,8,0,
		0,0,0,0,0,0,13,19,11,16,19,14,0,0,28,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,13,19
	};
}

namespace CURVES {
	namespace BEZIER {
		const std::vector<Framework::vec2> TITLE_CONTROL_POINTS {
			Framework::vec2{ 0.0f, -1.0f },
			Framework::vec2{ 0.0f, -1.0f },
			Framework::vec2{ 0.0f, 0.6f },
			Framework::vec2{ 0.0f, -0.1f },
			Framework::vec2{ 0.0f, 0.0f },
			Framework::vec2{ 0.0f, 0.0f }
		};
	}
}

namespace BUTTONS {
	const uint8_t NONE = 255;
}