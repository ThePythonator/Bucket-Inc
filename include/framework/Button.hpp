#pragma once

#include "Image.hpp"
#include "Font.hpp"
#include "Input.hpp"

namespace Framework {
	class Button {
	public:
		enum class ButtonState {
			STILL_UP, // Button isn't pressed (has already been up for at least one frame)
			JUST_RELEASED, // Button has just been released
			STILL_DOWN, // Button is pressed (has already been down for at least one frame)
			JUST_PRESSED // Button has been pressed that frame
		};

		struct ButtonImages {
			Image* unselected = nullptr;
			Image* selected = nullptr;
		};

		Button();
		Button(Rect rect, ButtonImages images, Text text, uint8_t id = 0);
		Button(Rect render_rect, Rect collider_rect, ButtonImages images, Text text, uint8_t id = 0);

		ButtonState state();
		bool pressed();

		void update(InputHandler* input);
		void render();

		void set_position(vec2 position);

		uint8_t get_id();

	private:
		ButtonState _state = ButtonState::STILL_UP;

		Rect _render_rect, _collider_rect;
		ButtonImages _images;
		Text _text;

		uint8_t _id = 0;
	};
}