#include "Graphics.hpp"

namespace Framework {
	Graphics::Graphics() {

	}

	void Graphics::fill(const Colour& colour) {
		SDLUtils::SDL_SetRenderDrawColor(renderer, colour);
		SDL_RenderClear(renderer); // need workaround for alpha
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