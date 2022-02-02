#include "Button.hpp"

namespace Framework {
	Button::Button() {

	}

	Button::Button(Rect rect, Image* image, Text* text) {
		_rect = rect;
		_image_ptr = image;
		_text_ptr = text;
		// TODO: support different images for hover
	}

	Button::ButtonState Button::state() {
		return _state;
	}

	bool Button::pressed() {
		return _state == ButtonState::JUST_PRESSED || _state == ButtonState::STILL_DOWN;
	}

	void Button::update(MouseHandler::Mouse* mouse) {
		if (colliding(_rect, mouse->position())) {
			if (_state == ButtonState::JUST_PRESSED) {
				_state = ButtonState::STILL_DOWN;
			}
			else if (_state == ButtonState::JUST_RELEASED) {
				_state = ButtonState::STILL_UP;
			}

			if (mouse->button_state(MouseHandler::MouseButton::LEFT) == MouseHandler::MouseButtonState::JUST_PRESSED) {
				_state = ButtonState::JUST_PRESSED;
			}
			else if (mouse->button_state(MouseHandler::MouseButton::LEFT) == MouseHandler::MouseButtonState::JUST_RELEASED) {
				_state = ButtonState::JUST_RELEASED;
			}
		}
	}

	void Button::render(Graphics* graphics) {
		_image_ptr->render(graphics, _rect);
		_text_ptr->render(_rect.position);
	}
}