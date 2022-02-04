#include "Stages.hpp"

// IntroStage

bool IntroStage::update(float dt) {
	_intro_timer.update(dt);

	if (_intro_timer.running()) {
		if (_intro_timer.time() > TIMINGS::INTRO::CUMULATIVE::FADE_OUT) {
			// Switch to title
			finish(new TitleStage());
		}
	}
	else {
		_intro_timer.start();
	}

	return true;
}

void IntroStage::render() {
	graphics_objects->graphics_ptr->fill(COLOURS::BLACK);

	// Render icon
	graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(SPRITE::INDEX::SPLASH_ICON, WINDOW::SIZE_HALF / SPRITE::SPLASH_ICON_SCALE - SPRITE::SIZE_HALF, SPRITE::SPLASH_ICON_SCALE);

	if (_intro_timer.time() < TIMINGS::INTRO::CUMULATIVE::INITIAL_DELAY) {
		// Black
		graphics_objects->graphics_ptr->fill(COLOURS::BLACK);
	}
	else if (_intro_timer.time() < TIMINGS::INTRO::CUMULATIVE::FADE_IN) {
		// Fade in
		graphics_objects->graphics_ptr->fill(COLOURS::BLACK, Framework::Curves::linear(0xFF, 0x00, (_intro_timer.time() - TIMINGS::INTRO::CUMULATIVE::INITIAL_DELAY) / TIMINGS::INTRO::DURATION::FADE_IN));
	}
	else if (_intro_timer.time() < TIMINGS::INTRO::CUMULATIVE::INTRO_DELAY) {
		// Show image
		// i.e. don't render over the top
	}
	else if (_intro_timer.time() < TIMINGS::INTRO::CUMULATIVE::FADE_OUT) {
		// Fade out
		graphics_objects->graphics_ptr->fill(COLOURS::BLACK, Framework::Curves::linear(0x00, 0xFF, (_intro_timer.time() - TIMINGS::INTRO::CUMULATIVE::INTRO_DELAY) / TIMINGS::INTRO::DURATION::FADE_OUT));
	}
	else {
		// Black
		graphics_objects->graphics_ptr->fill(COLOURS::BLACK);
	}
}

// TitleStage

void TitleStage::start() {
	// Create menu buttons
	float step = WINDOW::SIZE.y * 0.15f;
	float start = WINDOW::SIZE.y * 0.225f - step * 2;

	Framework::vec2 scaled_size = graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BUTTON_UNSELECTED]->get_size() * SPRITE::UI_SCALE;
	Framework::vec2 offset = Framework::vec2{ 0.0f, start };

	Framework::Button::ButtonImages button_images {
		graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BUTTON_UNSELECTED],
		graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BUTTON_SELECTED]
	};

	for (uint8_t i = 0; i < BUTTONS::TITLE::TOTAL; i++) {
		Framework::Rect render_rect = Framework::Rect(WINDOW::SIZE_HALF - scaled_size / 2 + offset, scaled_size);
		Framework::Rect collider_rect = Framework::Rect(render_rect.position + SPRITE::UI_SCALE, scaled_size - 2 * SPRITE::UI_SCALE);

		button_positions.push_back(render_rect.position);

		Framework::Text text = Framework::Text(graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], STRINGS::TITLE::BUTTONS[i], COLOURS::BLACK);
		
		buttons.push_back(Framework::Button(render_rect, collider_rect, button_images, text, i));

		offset.y += step;
	}

	// Start timer
	_transition_timer.start();
}

void TitleStage::end() {
	// Delete any pointers we're done with
	for (Framework::Text* text_ptr : text_ptrs) {
		delete text_ptr;
	}
	text_ptrs.clear();
}

