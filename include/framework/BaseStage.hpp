#pragma once

#include "Input.hpp"
#include "GraphicsObjects.hpp"

namespace Framework {
	class BaseStage {
	public:
		BaseStage();

		virtual void update(float dt, InputHandler& input) = 0;
		virtual void render(GraphicsObjects& graphics_objects) = 0;

		BaseStage* next();

		bool finished();
		bool delete_me();

	protected:
		void finish(BaseStage* next, bool can_delete_me = true);

	private:
		bool _finished = false;
		bool _delete_me = false;
		BaseStage* _next = nullptr;
	};
}