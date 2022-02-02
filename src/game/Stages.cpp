#include "Stages.hpp"

// IntroStage

IntroStage::IntroStage() : BaseStage() {

}

void IntroStage::update(float dt) {
	_intro_timer.update(dt);

	if (!_intro_timer.running()) {
		_intro_timer.start();
	}
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

		// Switch to title
		finish(new TitleStage());
	}
}

// TitleStage

TitleStage::TitleStage() : BaseStage() {
	temp_x = temp_y = 0;
	temp_b = false;
	// TODO: need to get graphics objects somehow in order to get images
	//Framework::Button play_button = Framework::Button(Framework::Rect(), graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BUTTON], Framework::Text(graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], STRINGS::TITLE::PLAY, COLOURS::BLACK));
}

void TitleStage::update(float dt) {
	_transition_timer.update(dt);

	if (!_transition_timer.running()) {
		_transition_timer.start();
	}

	//printf("%f, %f\n", input.mouse_position().x, input.mouse_position().y);
	temp_x = input->mouse_position().x;
	temp_y = input->mouse_position().y;
	temp_b = input->is_down(Framework::MouseHandler::MouseButton::LEFT);
}

void TitleStage::render() {
	graphics_objects->graphics_ptr->fill(COLOURS::BLACK);

	// Render background artwork
	// Empty rect means 0,0,w,h
	graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BACKGROUND]->render(graphics_objects->graphics_ptr, Framework::Rect(Framework::VEC_NULL, WINDOW::SIZE));

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
	// TODO: animate (bezier?)
	float t = _transition_timer.time() * 0.8f;
	Framework::vec2 offset = t < 1.0f ? Framework::Curves::bezier(CURVES::BEZIER::TITLE_CONTROL_POINTS, t) * WINDOW::SIZE : Framework::VEC_NULL;
	//Framework::vec2 offset = Framework::Curves::bezier(std::vector<Framework::vec2>{Framework::VEC_NULL, Framework::vec2{ 100.0f, 50.0f }, Framework::vec2{ 50.0f, 200.0f }, Framework::vec2{ 100.0f, 50.0f }}, _transition_timer.time() / 3.0f);

	// Render background for options
	Framework::vec2 scaled_size = graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::POPUP]->get_size() * SPRITE::UI_SCALE;
	graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::POPUP]->render(graphics_objects->graphics_ptr, Framework::Rect(WINDOW::SIZE_HALF - scaled_size / 2 + offset, scaled_size));

	// need text and font stuff
	// need button class
	// Render PLAY
	// Render SETTINGS
	// Render QUIT

	// temp for now, just demoing button image

	scaled_size = graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BUTTON]->get_size() * SPRITE::UI_SCALE;
	graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BUTTON]->render(graphics_objects->graphics_ptr, Framework::Rect(WINDOW::SIZE_HALF - scaled_size / 2 + offset - Framework::vec2{ 0.0f, 100.0f }, scaled_size));
	graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BUTTON]->render(graphics_objects->graphics_ptr, Framework::Rect(WINDOW::SIZE_HALF - scaled_size / 2 + offset, scaled_size));
	graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::BUTTON]->render(graphics_objects->graphics_ptr, Framework::Rect(WINDOW::SIZE_HALF - scaled_size / 2 + offset + Framework::vec2{ 0.0f, 100.0f }, scaled_size));


	// Test text rendering
	//graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT]->render_text("QUIT", Framework::vec2{ 5.0f, 5.0f }, COLOURS::BLACK);
	graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT]->render_text("Settings", (WINDOW::SIZE_HALF + offset) / FONTS::SCALE::MAIN_FONT, COLOURS::BLACK, Framework::Font::CENTER_CENTER);
	//graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::FONT_SPRITESHEET]->rect(Framework::Rect(128, 16, 16, 16), 10, 10, 4);
	//graphics_objects->image_ptrs[GRAPHICS_OBJECTS::IMAGES::FONT_SPRITESHEET]->render(graphics_objects->graphics_ptr, Framework::Rect());


	Framework::SDLUtils::SDL_SetRenderDrawColor(graphics_objects->graphics_ptr->get_renderer(), COLOURS::BLACK);
	if (temp_b) Framework::SDLUtils::SDL_RenderDrawCircle(graphics_objects->graphics_ptr->get_renderer(), temp_x, temp_y, 10);

	if (_transition_timer.time() < TIMINGS::TITLE::DURATION::FADE_IN) {
		// Fade in
		graphics_objects->graphics_ptr->fill(COLOURS::BLACK, Framework::Curves::linear(0xFF, 0x00, _transition_timer.time() / TIMINGS::TITLE::DURATION::FADE_IN));
	}
} 

// SettingsStage

SettingsStage::SettingsStage() : BaseStage() {

}

void SettingsStage::update(float dt) {

}

void SettingsStage::render() {

}

// GameStage

GameStage::GameStage() : BaseStage() {

}

void GameStage::update(float dt) {
	// Note: if pausing game, call
	// finish(new PausedStage(this), false);
}

void GameStage::render() {

}

// PausedStage

PausedStage::PausedStage(BaseStage* background_stage) : BaseStage() {
	// Save the background stage so we can still render it, and then go back to it when done
	_background_stage = background_stage;
}

void PausedStage::update(float dt) {
	if (false) {
		// Exit pause
		finish(_background_stage);
	}
}

void PausedStage::render() {
	// Render background stage
	_background_stage->render();
}