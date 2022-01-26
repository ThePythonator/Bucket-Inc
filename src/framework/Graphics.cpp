#include "Graphics.hpp"

namespace Framework {
	Graphics::Graphics() {

	}

	void Graphics::fill(const Colour& colour) {
		SDLUtils::SDL_SetRenderDrawColor(renderer, colour);
		// RenderClear doesn't do alpha
		//SDL_RenderClear(renderer);

		// So we draw a rectangle over the window instead
		SDL_RenderFillRect(renderer, NULL);
	}

	void Graphics::fill(const Colour& colour, uint8_t alpha) {
		fill(Colour(colour, alpha)); // note: alpha doen't work
	}

	void Graphics::set_renderer(SDL_Renderer* _renderer) {
		renderer = _renderer;
	}

	SDL_Renderer* Graphics::get_renderer() {
		return renderer;
	}
}