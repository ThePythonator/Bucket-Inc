#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Colour.hpp"

#include "Maths.hpp"

namespace WINDOW {
	extern const uint32_t WIDTH;
	extern const uint32_t HEIGHT;

	extern const Framework::vec2 SIZE;

	extern const uint32_t WIDTH_HALF;
	extern const uint32_t HEIGHT_HALF;

	extern const Framework::vec2 SIZE_HALF;

	extern const char* TITLE;

	extern const float TARGET_FPS;
	extern const float TARGET_DT;

	extern const float MAX_DT;
}

namespace STRINGS {
	namespace TITLE {
		extern const std::vector<std::string> BUTTONS;
	}

	namespace SETTINGS {
		extern const std::vector<std::string> BUTTONS;
	}
}

namespace PATHS {
	extern const uint8_t DEPTH;

	namespace IMAGES {
		extern const std::string LOCATION;

		extern const std::string MAIN_SPRITESHEET;
		extern const std::string FONT_SPRITESHEET;
		extern const std::string BACKGROUND;
		extern const std::string POPUP;
		extern const std::string BUTTON_UNSELECTED;
		extern const std::string BUTTON_SELECTED;
	}
}

namespace GRAPHICS_OBJECTS {
	// enum inside its own namespace allows multiple repeated names in the enums, without needing enum class and all the casting
	namespace IMAGES {
		enum IMAGES {
			MAIN_SPRITESHEET,
			FONT_SPRITESHEET,
			BACKGROUND,
			POPUP,
			BUTTON_UNSELECTED,
			BUTTON_SELECTED,

			TOTAL_IMAGES
		};
	}

	namespace SPRITESHEETS {
		enum SPRITESHEETS {
			MAIN_SPRITESHEET,
			FONT_SPRITESHEET,

			TOTAL_SPRITESHEETS
		};
	}

	namespace FONTS {
		enum FONTS {
			MAIN_FONT,

			TOTAL_FONTS
		};
	}
}

namespace FONTS {
	namespace SIZE {
		extern const uint8_t MAIN_FONT;
	}

	namespace SCALE {
		extern const uint8_t MAIN_FONT;
	}

	namespace SPACING {
		extern const uint8_t MAIN_FONT;
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

	namespace MENU {
		namespace DURATION {
			extern const float FADE;
		}
	}
}

namespace SPRITE {
	extern const uint8_t SIZE;
	extern const uint8_t SIZE_HALF;
	extern const uint8_t SCALE;
	extern const uint8_t UI_SCALE;

	extern const uint8_t SPLASH_ICON_SCALE;

	namespace INDEX {
		extern const uint8_t SPLASH_ICON;

		extern const std::vector<uint8_t> CRACKED_PIPES_VERTICAL;
		extern const std::vector<uint8_t> CRACKED_PIPES_HORIZONTAL;

		extern const uint8_t PIPE_VERTICAL;
		extern const uint8_t PIPE_HORIZONTAL;
	}

	namespace RECT {
		extern const Framework::Rect BUCKET_RECT;
	}

	extern const uint8_t PIPES_ARRAY_WIDTH;
	extern const uint8_t PIPES_ARRAY_HEIGHT;
	extern const uint8_t PIPES_ARRAY_SIZE;
	extern const uint8_t PIPES[];
}

namespace CURVES {
	namespace BEZIER {
		extern const std::vector<Framework::vec2> TITLE_CONTROL_POINTS;
	}
}

namespace BUTTONS {
	extern const uint8_t NONE;

	namespace TITLE {
		enum TITLE {
			PLAY,
			SETTINGS,
			QUIT,

			TOTAL
		};
	}

	namespace SETTINGS {
		enum SETTINGS {
			SOUND,
			MUSIC,
			BACK,

			TOTAL
		};
	}
}