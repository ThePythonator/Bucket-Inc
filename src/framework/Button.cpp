#include "Button.hpp"

namespace Framework {
	Button::Button() {

	}

	Button::Button(Rect rect, ButtonImages images, Text text, uint8_t id) {
		_render_rect = rect;
		_collider_rect = rect;

		_images = images;
		_text = text;
		_id = id;
		// TODO: support different images for hover
	}

	Button::Button(Rect render_rect, Rect collider_rect, ButtonImages images, Text text, uint8_t id) {
		_render_rect = render_rect;
		_collider_rect = collider_rect;

		_images = images;
		_text = text;
		_id = id;
		// TODO: support different images for hover
	}

	Button::ButtonState Button::state() {
		return _state;
	}

	bool Button::pressed() {
		return _state == ButtonState::JUST_PRESSED || _state == ButtonState::STILL_DOWN;
	}

	void Button::update(InputHandler* input) {
		if (_state == ButtonState::JUST_PRESSED) {
			_state = ButtonState::STILL_DOWN;
		}
		else if (_state == ButtonState::JUST_RELEASED) {
			_state = ButtonState::STILL_UP;
		}

		if (input->just_up(MouseHandler::MouseButton::LEFT)) {
			_state = ButtonState::JUST_RELEASED;
		}
		else if (input->just_down(MouseHandler::MouseButton::LEFT)) {
			if (colliding(_collider_rect, input->mouse_position())) {
				_state = ButtonState::JUST_PRESSED;
			}
		}
	}

	void Button::render() {
		(pressed() ? _images.selected : _images.unselected)->render(_render_rect);
		_text.render(_render_rect.centre());
	}

	void Button::set_position(vec2 position) {
		_render_rect.position = position;
	}

	uint8_t Button::get_id() {
		return _id;
	}
}