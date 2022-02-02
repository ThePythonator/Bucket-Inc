#pragma once

#include "Image.hpp"
#include "Font.hpp"
#include "Mouse.hpp"

namespace Framework {
	class Button {
	public:
		enum class ButtonState {
			STILL_UP, // Button isn't pressed (has already been up for at least one frame)
			JUST_RELEASED, // Button has just been released
			STILL_DOWN, // Button is pressed (has already been down for at least one frame)
			JUST_PRESSED // Button has been pressed that frame
		};

		Button();
		Button(Rect rect, Image* image, Text* text);

		ButtonState state();
		bool pressed();

		void update(MouseHandler::Mouse* mouse);
		void render(Graphics* graphics);

	private:
		ButtonState _state = ButtonState::STILL_UP;

		Rect _rect;
		Image* _image_ptr = nullptr;
		Text* _text_ptr = nullptr;

		// Add ID attribute??
	};
}