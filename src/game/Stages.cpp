#include "Stages.hpp"

// TitleStage

TitleStage::TitleStage() : BaseStage() {
	temp_x = temp_y = 0;
	temp_b = false;
}

void TitleStage::update(float dt, Framework::InputHandler& input) {

	//printf("%f, %f\n", input.mouse_position().x, input.mouse_position().y);
	temp_x = input.mouse_position().x;
	temp_y = input.mouse_position().y;
	temp_b = input.is_down(Framework::MouseHandler::MouseButton::LEFT);
}

void TitleStage::render(Framework::Graphics& graphics) {
	//graphics.fill(COLOURS::WHITE, 0x5F);
	graphics.fill(Framework::Colour(0x5F, 0xFF, 0xFF, 0x5F));
	Framework::SDLUtils::SDL_SetRenderDrawColor(graphics.get_renderer(), COLOURS::BLACK);
	if (temp_b) Framework::SDLUtils::SDL_RenderDrawCircle(graphics.get_renderer(), temp_x, temp_y, 10);
}

// SettingsStage

SettingsStage::SettingsStage() : BaseStage() {

}

void SettingsStage::update(float dt, Framework::InputHandler& input) {

}

void SettingsStage::render(Framework::Graphics& graphics) {

}

// GameStage

GameStage::GameStage() : BaseStage() {

}

void GameStage::update(float dt, Framework::InputHandler& input) {

}

void GameStage::render(Framework::Graphics& graphics) {

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

void PausedStage::render(Framework::Graphics& graphics) {
	// Render background stage
	_background_stage->render(graphics);
}