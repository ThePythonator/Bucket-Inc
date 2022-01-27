#include "Stages.hpp"

// IntroStage

IntroStage::IntroStage() : BaseStage() {

}

void IntroStage::update(float dt, Framework::InputHandler& input) {
	_intro_timer.update(dt);

	if (!_intro_timer.running()) {
		_intro_timer.start();
	}
}

void IntroStage::render(Framework::GraphicsObjects& graphics_objects) {
	graphics_objects.graphics_ptr->fill(COLOURS::BLACK);

	// Render icon
	//graphics_objects.graphics_ptr->fill(COLOURS::WHITE); // to remove
	graphics_objects.spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(SPRITE::INDEX::SPLASH_ICON, WINDOW::WIDTH_HALF / SPRITE::SPLASH_ICON_SCALE - SPRITE::SIZE_HALF, WINDOW::HEIGHT_HALF / SPRITE::SPLASH_ICON_SCALE - SPRITE::SIZE_HALF, SPRITE::SPLASH_ICON_SCALE);
	//graphics_objects.spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(56, 10, 10);

	if (_intro_timer.time() < TIMINGS::INTRO::CUMULATIVE::INITIAL_DELAY) {
		// Black
		graphics_objects.graphics_ptr->fill(COLOURS::BLACK);
	}
	else if (_intro_timer.time() < TIMINGS::INTRO::CUMULATIVE::FADE_IN) {
		// Fade in
		graphics_objects.graphics_ptr->fill(COLOURS::BLACK, Framework::Curves::linear(0xFF, 0x00, (_intro_timer.time() - TIMINGS::INTRO::CUMULATIVE::INITIAL_DELAY) / TIMINGS::INTRO::DURATION::FADE_IN));
	}
	else if (_intro_timer.time() < TIMINGS::INTRO::CUMULATIVE::INTRO_DELAY) {
		// Show image
		// i.e. don't render over the top
	}
	else if (_intro_timer.time() < TIMINGS::INTRO::CUMULATIVE::FADE_OUT) {
		// Fade out
		graphics_objects.graphics_ptr->fill(COLOURS::BLACK, Framework::Curves::linear(0x00, 0xFF, (_intro_timer.time() - TIMINGS::INTRO::CUMULATIVE::INTRO_DELAY) / TIMINGS::INTRO::DURATION::FADE_OUT));
	}
	else {
		// Black
		graphics_objects.graphics_ptr->fill(COLOURS::BLACK);

		// Switch to title
		finish(new TitleStage());
	}
}

// TitleStage

TitleStage::TitleStage() : BaseStage() {
	temp_x = temp_y = 0;
	temp_b = false;
}

void TitleStage::update(float dt, Framework::InputHandler& input) {
	_transition_timer.update(dt);

	if (!_transition_timer.running()) {
		_transition_timer.start();
	}

	//printf("%f, %f\n", input.mouse_position().x, input.mouse_position().y);
	temp_x = input.mouse_position().x;
	temp_y = input.mouse_position().y;
	temp_b = input.is_down(Framework::MouseHandler::MouseButton::LEFT);
}

void TitleStage::render(Framework::GraphicsObjects& graphics_objects) {
	//graphics.fill(COLOURS::WHITE, 0x5F);
	graphics_objects.graphics_ptr->fill(Framework::Colour(0x5F, 0xFF, 0xFF, 0xFF));
	Framework::SDLUtils::SDL_SetRenderDrawColor(graphics_objects.graphics_ptr->get_renderer(), COLOURS::BLACK);
	if (temp_b) Framework::SDLUtils::SDL_RenderDrawCircle(graphics_objects.graphics_ptr->get_renderer(), temp_x, temp_y, 10);

	if (_transition_timer.time() < TIMINGS::TITLE::DURATION::FADE_IN) {
		// Fade in
		graphics_objects.graphics_ptr->fill(COLOURS::BLACK, Framework::Curves::linear(0xFF, 0x00, _transition_timer.time() / TIMINGS::TITLE::DURATION::FADE_IN));
	}
} 

// SettingsStage

SettingsStage::SettingsStage() : BaseStage() {

}

void SettingsStage::update(float dt, Framework::InputHandler& input) {

}

void SettingsStage::render(Framework::GraphicsObjects& graphics_objects) {

}

// GameStage

GameStage::GameStage() : BaseStage() {

}

void GameStage::update(float dt, Framework::InputHandler& input) {

}

void GameStage::render(Framework::GraphicsObjects& graphics_objects) {

}

// PausedStage

PausedStage::PausedStage(BaseStage* background_stage) : BaseStage() {
	// Save the background stage so we can still render it, and then go back to it when done
	_background_stage = background_stage;
}

void PausedStage::update(float dt, Framework::InputHandler& input) {
	if (false) {
		// Exit pause
		finish(_background_stage);
	}
}

void PausedStage::render(Framework::GraphicsObjects& graphics_objects) {
	// Render background stage
	_background_stage->render(graphics_objects);
}