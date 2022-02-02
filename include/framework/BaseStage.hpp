#pragma once

#include "Input.hpp"
#include "GraphicsObjects.hpp"
#include "Button.hpp"

namespace Framework {
	class BaseStage {
	public:
		BaseStage();

		virtual void update(float dt) = 0;
		virtual void render() = 0;

		BaseStage* next();

		bool finished();
		bool delete_me();

		void init(GraphicsObjects* _graphics_objects, InputHandler* _input);

	protected:
		void finish(BaseStage* next, bool can_delete_me = true);

		std::vector<Framework::Button> buttons;

		GraphicsObjects* graphics_objects = nullptr;
		InputHandler* input = nullptr;

	private:
		bool _finished = false;
		bool _delete_me = false;
		BaseStage* _next = nullptr;
	};
}