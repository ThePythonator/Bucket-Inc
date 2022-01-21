#include "BaseStage.hpp"
#include "Stages.hpp"

// TitleStage

TitleStage::TitleStage() : BaseStage() {

}

void TitleStage::update(float dt) {

}

void TitleStage::render(Framework::Graphics& graphics) {
	graphics.fill(COLOURS::WHITE);
	graphics.fill(COLOURS::BLACK);
}

// SettingsStage

SettingsStage::SettingsStage() : BaseStage() {

}

void SettingsStage::update(float dt) {

}

void SettingsStage::render(Framework::Graphics& graphics) {

}

// GameStage

GameStage::GameStage() : BaseStage() {

}

void GameStage::update(float dt) {

}

void GameStage::render(Framework::Graphics& graphics) {

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

void PausedStage::render(Framework::Graphics& graphics) {
	// Render background stage
	_background_stage->render(graphics);
}