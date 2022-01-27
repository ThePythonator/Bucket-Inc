#include "SDLUtils.hpp"

namespace Framework::SDLUtils {

	bool init_sdl(SDL_Window*& window, SDL_Renderer*& renderer) {
		// Initialise SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize!\nSDL Error: %s\n", SDL_GetError());
			return false;
		}

		// Initialise SDL_image
		int img_init_flags = IMG_INIT_JPG | IMG_INIT_PNG;
		if ((IMG_Init(img_init_flags) & img_init_flags) != img_init_flags) {
			printf("SDL_IMG could not initialize!\nSDL_IMG Error: %s\n", IMG_GetError());
			return false;
		}

		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		window = SDL_CreateWindow(
			WINDOW::TITLE,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WINDOW::WIDTH,
			WINDOW::HEIGHT,
			SDL_WINDOW_SHOWN
		);

		// Create renderer for window
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		// Set renderer mode
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		return renderer != nullptr && window != nullptr;
	}

	std::string find_assets_path(std::string test_file, uint8_t depth) {
		printf("Attempting to find assets folder...\n");

		std::string base_path = SDL_GetBasePath();

		SDL_Surface* test_surface = IMG_Load(("assets/" + test_file).c_str());

		if (test_surface != NULL) {
			base_path = "";
		}

		uint8_t count = 0;
		while (test_surface == NULL && count < depth) {
			test_surface = IMG_Load((base_path + "assets/" + test_file).c_str());

			if (test_surface == NULL) {
				base_path += "../";
			}

			count++;
		}

		if (test_surface == NULL) {
			printf("Could not find assets folder!\n");
			return "assets/";
		}

		SDL_FreeSurface(test_surface);

		std::string message = "Found assets folder: " + base_path + "assets/\n\n";

		printf("%s", message.c_str());

		return base_path + "assets/";
	}

	int SDL_SetRenderDrawColor(SDL_Renderer* renderer, const Colour& colour) {
		return SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	}

	int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
		// From https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c

		int offset_x = 0;
		int offset_y = radius;
		int d = radius - 1;
		int status = 0;

		while (offset_y >= offset_x) {
			status += SDL_RenderDrawPoint(renderer, x + offset_x, y + offset_y);
			status += SDL_RenderDrawPoint(renderer, x + offset_y, y + offset_x);
			status += SDL_RenderDrawPoint(renderer, x - offset_x, y + offset_y);
			status += SDL_RenderDrawPoint(renderer, x - offset_y, y + offset_x);
			status += SDL_RenderDrawPoint(renderer, x + offset_x, y - offset_y);
			status += SDL_RenderDrawPoint(renderer, x + offset_y, y - offset_x);
			status += SDL_RenderDrawPoint(renderer, x - offset_x, y - offset_y);
			status += SDL_RenderDrawPoint(renderer, x - offset_y, y - offset_x);

			if (status < 0) {
				status = -1;
				break;
			}

			if (d >= 2 * offset_x) {
				d -= 2 * offset_x + 1;
				offset_x += 1;
			}
			else if (d < 2 * (radius - offset_y)) {
				d += 2 * offset_y - 1;
				offset_y -= 1;
			}
			else {
				d += 2 * (offset_y - offset_x - 1);
				offset_y -= 1;
				offset_x += 1;
			}
		}

		return status;
	}
}