bool TitleStage::update(float dt) {
	_transition_timer.update(dt);

	// Update buttons
	for (Framework::Button& button : buttons) {
		button.update(input);

		if (button.pressed() && _button_selected == BUTTONS::NONE) {
			_button_selected = button.get_id();
			_transition_timer.reset();
			_transition_timer.start();

			if (_button_selected == BUTTONS::TITLE::QUIT) {
				// Returning false causes program to exit
				return false;
			}
		}
	}

	if (_button_selected != BUTTONS::NONE && _transition_timer.time() > TIMINGS::TITLE::DURATION::FADE_OUT) {
		// Next stage!
		switch (_button_selected) {
		case BUTTONS::TITLE::PLAY:
			finish(new GameStage());
			break;

		case BUTTONS::TITLE::SETTINGS:
			finish(new SettingsStage());
			break;

		default:
			break;
		}
	}

	return true;
}

void TitleStage::render() {
	graphics_objects->graphics_ptr->fill(COLOURS::BLACK);

	// Render background artwork
	// Empty rect means 0,0,w,h
	graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BACKGROUND]->render(Framework::Rect(Framework::VEC_NULL, WINDOW::SIZE));

	// Render pipes
	for (uint8_t i = 0; i < SPRITE::PIPES_ARRAY_SIZE; i++) {
		if (SPRITE::PIPES[i] != 0) {
			uint16_t x = (i % SPRITE::PIPES_ARRAY_WIDTH) * SPRITE::SIZE;
			uint16_t y = (i / SPRITE::PIPES_ARRAY_WIDTH) * SPRITE::SIZE;

			uint8_t sprite_index = SPRITE::PIPES[i] - 1;

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

			graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(sprite_index, x, y);
		}
	}

	// Render box thing with wires
	// TODO

	// Fade out background graphics slightly
	graphics_objects->graphics_ptr->fill(COLOURS::BLACK, 0x7F);

	// Calculate offset used for animating menu options
	float t = Framework::clamp(_transition_timer.time(), 0.0f, 1.0f);
	if (_button_selected != BUTTONS::NONE) {
		// Reverse animation
		t = 1.0f - t;
	}
	Framework::vec2 offset = Framework::Curves::bezier(CURVES::BEZIER::TITLE_CONTROL_POINTS, t) * WINDOW::SIZE;// : Framework::VEC_NULL;
	
	// Render background for options
	Framework::vec2 scaled_popup_size = graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::POPUP]->get_size() * SPRITE::UI_SCALE;
	graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::POPUP]->render(Framework::Rect(WINDOW::SIZE_HALF - scaled_popup_size / 2 + offset, scaled_popup_size));

	// Shift button positions so they're animated too
	// Render buttons
	for (uint8_t i = 0; i < buttons.size(); i++) {
		buttons[i].set_position(button_positions[i] + offset);
		buttons[i].render();
	}

	if (_button_selected == BUTTONS::NONE && _transition_timer.time() < TIMINGS::TITLE::DURATION::FADE_IN) {
		// Fade in
		graphics_objects->graphics_ptr->fill(COLOURS::BLACK, Framework::Curves::linear(0xFF, 0x00, _transition_timer.time() / TIMINGS::TITLE::DURATION::FADE_IN));
	}
	else if (_button_selected != BUTTONS::NONE) {
		if (_transition_timer.time() < TIMINGS::TITLE::DURATION::FADE_OUT) {
			// Fade out
			graphics_objects->graphics_ptr->fill(COLOURS::BLACK, Framework::Curves::linear(0x00, 0xFF, _transition_timer.time() / TIMINGS::TITLE::DURATION::FADE_OUT));
		}
		else {
			graphics_objects->graphics_ptr->fill(COLOURS::BLACK);
		}
	}
} 

// SettingsStage

SettingsStage::SettingsStage() : BaseStage() {

}

bool SettingsStage::update(float dt) {
	return true;
}

void SettingsStage::render() {

}

// GameStage

GameStage::GameStage() : BaseStage() {

}

bool GameStage::update(float dt) {
	// Note: if pausing game, call
	// finish(new PausedStage(this), false);

	return true;
}

void GameStage::render() {

}

// PausedStage

PausedStage::PausedStage(BaseStage* background_stage) : BaseStage() {
	// Save the background stage so we can still render it, and then go back to it when done
	_background_stage = background_stage;
}

bool PausedStage::update(float dt) {
	if (false) {
		// Exit pause
		finish(_background_stage);
	}

	return true;
}

void PausedStage::render() {
	// Render background stage
	_background_stage->render();
}