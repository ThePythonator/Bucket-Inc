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

	protected:
		void finish(BaseStage* next);

	private:
		bool _finished = false;
		BaseStage* _next = nullptr;
	};
}