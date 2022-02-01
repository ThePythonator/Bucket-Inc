#include "Font.hpp"

namespace Framework {
	const uint8_t FONT_SHEET_WIDTH = 32;
	const uint8_t FONT_SHEET_HEIGHT = 3;
	const uint8_t ALPHABET_LENGTH = FONT_SHEET_WIDTH * FONT_SHEET_HEIGHT;

	Font::Font() {

	}

	Font::Font(Graphics* graphics, Spritesheet* spritesheet, uint8_t spacing = 1) {
		graphics_ptr = graphics;
		font_spritesheet_ptr = spritesheet;
		_spacing = spacing;

		SDL_Surface* font_sheet_surface = spritesheet.get_image()->get_surface();
		uint8_t sprite_size = spritesheet->get_sprite_size();

		uint16_t base_x, base_y, x, y, left, right;
		Colour c;
		bool found;

		// Generate character_rects
		for (uint8_t i = 0; i < ALPHABET_LENGTH; i++) {
			base_x = (i % FONT_SHEET_WIDTH) * sprite_size;
			base_y = (i / FONT_SHEET_WIDTH) * sprite_size;

			left = 0;
			right = sprite_size - 1;

			// Find leftmost pixel
			found = false;

			x = y = 0;
			while (!found) {
				// Get pixel at (x, y)
				c = SDLUtils::SDL_GetPixel(font_sheet_surface, base_x + x, base_y + y);

				if (c.a) {
					// We found the left edge of the character!
					left = x;
					found = true;
				}

				y++;
				if (y == sprite_size) {
					if (x == sprite_size - 1) {
						// Character is blank
						found = true;
					}

					y = 0;
					x++;
				}
			}

			// Find rightmost pixel
			found = false;

			x = sprite_size - 1;
			y = 0;
			while (!found) {
				// Get pixel at (x, y)
				c = SDLUtils::SDL_GetPixel(font_sheet_surface, base_x + x, base_y + y);

				if (c.a) {
					// We found the right edge of the character!
					right = x;
					found = true;
				}

				y++;
				if (y == sprite_size) {
					if (x == 0) {
						// Character is blank
						found = true;
					}

					y = 0;
					x--;
				}
			}

			character_rects[i] = Rect{ base_x + left, base_y, right - left + 1, sprite_size };
		}

		// White
		Colour WHITE{ 0xFF, 0xFF, 0xFF };

		// Set all pixels to white (with no transparency at all) if they are not completely transparent
		for (x = 0; x < FONT_SHEET_WIDTH * sprite_size; x++) {
			for (y = 0; y < FONT_SHEET_HEIGHT * sprite_size; y++) {
				c = SDLUtils::SDL_GetPixel(font_sheet_surface, x, y);

				if (c.a) {
					// Pixel isn't transparent!
					SDLUtils::SDL_SetPixel(font_sheet_surface, x, y, WHITE);
				}
			}
		}
	}
}