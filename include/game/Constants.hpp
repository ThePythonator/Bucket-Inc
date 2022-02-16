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
		extern const std::string TITLE;
	}

	namespace SETTINGS {
		extern const std::vector<std::string> BUTTONS;
		extern const std::string TITLE;
	}

	namespace PAUSED {
		extern const std::vector<std::string> BUTTONS;
		extern const std::string TITLE;
	}

	namespace END {
		extern const std::vector<std::string> BUTTONS;
		extern const std::string TITLE;
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

	namespace SAVE_DATA {
		extern const std::string HIGHSCORE;
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

	namespace TRANSITIONS {
		enum TRANSITIONS {
			FADE_TRANSITION,
			PAUSE_TRANSITION,

			TOTAL_TRANSITIONS
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
	extern const Framework::Colour GREY;
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
}

namespace TRANSITIONS {
	extern const float FADE_TIME;
	extern const float PAUSE_FADE_TIME;
	extern uint8_t PAUSE_ALPHA;
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

		extern const uint8_t SCORE_BOX;
	}

	namespace RECT {
		extern const Framework::Rect BUCKET_RECT;
		extern const Framework::Rect BOX_RECT;
	}

	extern const uint8_t PIPES_ARRAY_WIDTH;
	extern const uint8_t PIPES_ARRAY_HEIGHT;
	extern const uint8_t PIPES_ARRAY_SIZE;
	extern const uint8_t PIPES[];

	extern const Framework::vec2 BOX_POSITION;

	extern const uint8_t BUCKET_SCALE;
	extern const float TITLE_FONT_SCALE;
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

	namespace PAUSED {
		enum PAUSED {
			RESUME,
			EXIT,

			TOTAL
		};
	}

	namespace END {
		enum END {
			RETRY,
			EXIT,

			TOTAL
		};
	}
}

namespace GAME {
	extern const float INITIAL_CRACKED_PIPE_DELAY;
	extern const float INITIAL_CRACKED_PIPE_DROP_COUNT;
	extern const float CRACKED_PIPE_DELAY_DECREASE_FACTOR;
	extern const float CRACKED_PIPE_DROP_INCREASE_FACTOR;

	extern const float CRACKED_PIPE_DROP_DELAY_MIN;
	extern const float CRACKED_PIPE_DROP_DELAY_MAX;

	extern const uint8_t MAX_CRACKED_PIPES;

	extern const float DROP_FALL_RATE;

	extern const uint8_t MAX_WATER_HEIGHT;

	extern const Framework::vec2 BUCKET_COLLIDER_SIZE;
	extern const Framework::vec2 BUCKET_COLLIDER_OFFSET;
	extern const Framework::vec2 BUCKET_SIZE;
	extern const Framework::vec2 DROP_COLLIDER;
	extern const Framework::vec2 DROP_COLLIDER_OFFSET;
}