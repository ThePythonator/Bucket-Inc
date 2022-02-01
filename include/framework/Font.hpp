#pragma once

#include <string>

#include "Spritesheet.hpp"

namespace Framework {
	extern const uint8_t FONT_SHEET_WIDTH;
	extern const uint8_t FONT_SHEET_HEIGHT;
	extern const uint8_t ALPHABET_LENGTH;

	class Font {
	public:
		enum AnchorPosition {
			LEFT = 0b0100,
			CENTER_X = 0b0000,
			RIGHT = 0b1000,

			TOP = 0b0001,
			CENTER_Y = 0b0000,
			BOTTOM = 0b0010,

			TOP_RIGHT = TOP | RIGHT,
			TOP_CENTER = TOP | CENTER_X,
			TOP_LEFT = TOP | LEFT,

			CENTER_RIGHT = CENTER_Y | RIGHT,
			CENTER_CENTER = CENTER_X | CENTER_Y,
			CENTER_LEFT = CENTER_Y | LEFT,

			BOTTOM_RIGHT = BOTTOM | RIGHT,
			BOTTOM_CENTER = BOTTOM | CENTER_X,
			BOTTOM_LEFT = BOTTOM | LEFT
		};

		Font();
		Font(Graphics* graphics, Spritesheet* spritesheet, uint8_t spacing = 1);

		void render_text(std::string text, vec2 position, Colour colour, AnchorPosition anchor_position = AnchorPosition::CENTER_CENTER);

	private:
		void render_char(uint8_t c, vec2 position);
		void set_colour(Colour colour);

		Graphics* graphics_ptr = nullptr;
		Spritesheet* font_spritesheet_ptr = nullptr;

		Rect character_rects[96]; // TODO: sort out issue with ALPHABET_LENGTH - where to define it??

		uint8_t _spacing = 1;
	};
}