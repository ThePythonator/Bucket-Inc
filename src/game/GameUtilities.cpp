#include "GameUtilities.hpp"

void render_background_scene(Framework::GraphicsObjects* graphics_objects, std::vector<CrackedPipe> cracked_pipes) {
	graphics_objects->graphics_ptr->fill(COLOURS::BLACK);

	// Render background artwork
	// Empty rect means 0,0,w,h
	graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BACKGROUND]->render(Framework::Rect(Framework::VEC_NULL, WINDOW::SIZE));

	// Render pipes
	for (uint8_t i = 0; i < SPRITE::PIPES_ARRAY_SIZE; i++) {
		if (SPRITE::PIPES[i] != 0) {
			uint16_t x = (i % SPRITE::PIPES_ARRAY_WIDTH) * SPRITE::SIZE;
			uint16_t y = (i / SPRITE::PIPES_ARRAY_WIDTH) * SPRITE::SIZE;

			bool cracked = false;
			uint8_t sprite_index = SPRITE::PIPES[i] - 1;

			for (CrackedPipe& pipe : cracked_pipes) {
				if (pipe.get_id() == i) {
					sprite_index = pipe.get_sprite_index();
					cracked = true;
					break;
				}
			}

			if (!cracked) {
				if (std::count(SPRITE::INDEX::CRACKED_PIPES_HORIZONTAL.begin(), SPRITE::INDEX::CRACKED_PIPES_HORIZONTAL.end(), sprite_index) > 0) {
					// sprite_index is a horizontal cracked pipe
					// We don't want to render cracked pipes right now, instead render a normal pipe
					sprite_index = SPRITE::INDEX::PIPE_HORIZONTAL;
				}
				else if (std::count(SPRITE::INDEX::CRACKED_PIPES_VERTICAL.begin(), SPRITE::INDEX::CRACKED_PIPES_VERTICAL.end(), sprite_index) > 0) {
					// sprite_index is a vertical cracked pipe
					// We don't want to render cracked pipes right now, instead render a normal pipe
					sprite_index = SPRITE::INDEX::PIPE_VERTICAL;
				}
			}

			graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(sprite_index, x, y);
		}
	}

	// Render box thing with wires
	// TODO
}

void render_menu(Framework::GraphicsObjects* graphics_objects, Framework::Timer& transition_timer, std::vector<Framework::Button> buttons, uint8_t button_selected) {
	render_background_scene(graphics_objects);

	// Fade out background graphics slightly
	graphics_objects->graphics_ptr->fill(COLOURS::BLACK, 0x7F);

	// Calculate offset used for animating menu options
	float t = Framework::clamp(transition_timer.time() / TIMINGS::MENU::DURATION::FADE, 0.0f, 1.0f);
	if (button_selected != BUTTONS::NONE) {
		// Reverse animation
		t = 1.0f - t;
	}
	Framework::vec2 offset = Framework::Curves::bezier(CURVES::BEZIER::TITLE_CONTROL_POINTS, t) * WINDOW::SIZE;

	// Render background for options
	Framework::vec2 scaled_popup_size = graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::POPUP]->get_size() * SPRITE::UI_SCALE;
	graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::POPUP]->render(Framework::Rect(WINDOW::SIZE_HALF - scaled_popup_size / 2 + offset, scaled_popup_size));

	// Shift button positions so they're animated too
	// Render buttons
	for (uint8_t i = 0; i < buttons.size(); i++) {
		buttons[i].set_position(buttons[i].initial_position() + offset);
		buttons[i].render();
	}

	handle_fade(graphics_objects, transition_timer, button_selected == BUTTONS::NONE ? FadeState::IN : FadeState::OUT);
}

void handle_fade(Framework::GraphicsObjects* graphics_objects, Framework::Timer& transition_timer, FadeState state) {
	// Handle fading
	if (state == FadeState::IN) {
		if (transition_timer.time() < TIMINGS::MENU::DURATION::FADE) {
			// Fade in
			graphics_objects->graphics_ptr->fill(COLOURS::BLACK, Framework::Curves::linear(0xFF, 0x00, transition_timer.time() / TIMINGS::MENU::DURATION::FADE));
		}
	}
	else if (state == FadeState::OUT) {
		if (transition_timer.time() < TIMINGS::MENU::DURATION::FADE) {
			// Fade out
			graphics_objects->graphics_ptr->fill(COLOURS::BLACK, Framework::Curves::linear(0x00, 0xFF, transition_timer.time() / TIMINGS::MENU::DURATION::FADE));
		}
		else {
			graphics_objects->graphics_ptr->fill(COLOURS::BLACK);
		}
	}
}

std::vector<Framework::Button> setup_menu_buttons(Framework::GraphicsObjects* graphics_objects, std::vector<std::string> names) {
	std::vector<Framework::Button> buttons;

	// Create menu buttons
	float step = WINDOW::SIZE.y * 0.15f;
	float start = WINDOW::SIZE.y * 0.225f - step * 2;

	Framework::vec2 scaled_size = graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BUTTON_UNSELECTED]->get_size() * SPRITE::UI_SCALE;
	Framework::vec2 offset = Framework::vec2{ 0.0f, start };

	Framework::Button::ButtonImages button_images{
		graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BUTTON_UNSELECTED],
		graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BUTTON_SELECTED]
	};

	for (uint8_t i = 0; i < names.size(); i++) {
		Framework::Rect render_rect = Framework::Rect(WINDOW::SIZE_HALF - scaled_size / 2 + offset, scaled_size);
		Framework::Rect collider_rect = Framework::Rect(render_rect.position + SPRITE::UI_SCALE, scaled_size - 2 * SPRITE::UI_SCALE);

		Framework::Text text = Framework::Text(graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], names[i], COLOURS::BLACK);

		buttons.push_back(Framework::Button(render_rect, collider_rect, button_images, text, i));

		offset.y += step;
	}

	return buttons;
}