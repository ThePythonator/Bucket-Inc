#include "Image.hpp"

namespace Framework {
	Image::Image() {

	}

	bool Image::load(Graphics* graphics, std::string path, uint8_t flags) {
		// Load image at specified path
		SDL_Surface* temp_surface = IMG_Load(path.c_str());

		if (temp_surface == NULL)
		{
			printf("Unable to create surface from %s!\nSDL Error: %s\n", path.c_str(), SDL_GetError());
			return false;
		}

		// Get width and height
		_w = temp_surface->w;
		_h = temp_surface->h;

		// Create texture from image
		SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(graphics->get_renderer(), temp_surface);

		if (temp_texture == NULL)
		{
			printf("Unable to create texture from %s!\nSDL Error: %s\n", path.c_str(), SDL_GetError());
			SDL_FreeSurface(temp_surface);
			return false;
		}

		if (flags & Flags::SDL_SURFACE) {
			// We want to keep the surface
			surface = temp_surface;
			types |= Flags::SDL_SURFACE; // set bit
		}
		else {
			// Free
			SDL_FreeSurface(temp_surface);
		}

		if (flags & Flags::SDL_TEXTURE) {
			// We want to keep the surface
			texture = temp_texture;
			types |= Flags::SDL_TEXTURE; // Set bit
		}
		else {
			// Free
			SDL_DestroyTexture(temp_texture);
		}

		return true;
	}

	void Image::free() {
		// Free the images
		if (types & Flags::SDL_SURFACE) {
			SDL_FreeSurface(surface);
			types &= ~Flags::SDL_SURFACE; // Unset bit
		}
		if (types & Flags::SDL_TEXTURE) {
			SDL_DestroyTexture(texture);
			types &= ~Flags::SDL_TEXTURE; // Unset bit
		}
	}

	void Image::render(Graphics* graphics, Rect source_rect, Rect destination_rect) {
		if (source_rect.size == vec2{ 0.0f, 0.0f }) {
			source_rect.size = get_size();
		}
		if (destination_rect.size == vec2{ 0.0f, 0.0f }) {
			destination_rect.size = get_size();
		}

		// Render from texture to screen
		SDL_RenderCopy(graphics->get_renderer(), texture, &SDLUtils::get_sdl_rect(source_rect), &SDLUtils::get_sdl_rect(destination_rect));
	}

	void Image::render(Graphics* graphics, Rect destination_rect) {
		render(graphics, VEC_NULL, destination_rect);
	}

	// Returns SDL_Texture* if loaded, otherwise returns nullptr
	SDL_Texture* Image::get_texture() {
		return texture;
	}

	// Returns SDL_Surface* if loaded, otherwise returns nullptr
	SDL_Surface* Image::get_surface() {
		return surface;
	}

	vec2 Image::get_size() {
		return vec2{ static_cast<float>(_w), static_cast<float>(_h)};
	}

	Image* create_image(Graphics* graphics, std::string path, uint8_t flags) {
		Image* image_ptr = new Image();
		image_ptr->load(graphics, path, flags);
		return image_ptr;
	}
}