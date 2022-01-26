#pragma once

#include <cstdint>

#include "Colour.hpp"

namespace WINDOW {
	extern const uint32_t WIDTH;
	extern const uint32_t HEIGHT;

	extern const char* TITLE;

	extern const float TARGET_FPS;
	extern const float TARGET_DT;

	extern const float MAX_DT;
}

namespace STRINGS {

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