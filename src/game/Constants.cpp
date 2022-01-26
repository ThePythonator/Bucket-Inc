#include "Constants.hpp"

namespace WINDOW {
	const uint32_t WIDTH = 1024;
	const uint32_t HEIGHT = 768;

	const char* TITLE = "Bucket, Inc.";

	const float TARGET_FPS = 60.0f;
	const float TARGET_DT = 1.0f / TARGET_FPS;

	const float MAX_DT = 0.05f;
}

namespace STRINGS {

}

namespace COLOURS {
	const Framework::Colour BLACK{ 0x00, 0x00, 0x00 };
	const Framework::Colour WHITE{ 0xFF, 0xFF, 0xFF };
}

namespace TIMINGS {
	namespace INTRO {
		namespace DURATION {
			const float INITIAL_DELAY = 1.0f;
			const float FADE_IN = 1.0f;
			const float INTRO_DELAY = 3.0f;
			const float FADE_OUT = 1.0f;
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