#include "BaseStage.hpp"

namespace Framework {
	BaseStage::BaseStage() {

	}

	BaseStage* BaseStage::next() {
		return _next;
	}

	bool BaseStage::finished() {
		return _finished;
	}

	bool BaseStage::delete_me() {
		return _delete_me;
	}

	void BaseStage::finish(BaseStage* next, bool can_delete_me) {
		_finished = true;
		_delete_me = can_delete_me;
		_next = next;
	}

	void BaseStage::init(GraphicsObjects* _graphics_objects, InputHandler* _input) {
		graphics_objects = _graphics_objects;
		input = _input;
	}
}