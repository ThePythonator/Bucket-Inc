#include "FadeTransition.hpp"

namespace Framework {
	FadeTransition::FadeTransition(Colour colour, float fade_time, uint8_t max_alpha, uint8_t min_alpha) {
		_colour = colour;

		_fade_time = fade_time;

		_min = min_alpha;
		_max = max_alpha;
	}

	void FadeTransition::update(float dt) {
		if (_state == TransitionState::OPENING || _state == TransitionState::CLOSING) {
			_timer.update(dt);

			if (_timer.time() > _fade_time) {
				_state = _state == TransitionState::OPENING ? TransitionState::OPEN : TransitionState::CLOSED;
			}
		}
	}

	void FadeTransition::render(GraphicsObjects* graphics_objects) {
		// Handle fading
		switch (_state) {
		case TransitionState::CLOSED:
			// Fill with solid colour
			graphics_objects->graphics_ptr->fill(_colour);
			break;

		case TransitionState::CLOSING:
			// Fade out
			graphics_objects->graphics_ptr->fill(_colour, Framework::Curves::linear(_min, _max, _timer.time() / TRANSITIONS::FADE_TIME));
			break;

		case TransitionState::OPENING:
			// Fade in
			graphics_objects->graphics_ptr->fill(_colour, Framework::Curves::linear(_max, _min, _timer.time() / TRANSITIONS::FADE_TIME));
			break;

		default:
			break;
		}
	}

	float FadeTransition::percent() {
		return _timer.time() / _fade_time;
	}
}